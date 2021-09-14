/*
 * 変数群
 */

int LED_R = 10;            // デジタルピン9番に赤色LEDを割り当てる(変数)
int LED_G = 11;            // デジタルピン10番に緑色LEDを割り当てる(変数)
int LED_B = 12;            // デジタルピン11番に青色LEDを割り当てる(変数)
int WAIT = 500;            // 待ち時間の指定
int pirSensor=2;           //人感センサを読み取るピン
int speedPin = 3;          // PWM制御出力ピン
int motor1APin = 8;        // 1A ピン
int motor2APin = 9;        // 2A　ピン
int speed_value_motor1;    //PWM値
int temp_analogPin=0;      //温度センサを読み取るアナログピン
float cel2=0.0;            //気温
volatile int pir_flag =0;  //人感センサのオンオフのフラグ

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

void orange(){
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
    orange();
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
  Serial.println("Senror->ok");
  pwm_with(255);
  delay(5000);
}
void turnOff_fan(){
  Serial.println("Sensor->no signal");
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
void pir_rising(){
  
  pir_flag=1;
}

void pir_falling(){
  pir_flag=0;
}
void pir_change(){
  pir_flag=(pir_flag+1)%2;
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
    delay(5000);
  }
  else if(cel2>=15){
    Serial.println("Senror->elseIfok");
    pwm_with(156);
    delay(5000);
  }
  else{
    Serial.println("Senror->elseIfok");
    pwm_with(0);
    delay(1000);
  }
}

 /*
  * 終了
  *------------------------
  */

 void setup(){
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);  // それぞれのピンを出力に設定
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(motor1APin, OUTPUT); 
  pinMode(motor2APin, OUTPUT); 
  pinMode(pirSensor,INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(pirSensor),pir_rising,RISING);
  //attachInterrupt(digitalPinToInterrupt(pirSensor),pir_falling,FALLING);
  attachInterrupt(digitalPinToInterrupt(pirSensor),pir_change,CHANGE);
}


 void loop(){
  int pos=pir_flag;
  temp_LED();
  Serial.println(cel2);
  Serial.println(pos);
  if(pos){
    motor_from_temp();
  }
  else{
    turnOff_fan();
  }
}
