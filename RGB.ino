int LED_R = 9;   // デジタルピン9番に赤色LEDを割り当てる(変数)
 int LED_G = 10;  // デジタルピン10番に緑色LEDを割り当てる(変数)
 int LED_B = 11;  // デジタルピン11番に青色LEDを割り当てる(変数)
 int WAIT = 500;      // 待ち時間の指定
 float cel2=0.0;
void red(){
   digitalWrite(LED_R, LOW);
   digitalWrite(LED_G, HIGH);   // 赤色LEDを点灯しその他を消灯
   digitalWrite(LED_B, HIGH);
   delay(WAIT);
}
void blue(){
  digitalWrite(LED_R, HIGH);
   digitalWrite(LED_G, LOW);  // 緑色LEDを点灯しその他を消灯
   digitalWrite(LED_B, HIGH);
   delay(WAIT);
 
}
void green(){
   digitalWrite(LED_R, HIGH);
   digitalWrite(LED_G, HIGH);   // 青色LEDを点灯しその他を消灯
   digitalWrite(LED_B, LOW);
   delay(WAIT);
}

void orange(){
  digitalWrite(LED_R, LOW);
   digitalWrite(LED_G, HIGH);   // 青色LEDを点灯しその他を消灯
   digitalWrite(LED_B, LOW);
   delay(WAIT);
}
void white(){
  digitalWrite(LED_R, LOW);
   digitalWrite(LED_G, LOW);   // 青色LEDを点灯しその他を消灯
   digitalWrite(LED_B, LOW);
   delay(WAIT);
}

void temp_LED(){
  int val=analogRead(A0);
  float cel =(float)val*500.0/1024.0-60.0;
  if(cel<10)
    blue();
  else if(cel<20)
    white();
  else if(cel<30)
    orange();
  else
    red();
  cel2=cel;
}

 void setup(){
   Serial.begin(9600);
   pinMode(LED_R, OUTPUT);  // それぞれのピンを出力に設定
   pinMode(LED_G, OUTPUT);
   pinMode(LED_B, OUTPUT);
}


 void loop(){
  temp_LED();
  Serial.println(cel2);
}
