#include "Input.h"
#include "Motors.h"
#include "IMU.h"

void setup() {
  Serial.begin(9600);
  beginInput();
  beginMotors();
  beginIMU();
}

void loop() {
  updateInput();
  updateIMU(inputs[CH1],inputs[CH2],inputs[CH3],inputs[CH4]);
  motorInput(imuOutput[CH1],imuOutput[CH2],imuOutput[CH3],imuOutput[CH4]);
  Serial.print("Ch1: ");
  Serial.print(imuOutput[0]);
  Serial.print(" | Ch2: ");
  Serial.print(imuOutput[1]);
  Serial.print(" | Ch3: ");
  Serial.print(imuOutput[2]);
  Serial.print(" | Ch4: ");
  Serial.println(imuOutput[3]);
}
