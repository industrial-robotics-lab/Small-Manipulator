// These define's must be placed at the beginning before #include "TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#if ( TIMER_INTERRUPT_USING_ATMEGA_32U4 )
  #define USE_TIMER_1     true
#else
  #define USE_TIMER_1     true
  #define USE_TIMER_2     true
  #define USE_TIMER_3     false
  #define USE_TIMER_4     false
  #define USE_TIMER_5     false
#endif

// Controller PINs
#define EN_PIN    11   // LOW: Driver enabled. HIGH: Driver disabled
unsigned int STEP_PIN = 7;    // Step on rising edge
#define DIR_PIN   6    // Set stepping direction

#include "TimerInterrupt.h"
#include <TMC2208Stepper.h>    // Include library



TMC2208Stepper driver = TMC2208Stepper(&Serial);  // Create driver and use
                          // HardwareSerial0 for communication


unsigned int toggle1 = 1; 

void TimerHandler1(unsigned int STEP_PIN = STEP_PIN)
{
//
//if (toggle == 1)
//  {
//    digitalWrite(STEP_PIN, HIGH);
////    toggle1 = !toggle1;
//    Serial.print("IN toggle1 = "); Serial.println(toggle);
//  }
//else{
//    digitalWrite(STEP_PIN, LOW);
////    toggle1 = !toggle1;
//    Serial.print("IN toggle1 = "); Serial.println(toggle);
//  }
//
//  #if (TIMER_INTERRUPT_DEBUG > 1)
//    Serial.print(" IN ITimer1 called, millis() = "); Serial.println(millis());
//  #endif
  
//  Serial.print(digitalRead(STEP_PIN));
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN)); // Step
//  Serial.print(" - the state, INNER STEP_PIN = "); Serial.println(STEP_PIN);
}

#define TIMER1_INTERVAL_MS    (float) 1.0 / 1
#define TIMER1_FREQUENCY      (float) (1000.0f / TIMER1_INTERVAL_MS)
#define TIMER1_DURATION_MS    (2 * TIMER1_INTERVAL_MS)


static unsigned long lastSwitch = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println(F("\nStarting TimerInterruptTest on AVR"));
  Serial.println(TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Timer0 is used for micros(), millis(), delay(), etc and can't be used
  // Select Timer 1-2 for UNO, 0-5 for MEGA
  // Timer 2 is 8-bit timer, only for higher frequency

  ITimer1.init();

  // Using ATmega328 used in UNO => 16MHz CPU clock ,

  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1, STEP_PIN, TIMER1_DURATION_MS))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

  // Prepare pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
  driver.pdn_disable(1);              // Use PDN/UART pin for communication
  driver.I_scale_analog(0);           // Adjust current from the registers
  driver.rms_current(100);            // Set driver current 500mA
  driver.toff(0x2);               // Enable driver

//  digitalWrite(13, LOW);              // Enable driver
}

void loop()
{
  if (millis() - lastSwitch <= TIMER1_DURATION_MS *1)
  {
    // do enything
//    Serial.print(F("Waiting fot interaption...., lastSwitch = ")); Serial.println(lastSwitch);
//    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());
 

  }
  else
  {
    ITimer1.reattachInterrupt(TIMER1_DURATION_MS);
    lastSwitch = millis();
//    Serial.print(F("Current HIGH ITimer1, millis() = ")); Serial.print(millis());
//    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());
    
  }

}
