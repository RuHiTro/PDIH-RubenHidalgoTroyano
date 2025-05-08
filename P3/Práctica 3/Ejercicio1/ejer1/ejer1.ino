int ledRojo = 11;
int ledAmarillo = 12;
int ledVerde = 13;
int tiempo = 1500;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void loop() {
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledVerde, LOW);
  delay(tiempo);

  digitalWrite(ledRojo, LOW);     
  digitalWrite(ledAmarillo, HIGH);
  digitalWrite(ledVerde, LOW);
  delay(tiempo);

  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledVerde, HIGH);
  delay(tiempo);
}
