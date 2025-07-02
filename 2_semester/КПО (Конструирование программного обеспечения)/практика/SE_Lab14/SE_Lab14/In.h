#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'

namespace In
{
  struct IN
  {
    enum { T = 1024, F = 2048, I = 4096 };
    int size;                     
    int lines;               
    int ignor;                  
    unsigned char* text;          
    int code[256] = {
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, 
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,

        F, '-', F, T, F, T, F, F, T, T, F, T, T, T, F, F,
        F, F, T, F, F, F, T, F, I, F, F, F, F, F, F, F,  
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,  
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, 

        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,

        T, F, T, F, F, T, F, F, T, F, T, T, T, F, F, F,
        T, F, F, F, F, F, F, T, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    };

  };
  IN getin(wchar_t infile[]);   
};

