
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

/* SETUP PART */
void setup() {

  attachInterrupt(0, pin_ISR, RISING);

  //initializing LCD 2x16
  lcd.begin(16,2);  
  lcd.backlight(); 
  lcd.setCursor(0,0); 
  lcd.print("KN Spacja TV");
  lcd.setCursor(0,1); 
  lcd.print("Projekt Statyw");
  lcd.backlight(); 
  delay(2000);
  lcd.clear();
  
  //initializing pins
  pinMode(CW_PLUS_1,OUTPUT);
  pinMode(CLK_PLUS_1,OUTPUT);
  
  pinMode(CW_PLUS_2,OUTPUT);
  pinMode(CLK_PLUS_2,OUTPUT);
  
  digitalWrite(CW_PLUS_1,LOW);
  digitalWrite(CLK_PLUS_1,LOW);
  
  digitalWrite(CW_PLUS_2,LOW);
  digitalWrite(CLK_PLUS_2,LOW);

  if (!SD.begin(4)) {
    return;
  }
  
  myFile = SD.open(fileName);
  if (myFile) {
    myFile.close();
  } else {
    return;
  }
  Ethernet.begin(mac, ip);
  
  server.begin();
}

void loop(){
  
  if(!is_Joystick){
    lcd.setCursor(0,0);
    lcd.print("Ethernet mode");
    lcd.setCursor(0,1);
    delay(200);
    lcd.clear();
    EthernetClient client = server.available();
    if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
         if (req_index < (REQ_BUF_SZ - 1)) {
           HTTP_req[req_index] = c;          // save HTTP request character
           req_index++;
         }
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          if (StrContains(HTTP_req, "ajax_inputs")) {
            client.println("Content-Type: text/html");
            client.println("Connection: keep-alive");
            client.println();
            char* str_begin = strstr(HTTP_req, "&L1=");
            if(str_begin != NULL){
              str_begin = strstr(str_begin, "=");
              str_begin += 1;              
            }
            char CHOICE = str_begin[0];
            int Distance = 0;
            if(CHOICE == 'L')// L - left
            {
              while(Distance<500){
                digitalWrite(CW_PLUS_1,LOW);
                digitalWrite(CLK_PLUS_1,HIGH);
                delayMicroseconds(100);
                digitalWrite(CLK_PLUS_1,LOW);
                delayMicroseconds(100);
                Distance = Distance + 1;
              }
              Distance = 0;
            }
            else if(CHOICE == 'R')// R - right
            {              
              while(Distance<500){
                digitalWrite(CW_PLUS_1,HIGH);
                digitalWrite(CLK_PLUS_1,HIGH);
                delayMicroseconds(100);
                digitalWrite(CLK_PLUS_1,LOW);
                delayMicroseconds(100);
                Distance = Distance + 1;
              }
              Distance = 0;
            }            
            else if(CHOICE == 'C')// C - clockwise
            {
              while(Distance<500){
                digitalWrite(CW_PLUS_1,HIGH);
                digitalWrite(CLK_PLUS_1,HIGH);
                delayMicroseconds(100);
                digitalWrite(CLK_PLUS_1,LOW);
                delayMicroseconds(100);
                Distance = Distance + 1;
              }
              Distance = 0;
            }            
            else if(CHOICE == 'A')// A - counter-clockwise
            {              
              while(Distance<500){
                digitalWrite(CW_PLUS_1,HIGH);
                digitalWrite(CLK_PLUS_1,HIGH);
                delayMicroseconds(100);
                digitalWrite(CLK_PLUS_1,LOW);
                delayMicroseconds(100);
                Distance = Distance + 1;
              }
              Distance = 0;
            }
          }
          else{
            client.println("Content-Type: text/html");
            client.println("Connection: close");  // the connection will be closed after completion of the response
            client.println();
            myFile = SD.open(fileName);
            while (myFile.available()) {
              client.print((char)myFile.read());
            }
            myFile.close();
          }      
          req_index = 0;
          StrClear(HTTP_req, REQ_BUF_SZ);
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    char myresponse;
    myresponse = client.read();
    client.stop();    
    
    }
  }
  else{
    xAxis = analogRead(A1);
    yAxis = analogRead(A0);
    lcd.setCursor(0,0);
    lcd.print("Joystick mode");
    lcd.setCursor(0,1);
    lcd.print("X:");
    lcd.print(xAxis);
    lcd.print(" Y:");
    lcd.print(yAxis);
    delay(200);
    lcd.clear();
    
  }
  
}

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



