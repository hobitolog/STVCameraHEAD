#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

/* BUTTON PART */
char BUTTON_PIN = 2;
boolean is_Joystick = true;
boolean previous = false;
char reading;           // the current reading from the input pin

/* LCD PART */
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27

/* JOYSTICK PART */
int xAxis;
int yAxis;

/* STEP MOTOR PART */
// Lower step-motor
char CW_PLUS_1 = 7; // Normal pin
char CLK_PLUS_1 = 6; // PWM pin

// Upper step-motor
char CW_PLUS_2 = 8; // Normal pin
char CLK_PLUS_2 = 9; // PWM pin

/* FILE PART */
// File declaration
File myFile;
char fileName[] = "index001.htm";

/* NETWORK PART*/
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// Size of buffer used to capture HTTP requests
#define REQ_BUF_SZ 90
char HTTP_req[REQ_BUF_SZ] = {0}; // Buffered HTTP request stored as null terminated string
char req_index = 0;              // Index into HTTP_req buffer

int Distance = 0;

void pin_ISR() {
  
  reading = digitalRead(BUTTON_PIN);
  is_Joystick = !is_Joystick;
  
}


// sets every element of str to 0 (clears array)
void StrClear(char *str, char length){
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}



