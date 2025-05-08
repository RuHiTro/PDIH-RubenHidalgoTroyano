int leds[] = {8, 9, 10, 11}; // Array de pines
int numLeds = 4;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Ir hacia la derecha
  for (int i = 0; i < numLeds; i++) {
    encenderUno(i);
  }

  // Volver hacia la izquierda
  for (int i = numLeds - 2; i > 0; i--) {
    encenderUno(i);
  }
}

void encenderUno(int index) {
  // Apagar todos
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], LOW);
  }

  // Encender el actual
  digitalWrite(leds[index], HIGH);
  delay(200);
}
