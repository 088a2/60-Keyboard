#include <USB.h>
#include <Adafruit_NeoPixel.h>
#include <USBHIDKeyboard.h>
#include <USBHIDConsumerControl.h>
// #include <usb_hid_keys.h>

#include <keymap.h>
#include <update_led.h>
#include <Press_Hid.h>
#include <Release_Hid.h>

#define ROWS 5
#define COLS 13
#define DEBOUNCE_TIME 5  // ms

USBHIDKeyboard Keyboard;
USBHIDConsumerControl ConsumerControl;

const int colPins[COLS] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
const int rowPins[ROWS] = { 45, 42, 41, 17, 40 };

const int PIN_NEOPIXEL = 21;
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRBW + NEO_KHZ800);

bool capsOn = false;

bool layer1Active = false;
bool layer2Active = false;

bool keyState[ROWS][COLS] = { false };
unsigned long lastDebounceTime[ROWS][COLS] = { 0 };


void setup() {
  // Serial.begin(115200);
  Keyboard.begin();
  USB.begin();
  ConsumerControl.begin();

  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));
  pixels.show(); 

  for (int c = 0; c < COLS; c++) {
    pinMode(colPins[c], OUTPUT);
    digitalWrite(colPins[c], LOW);
  }
  for (int r = 0; r < ROWS; r++) {
    pinMode(rowPins[r], INPUT_PULLDOWN);
  }
}


void loop() {
  for (int c = 0; c < COLS; c++) {
    digitalWrite(colPins[c], HIGH);
    delayMicroseconds(30);

    for (int r = 0; r < ROWS; r++) {
      bool current = digitalRead(rowPins[r]) == HIGH;
      unsigned long now = millis();

      if (current != keyState[r][c] && (now - lastDebounceTime[r][c] > DEBOUNCE_TIME)) {
        const char* code = keyMap[r][c];
        if (current) {
          pressHID(code);
        } else {
          releaseHID(code);
        }
        keyState[r][c] = current;
        lastDebounceTime[r][c] = now;
      }
    }

    digitalWrite(colPins[c], LOW);
    updateCapsLED();
  }
}


// void CapsLEDTask(bool layer1, bool layer2) {
//   for (;;) {
//     if (capsOn) {
//       pixels.setPixelColor(0, pixels.Color(255, 255, 255, 0));  // white
//     }
//     if (layer1) {
//       pixels.setPixelColor(0, pixels.Color(0, 255, 0, 0));  // red
//     }
//     if (layer2) {
//       pixels.setPixelColor(0, pixels.Color(0, 0, 255, 0));  // blue
//     } else {
//       pixels.clear();
//     }
//     pixels.show();
//   }
// }
