// example: class constructor
using namespace std;

//different states storm can be set with
String CALM = "CALM";
String STRIKE = "STRIKE";
String FLICKER = "FLICKER";
String SETTLE = "SETTLE";

class Bolt {
    int pinId;
    String stormState = CALM;
    
    //timeout durations
    unsigned long flickerDuration = rand() % 2000 + 1;
    unsigned long calmDuration = rand() % 5000 + 1000;
    
    //timer
    unsigned long previousTime = 0;
    
    int brightness = 0;    // how bright the LED is
    int fadeAmount = 5;    // how many points to fade the LED by
  public:
    Bolt (int);
    int getPinId () {return pinId;}
    void controlStorm();
  private:
    void timeNextStrike();
    void timeLightFlicker();
    void flickerLightning();
    void settleLightning();
    void stikeLightning();
};

Bolt::Bolt (int pin) {
  pinId = pin;
}

void Bolt::stikeLightning () {
  // set the brightness
  analogWrite(pinId, brightness);

  // change the brightness for next time through the loop:
  if(brightness < 255) {
   brightness = brightness + fadeAmount; 
  } else {
    stormState = FLICKER;
    flickerDuration = rand() % 2000 + 1;
  }
  // delay that causes dim effect
  delay(5);
}

void Bolt::settleLightning () {
  // set the brightness
  analogWrite(pinId, brightness);

  // change the brightness for next time through the loop:
  if(brightness > 0) {
   brightness = brightness - fadeAmount; 
  } else {
    stormState = CALM;
    calmDuration = rand() % 5000 + 1000;
  }
  // delay that causes dim effect
  delay(5);
}

void Bolt::flickerLightning() {
  //bring down to half light
  delay(100);
  brightness = 150;
  analogWrite(pinId, brightness);

  //return to full light
  delay(50);
  brightness = 255;
  analogWrite(pinId, brightness);
}

void Bolt::timeLightFlicker(){
  unsigned long currentTime = millis();

  Serial.print("flicker --- ");
  Serial.print(pinId);
  Serial.print(" ---- ");
  Serial.println(flickerDuration);

  if(currentTime - previousTime > flickerDuration){
    stormState = SETTLE;
    previousTime = currentTime;
  }
}

void Bolt::timeNextStrike(){
  unsigned long currentTime = millis();

  if(currentTime - previousTime > calmDuration){
    stormState = STRIKE;
    previousTime = currentTime;
  }
}

void Bolt::controlStorm(){
  if(stormState == CALM){
    timeNextStrike();
  }
  if(stormState == STRIKE){
   stikeLightning(); 
  }
  if(stormState == FLICKER){
    flickerLightning();
    timeLightFlicker();
  }
  if(stormState == SETTLE){
    settleLightning();
  }
};
