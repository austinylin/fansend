#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 0;
    int pulseLength = 333;
    int syncLength = 35;
    int repeat = 7;
    
    if (argc != 2) return 1;
    string command = argv[1];
    
    if (wiringPiSetup () == -1) return 1;
    pinMode(PIN, OUTPUT);
    
    vector<int> code;
    for(int i=0; i<command.size(); i++) {
        code.push_back(command[i]-'0');
    }
    
    for(int r=0; r<repeat; r++) {
        for(int i=0; i<code.size(); i++) {
            printf("%i", code[i]);
            if(code[i] == 1) {
                digitalWrite(PIN, HIGH);
                delayMicroseconds(pulseLength);
                digitalWrite(PIN, LOW);
            } else {
                digitalWrite(PIN, LOW);
                delayMicroseconds(pulseLength);
            }
        }
        // Sync
        digitalWrite(PIN, HIGH);
        delayMicroseconds(pulseLength);
        digitalWrite(PIN, LOW);
        delayMicroseconds(pulseLength*syncLength);
        printf("\n");

    }
    digitalWrite(PIN, LOW);
    
    return 0;

}

