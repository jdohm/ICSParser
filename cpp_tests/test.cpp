#include <iostream>
#include <fstream>//files
using namespace std;

    string line;
    ifstream myfile;

void test1(){
        while(getline (myfile,line)){
            if(!line.compare(0,3,"END",0,3)) return;
            else if(!line.compare(0,21,"SUMMARY:USB Abfuhr Grau",0,21)) {
                cout << "Heute Restmüll";
                return;
            }
        }
    return;
}

int main() 
{   
    myfile.open ("bochum.ICS");
    if (myfile.is_open()){
        while(getline (myfile,line)){
            if(!line.compare(0,7,"DTSTART",0,7)){
                if(!line.compare(19,8,"20200306",0,8))
                test1();
            }
        }
        myfile.close();
    }
    return 0;
}