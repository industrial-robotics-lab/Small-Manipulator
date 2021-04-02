#include <AS5600.h>
#define enc_dir_pin 2                     // задаем пин направления вращения для энкодера

AS5600 encoder;
double output = 0;                        // переменная данных с датчика (от 0 до 4096)
double angle = 0;                         // угол поворота вала

void setup() {
  Serial.begin(9600);
  pinMode(enc_dir_pin, LOW);              // задаем направление по часовой / против часовой стрелки (HIGH/LOW)
}

void loop() {
  output = encoder.getPosition();         // считываем чистые значения с энкодера
  angle = map(output, 0, 4096, 0, 360);   // переводим значение output в угл от 0 до 360
  Serial.println(angle);
  delay(100);
}
