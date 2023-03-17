#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 40; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 150; pos >= 40; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15 ms for the servo to reach the position
  }
}

// #include <Servo.h>
// Servo myservo; // create servo object to control a servo
// int degree=0;
// void setup()
// {
//   Serial.begin(9600);
//   myservo.attach(9); // attaches the servo on pin 9 to the servo object
// }
// void loop()
// {
//   if(Serial.available()>0)
//   {
//   degree = Serial.parseInt();
//   String str = Serial.readStringUntil('\n');
//   Serial.println(degree);
//   }
//   myservo.write(degree); // sets the servo position
//   delay(15); // waits for the servo to get there
// }
