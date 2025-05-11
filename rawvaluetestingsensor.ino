#include <OneWire.h>
#include <DallasTemperature.h>
#include "DFRobot_ESP_PH.h"
#include "DFRobot_ESP_EC.h"
#include <EEPROM.h>

// === Pin Definitions ===
#define ONE_WIRE_BUS 23
#define PH_PIN 35
#define EC_PIN 34

// === Pump Relay Pins ===
int pump1Pin = 16;
int pump2Pin = 17;
int pump3Pin = 18;
int pump4Pin = 19;

// === Constants ===
#define ESPADC 4095.0      // 12-bit ADC resolution for ESP32
#define ESPVOLTAGE 3300    // in millivolts

// === Sensor Objects ===
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);
DFRobot_ESP_PH phSensor;
DFRobot_ESP_EC ecSensor;

// === Global Variables ===
float temperature = 25.0;
float phVoltage = 0.0, ecVoltage = 0.0;
float phValue = 0.0, ecValue = 0.0;
int ecRaw = 0; // Raw ADC reading

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Initializing Sensors and Pumps...");

  EEPROM.begin(64);  // EEPROM for sensor calibration

  tempSensor.begin();
  phSensor.begin();
  ecSensor.begin();

  // Set pump pins as OUTPUT
  pinMode(pump1Pin, OUTPUT);
  pinMode(pump2Pin, OUTPUT);
  pinMode(pump3Pin, OUTPUT);
  pinMode(pump4Pin, OUTPUT);

  Serial.println("System ready.");
  Serial.println("Sensor data will be printed every 4 seconds.");
  Serial.println("To control pumps, enter: 'P1', 'P2', 'P3', 'P4', or 'OFF'");
}

void loop() {
  static unsigned long lastUpdate = 0;

  // === Read and print sensor values every 4 seconds ===
  if (millis() - lastUpdate >= 4000) {
    lastUpdate = millis();

    // Read water temperature
    tempSensor.requestTemperatures();
    temperature = tempSensor.getTempCByIndex(0);
    if (temperature == DEVICE_DISCONNECTED_C || isnan(temperature)) {
      Serial.println("Error: DS18B20 not connected or malfunctioning!");
      temperature = 25.0;
    }

    // Read pH voltage
    phVoltage = analogRead(PH_PIN) / ESPADC * ESPVOLTAGE;

    // Read EC voltage
    ecRaw = analogRead(A0);  // use EC_PIN, not A0
    ecVoltage = ecRaw * (3.3 / 4095.0);

    // Compute sensor values
    phValue = phSensor.readPH(phVoltage, temperature);
    ecValue = ecSensor.readEC(ecVoltage, temperature);

    // Display sensor data
    Serial.println("----- Sensor Readings -----");
    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" °C");

    Serial.print("pH Voltage: ");
    Serial.print(phVoltage, 4);
    Serial.println(" mV");
    Serial.print("pH: ");
    Serial.println(phValue, 4);

    Serial.print("EC Raw (ADC): ");
    Serial.println(ecRaw);

    Serial.print("EC Voltage: ");
    Serial.print(ecVoltage * 1000, 4);
    Serial.println(" mV");

    Serial.print("EC Value: ");
    Serial.print(ecValue, 4);
    Serial.println(" mS/cm");
    Serial.println("---------------------------");

    // Calibration routine
    phSensor.calibration(phVoltage, temperature);
    ecSensor.calibration(ecVoltage, temperature);
  }

  // === Pump Control via Serial Commands ===
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "P1") {
      digitalWrite(pump1Pin, HIGH);
      Serial.println("Pump 1 ON");
      delay(2000);
      digitalWrite(pump1Pin, LOW);
      Serial.println("Pump 1 OFF");
    } else if (command == "P2") {
      digitalWrite(pump2Pin, HIGH);
      Serial.println("Pump 2 ON");
      delay(2000);
      digitalWrite(pump2Pin, LOW);
      Serial.println("Pump 2 OFF");
    } else if (command == "P3") {
      digitalWrite(pump3Pin, HIGH);
      Serial.println("Pump 3 ON");
      delay(2000);
      digitalWrite(pump3Pin, LOW);
      Serial.println("Pump 3 OFF");
    } else if (command == "P4") {
      digitalWrite(pump4Pin, HIGH);
      Serial.println("Pump 4 ON");
      delay(2000);
      digitalWrite(pump4Pin, LOW);
      
      Serial.println("Pump 4 OFF");
    } else if (command == "OFF") {
      digitalWrite(pump1Pin, LOW);
      digitalWrite(pump2Pin, LOW);
      digitalWrite(pump3Pin, LOW);
      digitalWrite(pump4Pin, LOW);
      Serial.println("All pumps OFF");
    } else {
      Serial.println("Invalid command. Use 'P1', 'P2', 'P3', 'P4' or 'OFF'");
    }
  }
}
