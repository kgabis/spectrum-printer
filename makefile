CC=gcc
CFLAGS=
LFLAGS=-lportaudio
OBJS=spectrum_printer.o

all: spectrum-printer clean

spectrum-printer: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -f *.o