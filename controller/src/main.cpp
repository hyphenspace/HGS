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
int startButton = 0;
void countdown_timer();
void status_indicator();
void updateState();

void setup() {
  display.setBrightness(0x0f);
  attachInterrupt(digitalPinToInterrupt(3), updateState, FALLING);
  pinMode(STATUS_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() {
	switch(state) {
		case 0:
		  Serial.println("READY! YOU CAN NOW PUSH THE BUTTON.");
		  break;

		case 1:
		  HC12.write('1'); // Timer beginning
                  status_indicator();
                  countdown_timer();
                  HC12.write('0'); // Timer ending
		
		case 2:
                  // Button not pressed
                  Serial.println("STOP");
                  display.clear();
                  state = 0;
                  break;
	}

}


void status_indicator() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(STATUS_PIN, HIGH);
    delay(100);
    digitalWrite(STATUS_PIN, LOW);
    delay(50);
  }
}

void countdown_timer() {
  int i = COUNTDOWN_NUM;
  while (i > 0) {
    display.showNumberDec(i);	  
    i--;
    delay(1000);
   if (state > 1) {
   break;
   }
  }

}

void updateState() {
   state++;
}
