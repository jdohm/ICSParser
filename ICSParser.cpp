/*
  ICSParser.cpp - Library to parse ICS Calendar files.
  The aim of this library is, to enable you to easily search for words in the event description on given days.
  This will be used to evaluate if tomorrow the trash will be emtied. 
  So that an output can signal to put out the trash.
  Created by Jannis Dohm, 2020-02-12.
  Released under MIT License.
  210912 Kr modified algo to be compatible to , hopefully all, types of ics calendar from different regions.
*/

#include "Arduino.h"
#include "ICSParser.h"

ICSParser::ICSParser(char *DatabaseURL){
    SPIFFS.begin();
//    _file = SPIFFS.open(strcat("/",DatabaseURL), "r");
    _file = SPIFFS.open(DatabaseURL,"r");  // 210820 Kr
    if (!_file) {
    Serial.println("file open failed");
    }
    else {
      Serial.printf("open file %s OK",DatabaseURL); //210822 Kr
    }

}


bool ICSParser::CheckDate(char *SearchFor, int day, int month, int year){
    //search for BEGIN:VEVENT
    //get position index of BEGIN:VEVENT (can be more than one entryin the file)
        // check DTSTART and date is in same line and between BEGIN:VEVENT and END:VEVENT
          // set position index back to BEGIN
          // check if SearchFor can be found before "END:VEVENT"
          //    if yes -> return true
          //    if no -> start new instance of get index...
          //      recursive....
          //      return false if end of file was reached
    _SearchFor=SearchFor; // search pattern garbage container
    String _StartSearch1 = "BEGIN:VEVENT";
    String _StartSearch2 = "DTSTART";
    String _StartSearch3 = String(year) + _ToTwoString(month) + _ToTwoString(day);
    String _EndSearch = "END:VEVENT";
    _StartSearch1.toCharArray(_StartSearch1C,28);
    _StartSearch2.toCharArray(_StartSearch2C,28);
    _StartSearch3.toCharArray(_StartSearch3C,28);
    _EndSearch.toCharArray(_EndSearchC,28);
    return _CheckDateRekursiv(0);
}

bool ICSParser::_CheckDateRekursiv(int StartIndex){
    _file.seek(StartIndex,SeekSet); //set position to StartIndex bytes from the beginning
    if(_file.find(_StartSearch1C)){ //search for BEGIN:VEVENT
        _savedPosition = _file.position(); // save current position
        // search for DTSTART starting with BEGIN:VEVENT until END:VEVENT
        if(_file.findUntil(_StartSearch2C,_EndSearchC)) {
          // found DTSTART
          // search for date until end of line
          if(_file.findUntil(_StartSearch3C,"\n")) {
            // found date
            // set file position to BEGIN:VEVENT
            _file.seek(_savedPosition,SeekSet);
            // search for garbage pattern
            if(_file.findUntil(_SearchFor,"END:VEVENT")) return true; //if searced String is in event return true
          }
        }
        return _CheckDateRekursiv(_file.position()) ; //start rekursion, look for next event -> check for String ..
    }
    return false;
}

String ICSParser::_ToTwoString(int Num){
    if(Num<0) return "00";
    if(Num<10) return "0" + String(Num);
    return String(Num);
}
