//Atlas Laboratories, LLC
//Copyright 2017
//Written by Stephen Hawes
//EMG Prosthetic Hand Firmware
//Atlas Arm V4.0

//These libraries are from Adafruit that run the screen driver
//The SPI library is also for this
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
//#include <SD.h>

//For storing calibration values
#include <EEPROM.h>

//For controlling grip strength
#include <PID_v1.h>

//Defining I2C pins for the screen and all I2C peripheral attachments
#define I2C_SCK     3
#define I2C_DTA     4

//Defining joystick digital pins
#define joyUp       5
#define joyDown     6
#define joyLeft     7
#define joyRight    8
#define joyPress    9

//Defining analog pins
#define sphA1  A0
#define sphA2  A1
#define emg    A2

//Defining digital pins
#define sphD1  10
#define sphD2  11

//Defining size of EMG Cache
#define emgCacheSize  10

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
int currentHeight = 0;

//Joystick variables
int joyMemory = 0;
int joyDeadZoneTolerance = 100;

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
double setpoint = 0;
double input = 0;
double output = 0;



//Creates a new tft object that we can use to write to the screen
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
//myPID.SetControllerDirection(DIRECT);

void setup() {

  Serial.begin(9600);


  myPID.SetMode(AUTOMATIC);

  digitalWrite(dcDirection1, HIGH);
  digitalWrite(dcDirection2, LOW);


  //Initialize TFT screen
  tft.initR(INITR_BLACKTAB);

  //Accessing SD card
//  Serial.print("Initializing SD card...");
//  if (!SD.begin(SD_CS)) {
//   Serial.println("Failed!");
//    return;
//  }
  Serial.println("ATLAS ARM V2.0");

  void setRotation(uint8_t rotation);

  //Draw spashscreen
//  bmpDraw("splashscreen.bmp", 0, 0);
  loadMainMenu(0);
}

void loop() {
  //main loop of OS
  int joy = checkJoy();
  //Serial.print(joy);
  //Serial.println(currentMenu);
  if(joyMemory != 0 && joy == 0){
    joyMemory = 0;
  }
  if (joy != joyMemory && joy != 0){
    changeMenu(joy);
    joyMemory = joy;
  }


  if(currentMenu == 1){ //if on standard hand menu
    standardHandControl();

    //Serial.println(input);
/*
    if(setpoint == 0){
      myPID.SetControllerDirection(REVERSE);
      digitalWrite(dcDirection1, LOW);
      digitalWrite(dcDirection2, HIGH);
    }
    else{
      myPID.SetControllerDirection(DIRECT);
      digitalWrite(dcDirection1, HIGH);
      digitalWrite(dcDirection2, LOW);
    }

    updatePID();
*/
  }

  if(currentMenu == 2){ //if on solder hand menu
    solderHandControl();
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

void standardHandControl(){  //Get new EMG value from board,
  updateEmg();
  Serial.println(avgEmg);
  if(avgEmg < eepromThreshold1){
    state = 0;
  }
  else{
    state = 1;
  }

  if(oldState == 0 && state == 1){
    for(int i=0;i<20;i++){
      updateEmg();
      delay(10);
    }
    if(avgEmg > eepromThreshold1){
      if(setpoint == 0){
        digitalWrite(dcDirection1, HIGH);
        digitalWrite(dcDirection2, LOW);
        analogWrite(dcSpeed, 255);
        delay(500);
        analogWrite(dcSpeed, 153);
        setpoint = 1;
      }
      else{
        setpoint = 0;
        //spin backwards slightly to open hand
        digitalWrite(dcDirection1, LOW);
        digitalWrite(dcDirection2, HIGH);
        analogWrite(dcSpeed, 255);
        delay(140);
        analogWrite(dcSpeed, 0);
        digitalWrite(dcDirection1, HIGH);
        digitalWrite(dcDirection2, LOW);
      }
    }
    else{
      state = 0;
    }
  }

  oldState = state;

}

void solderHandControl(){
  updateEmg();
  Serial.println(avgEmg);
}

//gets new emg value, replaces oldest emg value in cache, averages the cache, and saves the average to avgEmg
void updateEmg(){
  //bring in new emg data point and add to cache.
  newEmg = analogRead(emgPin);
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

//gets new value from current sensing pin, computes pid loop with new data, and writes a new value to the driver. uses "myPID"
void updatePID(){
  input = analogRead(dcCurrent);
  myPID.Compute();
  analogWrite(dcSpeed, output);

}

/*
 *
 * MENU SHIT
 *
 */
void changeMenu(int joy){
  if(joy == 1 || joy == 3){
    changeMenuVertical(joy);
  }
  else{
    changeMenuHorizontal(joy);
  }
}

void changeMenuVertical(int joy){
    if (currentMenu == 0){
      if(currentHeight == 0){
        if(joy == 3){
          currentHeight = 1;
          loadMainMenu(currentHeight);
        }
      }
      else if (currentHeight == 1){
        if(joy == 1){
          currentHeight = 0;
          loadMainMenu(currentHeight);
        }
        else{
          currentHeight = 2;
          loadMainMenu(currentHeight);
        }
      }
      else if (currentHeight == 2){
        if (joy == 1){
          currentHeight = 1;
          loadMainMenu(currentHeight);
        }
      }
    }
  else if(currentMenu == 1){ //Standard hand menu
    if(joy == 3){
      /*
       *
       * THIS SPACE IS FOR DOING VERTICAL STUFF IN THE STANDARD HAND MENU
       */
    }
  }
  else if(currentMenu == 2){ //Solder hand menu
    if(joy == 3){
      /*
       * THIS SPACE FOR VERTICAL FEATURES IN SOLDER HAND MENU
       */
    }
  }
  else if (currentMenu == 3){ //threshold menu
    if(joy == 4){
      //WRITE NEW EEPROM VALUE
      currentHeight=0;
      loadMainMenu(currentHeight);
    }
  }
  else if (currentMenu == 4){ //Hand select menu
    if (currentHeight == 0){
      if(joy == 3){
        currentHeight = 1;
        loadHandSelectMenu(currentHeight);
      }
    }
    else if (currentHeight == 1){
      if(joy == 1){
        currentHeight = 0;
        loadHandSelectMenu(currentHeight);
      }
    }
  }

}

void changeMenuHorizontal(int joy){
  if (currentMenu == 0){
    if(joy == 2){
      if(currentHeight == 0){
        loadHandSelectMenu(0);
      }
      else if(currentHeight == 1){
        loadThresholdMenu(0);
      }
      else{
        loadVersionMenu(0);
      }
    }
  }
  else if(currentMenu == 1){ //Standard hand menu
    //Turn off motor
    analogWrite(dcSpeed, 0);
    digitalWrite(dcDirection1, HIGH);
    digitalWrite(dcDirection2, LOW);

    if(joy == 4){
      //WIPE EMG CACHE
      for(int i=0; i<emgCacheSize; i++){
        emgCache[i] = 0;
      }

      loadHandSelectMenu(0);
    }
    else{
      if(currentHeight == 0){
        loadCalibrateMenu(0);
      }
      else if(currentHeight == 1){
        //toggle to blah blah mode
      }
      else{
        //toggle to last option
      }
    }
  }
  else if(currentMenu == 2){ //Solder hand menu
    //Turn off motor
    analogWrite(dcSpeed, 0);
    digitalWrite(dcDirection1, HIGH);
    digitalWrite(dcDirection2, LOW);
    if(joy == 4){
      loadHandSelectMenu(1);
    }
    else{
      if(currentHeight == 0){
        //toggle to threshold mode
      }
      else if(currentHeight == 1){
        //toggle to blah blah mode
      }
      else{
        //toggle to last option
      }
    }
  }
  else if (currentMenu == 3){ //threshold menu
    if(joy == 4){
      //WRITE NEW EEPROM VALUE

      loadMainMenu(1);
    }
  }
  else if (currentMenu == 4){ //Hand select menu
    if(joy == 4){
      loadMainMenu(0);
    }
    else{
      if(currentHeight == 0){
        loadHandMenu(0);
      }
      else{
        loadSolderMenu(0);
      }
    }
  }
  else if(currentMenu == 5){ //Version Menu
    if(joy == 4){
      digitalWrite(dcDirection1, LOW);
      digitalWrite(dcDirection2, HIGH);
      analogWrite(dcSpeed, 255);
      delay(140);
      analogWrite(dcSpeed, 0);
      digitalWrite(dcDirection1, HIGH);
      digitalWrite(dcDirection2, LOW);

      loadMainMenu(2);
    }
  }
}

void loadMainMenu(int height){ //0
  //Draw Header
  drawBackgroundAndHeader();

  //Title
  tft.setCursor(25, (tft.height()/9) + 3);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.print("Main Menu");

  //HAND MENU OPTION
  if(height == 0){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 40, "Hand Select");

  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 40, "Hand Select");

  }

  //THRESHOLD MENU OPTION
  if(height == 1){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 70, "Threshold");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 70, "Threshold");
  }
  //VERSION MENU OPTION
  if(height == 2){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 100, "Version");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 100, "Version");
  }



  //setting current screen:
  currentMenu = 0;
  currentHeight = height;
}

void loadHandMenu(int height){ //1
  //Draw Header
  drawBackgroundAndHeader();

  //Title
  tft.setCursor(25, (tft.height()/9) + 3);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.print("Pulse");

  if(height == 0){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 40, "Calibrate");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 40, "Calibrate");
  }


  //setting current screen:
  currentMenu = 1;
  currentHeight = height;

}

void loadSolderMenu(int height){ //2
  //Draw Header
  drawBackgroundAndHeader();

    //Title
  tft.setCursor(25, (tft.height()/9) + 3);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.print("Hold");


  //setting current screen:
  currentMenu = 2;
  currentHeight = height;

}

void loadThresholdMenu(int height){ //3
  //Draw Header
  drawBackgroundAndHeader();

  //setting current screen:
  currentMenu = 3;
  currentHeight = height;

    //Title
  tft.setCursor(15, (tft.height()/9) + 4);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.print("Threshold");

  //First Threshold OPTION
  if(height == 0){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 40, "One");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 40, "One");
  }

  //Second Threshold OPTION
  if(height == 1){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 70, "Two");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 70, "Two");
  }

}

void loadHandSelectMenu(int height){ //4
  //Draw Header
  drawBackgroundAndHeader();

  //Title
  tft.setCursor(15, (tft.height()/9) + 4);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.print("Mode Select");

  //HAND MENU OPTION
  if(height == 0){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 40, "Pulse");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 40, "Pulse");
  }

  //THRESHOLD MENU OPTION
  if(height == 1){
    drawMenuOption(ST7735_WHITE, ST7735_BLACK, 5, 70, "Hold");
  }
  else{
    drawMenuOption(ST7735_RED, ST7735_BLACK, 5, 70, "Hold");
  }

  //setting current screen:
  currentMenu = 4;
  currentHeight = height;

}

void loadVersionMenu(int height){ //5
  //Draw Header
  drawBackgroundAndHeader();

  //Title
  tft.setCursor(15, (tft.height()/9) + 4);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Atlas Arm Version 2.0");
  tft.println("Copyright Atlas Laboratories, LLC");
  tft.println("2016");
  tft.println("www.atlas-laboratories.com");

  digitalWrite(dcDirection1, HIGH);
  digitalWrite(dcDirection2, LOW);
  analogWrite(dcSpeed, 255);
  delay(500);
  analogWrite(dcSpeed, 153);

  //setting current screen:
  currentMenu = 5;
  currentHeight = height;
}

void loadCalibrateMenu(int height){ //6
  //Draw Header
  drawBackgroundAndHeader();

  //Title
  tft.setCursor(15, (tft.height()/9) + 4);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("CALIBRATING, RELAX ARM");

  //Give user a second to relax
  delay(1000);

  int calibrateTotal = 0;

  for(int i=0;i<200;i++){
    updateEmg();
    calibrateTotal = calibrateTotal + avgEmg;
    delay(10);
  }

  eepromNeutral = calibrateTotal / 200;

  //SET VALUE INTO EEPROM
  EEPROM.write(2, eepromNeutral);

  //setting current screen:
  currentMenu = 6;
  currentHeight = height;

  //SEND BACK TO HAND MENU
  loadHandMenu(0);

}

void drawBackgroundAndHeader(){

  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);

  tft.fillRect(0, 0, tft.width(), 13, ST7735_RED);
  tft.setCursor(3,3);
  tft.setTextColor(ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.print("ATLAS ARM V2.0 ");

  tft.setCursor(133, 3);
  tft.print("BETA");

}

void drawMenuOption(uint16_t bgColor, uint16_t textColor, int xPos, int yPos, String text){
  tft.fillRoundRect(xPos, yPos, 148, 20, 3, bgColor);
  tft.setCursor(xPos+3, yPos+3);
  tft.setTextColor(textColor);
  tft.print(text);

}
