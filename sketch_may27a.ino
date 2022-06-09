#include <SoftwareSerial.h>
#define trig 4
#define echo 5

SoftwareSerial bluetooth (2,3); //SoftwareSerial 선언, (TX, RX) 설정

int motor = 11; //motor 변수 11 저장

void setup() {  
  Serial.begin(9600);
  bluetooth.begin(9600);// SoftWareSerial 통신 설정
  pinMode(motor, OUTPUT);//DC 모터
  pinMode (trig, OUTPUT); 
  pinMode (echo, INPUT); //초음파센서
}

void loop(){
  char data; 
  if(bluetooth.available()>0){
    data = bluetooth.read();
    if(data == '0'){
      analogWrite(motor, 100);//약     
    }else if(data =='1'){
      analogWrite(motor, 180);//중
    }else if(data =='2'){
      analogWrite(motor, 255);//강      
    }else if(data == '3'){
      analogWrite(motor, 0); //정지
    }

   digitalWrite(trig, LOW);
   delayMicroseconds(2);
   digitalWrite(trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(trig, LOW);

   float len = pulseIn(echo, HIGH);
   float dist = ((float)(340*len) /10000) /2 ;

  if (dist > 50)
     analogWrite(motor, 0);     
  bluetooth.println(String(dist));

  delay(1000);  
  }
}
