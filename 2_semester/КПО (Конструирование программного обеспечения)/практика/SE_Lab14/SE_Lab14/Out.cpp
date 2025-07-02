#include "stdafx.h"
#include "Out.h"

using namespace std;


namespace Out {
    OUT getout(wchar_t outfile[]) {

        OUT out;
        out.streamOut = new std::ofstream;
        out.streamOut->open(outfile);
        if (!out.streamOut->is_open())
        {
            throw ERROR_THROW(110);
        }
        wcscpy_s(out.outfile, outfile);

        return out;
    }

    void WriteErrorOut(OUT out, Error::ERROR error) {

        *out.streamOut << "Ошибка " << error.id << ":" << error.message << endl;

        if (error.inext.line != -1)
        {
            *out.streamOut << "Строка " << error.inext.line << " Символ: " << error.inext.col << endl << endl;
        }
    }
    void WriteInOut(OUT out, In::IN in) {
        *out.streamOut << in.text << endl;
    }

    void Close(OUT out) {
        out.streamOut->close();
        delete out.streamOut;
    }
};