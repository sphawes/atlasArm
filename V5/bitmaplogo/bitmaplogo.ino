/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET A1
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
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

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.clearDisplay();


  
}


void loop() {

  // miniature bitmap display
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 32, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
  delay(1);
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    delay(1);
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
    delay(1);
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
    delay(1);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}


void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Atlas");
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0xFF);
  delay(2000);
  display.stopscroll();
  delay(1000);
}
