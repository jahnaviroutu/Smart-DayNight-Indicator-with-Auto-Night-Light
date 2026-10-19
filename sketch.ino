#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int LDR_PIN = 34;
const int LED_PIN = 5;

const int DARK_THRESHOLD = 30;            // below this brightness % = night
const bool HIGHER_MEANS_BRIGHTER = true;  // set to false if your test showed the opposite

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(22, 23);   // Wire.begin(SDA pin, SCL pin)

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int raw = analogRead(LDR_PIN);
  int brightness = map(raw, 0, 4095, 100,0);

  bool isDark = brightness < DARK_THRESHOLD;

  display.clearDisplay();

  // Big line: DAYTIME or NIGHTTIME
  display.setTextSize(2);
  display.setCursor(0, 8);
  if (isDark) {
    display.println("NIGHTTIME");
    digitalWrite(LED_PIN, HIGH);
  } else {
    display.println("DAYTIME");
    digitalWrite(LED_PIN, LOW);
  }

  // Small line: brightness percentage
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Brightness: ");
  display.print(brightness);
  display.println("%");

  display.display();
  delay(300);
}
