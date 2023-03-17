#define EN1 10 
#define EN2 11 
#define IN1 4 
#define IN2 5 
#define IN3 6 
#define IN4 7 
int U=100; 
int startSpeed = 50;
void AllStop(void); 
void setup() 
{ 
 Serial.begin(9600); 
 pinMode(EN1,OUTPUT);pinMode(EN2,OUTPUT); 
 pinMode(IN1,OUTPUT);pinMode(IN2,OUTPUT); 
 pinMode(IN3,OUTPUT);pinMode(IN4,OUTPUT); 
 AllStop(); 
 Serial.println("Enter percent PWM (0-100%)"); 
} 
void loop() 
{ 
 if(Serial.available()) 
  { 
  int number = Serial.parseInt(); 
  String str = Serial.readStringUntil('\n'); 
  U=map(number,0,100,0,255); 
  // PWM_1 = map(startSpeed + number, 0, 100, 0, 255);
  // PWM_2 = map(startSpeed - number, 0, 100, 0, 255);
  Serial.println(U); 
  // Serial.println(PWM_1);
  // Serial.println(Pw)

 
  } 
 for(int i=0;i<100;i++) 
 { 
  analogWrite(EN1,startSpeed+U);
  analogWrite(EN2,startSpeed-U); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);delay(30); 
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);delay(20); 
 } 
 AllStop(); 
 for(int i=0;i<100;i++) 
 { 
  analogWrite(EN1,startSpeed+U);analogWrite(EN2,startSpeed-U); 
  digitalWrite(IN1,HIGH);digitalWrite(IN2,LOW);delay(30); 
  digitalWrite(IN3,HIGH);digitalWrite(IN4,LOW);delay(20); 
 } 
 AllStop(); 
} 
 void AllStop(void) 
{ 
 digitalWrite(IN1,LOW);digitalWrite(IN2,LOW); 
 digitalWrite(IN3,LOW);digitalWrite(IN4,LOW); 
 delay(250); 
}