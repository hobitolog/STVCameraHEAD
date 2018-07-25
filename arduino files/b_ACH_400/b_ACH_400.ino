#include "Headers.h"

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



