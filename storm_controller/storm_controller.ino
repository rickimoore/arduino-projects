#include "Bolt.h"

Bolt bolts[6] = {
    Bolt(11),
    Bolt(10),
    Bolt(9),
    Bolt(6),
    Bolt(5),
    Bolt(3)
  };

void setUpPins(){
  int boltCount = sizeof(bolts)/sizeof(bolts[0]);
  for(int i = 0; i < boltCount; i++){
    pinMode(bolts[i].getPinId(), OUTPUT); 
  }
}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  setUpPins();
}

// the loop routine runs over and over again forever:
void loop() {

  int boltCount = sizeof(bolts)/sizeof(bolts[0]);
  for(int i = 0; i < boltCount; i++){
    bolts[i].controlStorm();
  }
  
}
