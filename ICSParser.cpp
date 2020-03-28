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

ICSParser::ICSParser(char *DatabaseURL){
    SPIFFS.begin();
    _file = SPIFFS.open(strcat("/",DatabaseURL), "r");
    if (!_file) {
    Serial.println("file open failed");
    }
}


bool ICSParser::CheckDate(char *SearchFor, int day, int month, int year){
    //get index of "DTSTART;VALUE=DATE:year+month+day" (can be more than one)
        //check if SearchFor can be found before "END:VEVENT" 
        //    if yes -> return true
        //    if no -> start new instance of get index...
        //      recursive.... 
        //      return false if end of file was reached
    _SearchFor=SearchFor;
    String _StartSearch= "DTSTART;VALUE=DATE:" + String(year) + _ToTwoString(month) + _ToTwoString(day);
    _StartSearch.toCharArray(_StartSearchC,28);
    return _CheckDateRekursiv(0);
}

bool ICSParser::_CheckDateRekursiv(int StartIndex){
    _file.seek(StartIndex,SeekSet); //set position to StartIndex bytes from the beginning
        Serial.println(_SearchFor);
        Serial.print("print Char:");
        Serial.println(_StartSearchC);
    if(_file.find(_StartSearchC)){ //search for event on the given day
        Serial.println("found Date!, looking for String");
        if(_file.findUntil(_SearchFor,"END:VEVENT")) return true; //if searced String is in event return true
        else return _CheckDateRekursiv(_file.position()) ; //start rekursion, look for next event -> check for String ...
    }
    return false;
}

String ICSParser::_ToTwoString(int Num){
    if(Num<0) return "00";
    if(Num<10) return "0" + String(Num);
    return String(Num);
}