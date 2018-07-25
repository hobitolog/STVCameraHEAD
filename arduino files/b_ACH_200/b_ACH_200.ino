#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

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

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
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
  // listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // buffer first part of HTTP request in HTTP_req array (string)
          // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
         if (req_index < (REQ_BUF_SZ - 1)) {
           HTTP_req[req_index] = c;          // save HTTP request character
           req_index++;
         }
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // limit the size of the stored received HTTP request
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");

          // remainder of header follows below, depending on if
          // web page or XML page is requested
          // Ajax request - send XML file
          if (StrContains(HTTP_req, "ajax_inputs")) {
             // send rest of HTTP header
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
            // L - left
            if(CHOICE == 'L')
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
            // R - right
            else if(CHOICE == 'R'){
              
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
            // C - clockwise
            else if(CHOICE == 'C'){
              
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
            // A - counter-clockwise
            else if(CHOICE == 'A'){
              
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
            //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
            client.println();
            myFile = SD.open(fileName);
            while (myFile.available()) {
              client.print((char)myFile.read());
            }
            myFile.close();
          }
          
          // reset buffer index and all buffer elements to 0
          req_index = 0;
          StrClear(HTTP_req, REQ_BUF_SZ);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    char myresponse;
    myresponse = client.read();
    client.stop();    
  }
  else{
    xAxis = analogRead(A1);
    yAxis = analogRead(A0);
    Serial.print("X:");
    Serial.print(xAxis);
    Serial.print(" Y:");
    Serial.println(yAxis);
    
  }
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



