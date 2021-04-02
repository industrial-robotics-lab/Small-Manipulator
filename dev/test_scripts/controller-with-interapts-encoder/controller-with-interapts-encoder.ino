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
#define enc_dir_pin 2  // Just give the sitive dirrection of enconer counting

#include "TimerInterrupt.h"
#include <TMC2208Stepper.h>    // Include library
#include <AS5600.h>           // Include library for encoder


TMC2208Stepper driver = TMC2208Stepper(&Serial);  // Create driver and use HardwareSerial0 for communication
AS5600 encoder1;   // Create ecoder

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
#define TIMER1_DURATION_MS    (100 * TIMER1_INTERVAL_MS)


static unsigned long lastSwitch = 0;
unsigned int toggle1 = 1;
double output, start_angle, curent_angle, target_velocity, angle_diff, actual_velocity, start_time, time_diff;
double angle = 0.0;
int started = 0;

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

    // Prepare pins for driver
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(enc_dir_pin, OUTPUT);
  // Prepare pins for encoder
  pinMode(enc_dir_pin, LOW);      // five positive direction clockwise / conter clockwise (HIGH/LOW)

  // presets for driver
  driver.pdn_disable(1);              // Use PDN/UART pin for communication
  driver.I_scale_analog(0);           // Adjust current from the registers
  driver.rms_current(500);            // Set driver current 500mA
  driver.toff(0x2);               // Enable driver
  digitalWrite(DIR_PIN, LOW); // give direction
//  digitalWrite(DIR_PIN, HIGH); // give direction
//  digitalWrite(13, LOW);              // Enable driver

  start_time = millis();
  start_angle = map(encoder1.getPosition(), 0, 4096, 0, 360);   // read and transform to degrees
}

void loop()
{
  if (millis() - lastSwitch <= TIMER1_DURATION_MS *1)
  {
    curent_angle = map(encoder1.getPosition(), 0, 4096, 0, 360);   // read and transform to degrees
//    Serial.println(curent_angle);
//    Serial.print(F("Waiting fot interaption...., lastSwitch = ")); Serial.println(lastSwitch);
//    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());

  }
  else
  {
    ITimer1.reattachInterrupt(TIMER1_DURATION_MS);
    lastSwitch = millis();

    time_diff = (millis() - start_time) / 1000;
    if (curent_angle < start_angle){
      angle_diff = 360 - start_angle + curent_angle;
    }
    else{
      angle_diff = curent_angle - start_angle;
      }
    actual_velocity = angle_diff / time_diff;
    Serial.print(F("time_diff = ")); Serial.println(time_diff);
    Serial.print(F("curent_angle = ")); Serial.println(curent_angle);
    Serial.print(F("actual_velocity = ")); Serial.println(actual_velocity);
//    Serial.print(F("Current HIGH ITimer1, millis() = ")); Serial.print(millis());
//    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());

    start_time = millis();
    start_angle = map(encoder1.getPosition(), 0, 4096, 0, 360);   // read and transform to degrees
    
  }

}
