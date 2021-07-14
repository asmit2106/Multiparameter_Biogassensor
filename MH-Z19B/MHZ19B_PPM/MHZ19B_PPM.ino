
#define RANGE 5000
#define INTERVALL 1004
#define SENSOR_PIN 3
void setup (){
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
   
}
void loop() {
  int pulse_high, pulse_high_2, pulse_low;
  unsigned long time_start;
 
  // pulseIn() arbeitet mit Mikro- (nicht Milli-)Sekunden
  // erst einmal Länge des HIGH-Pegels ermitteln ...
  pulse_high = pulseIn(SENSOR_PIN, HIGH, 2200000UL) / 1000;
 
  time_start = millis();  // jetzt beginnt der LOW-Pegel
 
  // ... dann die Länge des folgenden HIGH-Pegels messen
  pulse_high_2 = pulseIn(SENSOR_PIN, HIGH, 1100000UL) / 1000;
 
  // die Dauer des LOW-Pegels ist die Zeit seit Beginn der 
  // Messung minus die Dauer des zweiten HIGH-Pegels;
  pulse_low = millis() - time_start - pulse_high_2;
 
  // Ausgabe im seriellen Monitor: 
  // - CO2-Wert nach einfacher Formel
  // - Wert nach vollständiger Formel
  // - Roh-Werte der Messung
  //Serial.print("PPM CO2: ");
  //Serial.println((pulse_high - 2) * RANGE / 1000);
  //Serial.print(" (einfach); ");
  Serial.println((pulse_high - 2) * RANGE / (pulse_high + pulse_low -4));
  //Serial.print(" (korrekt); ");
  //Serial.print("Rohwerte (HIGH, LOW): ");
  //Serial.print(pulse_high);
  //Serial.print(", ");
  //Serial.println(pulse_low);*/
  delay(2500);
  Serial.flush();
  }
