#define THRESHOLD 800

// Input Sensor
int Out1 = A0;
int Out2 = A1;
int Out3 = A2;
int Out4 = A3;
int Out5 = A4;
int Out6 = A5;

// Sensor variable
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int Sensor4 = 0;
int Sensor5 = 0;
int Sensor6 = 0;

//PID
int error = 0;
int pre_error = 0;
int sum_error = 0;
int Kp = 7;
int Kd = 4;
int Ki = 0;

//Right
#define EN1 10
#define IN1 4
#define IN2 5
// Left
#define EN2 11
#define IN3 6
#define IN4 7

int motorSpeed;
int baseSpeed = ;
int rightSpeed;
int leftSpeed;

int saveMapFromError = 0;

bool Black(int n){
  if(n >= THRESHOLD){
    return true;
  }
  return false;
}

bool White(int n){
  if(n < THRESHOLD){
    return true;
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(Out1, INPUT);
  pinMode(Out2, INPUT);
  pinMode(Out3, INPUT);
  pinMode(Out4, INPUT);
  pinMode(Out5, INPUT);
  pinMode(Out6, INPUT);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
  pinMode(IN3, INPUT);
  pinMode(IN4, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor1 = analogRead(Out1);
  Serial.println("\nSensor1: ");
  Serial.println(Sensor1);
  Sensor2 = analogRead(Out2);
  Serial.println("\nSensor2: ");
  Serial.println(Sensor2);
  Sensor3 = analogRead(Out3);
  Serial.println("\nSensor3: ");
  Serial.println(Sensor3);
  Sensor4 = analogRead(Out4);
  Serial.println("\nSensor4: ");
  Serial.println(Sensor4);
  Sensor5 = analogRead(Out5);
  Serial.println("\nSensor5: ");
  Serial.println(Sensor5);
  Sensor6 = analogRead(Out6);
  Serial.println("\nSensor6: ");
  Serial.println(Sensor6);
  // delay(5000);

  // การกำหนดค่า State ทั้ง 11 States
  if(White(Sensor1) && White(Sensor2) && White(Sensor3) && White(Sensor4) && White(Sensor5) && Black(Sensor6)){ //000001
    error = 5;
  }
  else if(White(Sensor1) && White(Sensor2) && White(Sensor3) && White(Sensor4) && Black(Sensor5) && Black(Sensor6)){ //000011
    error = 4;
  }
  else if(White(Sensor1) && White(Sensor2) && White(Sensor3) && White(Sensor4) && Black(Sensor5) && White(Sensor6)){ //000010
    error = 3;
  }
  else if(White(Sensor1) && White(Sensor2) && White(Sensor3) && Black(Sensor4) && Black(Sensor5) && White(Sensor6)){ //000110
    error = 2;
  }
  else if(White(Sensor1) && White(Sensor2) && White(Sensor3) && Black(Sensor4) && White(Sensor5) && White(Sensor6)){ //000100
    error = 1;
  }
  else if(White(Sensor1) && White(Sensor2) && Black(Sensor3) && Black(Sensor4) && White(Sensor5) && White(Sensor6)){ //001100
    error = 0;
  }
  else if(White(Sensor1) && White(Sensor2) && Black(Sensor3) && White(Sensor4) && White(Sensor5) && White(Sensor6)){ //001000
    error = -1;
  }
  else if(White(Sensor1) && Black(Sensor2) && Black(Sensor3) && White(Sensor4) && White(Sensor5) && White(Sensor6)){ //011000
    error = -2;
  }
  else if(White(Sensor1) && Black(Sensor2) && White(Sensor3) && White(Sensor4) && White(Sensor5) && White(Sensor6)){ //010000
    error = -3;
  }
  else if(Black(Sensor1) && Black(Sensor2) && White(Sensor3) && White(Sensor4) && White(Sensor5) && White(Sensor6)){ //110000
    error = -4;
  }
  else if(Black(Sensor1) && White(Sensor2) && White(Sensor3) && White(Sensor4) && White(Sensor5) && White(Sensor6)){ //100000
    error = -5;
  }
  else if(White(Sensor1) && White(Sensor2) && White(Sensor3) && White(Sensor4) && White(Sensor5) && White(Sensor6)){
    error = pre_error;
  }
  Serial.print("error : ");
  Serial.println(error);

  // การคำนวน PD Control
  motorSpeed = Kp*error + Kd*(error - pre_error);
  leftSpeed = baseSpeed + motorSpeed;
  rightSpeed = baseSpeed - motorSpeed;

  pre_error = error;
  sum_error += error;

  analogWrite(EN1, leftSpeed);
  analogWrite(EN2, rightSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(30);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(20);

}
