/*
  ICSParser.cpp - Library to parse ICS Calendar files.
  The aim of this library is, to enable you to easily search for words in the event description on given days.
  This will be used to evaluate if tomorrow the trash will be emtied. 
  So that an output can signal to put out the trash.
  Created by Jannis Dohm, 2020-02-12.
  Released under MIT License.
*/

#include "Arduino.h"
#include "ICSParser.h"

ICSParser::ICSParser(String DatabaseURL){
    SPIFFS.begin();
    _DatabaseURL =  DatabaseURL;
    _file = SPIFFS.open("/" + _DatabaseURL, "r");
    if (!_file) {
    Serial.println("file open failed");
    }
}


bool ICSParser::CheckDate(String SearchFor, int day, int month, int year){
    //get index of "DTSTART;VALUE=DATE:year+month+day" (can be more than one)
        //check if SearchFor can be found before "END:VEVENT" 
        //    if yes -> return true
        //    if no -> start new instance of get index...
        //      recursive.... 
        //      return false if end of file was reached
    return _CheckDateRekursiv(0);
}

bool ICSParser::_CheckDateRekursiv(int StartIndex){
    _file.seek(StartIndex,SeekSet); //set position to StartIndex bytes from the beginning
    if(_file.find("DTSTART;VALUE=DATE:" + year + month + day, _file.size())){ //search for event on the given day
        if(_file.findUntil(SearchFor,"END:VEVENT")) return true; //if searced String is in event return true
        else return _CheckDateRekursiv(_file.position()) ; //start rekursion, look for next event -> check for String ...
    }
    return false;
}

