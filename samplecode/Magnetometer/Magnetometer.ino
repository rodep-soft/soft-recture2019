//I2C通信ライブラリを取り込む
#include <Wire.h>

//デジタルコンパスモジュールのアドレス設定
int compassAddress = 0x42 >> 1; //=0x21
//読み込み値（角度）の変数を用意
int reading = 0; 
 
void setup() {
  //I2C通信開始 
  Wire.begin();
  //角度表示のためのシリアル通信開始
  Serial.begin(9600);
  
  //Continuous Modeに設定する
  Wire.beginTransmission(compassAddress);
  //RAM書き込み用コマンド
  Wire.write('G');
  //書き込み先指定
  Wire.write(0x74);
  //モード設定
  Wire.write(0x72);
  //通信終了
  Wire.endTransmission();
  //処理時間
  delayMicroseconds(70);
} 
  
void loop() {
  //デバイスに２バイト分のデータを要求する
  Wire.requestFrom(compassAddress, 2);
  //要求したデータが２バイト分来たら
  if(Wire.available()>1){
    //１バイト分のデータの読み込み 
    reading = Wire.read();
    //読み込んだデータを８ビット左シフトしておく
    reading = reading << 8;
    //次の１バイト分のデータを読み込み
    //一つ目のデータと合成（２バイト）
    reading += Wire.read();
    //２バイト分のデータを１０で割る
    reading /= 10; 
    Serial.println(reading);
  } 
  //処理のために少し待つ（20Hz）
  delay(50);
}
