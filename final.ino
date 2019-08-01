#define BLYNK_PRINT SwSerial


#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX
    
#include <BlynkSimpleStream.h>
#include <dht.h>

int sensorPin = A1; // select the input pin for LDR

int sensorValue = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a3177460f9f24bbfbc2f6a4be209506a";

#define DHTPIN 2          // What digital pin we're connected to

#define LDRPIN 8
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

 dht DHT;
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  DHT.read11(DHTPIN);
  float h = DHT.humidity;
  float t = DHT.temperature; // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    SwSerial.println("Failed to read from DHT sensor!");
    return;
  }
  sensorValue = analogRead(sensorPin);
  int sensorValue1 = analogRead(A0);
 if(sensorValue<=400){
        digitalWrite(LDRPIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }
  else
  {digitalWrite(LDRPIN,LOW);
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, sensorValue);
  Blynk.virtualWrite(V8, sensorValue1);
}

void setup()
{
  // Debug console
  SwSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  

  // Setup a function to be called every second
  timer.setInterval(1000, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
