# Custom 60%-Keyboard

![ESP32-S3](https://img.shields.io/badge/MCU-ESP32--S3-blue?logo=espressif)  
![License: MIT](https://img.shields.io/badge/License-MIT-green)  
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)  
![Made with C++](https://img.shields.io/badge/Made%20with-C++-orange?logo=c%2b%2b)  
![3D Printed](https://img.shields.io/badge/Case-3D%20Printed-purple)

---

A custom 60% ortholinear mechanical keyboard, built from scratch with a 3D-printed case and handwired matrix.  
Powered by an **ESP32-S3 Zero** microcontroller and programmed in **C++** for key scanning, debouncing, and USB HID input.

---

## Features

- Ortholinear (grid-style) key layout  
- 3D-printed case and plate design  
- Handwired switch matrix with diodes  
- ESP32-S3 Zero for USB HID functionality  
- Firmware written in C++ (Arduino / PlatformIO compatible)

---

## Bill of Materials

- ESP32-S3 Zero (microcontroller)  
- 63 × Blue mechanical switches
- 63 × 1N4148 diodes (one per switch)  
- Keycaps Cherry MX style
- Wires (24-26 AWG preferred for handwiring)  
- 3D-printed case & plate  
- Screws, brass threaded inserts, stabilizers

---

## Wiring (high level)

1. Decide your matrix rows × columns based on your ortholinear layout (common 60% ortholinear uses a grid sized to the key count).  
2. Handwire switches into a matrix: one side of each switch goes to a row wire, the other side goes through a diode to a column wire.  
3. **Diode orientation:** place the **1N4148** diode on each switch such that current flows from the switch toward the column/scan line. In practice, orient the diode with its **striped end (cathode)** pointing to the column/scan line (the MCU side). This prevents ghosting during matrix scanning.  
4. Route row and column wires to ESP32-S3 Zero GPIOs. Reserve a few extra GPIOs for indicators or encoders if needed. Use internal pull-ups or external resistors per your scanning routine.

![Final Keyboard](/images/Keyboard_Matrix_Circuit.png)  
*Keyboard Matrix Circuit — [Arduino Forum Reference](https://forum.arduino.cc/t/what-is-the-actual-circuitry-of-a-keypad-and-the-switch/1046828)*

---

## Assembly

- 3D-print the case and plate. Test fit switches and stabilizers before final assembly.  
- Solder diodes to switch pins first (striped end toward column).
- Solder row/column buses and label them (R0, R1, ... / C0, C1, ...).  
- Connect buses to the ESP32-S3 Zero following your planned pin mapping. Secure the MCU and wiring inside the case, then close and mount.

---

## Design & Gallery

The complete CAD model of the keyboard is included in the repository:  

- [`3d_model/60_keyboard.step`](./3D_Model/60_Keyboard.step)

---

![Final Keyboard](/images/Final_Keyboard.png)  
*Final keyboard — fully assembled.*

![3D Render Old](/images/3D_Render_Old.jpeg)  
*Early render — initial concept.*

![3D Model 4](/images/3D_Model_4.jpeg)  
*3D model — bottom view.*

![3D Model 3](/images/3D_Model_3.jpeg)  
*3D model — side view.*

![3D Model 2](/images/3D_Model_2.png)  
*3D model — top view.*

![3D Model 1](/images/3D_Model_1.png)  
*3D model — case design.*

![Frame Backside](/images/Frame_Backside.png)  
*Top-right — underside and keycaps points.*

![Top Right Frame with keys](/images/Top_Right_Frame_with_keys.png)  
*Top-right — keycap test fit.*

![3D_Print](/images/3D_Print.png)  
*Top-Left — 3D Print.*

![Top left frame](/images/Top_left_frame.png)  
*Top-left — Plate.*

![No keycaps](/images/No_keycaps.png)  
*Top view without keycaps — switch layout.*

![Handwired circuit](/images/Handwired_circuit.png)  
*Handwired matrix — bus routing. (Without Diodes)*

![Handwired circuit](/images/Circuit.jpg)  
*Handwired matrix circuit*

![Added Keys](/images/Added_Keys.png)  
*Partial assembly*

---

## Firmware

This project uses C++. You can use either the Arduino IDE (with ESP32 board installed) or PlatformIO.

### Quick start (Arduino IDE)

1. Install ESP32 board support (Espressif) in Arduino IDE.  
2. Open the provided `Firmware/` sketch.  
3. Edit the `ROW_PINS[]` and `COL_PINS[]` arrays to match your wiring.  
4. Select the ESP32-S3 Zero board and the correct port.  
5. Upload.

### Firmware notes

- Implement a debouncing routine (5–20 ms typical) to avoid chatter.  
- Use a matrix scanning algorithm that drives columns (or rows) actively and reads inputs on the other side.  
- Configure USB HID descriptors correctly for keyboard behavior.  
- Keep serial debugging optional (enable via a compile flag) so HID is unaffected.

---

## License

This project is licensed under the [MIT License](./license).  
Copyright (c) 2025 Mrinal Kumar

---
