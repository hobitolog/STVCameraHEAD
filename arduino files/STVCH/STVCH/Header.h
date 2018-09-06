/*
STVCameraHEAD project
Distributed under MIT License

Copyright (c) 2018 Krzysztof Stężała and Adam Banaszczyk
*/
/* Used Libraries */
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <String.h>
#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

/* SAFETY PINS */
#define C_PIN A2
#define CC_PIN A3
#define L_PIN A4
#define R_PIN A5


// co dalej z tym?
/* BUTTON PART */
char BUTTON_PIN = 2;                /* Pin at which button is connected. */
boolean is_Joystick = true;
int currentState;
int previousState;
char reading;           // the current reading from the input pin

/* JOYSTICK PART */
int xAxis;                          /* getting reading from X axis of joystick */
int yAxis;                          /* getting reading from Y axis of joystick */
int xMotorSpeed;                    /* calculated speed for X axis */
int yMotorSpeed;                    /* calculated speed for Y axis */

/* STEP MOTOR PART */
// Lower step-motor
char CW_PLUS_1 = 7;                 /* Normal pin */
char CLK_PLUS_1 = 6;                /* PWM pin */

// Upper step-motor
char CW_PLUS_2 = 8;                 /* Normal pin */
char CLK_PLUS_2 = 9;                /* PWM pin */

MultiStepper StepperControl;        /* MultiStepper object helps to provide seemless 
                                       simultaneous movement for two or more motors */

AccelStepper stepper_up(1, 9, 8);   /* Initialization of the upper motor on pins 9 an 8 */
AccelStepper stepper_down(1, 6, 7); /* Initialization of the lower motor on pins 6 an 7 */
long initial_homing = 0;            /* Initializing the home position of steppers */

/* FILE PART */
// File declaration
File myFile;                        /* File to hold the webpage for web control */
char fileName[] = "index.htm";      /* Webpage filename */

/* NETWORK PART*/
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
/* Replace octets to match your network */
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// Size of buffer used to capture HTTP requests
#define REQ_BUF_SZ 90
char HTTP_req[REQ_BUF_SZ] = {0}; // Buffered HTTP request stored as null terminated string
char req_index = 0;              // Index into HTTP_req buffer

/* MOVEMENT PART */
int Distance = 0;
int desiredDistance = 1000;
int delayOn = 100;
int delayOff = 189;

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



