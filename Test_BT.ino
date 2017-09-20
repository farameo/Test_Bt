
#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 10

#define led1 3
#define led2 5
#define led3 6

SoftwareSerial Bluetooth(BT_RX, BT_TX); // RX, TX

String comando;

void setup() {
  Serial.begin(9600);

  Bluetooth.begin(9600); 

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);


}

void loop(){
  if (Bluetooth.available()) {
    Serial.println("a");
    while (Bluetooth.available()) {
      char caracter = Bluetooth.read();
      comando += caracter;
      delay(10);
    }
    
    if (comando.indexOf("led1") >= 0) {
        analogWrite(led1, 255);
    }
    if (comando.indexOf("led2") >= 0) {
        analogWrite(led2, 255);
    }
    if (comando.indexOf("led3") >= 0) {
        analogWrite(led3, 255);
    }
  }
  
}
