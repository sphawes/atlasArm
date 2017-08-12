/*
Atlas Laboratories, LLC
Written by Stephen Hawes
Atlas Arm V5.0
Find Pad Locations Script
*/

/*
Copyright (c) 2017 Stephen Hawes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
INSTRUCTIONS:

This script is to help aid in the process of determining the ideal locations for EMG sensor pads to be placed. Read the datasheet for the Advancer Technologies EMG board (Hardware/emgBoard.pdf) for instructions about finding pad locations and wiring. Use Analog pin 0 for the signal from the EMG board. If the Arduino is connected to the computer, use the Serial Plotter for a visual represenatation of the signal coming from the board. The on-board LED connected to pin 13 will increase in brightness according to the intensity of the signal for an untethered wiring setup.
*/

int emgInput = A0;
void setup() {
  Serial.begin(9600);
}
void loop() {
    int emg = analogRead(emgInput);
    Serial.write(emg);
    digitalWrite(13, HIGH);
    delay((1024-emg)/100);
    digitalWrite(13, LOW);
    delay(30);
}
