#include <Wire.h>
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int Feedback; 
int mapFeedback;
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;

void setup(){  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop()
{
 Feedback = AngleRead();   // อ่านค่าจากเซนเซอร์ตรวจจับตำแหน่ง
// แสดงผลกราฟ
  if(Feedback>=0 && Feedback <=180) {
    mapFeedback = map(Feedback, 0, 180, 0, 180);
    Serial.println (mapFeedback);   
 Serial.print("\t");
  }
  else{
    mapFeedback = map(Feedback, 181, 359, -179, -1);
    Serial.println (mapFeedback);   
 Serial.print("\t");
  }
 

}

int AngleRead(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
 
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  return(x);
  //delay(50);
}


// #include <Wire.h>
// #include <MPU6050_light.h>
// MPU6050 mpu(Wire);

// void setup() {
//   Serial.begin(9600);
//   mpu.begin();
// }

// void loop() {
//   mpu.update();
//   // เก็บค่ามุมในแกน X, Y, Z ไว้ในตัวแปร angleX, angleY, angleZ
//   float angleX = mpu.getAngleX();
//   float angleY = mpu.getAngleY();
//   float angleZ = mpu.getAngleZ();
//  // เก็บค่า Gyro ในแกน X, Y, Z ไว้ในตัวแปร gyroX, gyroY, gyroZ
//  float gyroX = mpu.getGyroX();
//  float gyroY = mpu.getGyroY();
//  float gyroZ = mpu.getGyroZ();

//  // Serial Print
//  Serial.print("Angle X ");
//  Serial.print(angleX);
//  Serial.println(" Degree");
//  Serial.print("Angle Y ");
//  Serial.print(angleY);
//  Serial.println(" Degree");
//  Serial.print("Angle Z ");
//  Serial.print(angleZ);
//  Serial.println(" Degree");
//  Serial.println();

//  Serial.print("Angular velocity X ");
//  Serial.print(gyroX);
//  Serial.println(" Degree/s");
//  Serial.print("Angular velocity Y ");
//  Serial.print(gyroY);
//  Serial.println(" Degree/s");
//  Serial.print("Angular velocity Z ");
//  Serial.print(gyroZ);
//  Serial.println(" Degree/s");
//  Serial.println();

//  delay(1000);
// }
