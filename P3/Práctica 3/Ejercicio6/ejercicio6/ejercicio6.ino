#include <Servo.h>

Servo servo;
int boton = 2;
int angulo = 0;

void setup() {
  servo.attach(9);
  pinMode(boton, INPUT);
  servo.write(0);
}

void loop() {
  bool estadoBoton = digitalRead(boton);

  if (estadoBoton == HIGH) {
    servo.write(90);  
  } else {
    servo.write(0);  
  }
}
