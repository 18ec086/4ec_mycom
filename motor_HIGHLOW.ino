int speedPin = 3; // H-bridge enable pin for speed control
int motor1APin = 6; // H-bridge leg 1 
int motor2APin = 7; // H-bridge leg 2 

int speed_value_motor1; // value for motor speed
void setup() {
 // set digital i/o pins as outputs:
 pinMode(speedPin, OUTPUT);
 pinMode(motor1APin, OUTPUT); 
 pinMode(motor2APin, OUTPUT); 
}
void strength(int speed_num){
  digitalWrite(motor1APin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor2APin, HIGH); // set leg 2 of the H-bridge high
 speed_value_motor1 = speed_num; // half speed
 analogWrite(speedPin, speed_value_motor1);
}
 
void loop() {
 strength(30);
 delay(5000);
 strength(255);
 delay(5000);
}
