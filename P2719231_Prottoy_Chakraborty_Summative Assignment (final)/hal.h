/************************************************************/
/* hal.h                                                    */
/*                                                          */
/* Hardware Abstraction Layer (HAL) definitions             */
/* Prottoy Chakraborty / P2719231 / 11th Octber 2022        */
/************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

#include <Arduino.h>
#include <Wire.h>
#define mpu_address 0x68

//Orientation
#define ORIENTATION_FLAT                  0
#define ORIENTATION_BASEUP                1
#define ORIENTATION_LANDSCAPE             2
#define ORIENTATION_UPSIDEDOWN_LANDSCAPE  3
#define ORIENTATION_LEFTPORTAIT           4
#define ORIENTATION_RIGHTPORTRAIT         5

//LEDs
#define Red1   B00000100
#define Amber1 B00001000
#define Green1 B00010000
#define Red2   B00100000
#define Amber2 B01000000
#define Green2 B10000000
#define AllLEDOff B00000000
#define AllLEDFunc B11111100

// traffic light sequence
#define HAL_TL_Seq0 PORTD = Amber1 | Amber2
#define HAL_TL_Seq1 PORTD = Red1 | Red2
#define HAL_TL_Seq2 PORTD = Red1 | Amber1 | Red2
#define HAL_TL_Seq3 PORTD = Green1 | Red2
#define HAL_TL_Seq4 PORTD = Amber1 | Red2
#define HAL_TL_Seq5 PORTD = Red1 | Red2
#define HAL_TL_Seq6 PORTD = Red1 | Red2 | Amber2
#define HAL_TL_Seq7 PORTD = Red1 | Green2
#define HAL_TL_Seq8 PORTD = Red1 | Amber2

//Traffic Lights set 1
#define HAL_TLS1_Seq0 PORTD = Amber1
#define HAL_TLS1_Seq1 PORTD = Red1
#define HAL_TLS1_Seq2 PORTD = Red1 | Amber1 
#define HAL_TLS1_Seq3 PORTD = Green1 

//Traffic Lights set 2
#define HAL_TLS2_Seq0 PORTD = Amber2
#define HAL_TLS2_Seq1 PORTD = Red2
#define HAL_TLS2_Seq2 PORTD = Red2 | Amber2 
#define HAL_TLS2_Seq3 PORTD = Green2

//button1
#define HAL_BUTTON1 B00000001  //button pin
#define HAL_SW1_RELEASED (PINC & HAL_BUTTON1)
#define HAL_SW1_PRESSED !HAL_SW1_RELEASED
#define HAL_SETUP_SW1  DDRC &= ~HAL_BUTTON1; PORTC |= HAL_BUTTON1

//button2
#define HAL_BUTTON2 B00000010  //button pin
#define HAL_SW2_RELEASED (PINC & HAL_BUTTON2)
#define HAL_SW2_PRESSED !HAL_SW2_RELEASED
#define HAL_SETUP_SW2   DDRC &= ~HAL_BUTTON2;  PORTC |= HAL_BUTTON2

//Heartbeat
#define DATA B00000001
#define LATCH B00100000
#define CLOCK B00010000
#define DLCoff B00000000
#define SEG_DP 0b10000000

#define HAL_SEG_DPon SEG_DP
#define HAL_SEG_DPoff B00000000

//button states
typedef enum {
  NOT_PRESSED,
  PARTIAL_PRESS,
  DEBOUNCED_PRESS
} switch_state_t;

#define debounce 300  // debounce duration

void HAL_gpioInt();

//7seg
#define SEGA  B00000001
#define SEGB  B00000010
#define SEGC  B00000100
#define SEGD  B00001000
#define SEGE  B00010000
#define SEGF  B00100000
#define SEGG  B01000000
//#define SEGDP B10000000

//Characters
#define CHAR0  (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF)
#define CHAR1  (SEGB | SEGC)
#define CHAR2  (SEGA | SEGB | SEGD | SEGE | SEGG)
#define CHAR3  (SEGA | SEGB | SEGC | SEGD | SEGG)
#define CHAR4  (SEGB | SEGC | SEGF | SEGG)
#define CHAR5  (SEGA | SEGC | SEGD | SEGF | SEGG)
#define CHAR6  (SEGA | SEGC | SEGD | SEGE | SEGF| SEGG)
#define CHAR7  (SEGA | SEGB | SEGC)
#define CHAR8  (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG)
#define CHAR9  (SEGA | SEGB | SEGC | SEGD | SEGF | SEGG)
#define CHARA  (SEGA | SEGB | SEGC | SEGE | SEGF | SEGG)
#define CHARB  (SEGC | SEGD | SEGE | SEGF | SEGG)
#define CHARC  (SEGA | SEGD | SEGE | SEGF)
#define CHARD  (SEGB | SEGC | SEGD | SEGE | SEGG)
#define CHARE  (SEGA | SEGD | SEGE | SEGF | SEGG)
#define CHARF  (SEGA | SEGE | SEGF | SEGG)
#define CHARL  (SEGD | SEGE | SEGF)
#define CHARUP (SEGA | SEGB | SEGC | SEGE | SEGF )
#define CHARLH (SEGD | SEGE)
#define CHARRH (SEGE | SEGG)
#define CHART  (SEGD | SEGE | SEGF | SEGG)

const byte chars[16] = { CHAR0, CHAR1, CHAR2, CHAR3, CHAR4, CHAR5, CHAR6, CHAR7, CHAR8, CHAR9, CHARA, CHARB, CHARC, CHARD, CHARE, CHARF };
const byte accel_chars[6] = {CHARF, CHARB, CHARL, CHARUP, CHARLH, CHARRH};
const byte t = CHART;
//accelerometer
void accelerometer(int* AccX, int* AccY, int* AccZ);

#endif
