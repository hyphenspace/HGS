#include <TM1637Display.h>
#include <SoftwareSerial.h>

#define CLK 2
#define DIO 3
#define COUNTDOWN_NUM 60 // 60 seconds


TM1637Display display(CLK, DIO);

const byte rxPin = 5;
const byte txPin = 6;
int button = 0;
int buttonPin = 8;
int statusLED = 9;

SoftwareSerial HC12(rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
pinMode(statusLED, OUTPUT);
pinMode(buttonPin, INPUT);
Serial.begin(9600);
HC12.begin(9600);
}

void loop() {
  
button = digitalRead(buttonPin);
 // put your main code here, to run repeatedly:
if(button == HIGH) {
  HC12.write('0');
  status_led(); // data has been sent.
  countdown_timer();
  HC12.write('1');
}
else {
  digitalWrite(statusLED, LOW); // on no button press 
  }
}

void status_led() {
  for(int i = 0; i < 5; i++) {
  digitalWrite(statusLED, HIGH);
  delay(100);
  digitalWrite(statusLED, LOW);
  delay(50);
  }
 }

void countdown_timer() {
  display.setBrightness(0x0f);

  for(int i = COUNTDOWN_NUM; i >= 0; i--) {
   display.showNumberDec(i);
    delay(1000);
  } 
 }
