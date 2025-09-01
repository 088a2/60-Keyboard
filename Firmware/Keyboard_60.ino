#include <USB.h>
#include <USBHIDKeyboard.h>
#include <Adafruit_NeoPixel.h>
#include <USBHIDConsumerControl.h>
// #include <usb_hid_keys.h>

#define ROWS 5
#define COLS 13
#define DEBOUNCE_TIME 5  // ms

USBHIDKeyboard Keyboard;
USBHIDConsumerControl ConsumerControl;

const int colPins[COLS] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
const int rowPins[ROWS] = { 45, 42, 41, 17, 40 };

const char* keyMap[ROWS][COLS] = {
  { "KC_ESC", "KC_1", "KC_2", "KC_3", "KC_4", "KC_5", "KC_6", "KC_7", "KC_8", "KC_9", "KC_0", "KC_BSLS", "KC_BSPC" },
  { "KC_TAB", "KC_Q", "KC_W", "KC_E", "KC_R", "KC_T", "KC_Y", "KC_U", "KC_I", "KC_O", "KC_P", "KC_MINS", "KC_EQL" },
  { "KC_CAPS", "KC_A", "KC_S", "KC_D", "KC_F", "KC_G", "KC_H", "KC_J", "KC_K", "KC_L", "KC_SCLN", "KC_QUOT", "KC_ENT" },
  { "KC_LSFT", "KC_Z", "KC_X", "KC_C", "KC_V", "KC_B", "KC_N", "KC_M", "KC_COMM", "KC_DOT", "KC_SLSH", "KC_LBRC", "KC_RBRC" },
  { "KC_LCTL", "MO(1)", "KC_LGUI", "KC_LALT", "KC_NO", "KC_SPC", "KC_NO", "KC_RALT", "KC_RCTL", "MO(2)", "KC_PGUP", "KC_PGDN", "KC_HOME" }
};

const int PIN_NEOPIXEL = 21;
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRBW + NEO_KHZ800);

bool capsOn = false;

// track each key’s last stable state
bool keyState[ROWS][COLS] = { false };
unsigned long lastDebounceTime[ROWS][COLS] = { 0 };

void setup() {
  // Serial.begin(115200);
  Keyboard.begin();
  USB.begin();
  ConsumerControl.begin();

  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));
  pixels.show();  // all off

  // init columns
  for (int c = 0; c < COLS; c++) {
    pinMode(colPins[c], OUTPUT);
    digitalWrite(colPins[c], LOW);
  }
  // init rows
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
        // state changed and debounce time passed
        const char* code = keyMap[r][c];
        if (current) {
          // Serial.print("PRESS: "); Serial.println(code);
          pressHID(code);
        } else {
          releaseHID(code);
        }
        keyState[r][c] = current;
        lastDebounceTime[r][c] = now;
      }
    }

    digitalWrite(colPins[c], LOW);
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
//     vTaskDelay(50 / portTICK_PERIOD_MS);  // Check every 50ms
//   }
// }

// handle non-modifier & modifier presses
bool layer1Active = false;
bool layer2Active = false;

void updateCapsLED() {
  if (capsOn) pixels.setPixelColor(0, pixels.Color(255, 255, 255, 0));       // white
  else if (!capsOn && !(layer1Active || layer2Active)) pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));  // green
  else if (!capsOn && layer1Active) pixels.setPixelColor(0, pixels.Color(0, 0, 255, 0));  // green
  else if (!capsOn && layer2Active) pixels.setPixelColor(0, pixels.Color(0, 255, 0, 0));  // green
  pixels.show();
}

void pressHID(const char* code) {
  if (!strcmp(code, "MO(1)")) {
    layer1Active = true;
    pixels.setPixelColor(0, pixels.Color(0, 0, 255, 0));  // blue
    pixels.show();
    return;
  }

  if (layer1Active) {
    if (!strcmp(code, "KC_W")) {
      Keyboard.press(KEY_UP_ARROW);
      return;
    }
    if (!strcmp(code, "KC_S")) {
      Keyboard.press(KEY_DOWN_ARROW);
      return;
    }
    if (!strcmp(code, "KC_A")) {
      Keyboard.press(KEY_LEFT_ARROW);
      return;
    }
    if (!strcmp(code, "KC_D")) {
      Keyboard.press(KEY_RIGHT_ARROW);
      return;
    }
    if (!strcmp(code, "KC_BSPC")) {
      Keyboard.press(KEY_DELETE);
      return;
    }
    if (!strcmp(code, "KC_ESC")) {
      Keyboard.pressRaw(0x35);
      return;
    }

    // Media Control
    if (!strcmp(code, "KC_1")) {
      ConsumerControl.press(CONSUMER_CONTROL_MUTE);
      return;
    }
    if (!strcmp(code, "KC_2")) {
      ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
      return;
    }
    if (!strcmp(code, "KC_3")) {
      ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
      return;
    }
    if (!strcmp(code, "KC_4")) {
      ConsumerControl.press(CONSUMER_CONTROL_SCAN_PREVIOUS);
      return;
    }
    if (!strcmp(code, "KC_5")) {
      ConsumerControl.press(CONSUMER_CONTROL_PLAY_PAUSE);
      return;
    }
    if (!strcmp(code, "KC_6")) {
      ConsumerControl.press(CONSUMER_CONTROL_SCAN_NEXT);
      return;
    }
    if (!strcmp(code, "KC_9")) {
      ConsumerControl.press(CONSUMER_CONTROL_SEARCH);
      return;
    }
    if (!strcmp(code, "KC_0")) {
      ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
      return;
    }
    if (!strcmp(code, "KC_BSLS")) {
      ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
      return;
    }
    if (!strcmp(code, "KC_HOME")) {
      Keyboard.press(KEY_END);
      return;
    }
  }

  if (!strcmp(code, "MO(2)")) {
    layer2Active = true;
    pixels.setPixelColor(0, pixels.Color(0, 255, 0, 0));  // red
    pixels.show();
    return;
  }

  if (layer2Active) {
    if (!strcmp(code, "KC_1")) {
      Keyboard.press(KEY_F1);
      return;
    }
    if (!strcmp(code, "KC_2")) {
      Keyboard.press(KEY_F2);
      return;
    }
    if (!strcmp(code, "KC_3")) {
      Keyboard.press(KEY_F3);
      return;
    }
    if (!strcmp(code, "KC_4")) {
      Keyboard.press(KEY_F4);
      return;
    }
    if (!strcmp(code, "KC_5")) {
      Keyboard.press(KEY_F5);
      return;
    }
    if (!strcmp(code, "KC_6")) {
      Keyboard.press(KEY_F6);
      return;
    }
    if (!strcmp(code, "KC_7")) {
      Keyboard.press(KEY_F7);
      return;
    }
    if (!strcmp(code, "KC_8")) {
      Keyboard.press(KEY_F8);
      return;
    }
    if (!strcmp(code, "KC_9")) {
      Keyboard.press(KEY_F9);
      return;
    }
    if (!strcmp(code, "KC_0")) {
      Keyboard.press(KEY_F10);
      return;
    }
    if (!strcmp(code, "KC_BSLS")) {
      Keyboard.press(KEY_F11);
      return;
    }
    if (!strcmp(code, "KC_BSPC")) {
      Keyboard.press(KEY_F12);
      return;
    }
  }

  // modifiers
  if (!strcmp(code, "KC_LCTL")) Keyboard.press(KEY_LEFT_CTRL);
  else if (!strcmp(code, "KC_RCTL")) Keyboard.press(KEY_RIGHT_CTRL);
  else if (!strcmp(code, "KC_LSFT")) Keyboard.press(KEY_LEFT_SHIFT);
  else if (!strcmp(code, "KC_LALT")) Keyboard.press(KEY_LEFT_ALT);
  else if (!strcmp(code, "KC_RALT")) Keyboard.press(KEY_RIGHT_ALT);
  else if (!strcmp(code, "KC_CAPS")) Keyboard.press(KEY_CAPS_LOCK);
  else if (!strcmp(code, "KC_LGUI")) Keyboard.press(KEY_LEFT_GUI);


  // normal keys
  else if (!strcmp(code, "KC_A")) Keyboard.press('a');
  else if (!strcmp(code, "KC_B")) Keyboard.press('b');
  else if (!strcmp(code, "KC_C")) Keyboard.press('c');
  else if (!strcmp(code, "KC_D")) Keyboard.press('d');
  else if (!strcmp(code, "KC_E")) Keyboard.press('e');
  else if (!strcmp(code, "KC_F")) Keyboard.press('f');
  else if (!strcmp(code, "KC_G")) Keyboard.press('g');
  else if (!strcmp(code, "KC_H")) Keyboard.press('h');
  else if (!strcmp(code, "KC_I")) Keyboard.press('i');
  else if (!strcmp(code, "KC_J")) Keyboard.press('j');
  else if (!strcmp(code, "KC_K")) Keyboard.press('k');
  else if (!strcmp(code, "KC_L")) Keyboard.press('l');
  else if (!strcmp(code, "KC_M")) Keyboard.press('m');
  else if (!strcmp(code, "KC_N")) Keyboard.press('n');
  else if (!strcmp(code, "KC_O")) Keyboard.press('o');
  else if (!strcmp(code, "KC_P")) Keyboard.press('p');
  else if (!strcmp(code, "KC_Q")) Keyboard.press('q');
  else if (!strcmp(code, "KC_R")) Keyboard.press('r');
  else if (!strcmp(code, "KC_S")) Keyboard.press('s');
  else if (!strcmp(code, "KC_T")) Keyboard.press('t');
  else if (!strcmp(code, "KC_U")) Keyboard.press('u');
  else if (!strcmp(code, "KC_V")) Keyboard.press('v');
  else if (!strcmp(code, "KC_W")) Keyboard.press('w');
  else if (!strcmp(code, "KC_X")) Keyboard.press('x');
  else if (!strcmp(code, "KC_Y")) Keyboard.press('y');
  else if (!strcmp(code, "KC_Z")) Keyboard.press('z');
  else if (!strcmp(code, "KC_1")) Keyboard.press('1');
  else if (!strcmp(code, "KC_2")) Keyboard.press('2');
  else if (!strcmp(code, "KC_3")) Keyboard.press('3');
  else if (!strcmp(code, "KC_4")) Keyboard.press('4');
  else if (!strcmp(code, "KC_5")) Keyboard.press('5');
  else if (!strcmp(code, "KC_6")) Keyboard.press('6');
  else if (!strcmp(code, "KC_7")) Keyboard.press('7');
  else if (!strcmp(code, "KC_8")) Keyboard.press('8');
  else if (!strcmp(code, "KC_9")) Keyboard.press('9');
  else if (!strcmp(code, "KC_0")) Keyboard.press('0');

  else if (!strcmp(code, "KC_MINS")) Keyboard.press('-');
  else if (!strcmp(code, "KC_EQL")) Keyboard.press('=');
  else if (!strcmp(code, "KC_COMM")) Keyboard.press(',');
  else if (!strcmp(code, "KC_DOT")) Keyboard.press('.');
  else if (!strcmp(code, "KC_SLSH")) Keyboard.press('/');
  else if (!strcmp(code, "KC_SCLN")) Keyboard.press(';');
  else if (!strcmp(code, "KC_QUOT")) Keyboard.press('\'');
  else if (!strcmp(code, "KC_BSLS")) Keyboard.press('\\');
  else if (!strcmp(code, "KC_LBRC")) Keyboard.press('[');
  else if (!strcmp(code, "KC_RBRC")) Keyboard.press(']');
  else if (!strcmp(code, "KC_SPC")) Keyboard.press(' ');
  else if (!strcmp(code, "KC_ENT")) Keyboard.press('\n');
  else if (!strcmp(code, "KC_TAB")) Keyboard.press('\t');

  else if (!strcmp(code, "KC_ESC")) Keyboard.press(KEY_ESC);
  else if (!strcmp(code, "KC_BSPC")) Keyboard.press(KEY_BACKSPACE);
  else if (!strcmp(code, "KC_PGUP")) Keyboard.press(KEY_PAGE_UP);
  else if (!strcmp(code, "KC_PGDN")) Keyboard.press(KEY_PAGE_DOWN);
  else if (!strcmp(code, "KC_HOME")) Keyboard.press(KEY_HOME);

  if (!strcmp(code, "KC_CAPS")) {
    capsOn = !capsOn;
    updateCapsLED();
    return;
  }
}

// release keys/modifiers
void releaseHID(const char* code) {
  if (!strcmp(code, "MO(1)")) {
    layer1Active = false;
    if (!capsOn) pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));
    if (capsOn) pixels.setPixelColor(0, pixels.Color(255, 255, 255, 0));
    pixels.show();

    Keyboard.release(KEY_UP_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_DELETE);
    Keyboard.releaseRaw(0x35);
    Keyboard.release(KEY_END);

    ConsumerControl.release();
    return;
  }

  if (layer1Active) {
    if (!strcmp(code, "KC_W")) {
      Keyboard.release(KEY_UP_ARROW);
      return;
    }
    if (!strcmp(code, "KC_S")) {
      Keyboard.release(KEY_DOWN_ARROW);
      return;
    }
    if (!strcmp(code, "KC_A")) {
      Keyboard.release(KEY_LEFT_ARROW);
      return;
    }
    if (!strcmp(code, "KC_D")) {
      Keyboard.release(KEY_RIGHT_ARROW);
      return;
    }
    if (!strcmp(code, "KC_BSPC")) {
      Keyboard.release(KEY_DELETE);
      return;
    }
    if (!strcmp(code, "KC_ESC")) {
      Keyboard.releaseRaw(0x35);
      return;
    }

    // Media Control
    if (!strcmp(code, "KC_1")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_2")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_3")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_4")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_5")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_6")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_9")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_0")) {
      ConsumerControl.release();
      return;
    }
    if (!strcmp(code, "KC_BSLS")) {
      ConsumerControl.release();
      return;
    }

    if (!strcmp(code, "KC_HOME")) {
      Keyboard.release(KEY_END);
      return;
    }
  }

  if (!strcmp(code, "MO(2)")) {
    layer2Active = false;
    if (!capsOn) pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));
    if (capsOn) pixels.setPixelColor(0, pixels.Color(255, 255, 255, 0));
    pixels.show();

    Keyboard.release(KEY_F1);
    Keyboard.release(KEY_F2);
    Keyboard.release(KEY_F3);
    Keyboard.release(KEY_F4);
    Keyboard.release(KEY_F5);
    Keyboard.release(KEY_F6);
    Keyboard.release(KEY_F7);
    Keyboard.release(KEY_F8);
    Keyboard.release(KEY_F9);
    Keyboard.release(KEY_F10);
    Keyboard.release(KEY_F11);
    Keyboard.release(KEY_F11);
    Keyboard.releaseRaw(0x35);
    return;
  }

  if (layer2Active) {
    if (!strcmp(code, "KC_1")) {
      Keyboard.release(KEY_F1);
      return;
    }
    if (!strcmp(code, "KC_2")) {
      Keyboard.release(KEY_F2);
      return;
    }
    if (!strcmp(code, "KC_3")) {
      Keyboard.release(KEY_F3);
      return;
    }
    if (!strcmp(code, "KC_4")) {
      Keyboard.release(KEY_F4);
      return;
    }
    if (!strcmp(code, "KC_5")) {
      Keyboard.release(KEY_F5);
      return;
    }
    if (!strcmp(code, "KC_6")) {
      Keyboard.release(KEY_F6);
      return;
    }
    if (!strcmp(code, "KC_7")) {
      Keyboard.release(KEY_F7);
      return;
    }
    if (!strcmp(code, "KC_8")) {
      Keyboard.release(KEY_F8);
      return;
    }
    if (!strcmp(code, "KC_9")) {
      Keyboard.release(KEY_F9);
      return;
    }
    if (!strcmp(code, "KC_0")) {
      Keyboard.release(KEY_F10);
      return;
    }
    if (!strcmp(code, "KC_BSLS")) {
      Keyboard.release(KEY_F11);
      return;
    }
    if (!strcmp(code, "KC_BSPC")) {
      Keyboard.release(KEY_F12);
      return;
    }
  }


  if (!strcmp(code, "KC_LCTL")) Keyboard.release(KEY_LEFT_CTRL);
  else if (!strcmp(code, "KC_RCTL")) Keyboard.release(KEY_RIGHT_CTRL);
  else if (!strcmp(code, "KC_LSFT")) Keyboard.release(KEY_LEFT_SHIFT);
  else if (!strcmp(code, "KC_LALT")) Keyboard.release(KEY_LEFT_ALT);
  else if (!strcmp(code, "KC_RALT")) Keyboard.release(KEY_RIGHT_ALT);
  else if (!strcmp(code, "KC_CAPS")) Keyboard.release(KEY_CAPS_LOCK);
  else if (!strcmp(code, "KC_LGUI")) Keyboard.release(KEY_LEFT_GUI);


  else if (!strcmp(code, "KC_A")) Keyboard.release('a');
  else if (!strcmp(code, "KC_B")) Keyboard.release('b');
  else if (!strcmp(code, "KC_C")) Keyboard.release('c');
  else if (!strcmp(code, "KC_D")) Keyboard.release('d');
  else if (!strcmp(code, "KC_E")) Keyboard.release('e');
  else if (!strcmp(code, "KC_F")) Keyboard.release('f');
  else if (!strcmp(code, "KC_G")) Keyboard.release('g');
  else if (!strcmp(code, "KC_H")) Keyboard.release('h');
  else if (!strcmp(code, "KC_I")) Keyboard.release('i');
  else if (!strcmp(code, "KC_J")) Keyboard.release('j');
  else if (!strcmp(code, "KC_K")) Keyboard.release('k');
  else if (!strcmp(code, "KC_L")) Keyboard.release('l');
  else if (!strcmp(code, "KC_M")) Keyboard.release('m');
  else if (!strcmp(code, "KC_N")) Keyboard.release('n');
  else if (!strcmp(code, "KC_O")) Keyboard.release('o');
  else if (!strcmp(code, "KC_P")) Keyboard.release('p');
  else if (!strcmp(code, "KC_Q")) Keyboard.release('q');
  else if (!strcmp(code, "KC_R")) Keyboard.release('r');
  else if (!strcmp(code, "KC_S")) Keyboard.release('s');
  else if (!strcmp(code, "KC_T")) Keyboard.release('t');
  else if (!strcmp(code, "KC_U")) Keyboard.release('u');
  else if (!strcmp(code, "KC_V")) Keyboard.release('v');
  else if (!strcmp(code, "KC_W")) Keyboard.release('w');
  else if (!strcmp(code, "KC_X")) Keyboard.release('x');
  else if (!strcmp(code, "KC_Y")) Keyboard.release('y');
  else if (!strcmp(code, "KC_Z")) Keyboard.release('z');
  else if (!strcmp(code, "KC_1")) Keyboard.release('1');
  else if (!strcmp(code, "KC_2")) Keyboard.release('2');
  else if (!strcmp(code, "KC_3")) Keyboard.release('3');
  else if (!strcmp(code, "KC_4")) Keyboard.release('4');
  else if (!strcmp(code, "KC_5")) Keyboard.release('5');
  else if (!strcmp(code, "KC_6")) Keyboard.release('6');
  else if (!strcmp(code, "KC_7")) Keyboard.release('7');
  else if (!strcmp(code, "KC_8")) Keyboard.release('8');
  else if (!strcmp(code, "KC_9")) Keyboard.release('9');
  else if (!strcmp(code, "KC_0")) Keyboard.release('0');

  else if (!strcmp(code, "KC_MINS")) Keyboard.release('-');
  else if (!strcmp(code, "KC_EQL")) Keyboard.release('=');
  else if (!strcmp(code, "KC_COMM")) Keyboard.release(',');
  else if (!strcmp(code, "KC_DOT")) Keyboard.release('.');
  else if (!strcmp(code, "KC_SLSH")) Keyboard.release('/');
  else if (!strcmp(code, "KC_SCLN")) Keyboard.release(';');
  else if (!strcmp(code, "KC_QUOT")) Keyboard.release('\'');
  else if (!strcmp(code, "KC_BSLS")) Keyboard.release('\\');
  else if (!strcmp(code, "KC_LBRC")) Keyboard.release('[');
  else if (!strcmp(code, "KC_RBRC")) Keyboard.release(']');
  else if (!strcmp(code, "KC_SPC")) Keyboard.release(' ');
  else if (!strcmp(code, "KC_ENT")) Keyboard.release('\n');
  else if (!strcmp(code, "KC_TAB")) Keyboard.release('\t');

  else if (!strcmp(code, "KC_ESC")) Keyboard.release(KEY_ESC);
  else if (!strcmp(code, "KC_BSPC")) Keyboard.release(KEY_BACKSPACE);
  else if (!strcmp(code, "KC_PGUP")) Keyboard.release(KEY_PAGE_UP);
  else if (!strcmp(code, "KC_PGDN")) Keyboard.release(KEY_PAGE_DOWN);
  else if (!strcmp(code, "KC_HOME")) Keyboard.release(KEY_HOME);
}
