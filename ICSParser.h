/*
  ICSParser.h - Library to parse ICS Calendar files.
  The aim of this library is, to enable you to easily search for words in the event description on given days.
  This will be used to evaluate if tomorrow the trash will be emtied. 
  So that an output can signal to put out the trash.
  Created by Jannis Dohm, 2020-02-12.
  Released under MIT License.
*/
#ifndef ICSParser_
#define ICSParser_

#include "Arduino.h"
#include "FS.h" //filesystem for ESP8266: http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/filesystem.html under LGPL V2.1

class ICSParser
{
  public:
    ICSParser(char *DatabaseURL);
    bool CheckDate(char *SearchFor, int day, int month, int year);

  private:
    bool _CheckDateRekursiv(int StartIndex);
    String _ToTwoString(int Number);
    File _file;
    char *_SearchFor;
    char _StartSearchC[28];
};


#endif //ICSParser