/* Project Title: Tone Match
 Katie Ballinger
 DIGF 2B03 Physical Computing
 OCAD University
 Created on April 8th 2014

 Description: Plays the memory game with tones! Hurray!
 
 Based on:
 Blink, Public Domain, http://www.arduino.cc/en/Tutorial/Blink
 Button, DojoDave, http://www.arduino.cc/en/Tutorial/Button
 DigitalInputPullup, ScottFitzgerald, http://www.arduino.cc/en/Tutorial/InputPullupSerial
 toneMelody, Tom Igoe, http://www.arduino.cc/en/Tutorial/Tone
 Arrays, David A. Mellis, http://www.arduino.cc/en/Tutorial/Array
 (Forum Topic Help), Rob Tillaart, http://forum.arduino.cc/index.php?topic=66681.0
 */
#include "pitches.h" //pitches library

//array for pin numbers
const int pin[] = { 2, A5, 6, 7, 4, 5, 8,9,10,11,12,13 };
const int buttonCount = 12; //number of buttons
const int tonePairs   = 6; //number of pitches
const int speakerPin = 3;      // pin number for the speaker
const int noteDuration = 200;

//array for button order
int order[buttonCount] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
//array to check if a button is being held
bool held[buttonCount] = { 0,0,0,0,0,0,0,0,0,0,0,0};

int toneA[tonePairs] = { 2,A5,6,7,4,5 }; //first set of tone pairs
int toneB[tonePairs] = { 8,9,10,11,12,13 }; //second set of tone pairs
bool won[tonePairs]   = { 0,0,0,0,0,0 }; //array to set if pairs matched

int noteA[tonePairs]   = { NOTE_FS1,NOTE_E3,NOTE_F4,NOTE_G2,NOTE_A3,NOTE_B4 }; //array to set if pairs matched
int noteB[tonePairs]   = { NOTE_B4,NOTE_A3,NOTE_G2,NOTE_F4,NOTE_E3,NOTE_FS1 }; //array to set if pairs matched
int* notes[2];

int sensorVal; //variable to check if pin is HIGH or LOW
int previous = 0; //variable to hold first switch selection

void setup(){

  Serial.begin(9600); //initiates serial monitor
  /*reads analog pin that doesn't have anything connected, 
  (which generates noise) to produce a REAL random value */
  randomSeed(analogRead(0)); 

  notes[0] = noteA;
  notes[1] = noteB;

//setting up pins using built in pullup resistors through an array
  for (int i = 0; i < buttonCount; ++i)
  {
    pinMode(pin[i], INPUT_PULLUP);  
  }

  //(Forum Topic Help), Rob Tillaart, http://forum.arduino.cc/index.php?topic=66681.0
  //randomly swaps the position of the numbers in the array to produce random order
  for (int i= 0; i < buttonCount; i++) 
  { 
    int pos = random(12);
    int t = order[i];   
    order[i] = order[pos];
    order[pos] = t;
  }

  for (int i= 0; i< buttonCount; i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(order[i]);
  }

  pinMode(speakerPin, OUTPUT);

  pinMode(13, OUTPUT);  
  /*during debugging, this line made the pin behave correctly,
  probably because pin 13 is connected to the onboard LED*/

}

void loop(){

  for (int i = 0; i < buttonCount; ++i) //checks all buttons to see if pressed
  {

      sensorVal = digitalRead(pin[order[i]]); //checks pin's state change based on new order

      if(sensorVal == LOW) { //if switch is pressed
        
        if (held[i] == false) {
          if(previous != pin[i]) {
            check(pin[i]); //runs the function to check for a match

            //debugging code
            // Serial.print(pin[i]);
            // Serial.print(" <- real | order -> ");
            // Serial.println(pin[order[i]]);
          }
        }

        held[i] = true; //prevents from firing function if button is held

      } else {
        
        held[i] = false; //resets held state when button released

      }

  }   

  delay(10); 

}

void check(int current) {


  if (previous == 0) {
    previous = current;
    playButton(current);
  } else {

    playButton(current);

    bool correct  = false; //variable to tell if the pair is correct
    bool taken    = false; //variable to tell if you've matched that pair already

    for (int i = 0; i < tonePairs; ++i) //checks if tones match
    { 
      if(previous == toneA[i] && current == toneB[i] || current == toneA[i] && previous == toneB[i]) {
        if (won[i] == false) {
          correct = true;
          won[i]  = true;
          Serial.print(toneA[i]);
          Serial.print(" <- A | B -> ");
          Serial.println(toneB[i]);
        } else {
          taken = true;
        }
      }
    }

    if (taken) {
      //play nothing
      Serial.println("Taken");
    } else if(!correct) {
      Serial.println("Wrong");
      delay(175);
      playFail();
    } else if(correct) {
      //play yup function
      bool finished = true;
      // if you need it.
      for (int i = 0; i < tonePairs; ++i) {
        Serial.print(toneA[i]);
        Serial.print(" & ");
        Serial.print(toneB[i]);
        Serial.print(" status -> ");
        Serial.println(won[i]);

        if(!won[i]) {
          finished = false;
        }
      }

      if (finished) {
        Serial.println("GJ MOTHAFAKA");
        playWin();
      } else {
        delay(150);
        playCorrect();
      }

    }



    previous = 0; // Resets the game whether the answer is wrong or not.

  }
}

void playButton(int current) {
    int tonePosition;

    for (int i = 0; i < tonePairs; ++i) {
      if(toneA[i] == current || toneB[i] == current) {
        tonePosition = i;
      }
    }

    tone(speakerPin, notes[0][tonePosition], noteDuration);
    delay(150);
    noTone(speakerPin);
    tone(speakerPin, notes[1][tonePosition], noteDuration);
    delay(150);
    noTone(speakerPin);

}

//from toneMelody example, plays melody when you complete all the matches
void playWin() {
// notes in the melody:
int melody[] = {NOTE_C4,NOTE_G3,NOTE_G3,NOTE_A3,NOTE_G3,0,NOTE_B3,NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4};

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(speakerPin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin);
  }
}

//play sequence of notes when two buttons don't match
void playFail() {
  int noteDuration = 150; 
  int pauseBetweenNotes = 50; 
  int notes[] = {NOTE_G5, NOTE_E5,NOTE_C5 };
  for (int i = 0; i < 3; i++) {
    tone(speakerPin, notes[i], noteDuration);
    delay(pauseBetweenNotes);
    noTone(speakerPin);
    }
}

//play sequence of notes when two buttons match
void playCorrect() {
  int noteDuration = 150;
  int pauseBetweenNotes = 50;
  int notes[] = {NOTE_G5, NOTE_B5,NOTE_D6, NOTE_G6 };

  for (int i = 0; i < 3; i++) {
    tone(speakerPin, notes[i], noteDuration);
    delay(pauseBetweenNotes);
    noTone(speakerPin);
  }
}
