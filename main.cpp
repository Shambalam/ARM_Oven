#include "mbed.h"

#include <cstdio>
#include <exception>

#include <iostream>

#include <string>

 

using namespace std;

 

DigitalOut ovenLED(LED2);

DigitalIn userButton(USER_BUTTON);

 

bool parseTime(const string& input, int& minutes, int& seconds) {

    size_t pos = input.find(':');
    
    if (pos == string::npos) {

        printf("Invalid time format. Please use xx:xx (minutes:seconds) format.");

        return false;

    }
    string minStr = input.substr(0, pos); // PARSING INPUT STRING

    string secStr = input.substr(pos+1);



        minutes = stoi(minStr);
        

        seconds = stoi(secStr);

        if (minutes < 0 || minutes >= 60 || seconds < 0 || seconds >=60) { // VALID TIME CHECK

            printf("Invalid time entered.\n");

            return false;

        }
        else{

        printf("Valid time entered.\n");

        }
    

   

    return true;
}

 

void startOvenOperation(int totalSeconds) {

    ovenLED = 1;
    for(int i = 0; i < totalSeconds*1000; i++)
    {
        ThisThread::sleep_for(1);
        if(userButton == 0) // BUTTON DOUBLE PRESS OPERATION CANCEL
        {
            ThisThread::sleep_for(100);
            if(userButton == 0)
            {
            printf("Oven Operation Canceled\n");
            ovenLED = 0;
            return;
            }
        }
    }

   

    ovenLED = 0;

}

 

void buttonISR() {

    printf("Oven operation canceled.\n");
    ovenLED = 0;

}

 

int main() {

    string input;

    int minutes, seconds;

    

    while (true) {

        printf("Enter time (minutes:seconds): ");
        fflush(stdout);

        char inputBuffer[100];
       
        scanf("%s",inputBuffer); // USER INPUT
        input = inputBuffer;
        
        
 

        if (input.empty()) { // EMPTY CASE CHECK
            printf("INPUT IS EMPTY");
            printf("Invalid input. Please enter a valid time input.");

            continue;

        }

        if (parseTime(input, minutes, seconds)) { // CHECK FORMATING
            
            int totalSeconds = minutes * 60 + seconds;
            printf("Press button to start oven\n");
            while(true)
            {
                if(userButton == 0) // BUTTON PRESS TO START OVEN
                {
                        ThisThread::sleep_for(100);
                        
                        startOvenOperation(totalSeconds);
                        break;
                }
            }
                
        }



    }

}