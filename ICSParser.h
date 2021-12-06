/*
  ICSParser.h - Library to parse ICS Calendar files.
  The aim of this library is, to enable you to easily search for words in the event description on given days.
  This will be used to evaluate if tomorrow the trash will be emtied. 
  So that an output can signal to put out the trash.
  Created by Jannis Dohm, 2020-02-12.
  Released under MIT License.
  211206 Kr move from FS, deprecated, to LittleFS
*/
#ifndef ICSParser_
#define ICSParser_

#include "Arduino.h"
//#include "FS.h" //filesystem for ESP8266: http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/filesystem.html under LGPL V2.1
#include "LittleFS.h"

class ICSParser
{
  public:
    ICSParser(char *DatabaseURL);
    // the file name has to be given as "/filename" with leading "/" due to compatibility to FS filesystem
    bool CheckDate(char *SearchFor, int day, int month, int year);

  private:
    bool _CheckDateRekursiv(int StartIndex);
    String _ToTwoString(int Number);
    File _file;
    char *_SearchFor;
    char _StartSearchC[28];
    char _StartSearch1C[28];
    char _StartSearch2C[28];
    char _StartSearch3C[28];
    char _EndSearchC[28];
    int _savedPosition;
};


#endif //ICSParser
