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