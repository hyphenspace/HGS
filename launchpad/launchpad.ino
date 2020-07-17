/**
  Purpose: Code that powers the launchpad computer.

  @author Akil M Hylton
  @version 0.1 7/17/20
*/

#include <Servo.h>

#define COUNTDOWN_TIME    10000     
#define R_LED_A           5
#define W_LED_A           6

Servo clamp_A;
Servo clamp_B;
Servo clamp_C;
Servo clamp_D;

char incomingByte;
unsigned long timerStart = 0; // the time the delay started
bool timerRunning = false; // true if still waiting for delay to finish

void setup() {
  Serial.begin(9600);
  pinMode(R_LED_A, OUTPUT);
  pinMode(W_LED_A, OUTPUT);
  clamp_A.attach(10);
  clamp_B.attach(11);
  clamp_C.attach(9);
  clamp_D.attach(3);

  timerStart = millis();   // start timer
  timerRunning = true; // not finished yet
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == '1') {
       Serial.println("Testing Lights...");
       hold_down_go_lights();
       Serial.println("Lights testing completed.");
       delay(500);
       Serial.println("Testing hold down clamps...");
       test_hold_down_clamps();
       Serial.println("Hold down clamps testing completed,");
      }
      
    if (incomingByte == '2') {
      Serial.println("Starting hold down sequence");
      hold_down_sequence();
      }
      
  }

}

void test_hold_down_clamps() {
 delay(750);
 clamp_A.write(15);
 clamp_B.write(15);
 clamp_C.write(15);
 clamp_D.write(15);
 delay(7000);
 clamp_A.write(120);
 clamp_B.write(120);
 clamp_C.write(120);
 clamp_D.write(120);
 delay(500);  
}


void hold_down_go_lights() {
  for (int i = 0; i < 5; i++) {
  digitalWrite(R_LED_A, HIGH);
  digitalWrite(W_LED_A, HIGH);
  delay(750);
  digitalWrite(R_LED_A, LOW);
  digitalWrite(W_LED_A, LOW);
  delay(750);
  } 
 }

void hold_down_idle_lights() {
  digitalWrite(R_LED_A, HIGH);
  digitalWrite(W_LED_A, HIGH);
  delay(1000);
  digitalWrite(R_LED_A, LOW);
  digitalWrite(W_LED_A, LOW);
  delay(1000);
 }

void hold_down_sequence() {
  // check if delay has timed out after 10sec == 10000mS
  if (timerRunning && ((millis() - timerStart) >= COUNTDOWN_TIME)) {
    timerRunning = false;  // prevent this code being run more then once
    Serial.println("Transition into launch sequence...");
    delay(3000);
  }
  hold_down_idle_lights();
}
