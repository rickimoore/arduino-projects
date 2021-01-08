int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by


//storm state
String stormState = "";

//different states storm can be set with
String CALM = "CALM";
String STRIKE = "STRIKE";
String FLICKER = "FLICKER";
String SETTLE = "SETTLE";

//timeout durations
unsigned long flickerDuration = 0;
unsigned long calmDuration = 0;

//timer
unsigned long previousTime = 0;


void stikeLightning () {
  // set the brightness
  analogWrite(led, brightness);

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


void settleLightning () {
  // set the brightness
  analogWrite(led, brightness);

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

void flickerLightning() {
  //bring down to half light
  delay(100);
  brightness = 150;
  analogWrite(led, brightness);

  //return to full light
  delay(50);
  brightness = 255;
  analogWrite(led, brightness);
}

void timeLightFlicker(){
  unsigned long currentTime = millis();

  if(currentTime - previousTime > flickerDuration){
    stormState = SETTLE;
    previousTime = currentTime;
  }
}

void timeNextStrike(){
  unsigned long currentTime = millis();

  if(currentTime - previousTime > calmDuration){
    stormState = STRIKE;
    previousTime = currentTime;
  }
}

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  delay(500);
  stormState = CALM;
}

// the loop routine runs over and over again forever:
void loop() {

  // watch the storm states
  
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
}
