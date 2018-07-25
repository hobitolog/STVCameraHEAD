#include "Header.h"

/* SETUP PART */
void setup() {

  // Checking SD card
  if (!SD.begin(4)) {
    return;
  }

  stepper_up.setMaxSpeed(3000);
  stepper_up.setSpeed(600);
  stepper_up.currentPosition();
  stepper_up.setAcceleration(1000000);
  stepper_down.setMaxSpeed(3000);
  stepper_down.setSpeed(600);
  stepper_down.currentPosition();
  stepper_down.setAcceleration(1000000);

  StepperControl.addStepper(stepper_up);
  StepperControl.addStepper(stepper_down);

  // Initializing Ethernet server
  Ethernet.begin(mac, ip);
  server.begin();  
}

void loop(){
    EthernetClient client = server.available();
    if (false/*client*/) {
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
    else{
      
      xAxis = analogRead(A1);
      yAxis = analogRead(A0);
      
      if(xAxis<700 && xAxis>100 && yAxis<700 && yAxis>100){
      //gwaltowne hamowanie
      stepper_up.setSpeed(0);
      stepper_down.setSpeed(0);
      
      
      }
      else if(xAxis>700 && yAxis<700 && yAxis>100){
      //right
      stepper_up.setSpeed(0);
      stepper_down.setSpeed(200);
      }
      else if(xAxis<100 && yAxis<700 && yAxis>100){
      //left
      stepper_up.setSpeed(0);
      stepper_down.setSpeed(-200);
      }
      else if(yAxis>700 && xAxis<700 && xAxis>100){
      //up
        stepper_up.setSpeed(600);
        stepper_down.stop();
        stepper_down.setSpeed(0);
      }
      else if(yAxis<100 && xAxis<700 && xAxis>100){
      //down
       stepper_up.setSpeed(-600);
       stepper_down.stop();
       stepper_down.setSpeed(0);
      }
      else if(xAxis>700 && yAxis>700){
      //up&right
      stepper_up.setSpeed(600);
      stepper_down.setSpeed(200);
      }
      else if(xAxis<100 && yAxis<100){
      //down&left
      stepper_up.setSpeed(-600);
      stepper_down.setSpeed(-200);
      }
      else if(xAxis<100 && yAxis>700){
      //up&left
      stepper_up.setSpeed(600);
      stepper_down.setSpeed(-200);
      }
      else if(xAxis>700 && yAxis<100){
      //down&right
      stepper_up.setSpeed(-600);
      stepper_down.setSpeed(200);
      }
      
    }
    stepper_up.runSpeed();
    stepper_down.runSpeed();
  }
  
    


