#pragma once

void updateCapsLED() {
  if (capsOn) pixels.setPixelColor(0, pixels.Color(255, 255, 255, 0));       // white
  else if (!capsOn && !(layer1Active || layer2Active)) pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));  // green
  else if (!capsOn && layer1Active) pixels.setPixelColor(0, pixels.Color(0, 0, 255, 0));  // blue
  else if (!capsOn && layer2Active) pixels.setPixelColor(0, pixels.Color(0, 255, 0, 0));  // red
  pixels.show();
}