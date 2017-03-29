#include <Arduino.h>

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

	Pick one up today in the adafruit shop!
	------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
<<<<<<< Local Changes
*********************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include "./private.h"

/*
Your values for wifi login should be included in file private.h
const char *ssid     = "<SSID>";
const char *password = "<PASSWORD>"
*/

#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "194.58.202.20",2*3600,60);

void setup()   {
	Serial.begin(115200);
	Serial.println(ssid);
	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
	// init done

	// Clear the buffer.
	display.clearDisplay();
	// text display tests
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Hello, world!");
	display.display();

	display.clearDisplay();
	display.println("Initializing Wifi");
	display.display();
	display.setTextSize(2);
	WiFi.begin(ssid, password);

	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	timeClient.begin();

	 display.clearDisplay();
	 display.display();

 }

void loop() {
	display.clearDisplay();
	display.setCursor(0,0);
	timeClient.update();

	display.println(timeClient.getFormattedTime());
	display.display();
	delay(1000);

}
