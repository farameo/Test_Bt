
#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 10

#define led1 3
#define led2 5
#define led3 6

SoftwareSerial Bluetooth(BT_RX, BT_TX); // RX, TX

String comando;

int rxState;
int rxCmd;

int _BYTE = -86;

const int _rxState = 0;
const int _rxCmd = 1;
const int _rxData = 3;


void setup() {
  Serial.begin(9600);

  Bluetooth.begin(9600); 

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  Serial.println("esperando");
  rxState = _rxState;

}

void loop(){
 
  while (Bluetooth.available()) {
    
    char rxDato = (int)Bluetooth.read();
    
    switch (rxState) {
      
      case _rxState:
        if (rxDato == _BYTE) {
          rxState = _rxCmd; 
        }
        break;

      case _rxCmd:
        rxCmd = rxDato;
        rxState = _rxData;
        break;

      case _rxData:
        if (rxCmd == 1) {
          analogWrite(led1, rxDato);
        } else if (rxCmd == 2) {
          analogWrite(led2, rxDato);
        } else {
          analogWrite(led3, rxDato);
        }
        
        rxState = _rxState;

        break;
        

      default:
       rxState = _rxState;
    }
   
 
  }
  
}
