/* Project Title: Tone Match
Katie Ballinger
DIGF 2B03 Physical Computing
OCAD University
Created on April 8th 2014

Description: 

Based on:
Blink, Public Domain, http://www.arduino.cc/en/Tutorial/Blink
Button, DojoDave, http://www.arduino.cc/en/Tutorial/Button
DigitalInputPullup, ScottFitzgerald, http://www.arduino.cc/en/Tutorial/InputPullupSerial
toneMelody, Tom Igoe, http://www.arduino.cc/en/Tutorial/Tone
Arrays, David A. Mellis, http://www.arduino.cc/en/Tutorial/Array
(Forum Topic Help), Rob Tillaart, http://forum.arduino.cc/index.php?topic=66681.0
toneGame, Katie Ballinger, https://github.com/KatieStarks/physical-computing/blob/master/toneGame.ino
*/
#include "pitches.h" //pitches library
int speakerPin = 11;
int ledPin = 12;

//array of notes
int notes[] = { NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5 };

bool waitForInput = false; //wait for player to push a button
int firstNote = 0; //hold the random number picked
int secondNote = 0; //hold the random number picked
int sensorVal = 0; //is it HIGH or LOW
int score = 0; //keep track of score up to 10
int firstButton = 0; //store first button pressed
int secondButton = 0; //store second button pressed

void setup(){
Serial.begin(9600); //initiates serial monitor

pinMode(speakerPin, OUTPUT);
pinMode(ledPin, OUTPUT);

for (int i = 2; i < 11; ++i)
{
  pinMode(i, INPUT_PULLUP);
}

playBoot();

}

void loop(){

//gives random note only when not waiting for input
  if(!waitForInput){
    delay(250);
    randomSeed(analogRead(0));
    firstNote = random(8);
    secondNote = random(8);

    digitalWrite(ledPin,HIGH);
    playNote(firstNote);
    delay(150);
    playNote(secondNote);
    digitalWrite(ledPin,LOW);

    waitForInput = true;
    Serial.println(firstNote + "and" + secondNote);

  } else{

    sensorVal = digitalRead(10);

    if (sensorVal == 0) {
      digitalWrite(ledPin,HIGH);
      playNote(firstNote);
      delay(150);
      playNote(secondNote);
      digitalWrite(ledPin,LOW);
    }

    for (int i = 2; i < 10; ++i)
    {
      sensorVal = digitalRead(i);

      if (sensorVal == 0) {

        playNote(i-2);

        if(firstButton == 0) {

          if ((i-2) == firstNote) {
            firstButton = i;
            Serial.println("First Right");
          }

        } else {

          firstButton = 0;

          if ((i-2) == secondNote) {

            delay(250);
            playCorrect();
            Serial.println("Second Right");
            waitForInput = false;
            score++;

          } else {
            Serial.println("Reset");
          }

        }
      }
    }

    if (score == 10) {
      playWin();
      score = 0;
      delay(1000);
      playBoot();
    }
  }
}

void playBoot(){
  int noteDuration = 300;
  int pauseBetweenNotes = 300;
  for (int i = 0; i < 8; i++) {
    tone(speakerPin, notes[i], noteDuration);
    delay(pauseBetweenNotes);
    noTone(speakerPin);
  }
}


void playNote(int currentNote) {
  int noteDuration = 500;
  int pauseBetweenNotes = 300;

  tone(speakerPin,notes[currentNote],noteDuration);
  delay(pauseBetweenNotes);
  noTone(speakerPin);
}

//play sequence of notes when two buttons match
void playCorrect() {
  int noteDuration = 150;
  int pauseBetweenNotes = 50;
  int notesCorrect[] = {NOTE_G5, NOTE_B5,NOTE_D6, NOTE_G6 };

  for (int i = 0; i < 3; i++) {
    tone(speakerPin, notesCorrect[i], noteDuration);
    delay(pauseBetweenNotes);
    noTone(speakerPin);
  }
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
