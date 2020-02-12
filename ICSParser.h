/*
  ICSParser.h - Library to parse ICS Calendar files.
  The aim of this library is, to enable you to easily search for words in the event description on given days.
  This will be used to evaluate if tomorrow the trash will be emtied. 
  So that an output can signal to put out the trash.
  Created by Jannis Dohm, 2020-02-12.
  Released under MIT License.
*/
#ifndef ICSParser
#define ICSParser

#include "stdin.h"
#include "Arduino.h"

class ICSParser
{
    public:
        ICSParser(string DatabaseURL);
        uint_8 CheckDate(string SearchFor, int day, int month, int year);

    private:
        string _DatabaseURL;
        int _CheckDateRekursiv(int StartIndex);
        File _file;
};



#endif //ICSParser