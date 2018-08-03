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
            
            if(CHOICE == 'A')// A - left
            {
              //left
            }
            else if(CHOICE == 'B')// B - right
            {              
              //right
            }            
            else if(CHOICE == 'C')// C - clockwise
            {
              //clockwise
            }            
            else if(CHOICE == 'D')// D - counter-clockwise
            {              
              //counterclockwise
            }
            else if(CHOICE == 'E')// E - change speed up
            {              
              //change speed up
            }
            else if(CHOICE == 'F')// F - change speed down
            {              
              //change speed down
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
      JoyMove();
    }
  }
  
    
void JoyMove(){
  xAxis = analogRead(A1);
  yAxis = analogRead(A0);

  if (xAxis<20)
    xMotorSpeed = -350;

  else if (xAxis>20 && xAxis<225)
    xMotorSpeed = -200;
  
  else if (xAxis>225 && xAxis<400)
    xMotorSpeed = -50;
   
  else if (xAxis>600 && xAxis<775)
    xMotorSpeed = 50;
 
   else if (xAxis>775 && xAxis<980)
    xMotorSpeed = 200;
 
   else if(xAxis>980)
    xMotorSpeed = 350;
    

 
  if (yAxis<20)
    yMotorSpeed = -700;
   
 else if(yAxis>20 && yAxis<275)
    yMotorSpeed = -300;
    
  else if(yAxis>275 && yAxis<400)
    yMotorSpeed = -100;
  
  else if (yAxis>600 && yAxis<775)
    yMotorSpeed = 100;
    
 else if(yAxis>775 && yAxis<980)
    yMotorSpeed = 300;
    
  else if(yAxis>980)
    yMotorSpeed = 700;
    
    

  
      
  if(xAxis<600 && xAxis>400 && yAxis<600 && yAxis>400){
  //gwaltowne hamowanie
  stepper_up.setSpeed(0);
  stepper_down.setSpeed(0);
      
      
      }
      else if(xAxis>600 && yAxis<600 && yAxis>400){
      //right
      
      if(analogRead(R_PIN)<500){
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
        }
        else{
          stepper_up.setSpeed(0);
      stepper_down.setSpeed(xMotorSpeed);
        }
      }
      else if(xAxis<400 && yAxis<600 && yAxis>400){
      //left
      
      if(analogRead(L_PIN)<500){
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
      }
      else{
           stepper_up.setSpeed(0);
           stepper_down.setSpeed(xMotorSpeed);
      }
      }
      else if(yAxis>600 && xAxis<600 && xAxis>400){
      //up
        
     if(analogRead(C_PIN)<500){
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
     }
     else{
          stepper_up.setSpeed(yMotorSpeed);
          stepper_down.stop();
          stepper_down.setSpeed(0);
        }
      }
      else if(yAxis<400 && xAxis<600 && xAxis>400){
      //down
      if(analogRead(CC_PIN)<500){
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
      }    
      else{
        stepper_up.setSpeed(yMotorSpeed);
        stepper_down.stop();
        stepper_down.setSpeed(0);
      }
      }
      else if(xAxis>600 && yAxis>600){
      //up&right
      if(analogRead(C_PIN)<500 && analogRead(R_PIN)<500){
          stepper_up.stop();
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
     }
     else{
          stepper_up.setSpeed(yMotorSpeed);
          stepper_down.setSpeed(xMotorSpeed);
        }
      
      }
      else if(xAxis<400 && yAxis<400){
      //down&left
     if(analogRead(CC_PIN)<500 && analogRead(L_PIN)<500){
          stepper_up.stop();
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
     }
     else{
          stepper_up.setSpeed(yMotorSpeed);
          stepper_down.setSpeed(xMotorSpeed);
        }
      }
      else if(xAxis<400 && yAxis>600){
      //up&left
      if(analogRead(C_PIN)<500 && analogRead(L_PIN)<500){
          stepper_up.stop();
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
     }
     else{
          stepper_up.setSpeed(yMotorSpeed);
          stepper_down.setSpeed(xMotorSpeed);
        }
      }
      else if(xAxis>600 && yAxis<400){
      //down&right
      if(analogRead(CC_PIN)<500 && analogRead(R_PIN)<500){
          stepper_up.stop();
          stepper_up.setSpeed(0);
          stepper_down.stop();
          stepper_down.setSpeed(0);
     }
     else{
          stepper_up.setSpeed(yMotorSpeed);
          stepper_down.setSpeed(xMotorSpeed);
        }
      }
      stepper_up.runSpeed();
    stepper_down.runSpeed();
    }
