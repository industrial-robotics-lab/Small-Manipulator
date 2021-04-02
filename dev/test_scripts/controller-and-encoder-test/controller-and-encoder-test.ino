#define EN_PIN    11   // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN  7    // Step on rising edge
#define DIR_PIN   6    // Set stepping direction
#define enc_dir_pin 2  // Just give the sitive dirrection of enconer counting

// NOTHING USEFUL IN RUSSIAN 
// Vref - Напряжение замеряемое вольтметром между пином Vref и GND от 0 до 2,5 вольт.
// value 2.5 Volts
//Irms - Постоянный ток подаваемый на двигатели.
// value 0.55
//Imax - Пиковый ток подаваемый на двигатели.
//value 0.70

// Vref = (Irms * 2.5) / 1.77 must be

#include <TMC2208Stepper.h>    // Include library for driver
#include <AS5600.h>           // Include library for encoder
#include <SoftwareSerial.h>   // For multiple sertial connections

TMC2208Stepper driver = TMC2208Stepper(&Serial);  // Create driver and use HardwareSerial0 for communication
AS5600 encoder1;   // Create ecoder

double output, start_angle, curent_angle, target_velocity, angle_diff, actual_velocity;
double angle = 0;

int start_time, curent_time, msdelay;

void setup() {
  Serial.begin(9600);             // Init used serial port
  while(!Serial);                 // Wait for port to be ready
  
  // Prepare pins for driver
  pinMode(EN_PIN, OUTPUT);        // Enable PIN for driver 1
  pinMode(STEP_PIN, OUTPUT);      // STEP PIN for driver 1
  pinMode(DIR_PIN, OUTPUT);       // DIRection PIN for driver
  // Prepare pins for encoder
  pinMode(enc_dir_pin, LOW);      // five positive direction clockwise / conter clockwise (HIGH/LOW)

  // presets for driver
  driver.pdn_disable(1);              // Use PDN/UART pin for communication
  driver.I_scale_analog(0);           // Adjust current from the registers
  driver.rms_current(700);            // Set driver current 500mA
  driver.toff(0x2);               // Enable driver
  digitalWrite(13, LOW);              // Enable driver
  digitalWrite(DIR_PIN, LOW); // give direction
  //digitalWrite(DIR_PIN, HIGH); // give direction
}

void loop() {
  digitalWrite(STEP_PIN, HIGH); // Step
  delayMicroseconds(200);
  //output = encoder1.getPosition();         // считываем чистые значения с энкодера
//  angle = map(output, 0, 4096, 0, 360);   // переводим значение output в угл от 0 до 360
//  Serial.println(angle);
  digitalWrite(STEP_PIN, LOW); // Step
  delayMicroseconds(200);
}
