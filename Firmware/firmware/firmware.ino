/*
Atlas Laboratories, LLC
Written by Stephen Hawes
Atlas Arm V5.0
Standard Hand Firmware
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

/* Pin Reference
 * A4 - I2C Data / Hitch Analog Pin
 * A5 - I2C Clock / Hitch Analog Pin
 * A6 - Hitch Analog Pin
 * A7 - EMG Signal
 * D3 - PWM / Interrupt / Hitch Digital Pin
 * D5 - PWM / Hitch Digital Pin
 *
 * D4 - Joy Up (A)
 * D6 - Joy Down (C)
 * D7 - Joy Left (B)
 * D8 - Joy Right (D)
 * D9 - Joy Center Press (Center)
 *
 *
 */

/*
 *
 *  LIBRARIES
 *
 */
//These libraries are from Adafruit that run the screen driver
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
//For storing calibration values
#include <EEPROM.h>
//For controlling grip strength
#include <PID_v1.h>



static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B11111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000011, B11111111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00001111, B00000001, B11100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00011100, B00000000, B01110000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00111000, B00000000, B00111000, B00000001, B10001001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00110000, B00000000, B00011000, B00000001, B10001001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B01100000, B00000000, B00001100, B00000011, B11011101, B00111000, B11100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B01100000, B00000000, B00001100, B00000010, B01001001, B00001001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00000000, B00000110, B00000011, B11001001, B00111000, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00000000, B00000110, B00000110, B01101001, B01001000, B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00000000, B00000110, B00000100, B00101101, B01111101, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00000000, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00010000, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00010000, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B11000000, B00111000, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B01100000, B00111000, B00001100, B00000100, B00000000, B01000000, B00000000, B00001000, B00000000, B10000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B01100000, B01010100, B00001100, B00000100, B00000000, B01000000, B00000000, B00001000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00110000, B01010100, B00011000, B00000100, B00001110, B01110001, B10011101, B11011100, B11001110, B10011100, B01110000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00111000, B11010110, B00111000, B00000100, B00000010, B01001010, B01010000, B01001001, B00101000, B10100010, B10000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00011100, B10010010, B01110000, B00000100, B00001110, B01001010, B01010001, B11001001, B00101000, B10111110, B01100000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00001111, B10010011, B11100000, B00000100, B00010010, B01001010, B01010010, B01001001, B00101000, B10100000, B00010000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000011, B11111111, B10000000, B00000111, B11011111, B01110001, B10010011, B11101100, B11001000, B10011100, B11100000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B01111100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000011, B00000001, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000111, B10111011, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000111, B00111001, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000001, B00111001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111
  };



//Defining joystick digital pins
#define joyUp       4
#define joyDown     6
#define joyLeft     7
#define joyRight    8
#define joyPress    9

//Defining analog pins
#define sphA1  A4
#define sphA2  A5
#define sphA3  A6
#define emg    A7

//Defining digital pins
#define sphD1  3
#define sphD2  5

//Defining size of EMG Cache
#define emgCacheSize  10

#define OLED_RESET A1


/* Holds position of current menu.
 *  0=main menu
 *  1=hand menu
 *  2=solder menu
 *  3=threshold menu
 *  4=hand select menu
 *  5=version menu
 *  6=calibrate menu
 */
int currentMenu = 0;
int currentWidth = 0;
int currentHand = 0;
bool motorTestStatus = false;
bool logoViewStatus = false;

//Joystick variables
int joyMemory = 0;

//EMG variables
int emgCache[emgCacheSize] = {0,0,0,0,0,0,0,0,0,0};
int newEmg = 0;
float avgEmg = 0;
int emgCachePosition = 0;
int summedCache = 0;
int state = 0; //0 for open, 1 for light squeeze, 2 for hard squeeze
int oldState = 0;

//EEPROM
//address in eeprom is 0
int eepromThreshold1 = 530;
//EEPROM.read(0);
//address in eeprom is 1
//int eepromThreshold2 = 90;
//EEPROM.read(1);
//address in eeprom is 2
int eepromNeutral = 0;
//EEPROM.read(2);

//PID
int PIDstate = 0;
double Kp = 2;
double Ki = 5;
double Kd = 1;
double handSetpoint = 150;
double input = 0;
double output = 0;

//PID
PID handPID(&input, &output, &handSetpoint, Kp, Ki, Kd, DIRECT);

//Display
Adafruit_SSD1306 display(OLED_RESET);

void setup() {

  //Serial
  Serial.begin(9600);
  Serial.println("ATLAS ARM V5.0");

  //Display

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 32, 1);
  display.display();
  delay(1000);
  display.clearDisplay();
  loadHandMenu(0);

  handPID.SetMode(AUTOMATIC);

}

void loop() {
  //main loop of OS!

  //serial out a bit of data for diagnostics
  Serial.print("Menu: " + currentMenu);
  Serial.println(" Width: " + currentWidth);

  //checking joystick and changing (and displaying) menu accordingly
  int joy = checkJoy();
  if(joyMemory != 0 && joy == 0){
    joyMemory = 0;
  }
  if (joy != joyMemory && joy != 0){
    changeMenu(joy);
    joyMemory = joy;
  }

  //running loops for specific menus
  if(currentMenu == 0 && currentWidth == 0){ //if on standard hand menu
    standardHandControl();
  }
  else if(currentMenu == 0 && currentWidth == 1){ //if on solder hand menu
    solderHandControl();
  }
  else if(currentMenu == 0 && currentWidth == 2){
    bikeHandControl();
  }
  else if(motorTestStatus){
    runPidHand();
  }
}
//END MAIN OS LOOP


int checkJoy(){
  //check joy returns an integer representing which direction the joystick is pointing. 0 for neutral, 1 for up, 2 for right, 3 for down, and 4 for left
  int upBit = digitalRead(joyUp);
  int downBit = digitalRead(joyDown);
  int leftBit = digitalRead(joyLeft);
  int rightBit = digitalRead(joyRight);
  int pressBit = digitalRead(joyPress);

  if(upBit){
    return 1;
  }
  else if(downBit){
    return 3;
  }
  else if(leftBit){
    return 4;
  }
  else if(rightBit){
    return 2;
  }
  else if(pressBit){
    return 5;
  }
  else{
    return 0;
  }

}

void standardHandControl(){
  /* loop run through for normal atlas arm peripheral
   * D3 is pwm
   * D5 is direction
   * A6 is current sense
   */

  //Gather and analize emg data to update "setpoint" variable which will come into effect in Motor segment below
  updateEmgAvg();
  Serial.println(avgEmg);
  if(avgEmg < eepromThreshold1){
    state = 0;
  }
  else{
    state = 1;
  }

  if(oldState == 0 && state == 1){ //think: only on the rising edge
    delay(100);
    for(int i=0;i<10;i++){
      updateEmgAvg();
    }
    if(avgEmg > eepromThreshold1){
      if(handSetpoint == 0){
        handSetpoint = 150;
      }
      else{
        handSetpoint = 0;
        //spin backwards slightly to open hand
        digitalWrite(5, LOW);
        analogWrite(3, 100);
        delay(100);
        analogWrite(3, 0);
      }
    }
    else{
      state = 0;
    }
  }

  oldState = state;

  //Change Motor PID in accordance with changes in EMG segment above

  runPidHand();

}

void solderHandControl(){
  digitalWrite(3, HIGH);
  delay(10);
  digitalWrite(3, LOW);
  delay(10);
}

void bikeHandControl(){
    digitalWrite(5, HIGH);
    delay(10);
    digitalWrite(5, LOW);
    delay(10);
}

//gets new emg value, replaces oldest emg value in cache, averages the cache, and saves the average to avgEmg
void updateEmgAvg(){
  //bring in new emg data point and add to cache.
  newEmg = analogRead(A7);
  summedCache = summedCache - emgCache[emgCachePosition];
  summedCache = summedCache + newEmg;

  emgCache[emgCachePosition] = newEmg;
  if(emgCachePosition == (emgCacheSize - 1)){
    emgCachePosition = 0;
  }
  else{
    emgCachePosition++;
  }

  avgEmg = summedCache / emgCacheSize;

}

/*
*
* Ok, here's the PID function.
* This function reads the analog pin,
*
*/

void runPidHand(){
  input = analogRead(A6);
  handPID.Compute();
  digitalWrite(5, HIGH);
  analogWrite(3, output);
}

void stopPidHand(){
  //spin backwards slightly to open hand
  digitalWrite(5, LOW);
  analogWrite(3, 100);
  delay(100);
  //kill analog write function
  analogWrite(3, 0);
}

/*
 *
 * MENU SHIT
 *
 */
void changeMenu(int joy){
  if((joy == 1 || joy == 3) && motorTestStatus == false && logoViewStatus == false){
    changeMenuVertical(joy);
  }
  else if((joy == 2 || joy == 4) && motorTestStatus == false && logoViewStatus == false){
    changeMenuHorizontal(joy);
  }
  else if(joy == 5){
    changeMenuClick();
  }
}

void changeMenuVertical(int joy){
  if (currentMenu == 0){
    if(joy == 3){
      if(currentWidth == 0){ //turn off hand if left on in hand menu while moving vertical
        stopPidHand();
      }
      loadSettingsMenu(0);
    }
  }
  else if(currentMenu == 1){ //Standard hand menu
    if(joy == 3){
      loadInfoMenu(0);
    }
    else{
      loadHandMenu(0);
    }
  }
  else if(currentMenu == 2){ //Solder hand menu
    if(joy == 1){
      loadSettingsMenu(0);
    }
  }

}

void changeMenuHorizontal(int joy){
  if (currentMenu == 0){
    if(joy == 2){
      if(currentWidth == 0){
        //turning off hand if left on while menu changes
        stopPidHand();
        //normal menu change
        loadHandMenu(1);
      }
      else if(currentWidth == 1){
        loadHandMenu(2);
      }
    }
    else if(joy == 4){
      if(currentWidth == 2){
        loadHandMenu(1);
      }
      else if(currentWidth == 1){
        loadHandMenu(0);
      }
    }
  }
  else if(currentMenu == 1){ //Standard hand menu
    if(joy == 2){
      if(currentWidth == 0){
        loadSettingsMenu(1);
      }
      else if(currentWidth == 1){
        loadSettingsMenu(2);
      }
    }
    else if(joy == 4){
      if(currentWidth == 2){
        loadSettingsMenu(1);
      }
      else if(currentWidth == 1){
        loadSettingsMenu(0);
      }
    }
  }
  else if(currentMenu == 2){ //Solder hand menu
    if(joy == 2){
      if(currentWidth == 0){
        loadInfoMenu(1);
      }
      else if(currentWidth == 1){
        loadInfoMenu(2);
      }
    }
    else if(joy == 4){
      if(currentWidth == 2){
        loadInfoMenu(1);
      }
      else if(currentWidth == 1){
        loadInfoMenu(0);
      }
    }
  }
}

void changeMenuClick(){
  if(currentMenu == 2 && currentWidth == 1){ // if we click on the "test" menu item
    if(motorTestStatus){ // ...and if we're already running the motor (and looking to shut it off)
      //turn motor off
      stopPidHand();
      motorTestStatus = false;
    }
    else{ // ..or we just navigated here and we're looking to test the motor and turn it on
      motorTestStatus = true;
    }
  }
  if(currentMenu == 2 && currentWidth == 2){ // if we click on the "logo" menu item
    if(logoViewStatus){
      loadInfoMenu(2);
      logoViewStatus = false;
    }
    else{
      display.clearDisplay();
      display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 32, 1);
      logoViewStatus = true;
      display.display();
    }
  }
}

void loadHandMenu(int width){ //0
  //clear display
  display.clearDisplay();
  //write header
  display.fillRect(0, 0, 128, 9, WHITE);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(1,1);
  display.print("Atlas Arm");

  //HAND MENU OPTION
  if(width == 0){
    drawMenuItem(0, 8, 6, "HAND", true);
    drawMenuItem(1, 2, 6, "SOLDER", false);
    drawMenuItem(2, 8, 6, "BIKE", false);

  }
  //solder hand MENU OPTION
  else if(width == 1){
    drawMenuItem(0, 8, 6, "HAND", false);
    drawMenuItem(1, 2, 6, "SOLDER", true);
    drawMenuItem(2, 8, 6, "BIKE", false);
  }

  //motorcycle MENU OPTION
  else if(width == 2){
    drawMenuItem(0, 8, 6, "HAND", false);
    drawMenuItem(1, 2, 6, "SOLDER", false);
    drawMenuItem(2, 8, 6, "BIKE", true);
  }
  //setting current screen:
  currentMenu = 0;
  currentWidth = width;
  display.display();
}

void loadSettingsMenu(int width){ //1
  //clear display
  display.clearDisplay();
  //write header
  display.fillRect(0, 0, 128, 9, WHITE);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(1,1);
  display.print("Settings");

  //HAND MENU OPTION
  if(width == 0){
    drawMenuItem(0, 5, 6, "PULSE", true);
    drawMenuItem(1, 8, 6, "HOLD", false);
    drawMenuItem(2, 2, 6, "TEIRED", false);

  }
  //solder hand MENU OPTION
  else if(width == 1){
    drawMenuItem(0, 5, 6, "PULSE", false);
    drawMenuItem(1, 8, 6, "HOLD", true);
    drawMenuItem(2, 2, 6, "TEIRED", false);
  }

  //motorcycle MENU OPTION
  else if(width == 2){
    drawMenuItem(0, 5, 6, "PULSE", false);
    drawMenuItem(1, 8, 6, "HOLD", false);
    drawMenuItem(2, 2, 6, "TEIRED", true);
  }
  //setting current screen:
  currentMenu = 1;
  currentWidth = width;
  display.display();

}

void loadInfoMenu(int width){ //2
  //clear display
  display.clearDisplay();
  //write header
  display.fillRect(0, 0, 128, 9, WHITE);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(1,1);
  display.print("Info");

  //HAND MENU OPTION
  if(width == 0){
    drawMenuItem(0, 5, 6, "STATS", true);
    drawMenuItem(1, 8, 6, "TEST", false);
    drawMenuItem(2, 8, 6, "LOGO", false);

  }
  //solder hand MENU OPTION
  else if(width == 1){
    drawMenuItem(0, 5, 6, "STATS", false);
    drawMenuItem(1, 8, 6, "TEST", true);
    drawMenuItem(2, 8, 6, "LOGO", false);
  }
  else if(width == 2){
    drawMenuItem(0, 5, 6, "STATS", false);
    drawMenuItem(1, 8, 6, "TEST", false);
    drawMenuItem(2, 8, 6, "LOGO", true);
  }

  //setting current screen:
  currentMenu = 2;
  currentWidth = width;
  display.display();

}

void drawMenuItem(int pos, int x, int y, String title, bool active){
  int yBOX=11;
  int xBOX;
  if(pos == 0){
    xBOX = 1;
  }
  else if(pos == 1){
    xBOX = 44;
  }
  else if(pos == 2){
    xBOX = 87;
  }
  if(active){
    display.fillRoundRect(xBOX, yBOX, 40, 20, 3, WHITE);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(xBOX+x, yBOX+y);
    display.print(title);
  }
  else{
    display.drawRoundRect(xBOX, yBOX, 40, 20, 3, WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(xBOX+x, yBOX+y);
    display.print(title);
  }


}
