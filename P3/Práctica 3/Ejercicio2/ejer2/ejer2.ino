int ledRojo = 11;
int ledAmarillo = 12;
int ledVerde = 13;
int boton = 7;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(boton, INPUT);
}

void loop() {
  int estadoBoton = digitalRead(boton);

  if (estadoBoton == HIGH) {
  
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);
  } else {
 
    digitalWrite(ledRojo, LOW);

    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledVerde, LOW);
    delay(1500);

    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, HIGH);
    delay(1500);
  }
}
