#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

/* STEP MOTOR PART */
int CW_PLUS = 4;
int CLK_PLUS = 5;
int Distance = 0;

/* FILE PART */
//File declaration
File myFile;
char fileName[] = "index001.htm";

/* NETWORK PART*/
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 6);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ 90
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

/* SETUP PART */
//initializing serial interface
//initializing SD card reader
//initializing Ethernet shield
void setup() {
  pinMode(CW_PLUS,OUTPUT);
  pinMode(CLK_PLUS,OUTPUT);

  digitalWrite(CW_PLUS,LOW);
  digitalWrite(CLK_PLUS,LOW);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");  
  
  myFile = SD.open(fileName);
  if (myFile) {
    Serial.println("file properly opened");
    // read from the file until there's nothing else in it:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }

  
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP()); 
}

void loop(){
  // listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
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
            if(CHOICE == 'L')
            {
              
              while(Distance<3600){
                digitalWrite(CW_PLUS,LOW);
                digitalWrite(CLK_PLUS,HIGH);
                delayMicroseconds(100);
                digitalWrite(CLK_PLUS,LOW);
                delayMicroseconds(100);
                Distance = Distance + 1;
              }
              Distance = 0;
              Serial.println(CHOICE);
            }
            else{
              
              while(Distance<3600){
                digitalWrite(CW_PLUS,HIGH);
                digitalWrite(CLK_PLUS,HIGH);
                delayMicroseconds(100);
                digitalWrite(CLK_PLUS,LOW);
                delayMicroseconds(100);
                Distance = Distance + 1;
              }
              Distance = 0;
              
              Serial.println(CHOICE);
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
    Serial.println("client disconnected");
    
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



