/* Project Title: 1Button3Leds
 Katie Ballinger
 DIGF 2B03 Physical Computing
 OCAD University
 Created on Feb 3rd/14
 
 Based on:
 Blink, Public Domain, http://www.arduino.cc/en/Tutorial/Blink
 Button, DojoDave, http://www.arduino.cc/en/Tutorial/Button
 */

//set pin numbers
const int button = 2;   //the number of the pushbutton pin
const int led1 = 4;     //the number of the LED pin
const int led2 = 6;     //the number of the LED2 pin
const int led3 = 8;     //the number of the LED3 pin

//variables will change
int buttonState = 0;    //variable for reading the pushbutton status
boolean buttonOn = false;
int ledState = 0;        //variable to change LED blinking states

void setup() {
  pinMode(button, INPUT); //initialize the pushbutton pin as input
  pinMode(led1, OUTPUT);  //initialize the LED pins as output
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(button); //read the state of the pushbutton value
  //check if the pushbutton is pressed, if yes, buttonState is HIGH
  if (buttonState == HIGH) {
    if (buttonOn == true) {
      ledState++;
      buttonOn = false; //triggers the ledState only once, then sets buttonOn to false
      Serial.println(buttonOn);
    }
    else {
      buttonOn = false;
    }
  }
  else if(buttonState == LOW) {
    buttonOn = false;
  }

  if (ledState == 0) {
    //BLINK SEQUENCE 1
    seq1();
  }
  else if (ledState == 1) {
    //BLINK SEQUENCE 2
    seq2();
  }
  else if (ledState == 2) {
    //BLINK SEQUENCE 3
    seq3();
  }
  else {
    ledState = 0;
  }
}

void seq1() {
  digitalWrite(led1, HIGH);
  delay(250);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(250);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(250);
  digitalWrite(led3, LOW);

}

void seq2() {
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(500);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(500);
  digitalWrite(led3, LOW); 
}

void seq3() {
  digitalWrite(led1, HIGH);
  delay(50);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(50);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(50);
  digitalWrite(led3, LOW);
}

