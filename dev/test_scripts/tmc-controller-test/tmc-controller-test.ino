#define EN_PIN    11   // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN  7    // Step on rising edge
#define DIR_PIN   6    // Set stepping direction

// Vref - Напряжение замеряемое вольтметром между пином Vref и GND от 0 до 2,5 вольт.
// value 2.5 Volts
//Irms - Постоянный ток подаваемый на двигатели.
// value 0.55
//Imax - Пиковый ток подаваемый на двигатели.
//value 0.70

// Vref = (Irms * 2.5) / 1.77 must be

#include <TMC2208Stepper.h>    // Include library
TMC2208Stepper driver = TMC2208Stepper(&Serial);  // Create driver and use
                          // HardwareSerial0 for communication

void setup() {
  Serial.begin(9600);
  Serial.println("Start...");
  driver.push();                // Reset registers

  // Prepare pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);   // Disable driver in hardware

  driver.pdn_disable(true);     // Use PDN/UART pin for communication
  driver.I_scale_analog(false); // Use internal voltage reference
  driver.rms_current(500);      // Set driver current 500mA
  driver.toff(2);               // Enable driver in software


  uint32_t data = 0;
  Serial.print("DRV_STATUS = 0x");
  driver.DRV_STATUS(&data);
  Serial.println(data, HEX);
}

void loop() {
  
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
  delayMicroseconds(1000);
}
