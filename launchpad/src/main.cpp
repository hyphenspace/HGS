#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define IGNITION_PYRO 2 
#define LED_A 10
#define LED_B 9
#define LED_C 8
#define LED_D 7
#define RX 5
#define TX 6

char incomingData;
SoftwareSerial HC12(RX, TX);

Servo clamp_A;
Servo clamp_B;
Servo clamp_C;
Servo clamp_D;

void idle_lights();
void go_lights();
void ignition_sequence();
void hold_down_go();
void hold_down_idle();

void setup() {
  // put your setup code here, to run once:
  HC12.begin(9600);
  Serial.begin(9600);
  pinMode(IGNITION_PYRO, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  clamp_A.attach(3);
  clamp_B.attach(4);
  clamp_C.attach(11);
  clamp_D.attach(12);
}

void loop() {
  while (HC12.available()) {
    incomingData = HC12.read();
    int state = incomingData - 48;
    switch(state) {
	case 0:
      		go_lights();
		hold_down_idle();
		break;

	case 1:
		go_lights();
		hold_down_go();
		ignition_sequence();
		break;

	default:
    	  	break;
    }
  }
}

void hold_down_idle() {
  delay(500);
  clamp_A.write(15);
  clamp_B.write(15);
  clamp_C.write(15);
  clamp_D.write(15);
}


void hold_down_go() {
  delay(500);
  clamp_A.write(120);
  clamp_B.write(120);
  clamp_C.write(120);
  clamp_D.write(120);
}


void ignition_sequence() {
  digitalWrite(IGNITION_PYRO, HIGH);
  delay(500);
  digitalWrite(IGNITION_PYRO, LOW);
  delay(250);
}

void go_lights() { 
for (int i = 0; i < 15; i++) {
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_C, HIGH);
  digitalWrite(LED_D, HIGH);
  delay(250);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_C, LOW);
  digitalWrite(LED_D, LOW);
  delay(250);  
 }
}

void idle_lights() {
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_C, HIGH);
  digitalWrite(LED_D, HIGH);
  delay(1000);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_C, LOW);
  digitalWrite(LED_D, LOW);
  delay(1000);  
 }
