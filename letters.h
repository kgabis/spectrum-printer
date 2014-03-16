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

#ifndef spectrum_printer_letters_h
#define spectrum_printer_letters_h

#define ROWS_PER_LETTER 5

typedef struct {
    const char *array;
} Letter;

static Letter gLetters[256];

static void init_letters()
{
    gLetters['a'].array =
    "#### "
    " #  #"
    " #  #"
    "#### "
    "     ";    
    
    gLetters['b'].array =
    "#####"
    "# # #"
    "# # #"
    " # # "
    "     ";    

    gLetters['c'].array =
    " ### "
    "#   #"
    "#   #"
    "#   #"
    "     ";    

    gLetters['d'].array =
    "#####"
    "#   #"
    "#   #"
    " ### "
    "     ";    

    gLetters['e'].array =
    "#####"
    "# # #"
    "#   #"
    "     ";    

    gLetters['f'].array =
    "#####"
    "  # #"
    "    #"
    "     ";    

    gLetters['g'].array =
    "#####"
    "#   #"
    "# # #"
    "### #"
    "     ";    

    gLetters['h'].array =
    "#####"
    "  #  "
    "  #  "
    "#####"
    "     ";    

    gLetters['i'].array =
    "#####"
    "     ";    

    gLetters['j'].array =
    "### #"
    "# # #"
    "#   #"
    "#####"
    "     ";    

    gLetters['k'].array =
    "#####"
    "  #  "
    " # # "
    "#   #"
    "     ";    

    gLetters['l'].array =
    "#####"
    "#    "
    "#    "
    "     ";    

    gLetters['m'].array =
    "#####"
    "   # "
    "  #  "
    "   # "
    "#####"
    "     ";    

    gLetters['n'].array =
    "#####"
    "   # "
    "  #  "
    " #   "
    "#####"
    "     ";    

    gLetters['o'].array =
    " ### "
    "#   #"
    "#   #"
    " ### "
    "     ";    

    gLetters['p'].array =
    "#####"
    " #  #"
    " #  #"
    "  ## "
    "     ";    

    gLetters['q'].array =
    " ### "
    "#   #"
    "##  #"
    "#### "
    "     ";    

    gLetters['r'].array =
    "#####"
    "  # #"
    "  # #"
    "## # "
    "     ";    

    gLetters['s'].array =
    "# ###"
    "# # #"
    "# # #"
    "### #"
    "     ";    

    gLetters['t'].array =
    "    #"
    "#####"
    "    #"
    "     ";    

    gLetters['u'].array =
    "#####"
    "#    "
    "#    "
    "#####"
    "     ";    

    gLetters['v'].array =
    " ####"
    "#    "
    " ####"
    "     ";    

    gLetters['w'].array =
    "#####"
    " #   "
    "  #  "
    " #   "
    "#####"
    "     ";    

    gLetters['x'].array =
    "#   #"
    " # # "
    "  #  "
    " # # "
    "#   #"
    "    ";    

    gLetters['y'].array =
    "   ##"
    "  #  "
    "##   "
    "  #  "
    "   ##"
    "     ";    

    gLetters['z'].array =
    "#   #"
    "##  #"
    "# # #"
    "#  ##"
    "#   #"
    "     ";    

    gLetters[':'].array =
    " # # "
    "     ";    

    gLetters[')'].array =
    "#   #"
    " ### "
    "     ";    

    gLetters['('].array =
    " ### "
    "#   #"
    "     ";    

    gLetters['0'].array =
    "######"
    "#    #"
    "######"
    "     ";    

    gLetters['1'].array =
    "   # "
    "#####"
    "     ";    

    gLetters['2'].array =
    "### # "
    "# # #"
    "# ###"
    "     ";    

    gLetters['3'].array =
    "#   #"
    "# # #"
    "#####"
    "     ";    

    gLetters['4'].array =
    "  ###"
    "  #  "
    "#####"
    "     ";    

    gLetters['5'].array =
    "# ###"
    "# # #"
    "# # #"
    " #  #"
    "     ";    

    gLetters['6'].array =
    "#####"
    "# # #"
    "### #"
    "     ";    

    gLetters['7'].array =
    "    #"
    "    #"
    "#####"
    "     ";    

    gLetters['8'].array =
    "#####"
    "# # #"
    "#####"
    "     ";    

    gLetters['9'].array =
    "# ###"
    "# # #"
    "#####"
    "     ";    

    gLetters[' '].array =
    "     "
    "     ";    

    gLetters['.'].array =
    "#    "
    "     ";    

    gLetters[','].array =
    "#    "
    " ##  "
    "     ";    

    gLetters['/'].array =
    "##   "
    "  #  "
    "   ##"
    "     ";    
    gLetters['?'].array =
    "    #"
    "# # #"
    "   # "
    "     ";
    
    gLetters['!'].array =
    "# ###"
    "     ";
    
    gLetters['~'].array =
    "  #  "
    "   # "
    "  #  "
    " #   "
    "  #  "
    "     ";
    
    gLetters['@'].array =
    " ### "
    "#   #"
    "# ###"
    "# ###"
    "# # #"
    "#  # "
    " #   "
    "     ";
    
    gLetters['-'].array =
    "  #  "
    "  #  "
    "  #  "
    "     ";
    
    gLetters['\"'].array =
    "   ##"
    "     "
    "   ##"
    "     ";
    gLetters['\''].array =
    "   ##"
    "     ";
    
}

#endif
