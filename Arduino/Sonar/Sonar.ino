void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(3,HIGH);
  long t = 0;
  delayMicroseconds(20);
  digitalWrite(3,LOW);
  t = pulseIn(2,HIGH);
  double d = (double)t*0.00017015;
  Serial.println(d);
  delay(1000);
}
