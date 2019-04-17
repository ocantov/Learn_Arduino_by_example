const byte buttonAPin = 2; //interrupts pin , it depends on the arduino you are using
const byte buttonBPin = 3; //interrupts pin , it depends on the arduino you are using
byte buttonARisingState;
byte buttonBRisingState;
byte buttonBFallingState;

// macros for detection of rising/falling edge and debouncing 
//4 consecutive 1 (debounced rising edge) 
#define DRE(signal, state) (state=(state<<1)|signal)==B00001111  

// 4 consecutive 0. (debounced falling edge)
#define DFE(signal, state) (state=(state<<1)|signal)==B11110000

volatile int counter=0;
volatile int revolutions = 0;
volatile unsigned long dataTimer = 0;

void setup() {

  // Set pinmodes
  pinMode (buttonAPin, INPUT);
  pinMode (buttonBPin, INPUT_PULLUP);

  // attach the interrupts
  attachInterrupt(digitalPinToInterrupt(buttonAPin), readInterrupt1, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonBPin), readInterrupt2, CHANGE );
}


void readInterrupt1() {
   detachInterrupt(buttonAPin);
   if (DRE(digitalRead(buttonAPin), buttonARisingState)) {
      revolutions++;
      Serial.begin (9600);
      Serial.println (revolutions);
      Serial.end();
    }

  attachInterrupt(digitalPinToInterrupt(buttonAPin), readInterrupt1, RISING);

}
void readInterrupt2() {
  detachInterrupt(buttonBPin);
    /*If we get one rising edge followed by 4 consecutive 1's (debounced rising edge) or  if we get one falling edge followed by
  4 consecutive 0's. (debounced falling edge*/
  if (DRE(digitalRead(buttonBPin), buttonBRisingState) || DFE(digitalRead(buttonBPin), buttonBFallingState) ) {
    counter++;
    Serial.begin (9600);
    Serial.println (counter);
    Serial.end();
  }
  attachInterrupt(digitalPinToInterrupt(buttonBPin), readInterrupt2, CHANGE);
}


// MAIN LOOP

void loop() {

}
