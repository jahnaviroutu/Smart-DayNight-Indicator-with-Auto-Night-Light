# Smart-DayNight-Indicator-with-Auto-Night-Light
# Smart Day/Night Indicator with Auto Night Light

An ESP32 project that reads ambient light with an LDR (Light Dependent Resistor), shows **DAYTIME** or **NIGHTTIME** on an OLED display, and switches an LED on automatically when it gets dark, like a basic automatic night light.

## Problem
Lights that have to be switched on and off by hand waste energy and are easy to forget. Streetlights, corridor lights and night lamps all use the same idea: sense the light level and react automatically.

## What it does
- Reads the light level from a photoresistor (LDR) sensor
- Converts the raw reading into a 0–100% brightness value
- If brightness is below the threshold (30%), it is **NIGHTTIME**: the LED turns on
- Otherwise it is **DAYTIME**: the LED turns off
- Shows the status and the live brightness percentage on a 128x64 OLED display

## Components
- ESP32 (simulated in Wokwi)
- Photoresistor (LDR) sensor module
- SSD1306 OLED display (I2C)
- LED

## Circuit Diagram
![Circuit Diagram](circuit-diagram.png)

## Output
**Daytime** (high brightness, LED off):

![Daytime output](daytime.png)

**Nighttime** (low brightness, LED on):

![Nighttime output](nighttime.png)

## How it works
1. The LDR's resistance changes with light: low in bright light, high in darkness. The sensor module turns this into a voltage on its analog output (AO) pin.
2. The ESP32's ADC (Analog-to-Digital Converter) reads that voltage as a number from 0 to 4095 using `analogRead()`.
3. `map()` converts the 0–4095 reading into a 0–100% brightness value, so the threshold doesn't depend on the ADC range.
4. If brightness is below `DARK_THRESHOLD`, the code decides it is night. The LED turns on and the OLED shows NIGHTTIME. Otherwise the LED is off and the OLED shows DAYTIME.
5. The loop repeats every 300 ms, so the display and LED follow the light almost immediately.

A `HIGHER_MEANS_BRIGHTER` setting in the code flips the scale, because some sensor modules read high in the dark and low in the light.

## Pin connections (ESP32)
| Component     | Pin                              |
|---------------|----------------------------------|
| LDR sensor AO | GPIO 34                          |
| LED           | GPIO 5 (through a 220Ω resistor) |
| OLED SDA      | GPIO 22                          |
| OLED SCL      | GPIO 23                          |



 

## New concepts I learned building this
- **LDR (Light Dependent Resistor):** a sensor whose resistance changes with light, and how a voltage divider turns that change into a readable voltage
- **ADC resolution:** why ESP32 reads 0–4095 (12-bit) while Arduino Uno reads 0–1023 (10-bit)
- **`map()`:** scaling a raw sensor range into a useful 0–100% range
- **Lux:** the unit for light intensity, used to simulate day and night in Wokwi
- **`bool` and `!` (NOT):** true/false variables, and flipping the scale with one setting
- **`print()` vs `println()`:** building one line of OLED text from several parts
- **Reusing I2C:** wiring the same OLED setup from my parking project to a new sensor

## Try it live
[Click here to run the simulation on Wokwi](https://wokwi.com/projects/478216393236856833)

## What I'd add next
- Hysteresis (two thresholds) so the LED doesn't flicker when the light is near the boundary
- Logging brightness over time
- Sending the day/night status to a cloud dashboard
