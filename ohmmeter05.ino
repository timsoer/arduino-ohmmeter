// Widerstände messen
//              ______
//            -|__RX__|- VCC
//AnalogPin  -' ______
//           '-| 1k___|- pin5
//           '-|_10k__|- pin4
//           '-|_100k_|- pin3
//           '-|_1000k|- PIN2

// RX = zu messender Widerstand

#define analogPin 1  // adc nummer 1
#define R1K    1020   // PIN3
#define R10K   9990   // PIN5
#define R100K  98900  // PIN4
#define R1000K 1005000// PIN2
#define alle 0.892 kohm // alle zusammen 
#define PIN1K    3
#define PIN10K   5
#define PIN100K  4
#define PIN1000K 2
#define usbVoltage 5.11

float Vin = usbVoltage;
float Vout = 0;
float R = 10000;
float Rx = 0;
float R1k = 0;
float R10k = 0;
float R100k = 0;
float R1000k = 0;
float buffer = 0;

void hochohmig() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  delay(50);
}
void set1k() {
  hochohmig();
  R = R1K;
  pinMode(PIN1K, OUTPUT);
  digitalWrite(PIN1K, LOW);
  delay(20);
}
void set10k() {
  hochohmig();
  R = R10K;
  pinMode(PIN10K, OUTPUT);
  digitalWrite(PIN10K, LOW);
  delay(20);
}
void set100k() {
  hochohmig();
  R = R100K;
  pinMode(PIN100K, OUTPUT);
  digitalWrite(PIN100K, LOW);
  delay(20);
}
void set1000k() {
  hochohmig();
  R = R1000K;
  pinMode(PIN1000K, OUTPUT);
  digitalWrite(PIN1000K, LOW);
  delay(20);
}
float readV() {
  int adc=0;
  adc = analogRead(analogPin);
  buffer = adc * Vin;
  Vout = (buffer) / 1023.0;
  return Vout;
}
float readRX() {
  int adc=0;
  for(int i=0;i<5;i++){
    adc+=analogRead(analogPin);
    delay(10);
  }
  adc=trunc(adc/5);
  buffer = adc * Vin;
  Vout = (buffer) / 1023.0;
  buffer = (Vin / Vout) - 1;
  Rx = R * buffer;
  return Rx;
}
void setup()
{
  Serial.begin(9600);
  hochohmig();
}
void loop() {
  float V = 5;
  float Rx = 0;
  set1k();
  if (V > ( abs( 2.55 - readV() )) ) {
    V = abs( 2.55 - readV() );
    //Serial.print("R1k: "); //debug
    Rx = readRX();
  }
  set10k();
  if (V > (abs( 2.55 - readV() ) ) ) {
    V = abs( 2.55 - readV() );
    //Serial.print("R10k: "); //debug
    Rx = readRX();
  }
  set100k();
  if (V > (abs( 2.55 - readV() ) ) ) {
    V = abs( 2.55 - readV() );
    //Serial.print("R100k: "); //debug
    Rx = readRX();
  }
  set1000k();
  if (V > (abs( 2.55 - readV() ) ) ) {
    V = abs( 2.55 - readV() );
    //Serial.print("R1000k: "); //debug
    Rx = readRX();
  }

  Serial.print("Rx = ");
  if (Rx > 1000) {
    Serial.print((Rx / 1000), 2);
    Serial.println("  kohm");
  }
  else {
    Serial.print(Rx, 0);
    Serial.println("  ohm");
    delay(20);
    //Serial.println("  ");
  }
}
