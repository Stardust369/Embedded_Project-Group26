#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

// ---------------------------
// DHT & LCD Configuration
// ---------------------------
#define DHTPIN 7        
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change address if needed after scan

// ---------------------------
// Motor Configuration
// ---------------------------
#define MOTOR_PIN_ENA 9  
#define MOTOR_PIN_IN1 10 
#define MOTOR_PIN_IN2 11

#define TEMPERATURE_THRESHOLD 29 
#define TEMPERATURE_THRESHOLD1 32 

// ---------------------------
// Setup
// ---------------------------
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // -------- I2C Scanner --------
  Serial.println("\n--- I2C Scanner Running ---");
  byte error, address;
  int devices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C Device found at: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      devices++;
    }
  }

  if (devices == 0) Serial.println("No I2C devices found!");
  else Serial.println("Scan Complete.\n");

  // -------- Initialize LCD --------
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  // -------- DHT Start --------
  dht.begin();

  // -------- Motor Pins --------
  pinMode(MOTOR_PIN_ENA, OUTPUT);
  pinMode(MOTOR_PIN_IN1, OUTPUT);
  pinMode(MOTOR_PIN_IN2, OUTPUT);

  // Initial motor direction
  digitalWrite(MOTOR_PIN_IN1, HIGH);
  digitalWrite(MOTOR_PIN_IN2, LOW);
}

// ---------------------------
// Main Program Loop
// ---------------------------
void loop() {
  delay(2000);

  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("ERROR: Unable to read DHT sensor!");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error     ");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  lcd.setCursor(12, 0);
  lcd.print("   "); 
  lcd.setCursor(12, 0);
  lcd.print(temperature);

  // -------- Motor Logic Based on Temperature --------
  lcd.setCursor(0, 1);

  if (temperature > TEMPERATURE_THRESHOLD1) {
    analogWrite(MOTOR_PIN_ENA, 255);
    lcd.print("Motor: HIGH     ");
  } 
  else if (temperature > TEMPERATURE_THRESHOLD) {
    analogWrite(MOTOR_PIN_ENA, 120);
    lcd.print("Motor: MEDIUM   ");
  }
  else {
    analogWrite(MOTOR_PIN_ENA, 50);
    lcd.print("Motor: LOW      ");
  }
}
