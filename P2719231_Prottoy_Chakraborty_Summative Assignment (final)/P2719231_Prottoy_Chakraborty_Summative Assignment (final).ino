/************************************************************/
/* form1.ino                                                */
/*                                                          */
/* Formative Assignment 1: Traffic Lights Sequencer         */
/* Prottoy Chakraborty / P2719231 / 11th Octber 2022        */
/************************************************************/

#include "hal.h"

#include "Concurrent.h"

Concurrent tlightsequal;
Concurrent tlightsSet1;
Concurrent tlightsSet2;
Concurrent tlights;
Concurrent switch1;
Concurrent switch2;
Concurrent heartbeat;
Concurrent counter;
Concurrent scheduler;
Concurrent accel;

switch_state_t B1_state;  // buttons state variables
switch_state_t B2_state;

#define threshold 12000

int orientation;

#define DTA 8
#define CLCK 12
#define LTCH 13

byte hb = 0, disp = 0, dispc = 0;
byte tl = 0, dispt = 0;

void _7seg(byte d) {
  shiftOut(DTA, CLCK, MSBFIRST, d);
  digitalWrite(LTCH, HIGH);
  digitalWrite(LTCH, LOW);
}

void setup() {
  // put your setup code here, to run once:
  HAL_gpioInt();
  Serial.begin(115200);
  tlightsequal.setModuleDelay(45);
  tlightsequal.setRunning(false);
  tlightsSet1.setModuleDelay(40);
  tlightsSet1.setRunning(false);
  tlightsSet2.setModuleDelay(35);
  tlightsSet2.setRunning(false);
  tlights.setModuleDelay(50);
  tlights.setRunning(false);
  switch1.setModuleDelay(15);
  switch1.setRunning(true);
  switch2.setModuleDelay(30);
  switch2.setRunning(true);
  heartbeat.setModuleDelay(270);
  heartbeat.setRunning(true);
  counter.setModuleDelay(25);
  counter.setRunning(false);
  accel.setModuleDelay(333);
  accel.setRunning(false);
  scheduler.setModuleDelay(10);
  scheduler.setRunning(true);

  Wire.begin();
  Wire.beginTransmission(mpu_address);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
}

void loop() {

  //traffic lights equal priority
  if (tlightsequal.actionTask()) {
    static unsigned long module_delay;
    static unsigned char state = NOT_PRESSED;

    switch (state) {
      case 0:
        HAL_TL_Seq0;
        module_delay = 2000;
        state = 1;
        break;
      case 1:
        HAL_TL_Seq1;
        module_delay = 1000;
        state = 2;
        break;
      case 2:
        HAL_TL_Seq2;
        module_delay = 1000;
        state = 3;
        break;
      case 3:
        HAL_TL_Seq3;
        module_delay = 6000;
        state = 4;
        break;
      case 4:
        HAL_TL_Seq4;
        module_delay = 2000;
        state = 5;
        break;
      case 5:
        HAL_TL_Seq5;
        module_delay = 1000;
        state = 6;
        break;
      case 6:
        HAL_TL_Seq6;
        module_delay = 1000;
        state = 7;
        break;
      case 7:
        HAL_TL_Seq7;
        module_delay = 6000;
        state = 1;
        break;
    }
    tlightsequal.setModuleDelay(module_delay);
  }

  //traffic lights set 1
  if (tlightsSet1.actionTask()) {
    static unsigned long module_delay;
    static unsigned char state = NOT_PRESSED;

    switch (state) {
      case 0:
        HAL_TLS1_Seq0;
        module_delay = 2000;
        state = 1;
        break;
      case 1:
        HAL_TLS1_Seq1;
        module_delay = 1000;
        state = 2;
        break;
      case 2:
        HAL_TLS1_Seq2;
        module_delay = 1000;
        state = 3;
        break;
      case 3:
        HAL_TLS1_Seq3;
        module_delay = 8000;
        state = 4;
        break;
      case 4:
        HAL_TLS1_Seq0;
        module_delay = 2000;
        state = 5;
        break;
      case 5:
        HAL_TLS1_Seq1;
        module_delay = 8000;
        state = 1;
        break;
    }
    tlightsSet1.setModuleDelay(module_delay);
  }

  //traffic lights set 2
  if (tlightsSet2.actionTask()) {
    static unsigned long module_delay;
    static unsigned char state = NOT_PRESSED;

    switch (state) {
      case 0:
        HAL_TLS2_Seq0;
        module_delay = 2000;
        state = 1;
        break;
      case 1:
        HAL_TLS2_Seq1;
        module_delay = 9000;
        state = 2;
        break;
      case 2:
        HAL_TLS2_Seq2;
        module_delay = 1000;
        state = 3;
        break;
      case 3:
        HAL_TLS2_Seq3;
        module_delay = 8000;
        state = 4;
        break;
      case 4:
        HAL_TLS2_Seq0;
        module_delay = 2000;
        state = 1;
        break;
    }
    tlightsSet2.setModuleDelay(module_delay);
  }

  //traffic lights

  if (tlights.actionTask()) {
    static int priority = 0;

    Serial.print("TLights = ");
    Serial.println(priority);
    dispt = t;

    switch (priority) {
      case 0:
        tlightsequal.setRunning(true);
        tlightsSet1.setRunning(false);
        tlightsSet2.setRunning(false);
        if (B1_state == NOT_PRESSED) priority = 1;
        break;
      case 1:
        tlightsequal.setRunning(true);
        tlightsSet1.setRunning(false);
        tlightsSet2.setRunning(false);
        if (B1_state == DEBOUNCED_PRESS) priority = 2;
        break;
      case 2:
        tlightsequal.setRunning(false);
        tlightsSet1.setRunning(true);
        tlightsSet2.setRunning(true);
        if (B1_state == NOT_PRESSED) priority = 3;
        break;
      case 3:
        tlightsequal.setRunning(false);
        tlightsSet1.setRunning(true);
        tlightsSet2.setRunning(false);
        if (B1_state == DEBOUNCED_PRESS) priority = 4;
        break;
      case 4:
        tlightsequal.setRunning(false);
        tlightsSet1.setRunning(false);
        tlightsSet2.setRunning(true);
        if (B1_state == NOT_PRESSED) priority = 5;
        break;
      case 5:
        tlightsequal.setRunning(false);
        tlightsSet1.setRunning(false);
        tlightsSet2.setRunning(true);
        if (B1_state == DEBOUNCED_PRESS) priority = 0;
        break;
    }
  }

  //button1

  if (switch1.actionTask()) {
    static unsigned long debounce_count;
    static switch_state_t state;  // state variable for module 0

    switch (state) {
      case NOT_PRESSED:
        if (HAL_SW1_RELEASED) state = NOT_PRESSED;
        else {
          debounce_count = millis();
          state = PARTIAL_PRESS;
        }
        break;
      case PARTIAL_PRESS:
        if (HAL_SW1_RELEASED) state = NOT_PRESSED;
        else if ((millis() - debounce_count) < debounce) state = PARTIAL_PRESS;
        else state = DEBOUNCED_PRESS;
        break;
      case DEBOUNCED_PRESS:
        if (HAL_SW1_RELEASED) state = NOT_PRESSED;
        else state = DEBOUNCED_PRESS;
        break;

      default:
        state = NOT_PRESSED;
        break;
    }
    B1_state = state;
  }

  //button2

  if (switch2.actionTask()) {
    static unsigned long debounce_count;
    static switch_state_t state;  // state variable for module 0

    switch (state) {
      case NOT_PRESSED:
        if (HAL_SW2_RELEASED) state = NOT_PRESSED;
        else {
          debounce_count = millis();
          state = PARTIAL_PRESS;
        }
        break;
      case PARTIAL_PRESS:
        if (HAL_SW2_RELEASED) state = NOT_PRESSED;
        else if ((millis() - debounce_count) < debounce) state = PARTIAL_PRESS;
        else state = DEBOUNCED_PRESS;
        break;
      case DEBOUNCED_PRESS:
        if (HAL_SW2_RELEASED) state = NOT_PRESSED;
        else state = DEBOUNCED_PRESS;
        break;

      default:
        state = NOT_PRESSED;
        break;
    }
    B2_state = state;
  }

  //  HeartBeat
  if (heartbeat.actionTask()) {
    static unsigned long module_delay;
    static unsigned char state = NOT_PRESSED;

    switch (state) {
      case 0:
        hb = HAL_SEG_DPoff;
        state = 1;
        module_delay = 270;
        break;
      case 1:
        hb = HAL_SEG_DPon;
        state = 0;
        module_delay = 270;
        break;
    }
    _7seg(hb | disp);
  }

  // Button Counter
  if (counter.actionTask()) {
    static int count = 0;
    static int state = 0;

    dispc = chars[count % 16];
    switch (state) {
      case 0:
        if (B1_state == DEBOUNCED_PRESS) {
          count++;
          state = 1;
        }
        break;
      case 1:
        if (B1_state != DEBOUNCED_PRESS) {
          state = 0;
        }
        break;

      default:
        state = 0;
        break;
    }
    _7seg(hb | dispc);
  }

  //orientation
  if (accel.actionTask()) {
    {
      int AccX, AccY, AccZ;
      int absX, absY, absZ;
      accelerometer(&AccX, &AccY, &AccZ);
      absX = abs(AccX);

      Serial.println(absX);
      if (AccZ > threshold) orientation = ORIENTATION_FLAT;
      if (AccZ < -threshold) orientation = ORIENTATION_BASEUP;
      if (AccX > threshold) orientation = ORIENTATION_LANDSCAPE;
      if (AccX < -threshold) orientation = ORIENTATION_UPSIDEDOWN_LANDSCAPE;
      if (AccY > threshold) orientation = ORIENTATION_RIGHTPORTRAIT;
      if (AccY < -threshold) orientation = ORIENTATION_LEFTPORTAIT;
    }
    _7seg(accel_chars[orientation]);
  }

  //  Scheduler
  if (scheduler.actionTask()) {
    static int state = 0;

    Serial.print("SCHEDULER STATE = ");
    Serial.println(state);

    switch (state) {
      case 0:
        _7seg(tl | dispt);
        tlights.setRunning(true);
        counter.setRunning(false);
        accel.setRunning(false);
        if (B2_state == NOT_PRESSED) state = 1;
        break;
      case 1:
        _7seg(tl | dispt);
        tlights.setRunning(true);
        counter.setRunning(false);
        accel.setRunning(false);
        if (B2_state == DEBOUNCED_PRESS) state = 2;
        break;
      case 2:
        _7seg(tl != dispt);
        tlights.setRunning(false);
        DDRD = AllLEDOff;
        counter.setRunning(true);
        accel.setRunning(false);
        if (B2_state == NOT_PRESSED) state = 3;
        break;
      case 3:
        tlights.setRunning(false);
        counter.setRunning(true);
        accel.setRunning(false);
        if (B2_state == DEBOUNCED_PRESS) state = 4;
        break;

      case 4:
        tlights.setRunning(false);
        counter.setRunning(false);
        accel.setRunning(true);
        if (B2_state == NOT_PRESSED) state = 5;
        break;

      case 5:
        tlights.setRunning(false);
        counter.setRunning(false);
        accel.setRunning(true);
        if (B2_state == DEBOUNCED_PRESS) state = 6;
        break;
      case 6:
        DDRD = AllLEDFunc;
        tlights.setRunning(true);
        counter.setRunning(true);
        accel.setRunning(false);
        if (B2_state == NOT_PRESSED) state = 7;
        break;
      case 7:
        tlights.setRunning(true);
        counter.setRunning(true);
        accel.setRunning(false);
        if (B2_state == DEBOUNCED_PRESS) state = 8;
        break;
      case 8:
        tlights.setRunning(true);
        counter.setRunning(false);
        accel.setRunning(true);
        if (B2_state == NOT_PRESSED) state = 9;
        break;
      case 9:
        tlights.setRunning(true);
        counter.setRunning(false);
        accel.setRunning(true);
        if (B2_state == DEBOUNCED_PRESS) state = 0;
        break;
    }
  }
}