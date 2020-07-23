#include <Arduino.h>
#include <TM1637Display.h>
#include <SoftwareSerial.h>

#define CLK 2
#define DIO 3
#define RX 5
#define TX 6
#define BUTTON_PIN 8
#define STATUS_PIN 9
#define COUNTDOWN_NUM 60

TM1637Display display(CLK, DIO);
SoftwareSerial HC12(RX, TX);

int startButton = 0;
void countdown_timer();
void status_indicator();

void setup() {
  // put your setup code here, to run once:
  pinMode(STATUS_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  HC12.begin(9600);
}

void loop() {
  startButton = digitalRead(BUTTON_PIN);
  if (startButton == HIGH) {
    HC12.write('1'); // Timer beginning 
    status_indicator();
    countdown_timer();
    HC12.write('0'); // Timer ending 
  } else {
    // Button not pressed
    digitalWrite(STATUS_PIN, LOW);
  }
}

void countdown_timer() {
  display.setBrightness(0x0f);

  for (int i = COUNTDOWN_NUM; i > 0; i--) {
    display.showNumberDec(i);
    delay(1000);
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