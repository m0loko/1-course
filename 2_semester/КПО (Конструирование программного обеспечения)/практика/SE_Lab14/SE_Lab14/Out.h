#pragma once

#include "In.h"
#include "Parm.h"
#include "Error.h"
#include <fstream>


namespace Out
{
    struct OUT
    {
        wchar_t outfile[PARM_MAX_SIZE];
        std::ofstream* streamOut;
        unsigned char* textOut;
    };

    static const OUT INITOUT{ L"", NULL };
    OUT getout(wchar_t outfile[]);
    void WriteErrorOut(OUT out, Error::ERROR error);
    void WriteInOut(OUT out, In::IN in);
    void Close(OUT log);
};