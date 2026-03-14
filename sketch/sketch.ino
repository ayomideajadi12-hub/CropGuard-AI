#include <DHT.h>
#include <CropGuard-AI_inferencing.h>

// Pin definitions
#define DHTPIN 2
#define DHTTYPE DHT22
#define SOIL_PIN A0
#define LDR_PIN A1
#define BUZZER_PIN 8
#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_RED 7

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  Serial.println("CropGuard-AI Starting...");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilRaw = analogRead(SOIL_PIN);
  int lightRaw = analogRead(LDR_PIN);

  float soil_moisture = map(soilRaw, 0, 1023, 100, 0);
  float light = lightRaw;

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT read failed!");
    delay(2000);
    return;
  }

  Serial.print("Soil: "); Serial.print(soil_moisture);
  Serial.print(" | Temp: "); Serial.print(temperature);
  Serial.print(" | Humidity: "); Serial.print(humidity);
  Serial.print(" | Light: "); Serial.println(light);

  // Run Edge Impulse inference
  float features[4] = { soil_moisture, temperature, humidity, light };

  ei_impulse_result_t result = { 0 };
  signal_t signal;
  numpy::signal_from_buffer(features, 4, &signal);
  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

  if (res != EI_IMPULSE_OK) {
    Serial.println("Classifier failed!");
    return;
  }

  // Find top prediction
  int best = 0;
  for (int i = 1; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
    if (result.classification[i].value > result.classification[best].value)
      best = i;
  }

  String label = result.classification[best].label;
  float confidence = result.classification[best].value * 100;

  Serial.print("Prediction: "); Serial.print(label);
  Serial.print(" ("); Serial.print(confidence); Serial.println("%)");

  // LEDs + Buzzer
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  if (label == "safe") {
    digitalWrite(LED_GREEN, HIGH);
  } else if (label == "stressed") {
    digitalWrite(LED_YELLOW, HIGH);
  } else if (label == "critical") {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
  }

  Serial.println("---");
  delay(3000);
}
