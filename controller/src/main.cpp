#include <Arduino.h>
#include <TM1637Display.h>
#include <SoftwareSerial.h>

#define CLK 2
#define DIO 4
#define RX 11
#define TX 10
#define BUTTON_PIN 3
#define STATUS_PIN 9
#define COUNTDOWN_NUM 60

TM1637Display display(CLK, DIO);
SoftwareSerial HC12(RX, TX);

volatile int state = 0;
int brightness = 0;   
int fadeAmount = 5;    
int startButton = 0;
void countdown_timer();
void ready_indicator();
void idle_indicator();
void updateState();


void setup() {
  display.setBrightness(0x0f);
  attachInterrupt(digitalPinToInterrupt(3), updateState, FALLING);
  pinMode(STATUS_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  HC12.begin(9600);
}

void loop() {
	switch(state) {
		case 0: // IDLE
		 idle_indicator();
		 break;

		case 1: // COUNTDOWN
		  HC12.write('0'); // Timer start
          ready_indicator();
          countdown_timer();
		  break; 

		case 2: // ABORT
		  HC12.write('1');
		  display.clear();
          state = 0;
		  break;
	        
		case 3: // LAUNCH
		  HC12.write('2'); // Timer done
		  state = 0;
		  break;

		default:
		  break;
	}

}


void ready_indicator() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(STATUS_PIN, HIGH);
    delay(100);
    digitalWrite(STATUS_PIN, LOW);
    delay(50);
  }
}

void idle_indicator() {
  analogWrite(STATUS_PIN, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}

void countdown_timer() {
  int i = COUNTDOWN_NUM;
  while (i >= 0) {
    i--;
    display.showNumberDecEx(i, (0x80 >> 1), true);	  
    delay(1000);
   if (i == 0) { // If T-0 move to state 3
    state = 3;
    break;
   }
   if (state > 1) {
   break;
   }
  }

}

void updateState() {
 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 if (interrupt_time - last_interrupt_time > 200) {
      if (state < 2) {
	      state++;
      }
 }
 last_interrupt_time = interrupt_time;
}
