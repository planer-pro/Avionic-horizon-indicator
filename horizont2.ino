#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

enum commands
{
	sendX,
	sendY,
	sendZ,
};

void setup()
{
	Serial1.begin(19200);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
	display.clearDisplay();

	display.setTextSize(1);
	display.setTextColor(WHITE);
}

int x1 = 20;
int y1 = 32;
int x2 = 110;
int y2 = 32;
int y_cenrtal = 32;

int InAxe_x;
int InAxe_y;
int InAxe_z;

void loop()
{
	while (Serial1.available())
	{
		int com = Serial1.readStringUntil(',').toInt();
		int val = Serial1.readStringUntil(';').toInt();

		if (com == sendX) InAxe_y = val;
		else if (com == sendY) InAxe_x = val;
		else if (com == sendZ) InAxe_z = val;

		y_cenrtal = map(InAxe_y, 0, 1023, 0, 64);

		y1 = map(InAxe_x, 0, 1023, 0, 64);
		y2 = map(InAxe_x, 0, 1023, 64, 0);

		y1 += y_cenrtal - 32;
		y2 += y_cenrtal - 32;
	}



	display.clearDisplay();
	display.drawLine(x1, y1, x2, y2, WHITE);
	display.display();
}