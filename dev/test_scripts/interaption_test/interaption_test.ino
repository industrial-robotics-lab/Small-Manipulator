#if ( defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || \
      defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || \
      defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || \
      defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_BT) || \
      defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) )

#elif ( defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_LEONARDO_ETH) || defined(ARDUINO_AVR_YUN) || defined(ARDUINO_AVR_MICRO) || \
        defined(ARDUINO_AVR_ESPLORA)  || defined(ARDUINO_AVR_LILYPAD_USB)  || defined(ARDUINO_AVR_ROBOT_CONTROL) || defined(ARDUINO_AVR_ROBOT_MOTOR) || \
        defined(ARDUINO_AVR_CIRCUITPLAY)  || defined(ARDUINO_AVR_YUNMINI) || defined(ARDUINO_AVR_INDUSTRIAL101) || defined(ARDUINO_AVR_LININO_ONE) )       
  #if defined(TIMER_INTERRUPT_USING_ATMEGA_32U4)
    #undef TIMER_INTERRUPT_USING_ATMEGA_32U4
  #endif
  #define TIMER_INTERRUPT_USING_ATMEGA_32U4      true
  #warning Using ATMega32U4, such as Leonardo or Leonardo ETH. Only Timer1 is available
#elif defined(ARDUINO_AVR_GEMMA) 
  #error These AVR boards are not supported! You can use Software Serial. Please check your Tools->Board setting.
#else
  #error This is designed only for Arduino AVR board! Please check your Tools->Board setting.
#endif

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


#include "TimerInterrupt.h"



bool toggle1 = false;
bool toggle2 = false;

void TimerHandler1(unsigned int outputPin = LED_BUILTIN)
{

  static bool started = false;
  if (!started)
  {
    started = true;
    pinMode(outputPin, OUTPUT);
  }

#if (TIMER_INTERRUPT_DEBUG > 1)
  Serial.print("ITimer1 called, millis() = "); Serial.println(millis());
#endif

  //timer interrupt toggles pin LED_BUILTIN
  digitalWrite(outputPin, toggle1);
  toggle1 = !toggle1;
}

#if !( TIMER_INTERRUPT_USING_ATMEGA_32U4 )
void TimerHandler2(unsigned int outputPin = LED_BUILTIN)
{
  bool toggle = false;
  bool toggle2 = false;
  static bool started = false;
 
  if (!started)
  {
    started = true;
    pinMode(outputPin, OUTPUT);
  }

#if (TIMER_INTERRUPT_DEBUG > 1)
  Serial.print("ITimer2 called, millis() = "); Serial.println(millis());
#endif

  //timer interrupt toggles outputPin
  digitalWrite(outputPin, toggle2);
  toggle2 = !toggle2;
}
#endif

unsigned int outputPin1 = LED_BUILTIN;
unsigned int outputPin2 = A0;

#define TIMER1_INTERVAL_MS    1000
#define TIMER1_FREQUENCY      (float) (1000.0f / TIMER1_INTERVAL_MS)
#define TIMER1_DURATION_MS    (2 * TIMER1_INTERVAL_MS)

#define TIMER2_INTERVAL_MS    13000
#define TIMER2_FREQUENCY      (float) (1000.0f / TIMER2_INTERVAL_MS)
#define TIMER2_DURATION_MS    0   //(20 * TIMER2_INTERVAL_MS)

static unsigned long lastSwitch = 0;
static unsigned long lastTimer2 = 0;

static bool timerPaused         = false;
static bool timerResumed        = false;

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

  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1, outputPin1, TIMER1_DURATION_MS))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

#if !( TIMER_INTERRUPT_USING_ATMEGA_32U4 )

  ITimer2.init();

  if (ITimer2.attachInterruptInterval(TIMER2_INTERVAL_MS, TimerHandler2, outputPin2, TIMER2_DURATION_MS))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer2. Select another freq. or timer"));
    
#endif

}

void loop()
{
  if (millis() - lastSwitch < TIMER1_DURATION_MS * 2)
  {
    // do enything
//    Serial.print(F("Waiting fot interaption...., lastSwitch = ")); Serial.print(lastSwitch);
//    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());

    

  }
  else if (toggle1)
  {
    /// current HIGH state
    ITimer1.reattachInterrupt(TIMER1_DURATION_MS);
    lastSwitch = millis();
    toggle1 = !toggle1;
    Serial.print(F("Current HIGH ITimer1, millis() = ")); Serial.print(millis());
    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());
  }
  else
  {
    // current LOW state
    ITimer1.reattachInterrupt(TIMER1_DURATION_MS);
    lastSwitch = millis();
    toggle1 = !toggle1;
    Serial.print(F("Current LOW ITimer1, millis() = ")); Serial.print(millis());
    Serial.print(F(" count = ")); Serial.println(ITimer1.getCount());
    
  }

}
