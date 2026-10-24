const int trigPin = 9;
const int echoPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  // Sensorun olcumu baslatmasi icin 10 mikrosaniyelik darbe.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Yankiyi en fazla 30 milisaniye bekle.
  unsigned long sure = pulseIn(echoPin, HIGH, 30000UL);

  if (sure == 0) {
    Serial.println("Olcum alinamadi");
  } else {
    float mesafe = sure * 0.0343 / 2.0;

    if (mesafe < 2 || mesafe > 400) {
      Serial.println("Olcum aralik disinda");
    } else {
      Serial.print("Mesafe: ");
      Serial.print(mesafe, 1);
      Serial.println(" cm");
    }
  }

  delay(250);
}
