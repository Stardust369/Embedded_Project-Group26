#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2        
#define MQ2PIN A0       
#define BUZZERPIN 8

#define DHTTYPE DHT11  

float TEMP_THRESHOLD = 40.0;
int SMOKE_THRESHOLD = 320;   

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  //serial communication at 9600 baud rate for monitoring
  Serial.begin(9600);
  Serial.println("Fire Alarm System Initializing...");

  // Set the pin modes
  pinMode(BUZZERPIN, OUTPUT);
  
  // Start the DHT sensor
  dht.begin();
  
  // A small delay to let sensors stabilize
  delay(2000); 
  Serial.println("System Ready.");
}

void loop() {
  // A 2-second delay between readings
  delay(2000); 
  
  float temperature = dht.readTemperature(); // Read temperature in Celsius
  int smokeValue = analogRead(MQ2PIN);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | ");
  Serial.print("Smoke Level: ");
  Serial.println(smokeValue);

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return; // Exit the loop early if sensor fails
  }

  if (temperature > TEMP_THRESHOLD || smokeValue > SMOKE_THRESHOLD) {
    Serial.println("!!! ALERT: FIRE DETECTED !!!");
    
    tone(BUZZERPIN, 1050); // Produces a 1500Hz tone
    delay(300);              
    // noTone(BUZZERPIN);       
    // delay(300);              
  } else {
    Serial.println("Status: Normal");
    
    noTone(BUZZERPIN);
  }
}

