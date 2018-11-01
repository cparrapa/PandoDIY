#include <Servo.h>
#include <Otto.h>
#include "Gyro.h"
//#include "GoBLE.h"
MaxMatrix ledmatrix = MaxMatrix(12,10,11, 1); //PIN12=DIN, PIN10=CS, PIN11=CLK

Otto Otto;  // This is Otto!

byte dato;  // To store the char sent by the app
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         ---------------
        |   |_|   |_|   |
        |---------------|
  YR 3==> |               | <== YL 2
         ---------------
            ||     ||
  RR 9==>   -----   ------  <== RL 8
         |-----   ------|
*/
#define PIN_YL 2 //servo[2]
#define PIN_YR 4 //servo[3]
#define PIN_RL 7 //servo[4]
#define PIN_RR 8 //servo[5]

#define TOUCH_PIN A0
#define NoiseSensor_PIN A1
int touchVal = 0;
int noiseVal = 0;

Gyro gyro;

//GoBLE Goble(Serial);// init the bluetooth Serial port
// Bluno default port - Serial

/*SOUNDS******************
   S_connection  S_disconnection  S_buttonPushed S_mode1 S_mode2 S_mode3 S_surprise S_OhOoh  S_OhOoh2  S_cuddly
   S_sleeping  S_happy S_superHappy S_happy_short S_sad S_confused S_fart1 S_fart2  S_fart3
*/

/*MOVEMENTS LIST**************
   dir=1---> FORWARD/LEFT
   dir=-1---> BACKWARD/RIGTH
   T : amount of movement. HIGHER VALUE SLOWER MOVEMENT usually 1000 (from 600 to 1400)
   h: height of mov. around 20
     jump(steps=1, int T = 2000);
     walk(steps, T, dir);
     turn(steps, T, dir);
     bend (steps, T, dir); //usually steps =1, T=2000
     shakeLeg (steps, T, dir);
     updown(steps, T, HEIGHT);
     swing(steps, T, HEIGHT);
     tiptoeSwing(steps, T, HEIGHT);
     jitter(steps, T, HEIGHT); (small T)
     ascendingTurn(steps, T, HEIGHT);
     moonwalker(steps, T, HEIGHT,dir);
     crusaito(steps, T, HEIGHT,dir);
     flapping(steps, T, HEIGHT,dir);

  /*GESTURES LIST***************
  OttoHappy OttoSuperHappy  OttoSad   OttoSleeping  OttoFart  OttoConfused OttoLove  OttoAngry
  OttoFretful OttoMagic  OttoWave  OttoVictory  OttoFail*/
unsigned long int rock_symbol =    0b00000000001100011110011110001100;
unsigned long int paper_symbol =   0b00011110010010010010010010011110;
unsigned long int scissors_symbol = 0b00000010010100001000010100000010;
///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup() {

  Serial.begin(115200); //setup your bluetooth module to match this baudrate (or change it here)

  gyro.begin();

  pinMode(TOUCH_PIN, INPUT);
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, NoiseSensor_PIN);
  ledmatrix.init();   //Starting up LED matrix display
  ledmatrix.setIntensity(10);
  Otto.sing(S_connection); // Otto wake up!
  Otto.home();
  delay(50);
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {

  gyro.update();
  Serial.read();
    Serial.print("X:");
    Serial.print(gyro.getAngleX());
    Serial.print(" Y:");
    Serial.print(gyro.getAngleY());
    Serial.print(" Z:");
    Serial.println(gyro.getAngleZ());
  delay(10);

  if ((abs(gyro.getAngleX()) > 50 && abs(gyro.getAngleX() < 80)) || (abs(gyro.getAngleY()) > 50 && abs(gyro.getAngleY() < 80)))
  {
    
    Otto.playGesture(OttoHappy);
    Otto.putMouth(interrogation);
    delay(1000);
  }

    if(((gyro.getAngleX() > -10) && (gyro.getAngleX() < -3)) && ((gyro.getAngleY() > -10) && (gyro.getAngleY() < -3)))
    {
     Otto.playGesture(OttoConfused);
     }

  // testAllSongs();

  // test touch sensor
  touchVal = digitalRead(TOUCH_PIN);
  if (touchVal == HIGH) {
    Otto.playGesture(OttoLove);
    delay(10);
    touchVal = !touchVal;
  }

  // test noise sensor
  noiseVal = Otto.getNoise();
  delay(50);
  Serial.println(noiseVal);
  if (noiseVal > 30) {
    Otto.home();
    Otto.putAnimationMouth(littleUuh, 0);
    Otto.bendTones (100, 200, 1.04, 10, 10);
    delay (100);
    Otto.putAnimationMouth(dreamMouth, 0);
/*   Otto.putMouth(zero);
    delay(100);
    Otto.putMouth(one);
    delay(100);
    Otto.putMouth(two);
    delay(100);
    Otto.putMouth(3);
    delay(100);
    Otto.putMouth(four);
    delay(100);
    Otto.putMouth(five);
    delay(100);
    Otto.putMouth(6);
    delay(100);
    Otto.putMouth(8);
    delay(100);
    Otto.putMouth(9);
    delay(100);
    Otto.putMouth(smile);
    delay(100);
    Otto.putMouth(happyOpen);
    delay(100);
    Otto.putMouth(happyClosed);
    delay(100);
    Otto.putMouth(heart);
    delay(100);
    Otto.putMouth(tongueOut);
    delay(100);
    Otto.putMouth(vamp1);
    delay(100);
    Otto.putMouth(vamp2);
    delay(100);
    Otto.putMouth(thunder);
    delay(100);
    Otto.putAnimationMouth(dreamMouth, 0);
    delay(100);
    Otto.putMouth(lineMouth);
    delay(100);
    Otto.putMouth(smallSurprise);
    delay(100);
    Otto.putMouth(okMouth);
    delay(100);
     Otto.putMouth(rock_symbol, 0);
     delay(100);
    Otto.putMouth(scissors_symbol, 0);
    delay(100);
    Otto.putMouth(paper_symbol, 0);
    delay(100);
    Otto.putMouth(xMouth);
    delay(100);
    Otto.putMouth(culito);
    Otto.putMouth(angry);
    delay(100);
*/
    noiseVal = 0;
  }
}


// test function
void testAllSongs() {
  Otto.sing(S_connection);
  delay(2000);
  Otto.sing(S_disconnection);
  delay(2000);
  Otto.sing(S_buttonPushed);
  delay(2000);
  Otto.sing(S_mode1);
  delay(2000);
  Otto.sing(S_mode2);
  delay(2000);
  Otto.sing(S_mode3);
  delay(2000);
  Otto.sing(S_surprise);
  delay(2000);
  Otto.sing(S_OhOoh);
  delay(2000);
  Otto.sing(S_OhOoh2);
  delay(2000);
  Otto.sing(S_cuddly);
  delay(2000);
  Otto.sing(S_sleeping);
  delay(2000);
  Otto.sing(S_happy);
  delay(2000);
  Otto.sing(S_superHappy);
  delay(2000);
  Otto.sing(S_happy_short);
  delay(2000);
  Otto.sing(S_sad);
  delay(2000);
  Otto.sing(S_confused);
  delay(2000);
  Otto.sing(S_fart1);
  delay(2000);
  Otto.sing(S_fart2);
  delay(2000);
  Otto.sing(S_fart3);
  delay(2000);
}
