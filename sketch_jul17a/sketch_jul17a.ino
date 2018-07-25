#include <LiquidCrystal.h>

#include <pitches.h>

#include "pitches.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// setup hw
int SPEAKER_PIN = 10;
int SPEAKER = SPEAKER_PIN;
int lm35Pin = A0;
// end of setuphw

// code related to the melody itself
#define NUM_OF_NOTES 28
int   NOTE_SEQ[NUM_OF_NOTES] = {
      NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5, PAUSE,
      NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_G5, NOTE_F5, PAUSE,
      NOTE_C5, NOTE_C5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5, NOTE_D5, PAUSE,
      NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_F5 };
/* 
 * beware that I choosed to reproduce pauses in milliseconds.
 */
int   NOTE_LEN[NUM_OF_NOTES]   = {
      4,2,8,8,8,16,   50,     //50  millis for the first pause
      4,2,8,8,8,16,   100,    //100 millis for the second pause
      4,2,8,8,8,8,16, 150,    //150 millis for the third pause
      4,2,8,8,8,20 };

/*
 * increase or reduce this value if you want to speed up or slow down the song.
 * This won't affect pause duration, which is defined in the array right above 
 * and expressed in milliseconds
 */
int   TEMPO = 65;
float derece;
float analog;
float dereceilk;

void playNote(int pitch,int duration) {
    tone( SPEAKER, pitch);
    delay( duration);
    noTone( SPEAKER);
}
// end of the code related to the melody itself

/*
 * arduino's standard setup() and loop() methods section. I had no need to repe
 * at so I put it in setup()
 */

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {
  
  analog = analogRead(lm35Pin);
  analog = (analog / 1024.0)*5000;
  derece = analog / 10.0;
  Serial.println(derece);
  lcd.begin(16, 2);
  lcd.print("MUMU UFLER MISIN");
  delay(500);
    if( derece < 40){
        digitalWrite(13, LOW);
        lcd.begin(16, 2);
        lcd.print("  MUTLU YILLAR");
        lcd.setCursor(0, 1);
        lcd.print("     SEDA =)");
        for (int i = 0; i < NUM_OF_NOTES; i++){
            if ( NOTE_SEQ[i] != PAUSE) {
                  playNote( NOTE_SEQ[i], NOTE_LEN[i] * TEMPO);
                 // delay after note reproduction following TEMPO variable's diktat
                  delay( TEMPO);
              } 
              else 
              {
                  // delay if this is a pause. (it will be in millis, check NOTE_LEN)
                  delay( NOTE_LEN[i]);
              }
                                              }
                      }
    else{
      digitalWrite(13,HIGH);
      lcd.clear();
      }          
            }
