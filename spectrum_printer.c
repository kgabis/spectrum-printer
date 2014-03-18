/*
 Spectrum-Printer ( http://github.com/kgabis/spectrum-printer )
 Copyright (c) 2014 Krzysztof Gabis
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <portaudio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "letters.h"

#define SAMPLE_RATE 44100
#define TABLE_SIZE SAMPLE_RATE
#define FRAMES_PER_BUFFER 256

typedef struct {
    float sine[TABLE_SIZE];
    int phase;
    int muted;
} StreamData;

typedef struct {
    PaStream  **streams;
    StreamData *streamDatas;
    int         num_lines;
    int         msec_per_col;
} Context;

static int pa_callback(const void *inputBuffer,
                       void *outputBuffer, unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo* timeInfo,
                       PaStreamCallbackFlags statusFlags, void *userData);

void streamdata_init(StreamData *sd, float frequency)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        float t = (float)i/(float)SAMPLE_RATE;
        sd->sine[i] = sin(2 * M_PI * frequency * t);
    }
    sd->phase = 0;
    sd->muted = 1;
}

void context_init(Context *c, int num_lines, float freq_start, float freq_end, int msec_per_col)
{
    PaStreamParameters outputParameters;
    float d_freq = fabs(freq_end - freq_start);
    float freq_step = num_lines > 1 ? d_freq/(float)(num_lines-1) : 0.0f;
    c->num_lines = num_lines;
    c->msec_per_col = msec_per_col;
    c->streams = (PaStream**)malloc(sizeof(PaStream*) * num_lines);
    c->streamDatas = (StreamData*)malloc(sizeof(StreamData) * num_lines);
    PaError err;
    
    for (int line = 0; line < num_lines; line++) {
        float frequency = freq_start + (float)line * freq_step;
        streamdata_init(&c->streamDatas[line], frequency);
        outputParameters.device = Pa_GetDefaultOutputDevice();
        outputParameters.channelCount = 2;
        outputParameters.sampleFormat = paFloat32;
        outputParameters.suggestedLatency =
		Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        
        err = Pa_OpenStream( &c->streams[line], NULL /* no input */,
                            &outputParameters,
                            SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag,
                            pa_callback, &c->streamDatas[line]);
        
        if (err != paNoError) {
            printf("PortAudio error: open stream: %s\n", Pa_GetErrorText(err));
            exit(1);
        }
    }
}

void context_dealloc(Context *c)
{
    free(c->streams);
    free(c->streamDatas);
}

void set_muted(Context *c, int line, int val)
{
    c->streamDatas[line].muted = val;
}

void start_playback(Context *c)
{
    for (int line = 0; line < c->num_lines; line++) {
        PaError err = Pa_StartStream(c->streams[line]);
        if (err != paNoError) {
            printf("Error playing line %d because: %s\n", line, Pa_GetErrorText(err));
            exit(1);
        }
    }
    sleep(1); // wait for streams to initialize
}

void stop_playback(Context *c)
{
    for (int line = 0; line < c->num_lines; line++) {
        set_muted(c, line, 1);
    }
    for (int line = 0; line < c->num_lines; line++) {
        Pa_CloseStream(c->streams[line]);
    }
}

static int pa_callback( const void *inputBuffer,
                      void *outputBuffer, unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags, void *userData )
{
    StreamData *data = (StreamData*) userData;
    float *out = (float*) outputBuffer;
    
    for (int i = 0; i < framesPerBuffer; i++) {
        float sample = data->sine[data->phase++];
        if (data->muted) {
            sample = 0.0f;
        }
        *out++ = sample; /* left */
        *out++ = sample; /* right */
        if (data->phase >= TABLE_SIZE)
            data->phase -= TABLE_SIZE;
    }
    return paContinue;
}

char *prepare_message(const char *string, int *cols)
{
    int bufsize = 1024;
    char *output = (char*)malloc(bufsize);
    int size = 1;
    output[0] = '\0';
    *cols = 0;
    while (*string) {
        char c = tolower(*string);
        Letter l = gLetters[c];
        if (l.array == NULL) {
            string++;
            continue;
        }
        int len = (int)strlen(l.array);
        size += len;
        *cols += len / ROWS_PER_LETTER;
        if (size > bufsize) {
            bufsize *= 2;
            output = (char*)realloc(output, bufsize);
        }
        strcat(output, l.array);
        string++;
    }
    return output;
}

void print_column(Context *c, const char *column, int num_rows)
{
    int lines_per_pixel = c->num_lines / num_rows;
    for (int row = 0; row < num_rows; row++) {
        int line_offset = row * lines_per_pixel;
        char letter = column[row];
        for (int line = line_offset; line < line_offset+lines_per_pixel; line++) {
            set_muted(c, line, letter == '#' ? 0 : 1);
        }
    }
    usleep(c->msec_per_col * 1000);
}

void print_string(Context *c, const char *string)
{
    int num_cols = 0;
    const char *message = prepare_message(string, &num_cols);
    for (int col = 0; col < num_cols; col++) {
        const char *col_start = message + col*ROWS_PER_LETTER;
        print_column(c, col_start, ROWS_PER_LETTER);
    }
    free((void*)message);
}

int main(int argc, const char **argv)
{
    init_letters();
    Context context;
    const char *string = "hello world! :)";
    int num_lines = 20;
    int freq_min = 1000;
    int freq_max = 1500;
    int col_time_ms = 400;
    for (int i = 1; i < argc; i++) {
        int val = 0;
        if (sscanf(argv[i], "lines=%d", &val))
            num_lines = val;
        else if (sscanf(argv[i], "min=%d", &val))
            freq_min = val;
        else if (sscanf(argv[i], "max=%d", &val))
            freq_max = val;
        else if (sscanf(argv[i], "time=%d", &val))
            col_time_ms = val;
        else
            string = argv[i];
    }
    Pa_Initialize();
    context_init(&context, num_lines, freq_min, freq_max, col_time_ms);
    start_playback(&context);
    print_string(&context, string);
    stop_playback(&context);
    Pa_Terminate();
    context_dealloc(&context);
    return 0;
}
