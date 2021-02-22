// ranges
// 2-axis = from 0 to -70
// 3 axis = from 0 to 90
// 4 axis = from 0 to -90
 
// test demo////
// 70, -50, 50, 0, 0, 0
// 0, 0, 0, 0, 0, 0

// 70, -70, 70, -45, 0, 0

//big motors enable
#define X_ENABLE_PIN123 35

// axis 1
#define dirPin1 25
#define stepPin1 23

//axis 2
#define dirPin2 29
#define stepPin2 27

//axis 3
#define dirPin3 33
#define stepPin3 31

//axis 4 z axis
#define stepPin4 46
#define dirPin4 48
#define Z_ENABLE_PIN4 62 // z axis

//axis 5 y axis
#define stepPin5 60
#define dirPin5 61
#define Y_ENABLE_PIN5 56 // y axis

//axis 6  x axis
#define stepPin6 54
#define dirPin6 55
#define X_ENABLE_PIN6 38 // x axis

byte relays_dir[] = {dirPin1, dirPin2, dirPin3, dirPin4, dirPin5, dirPin6};
byte relays_step[] = {stepPin1, stepPin2, stepPin3, stepPin4, stepPin5, stepPin6};

int incomingByte = 0; //just for serial
int angles[6] = {0, 0, 0, 0, 0, 0}; // hold target angles
int anglesi[6] = {0, 0, 0, 0, 0, 0}; // hold current angles
float ratio[6] = {4.8, 4.0, 5.0, 0.2, 0.3, 0.8}; // hold ratio  for each joint

bool flag = true;
int delValue = 300;

int numberStepsForSpin = 200; // how many steps per one rotation
int stepDevision = 16; // step devide ratio
float OneDegry = (numberStepsForSpin * stepDevision) / 360.0; // how many steps per one degree

void setup() {
  // enable 1-2-3 exis
  pinMode(X_ENABLE_PIN123, OUTPUT);
  digitalWrite(X_ENABLE_PIN123, LOW);

  //axis 1
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin1, HIGH);

  //axis 2
  pinMode(stepPin2, OUTPUT); 
  pinMode(dirPin2, OUTPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin2, HIGH);

  //axis 3
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin3, HIGH);

  //axis 4
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin4, HIGH);
  //enable axis 4
  pinMode(Z_ENABLE_PIN4, OUTPUT);
  digitalWrite(Z_ENABLE_PIN4, LOW);

  //axis 5
  pinMode(stepPin5, OUTPUT);
  pinMode(dirPin5, OUTPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin5, HIGH);
  // anable axis 5
  pinMode(Y_ENABLE_PIN5, OUTPUT);
  digitalWrite(Y_ENABLE_PIN5, LOW);

  //axis 6
  pinMode(stepPin6, OUTPUT);
  pinMode(dirPin6, OUTPUT);
  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin6, HIGH);
  // anable axis 5
  pinMode(X_ENABLE_PIN6, OUTPUT);
  digitalWrite(X_ENABLE_PIN6, LOW);

  Serial.begin(9600); // init serial conn
  Serial.setTimeout(10);
}

void loop() {
  //use input data from the serial port
  if (Serial.available() > 0) {
    int reading_mode = 1;
    for (int i = 0; i < 5; i++) {
      angles[i] = ratio[i]* OneDegry * Serial.readStringUntil(',').toInt();
      Serial.read(); //next character is comma, so skip it using this
    }
    // the last one value also should read
    angles[6]  = Serial.readStringUntil('\0').toInt();
    Serial.print("U sent: ");
    for (int k = 0; k < 6; k++) {
      Serial.print(angles[k]);
      Serial.print("-->");
    }
  }
  for (int i = 0; i < 6; i++){
    if (anglesi[i] != angles[i]){
      if (anglesi[i] < angles[i])
      {
        digitalWrite(relays_dir[i], LOW);
        anglesi[i]++;
      }
      else
      {
        digitalWrite(relays_dir[i], HIGH);
        anglesi[i]--;
      }
      digitalWrite(relays_step[i], HIGH);
      delayMicroseconds(delValue);
      digitalWrite(relays_step[i], LOW);
      delayMicroseconds(delValue);
    }
  }
}
