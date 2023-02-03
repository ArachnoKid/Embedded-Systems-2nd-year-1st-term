/************************************************************/
/* hal.cpp                                                  */
/*                                                          */
/* Hardware Abstraction Layer (HAL) implementation          */
/* Prottoy Chakraborty / P2719231 / 11th Octber 2022        */
/************************************************************/

#include "hal.h"

void HAL_gpioInt() {
  DDRD |= (AllLEDOff);
  DDRD |= (AllLEDFunc);
  
  HAL_SETUP_SW1;
  HAL_SETUP_SW2;

  HAL_SEG_DPon;
  HAL_SEG_DPoff;

  DDRB |= (LATCH | DATA | CLOCK);
};

void accelerometer(int* AccX, int* AccY, int* AccZ) {
  Wire.beginTransmission(mpu_address);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_address, 6, true);
  *AccX = Wire.read() << 8 | Wire.read();
  *AccY = Wire.read() << 8 | Wire.read();
  *AccZ = Wire.read() << 8 | Wire.read();
}
