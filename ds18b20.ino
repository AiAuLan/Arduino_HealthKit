//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 10
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Bluetooth serial
SoftwareSerial btSerial(2,3);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void) {
  Serial.begin(115200); //Begin serial communication
  btSerial.begin(115200);
  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();
}

void loop(void) { 

  String btInput = btSerial.readStringUntil("\r"); btSerial.read();
  Serial.println(btInput);
  
  // Check BtSerial
  if (btInput.equals("1#")) {
    // Send the command to get temperatures
    sensors.requestTemperatures();  
    btSerial.println(sensors.getTempCByIndex(0));
    Serial.println(sensors.getTempCByIndex(0));
    delay(50);
  }
}
