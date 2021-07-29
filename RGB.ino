int LED_R = 9;   // デジタルピン9番に赤色LEDを割り当てる(変数)
 int LED_G = 10;  // デジタルピン10番に緑色LEDを割り当てる(変数)
 int LED_B = 11;  // デジタルピン11番に青色LEDを割り当てる(変数)
 int WAIT = 500;      // 待ち時間の指定
void red(int r, int g,int b,int wait){
   digitalWrite(r, LOW);
   digitalWrite(g, HIGH);   // 赤色LEDを点灯しその他を消灯
   digitalWrite(b, HIGH);
   delay(wait);
}
void blue(int r, int g,int b,int wait){
  digitalWrite(r, HIGH);
   digitalWrite(g, LOW);  // 緑色LEDを点灯しその他を消灯
   digitalWrite(b, HIGH);
   delay(wait);
 
}
void green(int r, int g,int b,int wait){
   digitalWrite(r, HIGH);
   digitalWrite(g, HIGH);   // 青色LEDを点灯しその他を消灯
   digitalWrite(b, LOW);
   delay(wait);
}
 
 void setup(){
   pinMode(LED_R, OUTPUT);  // それぞれのピンを出力に設定
   pinMode(LED_G, OUTPUT);
   pinMode(LED_B, OUTPUT);
  
}
 
 
 void loop(){
  red(LED_R,LED_G,LED_B,WAIT);
  blue(LED_R,LED_G,LED_B,WAIT);
  green(LED_R,LED_G,LED_B,WAIT);
}
