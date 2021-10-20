/*
 * 変数群
 */

int LED_R = 10;            // デジタルピン9番に赤色LEDを割り当てる(変数)
int LED_G = 11;            // デジタルピン10番に緑色LEDを割り当てる(変数)
int LED_B = 12;            // デジタルピン11番に青色LEDを割り当てる(変数)
int WAIT = 500;            // 待ち時間の指定
int pirSensor=2;           // 人感センサを読み取るピン
int speedPin = 3;          // PWM制御出力ピン
int mistPin  = 5;          // ミストのPWM制御
int motor1APin = 8;        // 1A ピン
int motor2APin = 9;        // 2A ピン
int motor3APin = 6;        // 3A 
int motor4APin = 7;        // 4A
int speed_value_motor1;    // PWM値(スピード)
int mist_value_motor2;     // PWM値(ミスト)
int temp_analogPin=0;      // 温度センサを読み取るアナログピン
float cel2=0.0;            // 気温
volatile int pir_flag =0;  // 人感センサのオンオフのフラグ

/*-------------------------------------------
 * LEDの色制御
 */
void red(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);   // 赤色LEDを点灯しその他を消灯
  digitalWrite(LED_B, HIGH);
}
void blue(){
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);  //青色LEDを点灯しその他を消灯
  digitalWrite(LED_B, LOW);
}
void green(){
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);   // 緑色LEDを点灯しその他を消灯
  digitalWrite(LED_B, HIGH);
}

void yellow(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);   // 橙=()を点灯しその他を消灯
  digitalWrite(LED_B, HIGH);
}
void white(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);   // 白=(赤＋青＋緑)を点灯しその他を消灯
  digitalWrite(LED_B, LOW);
}
/* 終了
 * ------------------------------------
 */


 

 /*-----------------------------------
  * 温度によりLEDの色を制御
  */
void temp_LED(){
  int val=analogRead(temp_analogPin);
  float cel =(float)val*500.0/1024.0-60.0;
  if(cel<10)//if temperature is in (-inf,10), then LED is blue.
    blue();
  else if(cel<20)//if temperature is in [10,20),then LED is white.
    white();
  else if(cel<30)//if temperature is in [20,30),then LED is orange
    yellow();
  else//LED is otherwise red. i.e. temperature is in [30,inf)
    red();
  cel2=cel;//計算結果を反映
}

/*
 * 終了
 * -------------------------------
 */


 

/*-------------------------------------
 * 扇風機関連のプログラム
 */
void pwm_with(int speed_num){
  digitalWrite(motor1APin, LOW); // 1Y is set LOW
  digitalWrite(motor2APin, HIGH); //　2Y is set HIGH
  speed_value_motor1 = speed_num; // this has 0~255 
  analogWrite(speedPin, speed_value_motor1);
}

void stop_fan(){
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor2APin, LOW);
  analogWrite(speedPin, 0); 
}
void turnOn_fan(){
  //Serial.println("Senror->ok");
  pwm_with(255);
  delay(5000);
}
void turnOff_fan(){
  Serial.println("turn_off,Sensor->no signal");
  stop_fan();
  delay(1000);
}
/*
 * 終了
 * ------------------------------------
 */


 

/*-------------------------------------------------
 * 人感フラグ割り込み時の関数
 */
void pir_change(){
  pir_flag=(pir_flag+1)%2;
  Serial.println("CHANGE");
}

/*
 * 終了
 * ----------------------------------------------
 */


/*
 * 温度によって速度を変化
 */

void motor_from_temp(){
  if(cel2>=25){
    Serial.println("Senror->Ifok");
    pwm_with(255);
    mistpwm_with(255);
    delay(5000);
  }
  else if(cel2>=15){
    Serial.println("Senror->elseIfok");
    pwm_with(156);
    stop_mist();
    delay(5000);
  }
  else{
    Serial.println("Senror->elseok");
    turnOff_fan();
    stop_mist();
    delay(1000);
  }
}

 /*
  * 終了
  *------------------------
  */

/*
 * ミスト関連
 */
void mistpwm_with(int speed_num){
  digitalWrite(motor3APin, LOW); // 1Y is set LOW
  digitalWrite(motor4APin, HIGH); //　2Y is set HIGH
  mist_value_motor2 = speed_num; // this has 0~255 
  analogWrite(mistPin, mist_value_motor2);
}
void stop_mist(){
  digitalWrite(motor3APin, LOW); // 1Y is set LOW
  digitalWrite(motor4APin, LOW); //　2Y is set HIGH 
  analogWrite(mistPin,0);
}

/*
 * 終了
 * ----------------------
 */
 
 void setup(){
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);  // それぞれのピンを出力に設定
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(mistPin,OUTPUT);
  pinMode(motor1APin, OUTPUT); 
  pinMode(motor2APin, OUTPUT);
  pinMode(motor3APin,OUTPUT);
  pinMode(motor4APin,OUTPUT); 
  pinMode(pirSensor,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pirSensor),pir_change,CHANGE);
}


 void loop(){
  int pos=pir_flag;
  temp_LED();
  Serial.println(cel2);
  //Serial.println(pos);
  if(pos){
    //Serial.println("ok");
    motor_from_temp();
  }
  else{
    //Serial.println("no signal");
    turnOff_fan();
    stop_mist();
  }
  delay(100);
}
