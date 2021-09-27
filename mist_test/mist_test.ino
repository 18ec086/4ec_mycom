int mistPin  = 5;          // ミストのPWM制御
int motor3APin = 6;        // 3A 
int motor4APin = 7;        // 4A
int mist_value_motor2;
void mistpwm_with(int speed_num){
  digitalWrite(motor3APin, LOW); // 1Y is set LOW
  digitalWrite(motor4APin, HIGH); //　2Y is set HIGH
  mist_value_motor2 = speed_num; // this has 0~255 
  analogWrite(mistPin, mist_value_motor2);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(mistPin,OUTPUT);
  pinMode(motor3APin,OUTPUT);
  pinMode(motor4APin,OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  mistpwm_with(128);
  delay(1000);
}
