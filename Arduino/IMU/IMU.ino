#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//Yaw - X (CW = Positive)
//Roll - Z (Right = Positive)
//Pitch - Y (Forward = Positive)
Adafruit_BNO055 ahrs = Adafruit_BNO055(55);
int rstC = 0;
float yOff = 0, zOff = 0;

void setup() {
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
  Serial.begin(9600);
  delay(100);
  
  if (!ahrs.begin())
  {
    Serial.print("Failed to initialize IMU");
    while (1){}
  }
  int i = 0;

  for (; i<10; ++i)
  {
    sensors_event_t event;
    ahrs.getEvent(&event);
    yOff += event.orientation.y;
    zOff += event.orientation.z;
    delay(100);
  }
  yOff /= 10;
  zOff /= 10;
}

void loop() {
  sensors_event_t event;
  ahrs.getEvent(&event);
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y-yOff, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z-zOff, 4);
  Serial.println("");

  rstC++;
  if (rstC>100)
  {
    rstC = 0;
    digitalWrite(7,HIGH);
    delay(10);
    digitalWrite(7,LOW);
  }
  delay(100);
}
