const int ldrPin = A0;
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  int brightness = map(ldrValue, 0, 1023, 255, 0); // Invertimos

  analogWrite(ledPin, brightness);
  delay(100);
}
