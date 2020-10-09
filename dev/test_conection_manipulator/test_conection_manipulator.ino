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

void rotateOnAngle(float angle, bool direct, int axisNumber);
 bool flag = true;
 
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

  
}
void loop() {
  // These four lines result in 1 step:
 /*            for(int i=0; i<1056l; i++){
     digitalWrite(stepPin4, HIGH);
  delayMicroseconds(1000);
  digitalWrite(stepPin4, LOW);
    delayMicroseconds(1000);
      }
  */
  if(flag == true){
    
   
    rotateOnAngle(120.0, true, 2);
     rotateOnAngle(120.0, false, 3);
     rotateOnAngle(100.0, false, 1);
     
    flag = false;
  }
      
}
void rotateOnAngle(float angle, bool dir, int axisNumber){
  const int numberStepsForSpin = 200; //количество шагов для одного оборота
  const int stepDevision = 16; // шаг дробления
  const float OneDegry = (numberStepsForSpin*stepDevision)/360.0;
  float ratio = 1;  
  if(axisNumber == 1){
      if(dir==true)
        digitalWrite(dirPin1, HIGH);
      else
        digitalWrite(dirPin1, LOW);
      ratio = 4.8;  
      int delValue=300;
      // число шагов двигаеля чтобы повернуться на заданный угол
      float totSteps=angle*OneDegry*ratio; 
      
      for (int i=0; i < totSteps; i++){
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(delValue);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(delValue);
      }
  }
  else if (axisNumber == 2){
        if(dir==true)
        digitalWrite(dirPin2, HIGH);
      else
        digitalWrite(dirPin2, LOW  );
      ratio = 4;  
      int delValue=300;
      // число шагов двигаеля чтобы повернуться на заданный угол
      float totSteps=angle*OneDegry*ratio; 
      
      for (int i=0; i < totSteps; i++){
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(delValue);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(delValue);
      }
  }
  else if (axisNumber == 3){
        if(dir==true)
        digitalWrite(dirPin3, HIGH);
      else
        digitalWrite(dirPin3, LOW );
      ratio = 5;  
      int delValue=300;
      // число шагов двигаеля чтобы повернуться на заданный угол
      float totSteps=angle*OneDegry*ratio; 
      
      for (int i=0; i < totSteps; i++){
        digitalWrite(stepPin3, HIGH);
        delayMicroseconds(delValue);
        digitalWrite(stepPin3, LOW);
        delayMicroseconds(delValue);
      }
  }   
    else if (axisNumber == 4){
        if(dir==true)
        digitalWrite(dirPin4,HIGH );
      else
        digitalWrite(dirPin4,LOW );
      ratio = 2.8;  
      int delValue=300;
      // число шагов двигаеля чтобы повернуться на заданный угол
      float totSteps=angle*OneDegry*ratio; 
      
      for (int i=0; i < totSteps; i++){
        digitalWrite(stepPin4, HIGH);
        delayMicroseconds(delValue);
        digitalWrite(stepPin4, LOW);
        delayMicroseconds(delValue);
      }
  } 
    else if (axisNumber == 5){
        if(dir==true)
        digitalWrite(dirPin5, LOW);
      else
        digitalWrite(dirPin5, HIGH );
      ratio = 2.1;  
      int delValue=300;
      // число шагов двигаеля чтобы повернуться на заданный угол
      float totSteps=angle*OneDegry*ratio; 
      
      for (int i=0; i < totSteps; i++){
        digitalWrite(stepPin5, HIGH);
        delayMicroseconds(delValue);
        digitalWrite(stepPin5, LOW);
        delayMicroseconds(delValue);
      }
  }     
  else if (axisNumber == 6){
      if(dir==true)
        digitalWrite(dirPin6, HIGH);
      else
        digitalWrite(dirPin6, LOW);
        
      int delValue=300;
      float totSteps=angle*OneDegry;
      
      for (int i=0; i < totSteps; i++){
        digitalWrite(stepPin6, HIGH);
        delayMicroseconds(delValue);
        digitalWrite(stepPin6, LOW);
        delayMicroseconds(delValue);
      }
  }
}
