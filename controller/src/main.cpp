#include <Arduino.h>
#include <TM1637Display.h>
#include <SoftwareSerial.h>

#define CLK 2
#define DIO 4
#define RX 11
#define TX 10
#define BUTTON_PIN 3
#define STATUS_PIN 9
#define COUNTDOWN_NUM 59


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
		  HC12.write('0'); // Timer beginning
                  status_indicator();
                  countdown_timer();
		  break; 

		case 2:
                  Serial.println("STOP");
                  display.clear();
                  state = 0;
                  break;
	        
		case 3:
		  HC12.write('1'); // Timer ending
		  state = 0;
		  break;

		default:
		  break;
	}

	Serial.print("state = ");
	Serial.println(state);
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
  while (i >= 0) {
    i--;
    display.showNumberDec(i);	  
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
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200) {
      if (state < 2) {
	 state++;
      }
 }
 last_interrupt_time = interrupt_time;
}
