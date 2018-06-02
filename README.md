# SoundReactiveNeoPixelRing
This code lights up a NeoPixel ring according to the sound volume in the environment.

Background
----------
1. Each NeoPixel includes three distinct LEDs: one red, one green and one blue.
2. The Arduino code lights up each of the LED colors seperately according to the sound picked up by the sensor:
   1. Red: brightness ramps up from 0% to 100% in a linear fashion.
   2. Green: brightness ramps down from 20% to 0% along a 1/x graph.
   3. Blue: brightness increases from 0% to 50% and then decreases back to 0% along a gaussian graph.

Components
----------
- 1 Arduino Uno
- 1 NeoPixel Ring 12 
- 2 100 ohm Resistors
- 1 47uF, 35V Polarized Capacitor
- 1 MAX4466 Microphone Amplifier

Circuit Diagram
---------------
![Circuit Diagram](Circuit.png?raw=true "Circuit Diagram")

Notes
-----
1. The NeoPixel ring requires 5V to operate
2. The MAX4466 Microphone Amplifier requires 3V to operate (*don't burn it out*)
3. Without the Resistors and Capacitor, the readings from the MAX4466 Microphone Amplifier will be all wrong, don't leave them out
