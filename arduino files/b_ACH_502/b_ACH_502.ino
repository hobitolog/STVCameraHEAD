#include "Header.h"



/* SETUP PART */
void setup() {
  // Initializing LCD 2x16
  lcd.begin(16,2);  
  lcd.backlight(); 
  lcd.setCursor(0,0); 
  lcd.print("KN Spacja TV");
  lcd.setCursor(0,1); 
  lcd.print("Projekt Statyw");
  lcd.backlight(); 
  delay(2000);
  lcd.clear();
  
  // Initializing pins for step-motors
  pinMode(CW_PLUS_1,OUTPUT);
  pinMode(CLK_PLUS_1,OUTPUT);
  
  pinMode(CW_PLUS_2,OUTPUT);
  pinMode(CLK_PLUS_2,OUTPUT);
  
  digitalWrite(CW_PLUS_1,LOW);
  digitalWrite(CLK_PLUS_1,LOW);
  
  digitalWrite(CW_PLUS_2,LOW);
  digitalWrite(CLK_PLUS_2,LOW);

  // Checking SD card
  if (!SD.begin(4)) {
    lcd.setCursor(0,0);
    lcd.print("SD card failed");
    delay(5000);
    lcd.clear();
    return;
  }

  Ethernet.begin(mac, ip);
  server.begin();
  /*
  // Checking file opening
  myFile = SD.open(fileName);
  if (myFile) {
    //Serial.println("file properly opened");
    lcd.setCursor(0,0);
    lcd.print("File opened");
    delay(1000);
    lcd.clear();
    myFile.close();
  } 
  else {
    //Serial.println("error opening file");
    lcd.setCursor(0,0);
    lcd.print("File open failed");
    delay(5000);
    lcd.clear();
    return;
  }
*/
  // Attaching interrupt to BUTTON_PIN
  //attachInterrupt(0, pin_ISR, RISING);
  
  
  
}

void loop(){
 if(!currentMode()){
    lcd.setCursor(0,0);
    lcd.print("Ethernet mode");
    lcd.setCursor(0,1);
    lcd.print(Ethernet.localIP());
    
    EthernetClient client = server.available();
    if (client) {
    //Serial.println("test1");
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
            
            if(CHOICE == 'L')// L - left
            {
              while(Distance<desiredDistance){
                digitalWrite(CW_PLUS_1,LOW);
                digitalWrite(CLK_PLUS_1,HIGH);
                delayMicroseconds(delayOn);
                digitalWrite(CLK_PLUS_1,LOW);
                delayMicroseconds(delayOff);
                Distance = Distance + 1;
              }
              Distance = 0;
            }
            else if(CHOICE == 'R')// R - right
            {              
              while(Distance<desiredDistance){
                digitalWrite(CW_PLUS_1,HIGH);
                digitalWrite(CLK_PLUS_1,HIGH);
                delayMicroseconds(delayOn);
                digitalWrite(CLK_PLUS_1,LOW);
                delayMicroseconds(delayOff);
                Distance = Distance + 1;
              }
              Distance = 0;
            }            
            else if(CHOICE == 'C')// C - clockwise
            {
              while(Distance<desiredDistance){
                digitalWrite(CW_PLUS_2,HIGH);
                digitalWrite(CLK_PLUS_2,HIGH);
                delayMicroseconds(delayOn);
                digitalWrite(CLK_PLUS_2,LOW);
                delayMicroseconds(delayOff);
                Distance = Distance + 1;
              }
              Distance = 0;
            }            
            else if(CHOICE == 'A')// A - counter-clockwise
            {              
              while(Distance<desiredDistance){
                digitalWrite(CW_PLUS_2,LOW);
                digitalWrite(CLK_PLUS_2,HIGH);
                delayMicroseconds(delayOn);
                digitalWrite(CLK_PLUS_2,LOW);
                delayMicroseconds(delayOff);
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
    lcd.print("             ");
    if(xAxis>700 && yAxis>700){
      while(Distance<desiredDistance){
        digitalWrite(CW_PLUS_1,LOW);
        digitalWrite(CW_PLUS_2,HIGH);
        digitalWrite(CLK_PLUS_1,HIGH);
        digitalWrite(CLK_PLUS_2,HIGH);
        delayMicroseconds(delayOn);
        digitalWrite(CLK_PLUS_1,LOW);
        digitalWrite(CLK_PLUS_2,LOW);
        delayMicroseconds(delayOff);
        Distance = Distance + 1;
      }
      Distance = 0;
    }
    else if(xAxis<10 && yAxis<10){
      while(Distance<desiredDistance){
        digitalWrite(CW_PLUS_1,HIGH);
        digitalWrite(CW_PLUS_2,LOW);
        digitalWrite(CLK_PLUS_1,HIGH);
        digitalWrite(CLK_PLUS_2,HIGH);
        delayMicroseconds(delayOn);
        digitalWrite(CLK_PLUS_1,LOW);
        digitalWrite(CLK_PLUS_2,LOW);
        delayMicroseconds(delayOff);
        Distance = Distance + 1;
      }
      Distance = 0;
    }
    else if(xAxis<10 && yAxis>700){
      while(Distance<desiredDistance){
        digitalWrite(CW_PLUS_1,HIGH);
        digitalWrite(CW_PLUS_2,HIGH);
        digitalWrite(CLK_PLUS_1,HIGH);
        digitalWrite(CLK_PLUS_2,HIGH);
        delayMicroseconds(delayOn);
        digitalWrite(CLK_PLUS_1,LOW);
        digitalWrite(CLK_PLUS_2,LOW);
        delayMicroseconds(delayOff);
        Distance = Distance + 1;
      }
      Distance = 0;
    }
    else if(xAxis>700 && yAxis<10){
      while(Distance<desiredDistance){
        digitalWrite(CW_PLUS_1,LOW);
        digitalWrite(CW_PLUS_2,LOW);
        digitalWrite(CLK_PLUS_1,HIGH);
        digitalWrite(CLK_PLUS_2,HIGH);
        delayMicroseconds(delayOn);
        digitalWrite(CLK_PLUS_1,LOW);
        digitalWrite(CLK_PLUS_2,LOW);
        delayMicroseconds(delayOff);
        Distance = Distance + 1;
      }
      Distance = 0;
    }
  }
}

