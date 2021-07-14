/* VernierLibTutorialAnalogRead (v2017)
 * This sketch reads a data point from a Vernier Analog (BTA) 
 * sensor once every half second and prints the sensor reading 
 * with units to the Serial Monitor.
 * 
 * Plug the sensor into the Analog 1 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A0.
 */
 /* VernierTutorialAnalogVoltage (v2017)
 * This sketch reads the raw count from a Vernier Analog (BTA) 
 * sensor once every half second, converts it to a voltage, 
 * and prints both values to the Serial Monitor.
 * 
 * Plug the sensor into the Analog 2 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A2.
 */
#include "VernierLib.h" //include Vernier functions in this sketch

VernierLib Vernier; //create an instance of the VernierLib library

float sensorReading; //create global variable to store sensor reading
float rawCount; //create global variable for reading from A/D converter (0-1023)
float voltage; //create global variable for voltage (0-5V)

void setup() {
  Serial.begin(9600); //setup communication to display
  Vernier.autoID(); //identify the sensor being used
}

void loop() {
  sensorReading = Vernier.readSensor(); //read one data value
  Serial.println(sensorReading); //print data value 
 // Serial.println(Vernier.sensorUnits()); //print units and skip to next line
  /*rawCount=analogRead(A2); //read one data value (0-1023)
  voltage=rawCount/1023*5; //convert raw count to voltage (0-5V)
  Serial.print(rawCount); //print raw count 
  Serial.print("\t"); //print a tab character
  Serial.println(voltage); //print voltage and skip to next line*/
  delay(1000); //wait a second
  
}
