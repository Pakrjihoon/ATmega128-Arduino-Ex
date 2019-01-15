#include <DHT11.h>
int B = 11; // OUTPUT PIN blue
int R = 10; // OUTPUT PIN red
int G = 12; // OUTPUT PIN green
int pin = 2;
DHT11 dht11(pin);
int trigPin = 9;
int echoPin = 8;
int trigPin2 = 7;
int echoPin2 = 6;
int trigPin3 = 5;
int echoPin3 = 4;
 
//시리얼 속도설정, trigPin을 출력, echoPin을 입력으로 설정
void setup(){
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}
 
//초음파를 보낸다. 다 보내면 echo가 HIGH(신호받기) 상태로 대기
void loop(){
  int err;
  float temp, humi;
  float duration, distance,duration2, distance2,duration3, distance3;
  float rice,avdu;
  int d = analogRead(A0);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 0);
  
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  duration3 = pulseIn(echoPin3, HIGH);
  avdu = ((float)(duration+duration2+duration3)/3);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  // 340은 초당 초음파(소리)의 속도, 10000은 밀리세컨드를 세컨드로, 왕복거리이므로 2로 나눠준다.
  distance = ((float)(340 * duration) / 10000) / 2;
  distance2 = ((float)(340 * duration2) / 10000) / 2;
  distance3 = ((float)(340 * duration3) / 10000) / 2;
  rice = (float)((distance+distance2+distance3)/3)-64;
 
  int iValue0 = analogRead(A3);
  Serial.println();
  Serial.print("물의 양 : ");
  Serial.print((1024 - iValue0)*0.1);
  Serial.println(" %");
  //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.
 
  Serial.println(rice);
  if(rice > 0.45){
    Serial.println("사료가 거의 없습니다.");
  }
  else if(rice >=-0.45&&rice <= 0.45 ){
    Serial.println("사료가 반정도 있습니다."); 
  }
  else if(rice <-0.5){
   Serial.println("사료가 충분합니다.");
  }
 
 
  delay(900);
 if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
  {
    if(temp>=30.0){
      Serial.println("사료의 온도가 높습니다!");
      Serial.print("현재 사료의 온도");
      Serial.println(temp);
    }
    else if(humi>=80.0){
      Serial.println("사료가 눅눅합니다. 건조 시켜주세요!");
      Serial.print("현재 사료통 습도 : ");
      Serial.println(humi);
    }
    else if(temp>=31.0 && humi>=81.0){
      Serial.println("사료의 상태가 좋지 않습니다. 냉장 보관 혹은 바꿔주세요");
    }
    else
    {
    Serial.print("사료통온도:");
    Serial.print(temp);
    Serial.print(" 사료통습도:");
    Serial.print(humi);
    Serial.println();
    }
  }
  else                                //에러일 경우 처리
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(1000);
  
  if(d >= 600){
  // RED
  for (int i = 0; i < 256; i++)
  {
    analogWrite(R, i);
    delay(10);  
  }
  for (int i = 0; i < 256; i++)
  {
    analogWrite(R, 255-i);
    delay(10);
  }
 
  // GREEN
  for (int i = 0; i < 256; i++)
  {
    analogWrite(G, i);
    delay(10);
  }
  for (int i = 0; i < 256; i++)
  {
    analogWrite(G, 255 - i);
    delay(10);
  }
 
  // BLUE
  for (int i = 0; i < 256; i++)
  {
    analogWrite(B, i);
    delay(10);
  } 
  for (int i = 0; i < 256; i++)
  {
    analogWrite(B, 255 - i);
    delay(10);
  }
 
  // WHITE
  for (int i = 0; i < 256; i++)
  {
    analogWrite(R, i);
    analogWrite(G, i);
    analogWrite(B, i);
    delay(10);
  }
 
  for (int i = 0; i < 256; i++)
  {
    analogWrite(R, 255 - i);
    analogWrite(G, 255 - i);
    analogWrite(B, 255 - i);
    delay(10);
  }
   
  }
  else  
  {
    analogWrite(R,0);
    analogWrite(G,0);
    analogWrite(B,0);
  }
  Serial.println(d);
  
}
