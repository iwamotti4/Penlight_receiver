#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6

#define NUMPIXELS      60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


char input[100];   // 文字列格納用
int i = 0;  // 文字数のカウンタ

int recv_data; // 受信データ

StaticJsonBuffer<200> jsonBuffer;
   
void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(6 , OUTPUT);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {
  // データ受信したとき
  if (Serial.available()) {
    input[i] = Serial.read();
    
//    if(input[i] =='G'){
//        Serial.println("GET_GREEN");
//        for(int i=0;i<NUMPIXELS;i++){
//
//          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//          pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
//  
//          pixels.show(); // This sends the updated pixel color to the hardware.
//  
//        }
//    }
//    if(input[i] == 'R'){
//      Serial.println("GET_RED");
//        for(int i=0;i<NUMPIXELS;i++){
//
//          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//          pixels.setPixelColor(i, pixels.Color(150,0,0)); // Moderately bright green color.
//  
//          pixels.show(); // This sends the updated pixel color to the hardware.
//  
//        }
//    }
//    if(input[i] == 'B'){
//      Serial.println("GET_BLUE");
//        for(int i=0;i<NUMPIXELS;i++){
//
//          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//          pixels.setPixelColor(i, pixels.Color(0,0,150)); // Moderately bright green color.
//  
//          pixels.show(); // This sends the updated pixel color to the hardware.
//  
//        }
//    }

      if (i > 25) {
      i = 0;
//      Serial.print(input);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(input);

      // Test if parsing succeeds.
        if (!root.success()) {
          Serial.println("parseObject() failed");
          return;
        }
        else{
          int x  = root["x"];
          int y  = root["y"];
          int z  = root["z"];
          Serial.print(x);
          Serial.print(',');
          Serial.print(y);
          Serial.print(',');
          Serial.println(z);
        }
      }
      else{
        i++;
      }
    }    
  else{
    digitalWrite(13, LOW);
    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      // pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
  
      // pixels.show(); // This sends the updated pixel color to the hardware.

    }
    delay(25);
  }
}

/*
void loop() { 

  // 受信バッファに３バイト（ヘッダ＋int）以上のデータが着ているか確認
  if ( Serial.available() >= sizeof('X') + sizeof(int) ) {
    // ヘッダの確認
    if ( Serial.read() == 'X' ) {
      int low = Serial.read(); // 下位バイトの読み取り
      int high = Serial.read(); // 上位バイトの読み取り
      recv_data = makeWord(high,low); // 上位バイトと下位バイトを合体させてint型データを復元
      
    }
  }

  // 受信したデータに基づいてLEDをON/OFF
  if ( recv_data < 400 ) {
//    digitalWrite(13, HIGH);
//      Serial.print("LOW");
  }
  else if ( recv_data > 400 ) {
//    digitalWrite(13, LOW);
//      Serial.print("HIGH");
  }
  Serial.print(recv_data);
}*/
