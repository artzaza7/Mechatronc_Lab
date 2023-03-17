int Analog_in = A1;
float distance_cm = 0.0;

void setup() {
  Serial.begin(9600);  
}

void loop() {   
    distance_cm = get_dist(100);   
    Serial.println (distance_cm);
    delay(500);                       
}

float get_dist(int n)
{
  long sum=0;
  for(int i=0;i<n;i++)
  {
    sum=sum+analogRead(Analog_in);
  }  
  float adc=sum/n;
  float volts = analogRead(adc)*0.0048828125;  // value from sensor * (5/1024)
  distance_cm = 3.3263*pow(volts, -0.397); 
  return(distance_cm);
}
