int en = 4;
int dir1 = 5;
int dir2 = 9;

void setup() {
  pinMode(en, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
}

void loop() {
  digitalWrite(en, HIGH);

  digitalWrite(dir1, HIGH);
  digitalWrite(dir2, LOW);
  delay(2000);

  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  delay(2000);
}
