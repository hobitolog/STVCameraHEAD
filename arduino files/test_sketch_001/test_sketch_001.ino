

int CW_PLUS = 8;
int CLK_PLUS = 9;
int Distance = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(CW_PLUS,OUTPUT);
  pinMode(CLK_PLUS,OUTPUT);

  digitalWrite(CW_PLUS,LOW);
  digitalWrite(CLK_PLUS,LOW);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(CLK_PLUS,HIGH);
  delayMicroseconds(150);
  digitalWrite(CLK_PLUS,LOW);
  delayMicroseconds(50);

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
  }
  

  
  
}

