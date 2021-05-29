[![](https://img.shields.io/badge/using-Processing-brightgreen.svg?style=flat-square&color=000000)](http://processing.org/)
[![](https://img.shields.io/badge/using-Arduino-brightgreen.svg?style=flat-square&color=000000)](http://arduino.cc/)

<p align="center">
  <img src="00 Assets/key.jpg" />
</p>

# floorScanners
Repository for the source code of an ongoing sound installation and performance. It was first presented at Resonate Festival in 2016 in its prototyped Version we called "Fine Tuning of Marble".


## Overview
* [Dependencies](#dependencies)
* [About](#about)
* [Classes](#classes)
* [PCB](#pcb)
* [Authors](#authors)

---

### About
tbd

---

### Dependencies
* [Automatic Orchestra Library](https://github.com/automatic-orchestra/ao_library)
* [AccelStepper Library, v1.51](http://www.airspayce.com/mikem/arduino/AccelStepper/)
* [MIDI, v3.2](https://www.pjrc.com/teensy/td_libs_MIDI.html)

---

### Classes
<font size="1">
	
| Classname         | Description                                   | No. of Methods    | Current working state |
|-------------------|-----------------------------------------------|-------------------|-----------------------|
| StateMachine      | Organize States of a floorScanner             | 4/4               | Working               |
| Clock             | Synchronize Scanners with a pulse             | N/A               | Deprecated (?)        |
| Motor             | Control Stepper Motor / Acceleration et al    | 11/11             | Working               |
| Score             | -                                             | N/A               | Deprecated (?)        |
| SensorHead        | Reading and storing sensordata on a circle    | 4/7               | Working               |
| Synth             | Synth output over speakers. Adjust timber etc | N/A               | Not working yet       |
| Communication     | Communication between Scanners over MIDI      | N/A               | Not working yet       |
| MacAddress        | Returns a Teensy MacAddress                   | 2/2               | Working               |

</font>

---

### PCB
Revisions
- [ ] Redesign the PCB stack into a single square board
- [ ] DRV8825 M0, M1, M2 to Pins
- [ ] Integrate TDA2030 circuit
- [ ] Switch terminal blocks with WAGO 2060 SMD
- [ ] Integrate PROTOSEQ circuit
- [ ] Expose all available pins
- [ ] Re-examine the audio interface between PROTOSEQ and TDA2030 (Is it really necessary to have the TDA2030?)

---

#### Authors
<sub>

Copyright (c) 2016 – 2021 (The Fine Tuning of Marble / floorScanners)
- &nearr; [Irena Kukric](https://www.irenakukric.com)
- &nearr; [Luiz Zanotello](https://www.luizzanotello.com)
- &nearr; [Julian Hespenheide](https://www.julian-h.de)

</sub>