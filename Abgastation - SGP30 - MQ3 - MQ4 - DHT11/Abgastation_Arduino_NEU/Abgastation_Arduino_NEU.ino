



/*********************************ToDo & Notes*************************************************
MQ3 & MQ4 kalibrieren --> #include <MQUnifiedsensor.h>
Serieller kommunikation mit Verniershield

Verkabelungs Liste

Timing vollständig gekoppet an SGP Messwert


/********************************Libraries********************************************/
#include <Wire.h>
#include <SparkFun_SGP30_Arduino_Library.h>
#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>
#include <MQUnifiedsensor.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>

/************************Hardware Related Macros************************************/
#define         Board                     ("Arduino MEGA")
#define         MQ3Pin                    (A1)  //Analog input 10 of your arduino
#define         MQ4Pin                    (A2)  //Analog input 11 of your arduino
#define         DHTPIN                     A3   //Der Sensor wird an PIN 32 angeschlossen    
/***********************Software Related Macros************************************/
#define         DHTTYPE                   DHT11     // Es handelt sich um den DHT11 Sensor
#define         Type3                     ("MQ-3")  //MQ3
#define         Type4                     ("MQ-4")  //MQ4
#define         Voltage_Resolution        (5)
#define         ADC_Bit_Resolution        (10)      // For arduino UNO/MEGA/NANO
#define         RatioMQ3CleanAir          (60)      //RS / R0 = 60 ppm 
/*****************************Globals***********************************************/


void t1Callback(void);

SGP30 mySensor; //create an object of the SGP30 class
DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dht“ angesprochen
MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, MQ3Pin, Type3);
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, MQ4Pin, Type4);
//MHZ co2(CO2_IN, MHZ19B);

bool results = false;
//run task t1Callback every 8000ms (8s) forever
Task t1(8000, TASK_FOREVER, &t1Callback);
Scheduler runner; //create an object of the Scheduler class

/*****************************VOID SETUP*******************************************/
void setup() {
  Serial.begin(9600);
  //inputString.reserve(200); // Only necessary for Option 2 of Vernier communication
  Wire.begin();
  Wire.setClock(400000);
      if (mySensor.begin() == false) {
        Serial.println("No SGP30 Detected. Check connections.");
      while (1);
      }
      dht.begin();
      MQ3.init();
      MQ4.init();
   
          //initialize scheduler
          runner.init();
          //add task t1 to the schedule
          runner.addTask(t1);
          //measureAirQuality should be called in five seconds increments after a call to initAirQuality
          mySensor.initAirQuality();
          //enable t1 to run
          t1.enable();
     //following parameters should be find out by calibration (see Library)
     /*MQ3.setRegressionMethod(1); //_PPM =  a*ratio^b
     MQ3.setA(4.8387); MQ3.setB(-2.68); // Configurate the ecuation values to get Benzene concentration
     MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
     MQ4.setA(1012.7); MQ4.setB(-2.786); // Configurate the ecuation values to get CH4 concentration*/
          
  }
/********************************VOID LOOP**********************************************/
void loop() {
    runner.execute();
    if (results == true) {
      
   
      
    /*SGP-30
      First fifteen readings will be
      CO2: 400 ppm  TVOC: 0 ppb*/
      mySensor.measureAirQuality();
      Serial.print("CO2:");
      Serial.print(mySensor.CO2);
      Serial.print("TVOC:");
      Serial.print(mySensor.TVOC);
      //Serial.print(" ppb ");
      //get raw values for H2 and Ethanol
      mySensor.measureRawSignals();
      Serial.print("Raw H2:");
      Serial.print(mySensor.H2);
      Serial.print("Raw Ethanol: ");
      Serial.print(mySensor.ethanol);
      
    //DHT11
      float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern
      float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern
      Serial.print("Luftfeuchtigkeit:"); //Im seriellen Monitor den Text und 
      Serial.print(Luftfeuchtigkeit); //die Dazugehörigen Werte anzeigen
      //Serial.print(" %");
      Serial.print("Temperatur:");
      Serial.print(Temperatur);
     //( Serial.print(" Grad Celsius");

    //MQ3
      //MQ3.update(); // Update data, the arduino will be read the voltage on the analog pin
      //MQ3.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
      analogRead(A1);
     
      Serial.print("MQ3:");
      //Serial.print(MQ3.readSensor());
      Serial.print(analogRead(A1));
      
    //MQ4
      //MQ4.update(); // Update data, the arduino will be read the voltage on the analog pin
      //MQ4.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
      analogRead(A2);
      Serial.print("MQ4:"); 
      //Serial.println(MQ4.readSensor());
      //Serial.print("RAW MQ4:      ");
      Serial.println(analogRead(A2));
  results = false;
  }
  /* 1. 
     //Kommunikation mit Verniershield
        1.Option: 
            if (Serial1.available()) {      // If anything comes in Serial1 (pins 0&1)
            Serial.write(Serial1.read());   // read it and send it out Serial (USB) 
        2.Option:
            while (Serial1.available()) {
            // get the new byte:
            char inChar = (char)Serial1.read();
            // add it to the inputString:
            inputString += inChar;
            // if the incoming character is a newline, set a flag so the main loop can
            // do something about it:
            if (inChar == '\n') {
            stringComplete = true;}}


            if (stringComplete = true) {      
            Serial.println(inputString);
            // clear the string:
            inputString = "";
            stringComplete = false;
             }}
             Option 3: Softwareserial --> Two port receive ... evtl ?!
             */
      Serial.flush();
       } //VoidLoop end




  
void t1Callback(void) {
  mySensor.measureAirQuality();
  results = true;}
