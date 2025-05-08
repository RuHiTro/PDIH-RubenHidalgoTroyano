const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  if (distance < 30) {
    digitalWrite(buzzer, HIGH);
    delay(map(distance, 5, 30, 50, 500));
    digitalWrite(buzzer, LOW);
    delay(map(distance, 5, 30, 50, 500));
  } else {
    digitalWrite(buzzer, LOW);
  }
}
