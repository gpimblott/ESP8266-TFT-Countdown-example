#include <UTFT.h>



// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];


int hours = 24;
int minutes = 0;

int count = 0;

// https://github.com/gnulabis/UTFT-ESP8266
//
// UTFT(byte model, int CS, int RST, int SER=0);
//
// When the above constructor is invoked, the library will automatically use the 
// hardware SPI pins for SCK and MOSI (GPIO14 and GPIO13 respectively on the ESP8266).
//

UTFT myGLCD ( ILI9341_S5P, 15, 5, 4 );

void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  Serial.println("Starting 24 countdown");

  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
}

void displayDigits( int value , int x , int y ) {
  String strValue = (value < 10 ? "0" + String(value) : String(value));
  myGLCD.print(strValue , x, y );

}

void loop()
{
  myGLCD.print("Text rotation", 0, 0);
  myGLCD.setColor(0, 0, 255);
  myGLCD.print("Arduino", 0, 16, 0);
  myGLCD.print("Arduino", 319, 0, 90);
  myGLCD.print("Arduino", 319, 239, 180);
  myGLCD.print("Arduino", 0, 239, 270);

  myGLCD.setColor( 255 , 0 , 0 );
  myGLCD.print("Hello World", 80 , 160 , 0);

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 255, 0);
  myGLCD.print(String(hours) , 100, 90 );
  myGLCD.print(String(minutes) , 180 , 90);

  while ( true ) {
    count++;

    if ( count % 10000 == 0 ) {
      Serial.println("Update");
      Serial.flush();

      if (--minutes < 0) {
        minutes = 60;
        if (--hours < 0) {
          hours = 24;
        }
      }

      displayDigits( hours , 100, 90);
      displayDigits( minutes, 180 , 90);
    }
  }
}

