

int CW_PLUS = 7;
int CLK_PLUS = 10;
int Distance = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(CW_PLUS,OUTPUT);
  pinMode(CLK_PLUS,OUTPUT);

  digitalWrite(CW_PLUS,LOW);
  digitalWrite(CLK_PLUS,LOW);
  
  Serial.begin(9600);



  while(Distance<3600){
    digitalWrite(CLK_PLUS,HIGH);
    delayMicroseconds(100);
    digitalWrite(CLK_PLUS,LOW);
    delayMicroseconds(100);
    Distance = Distance + 1;

    
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  digitalWrite(CLK_PLUS,HIGH);
  delayMicroseconds(100);
  digitalWrite(CLK_PLUS,LOW);
  delayMicroseconds(100);

  Distance = Distance + 1;

  //Serial.println(Distance);
  if(Distance == 3600){
    //Serial.println(Distance);
    if(digitalRead(CW_PLUS)==LOW){
      digitalWrite(CW_PLUS,HIGH);
    }
    else{
      digitalWrite(CW_PLUS,LOW);
    }
    Distance = 0;
  }*/
  

  
  
}

