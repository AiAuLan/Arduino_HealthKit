#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SoftwareSerial.h>

#define PUMP_PIN 8
#define VALVE_PIN 9

Adafruit_ADS1115 ads;
SoftwareSerial btSerial(2, 3);

int basePressureValue = 13335;
int prev = 0;
bool valveOpen = false;

float getCurrentPressure() {
  int sensorValue = ads.readADC_SingleEnded(0);
  return (sensorValue-basePressureValue) * 0.0714F;
}

void setup(void) {
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);
  digitalWrite(VALVE_PIN, LOW);
  ads.setGain(GAIN_TWO);
  ads.begin();
  
  Serial.begin(115200);
  btSerial.begin(9600);
  
  // get base sensor value
  Serial.println("Please wait, calibrating...");
  
  //basePressureValue = ads.readADC_SingleEnded(0);
  //for (int x=0; x<10; ++x) {
  //  delay(100);
  //  basePressureValue += ads.readADC_SingleEnded(0);
  //  basePressureValue /= 2;
  //}
  Serial.println(basePressureValue);
  
  // start pump
  //digitalWrite(PUMP_PIN, LOW);
  //digitalWrite(VALVE_PIN, LOW);
}

void loop(void){
  
  float curr = getCurrentPressure();
  Serial.println(curr);
  delay(50);
  if (btSerial.available()) {
    String stringSerial = btSerial.readStringUntil('#'); btSerial.readString();
    Serial.println(stringSerial);
    if (stringSerial == "pressure,1") {
      digitalWrite(PUMP_PIN, LOW);
      digitalWrite(VALVE_PIN, HIGH);
    } else if (stringSerial == "pressure,0") {
      digitalWrite(PUMP_PIN, HIGH);
      digitalWrite(VALVE_PIN, LOW);
    }
  }
  if (Serial.available()) {
    btSerial.write(Serial.read());
  }
  if (curr >= 160.0F) {
    digitalWrite(PUMP_PIN, HIGH);
    digitalWrite(VALVE_PIN, LOW);
  }
}
