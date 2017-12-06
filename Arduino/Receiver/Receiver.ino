#include <PinChangeInt.h>

#define PIN_COUNT 2
#define PIN_BASE 8

//RANGES (Min, Mid, Max):
//Aileron (Ch1, 2): 1088, 1500, 1912
//Elevator (Ch2, 3): 1080, 1500, 1904
//Throttle (Ch3, 8): 1096, 1504, 1912
//Rudder (Ch4, 9): 1088, 1496, 1912

//PinChangeInt pins on channels 3 and 4
volatile unsigned long ch34Val[PIN_COUNT] = {0,0};
volatile unsigned long ch34Prev[PIN_COUNT] = {0,0};
volatile uint8_t lastPin;

//external intterrupt pins on channels 1 and 2
volatile unsigned long ch1Val = 0, ch2Val = 0;
volatile unsigned long ch1Prev = 0, ch2Prev = 0;

void rising()
{
  lastPin=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(lastPin, &falling, FALLING);
  ch34Prev[lastPin-PIN_BASE] = micros();
}
 
void falling() {
  lastPin=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(lastPin, &rising, RISING);
  ch34Val[lastPin-PIN_BASE] = micros()-ch34Prev[lastPin-PIN_BASE];
}

void ch1Rise()
{
  ch1Prev = micros();
  attachInterrupt(digitalPinToInterrupt(2),&ch1Fall,FALLING);
}

void ch1Fall()
{
  ch1Val = micros()-ch1Prev;
  attachInterrupt(digitalPinToInterrupt(2),&ch1Rise,RISING);
}

void ch2Rise()
{
  ch2Prev = micros();
  attachInterrupt(digitalPinToInterrupt(3),&ch2Fall,FALLING);
}

void ch2Fall()
{
  ch2Val = micros()-ch2Prev;
  attachInterrupt(digitalPinToInterrupt(3),&ch2Rise,RISING);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Serial initialized!");
  for (int i = PIN_BASE; i<PIN_COUNT+PIN_BASE; ++i)
  {
    pinMode(i, INPUT); digitalWrite(i, HIGH);
    PCintPort::attachInterrupt(i, &rising, RISING);
  }
  pinMode(2,INPUT); digitalWrite(2,HIGH);
  pinMode(3,INPUT); digitalWrite(3,HIGH);
  attachInterrupt(digitalPinToInterrupt(2),&ch1Rise,RISING);
  attachInterrupt(digitalPinToInterrupt(3),&ch2Rise,RISING);
}

void loop() {
  Serial.print("1: ");
  Serial.print(ch1Val);
  Serial.print("  |  2: ");
  Serial.print(ch2Val);
  Serial.print("  |  3: ");
  Serial.print(ch34Val[0]);
  Serial.print("  |  4: ");
  Serial.println(ch34Val[1]);
  delay(100);
}
