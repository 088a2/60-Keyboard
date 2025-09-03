#pragma once

#include <USBHIDKeyboard.h>
#include <USBHIDConsumerControl.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>

extern USBHIDKeyboard Keyboard;
extern USBHIDConsumerControl ConsumerControl;
extern Adafruit_NeoPixel pixels;
extern bool layer1Active;
extern bool layer2Active;
extern bool capsOn;


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