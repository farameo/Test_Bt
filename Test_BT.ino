
#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 10

#define led1 3
#define led2 5
#define led3 6

SoftwareSerial Bluetooth(BT_RX, BT_TX); // RX, TX

String comando;

int rxState;
int rxLen;
int rxCmd;

int _BYTE = -86;
int _CMD = 1;

const int _rxState = 0;
const int _rxSync  = 1;
const int _rxCmd = 2;
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
    /*
    comando = "";
    while (Bluetooth.available()) {
      char caracter = Bluetooth.read();
      comando += caracter;
      delay(10);
    }
    */
  while (Bluetooth.available()) {
    
    char rxDato = (int)Bluetooth.read();
    Serial.println(rxDato, DEC);
    
    switch (rxState) {
      
      case _rxState:
        if (rxDato == _BYTE) {
          Serial.println("byte de inicio"); 
          rxState = _rxSync; 
        }
        break;

      case _rxSync:
        rxLen = rxDato;
        Serial.println("longitud : " + String(rxLen));
        rxLen--;
        rxState = _rxCmd;
               
        break;

      case _rxCmd:
        rxCmd = rxDato;
        Serial.println("comando: " + String(rxCmd));
        rxLen--;
        rxState = _rxData;
        break;

      case _rxData:
        Serial.println(rxDato, DEC);

        if (rxCmd == _CMD) {
          analogWrite(led1, rxDato);
        }
        
        rxLen--;
        if (rxLen == 0 ) {
          rxState = _rxState;
        }

        break;
        

      default:
       rxState = _rxState;
    }
   
 
  }
  
}
