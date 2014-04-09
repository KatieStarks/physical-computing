/* Project Title: _3buttons1LED
 Katie Ballinger
 DIGF 2B03 Physical Computing
 OCAD University
 Created on Feb 3rd/14
 
 Based on:
 Blink, Public Domain, http://www.arduino.cc/en/Tutorial/Blink
 Button, DojoDave, http://www.arduino.cc/en/Tutorial/Button
 */

// constants
const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 4;     // the number of the pushbutton pin
const int buttonPin3 = 6;     // the number of the pushbutton pin
const int led =  13;      // the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(led, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);     
    // initialize the pushbutton pin as an input:
  pinMode(buttonPin2, INPUT); 
    // initialize the pushbutton pin as an input:
  pinMode(buttonPin3, INPUT); 
}

void loop(){
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {     
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second 
  } 
  else if(buttonState2 == HIGH) {
    digitalWrite(led, HIGH);   // turn the LED on
  }
  else if(buttonState3 == HIGH) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                // wait for half a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                // wait for half a second
  }
  else {
    // turn LED off:
    digitalWrite(led, LOW); 
  }
}

