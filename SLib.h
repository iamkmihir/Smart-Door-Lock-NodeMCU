void servo(int x, int pin){
  int val = (x*10.25)+500;
  digitalWrite(pin,HIGH);
  delayMicroseconds(x);
  digitalWrite(pin,LOW);
  delay(20);
}
