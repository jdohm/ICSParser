# ICSParser
a Arduino ESP8266 Wemos D1 mini library to search for specific events in a ICS Calendar

## Usage
### upload ICS calendar
upload using newest [LittleFS_Tool](https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.5.0/ESP8266FS-0.5.0.zip).

### copy this library
copy this library into your Arduino library folder. For example on linux this means: /home/user/Arduino/libraries

### header
include header file:

``` #include <ICSParser.h> ```

### Setup
In the header erea of your code create ICSParser instance like this:

``` ICSParser  ICSParsery("YourFileName.ics"); ``` 

where YourFileName is the name of your file.

### check Date for event:
call CheckDate when ever you like.
It needs the following entries:

``` CheckDate(string SearchFor, int day, int month, int year); ``` 

For example if you'r interested if you need to bring the trash out on the 12.3.2020 you would call:

``` CheckDate("Grau", 13, 3, 2020); ``` 

This will return ```true``` if "Grau" was found on the given day and ```false``` if not.

