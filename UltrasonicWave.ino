#include <LiquidCrystal_I2C.h>

int trigpin = 11; //아두이노가 전류를 넣어 초음파를 발사하게 하는 핀
int echopin = 12; //수신부로 입력된 초음파를 받는 편
int redpin = 8;
int greenpin = 9;
int yellowpin = 10;
LiquidCrystal_I2C LCD(0x27,16,2); //LCD 제어 객체 생성
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  LCD.init(); //LCD 초기화
  LCD.backlight();
}

void loop() {
  unsigned long distance; //초음파가 발사되어 돌아온 시간

  //초음파 발생시킴 : 10us 동안 전류를 trigpin에 출력
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);       //초기화
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);      
  digitalWrite(trigpin, LOW);
  
    //돌아온 초음파를 분석하여 거리 계산
  distance = pulseIn(echopin, HIGH)/2*0.034;
        //왕복시간이므로 반으로 나눈다 : 반환값은 unsigned long
        //cm와 microsecond의 단위를 통일시켜야 함
        //1m = 100cm : 340m --> 34000cm
        //1s = 1,000,000us
        //34000/1000000 --> 0.034cm/us

  //화면 출력
  Serial.print("distance : " + String(distance) + "cm\n");
  delay(100);

  if(distance < 10) {
  digitalWrite(redpin, HIGH);
  digitalWrite(greenpin, HIGH);
  digitalWrite(yellowpin, HIGH);
  }else if(distance < 20) {
  digitalWrite(redpin, HIGH);
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, HIGH);
  }else if(distance < 30) {
  digitalWrite(redpin, HIGH);
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, LOW);   
  }else {
  digitalWrite(redpin, LOW);
  digitalWrite(greenpin, LOW);
  digitalWrite(yellowpin, LOW);
  }
  Serial.print("distance="); Serial.print(distance); //시리얼 모니터로 출력
  LCD.clear(); //LCD화면 모두 지우기
  LCD.setCursor(0,0);
  LCD.print("distance : "); LCD.print(distance);
  delay(500); 
}
