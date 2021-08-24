int pirSensor=7;
int speedPin = 3; // H-bridge enable pin for speed control
int motor1APin = 8; // H-bridge leg 1 
int motor2APin = 9; // H-bridge leg 2 
int speed_value_motor1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pirSensor,INPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(motor1APin, OUTPUT); 
  pinMode(motor2APin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int i=digitalRead(pirSensor);
  if(i){
    Serial.println("Senror->ok");
    strength(255);
  }
  else{
    Serial.println("Sensor->no signal");
  }
  //strength(255);
  delay(1000);
}
void strength(int speed_num){
 digitalWrite(motor1APin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor2APin, HIGH); // set leg 2 of the H-bridge high
 speed_value_motor1 = speed_num; // half speed
 analogWrite(speedPin, speed_value_motor1);
}
