#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
	Serial.begin(115200);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
	display.clearDisplay();

	display.setTextSize(1);
	display.setTextColor(WHITE);
}

void loop()
{
	while (Serial.available())
	{
		String input = Serial.readStringUntil('\n');
		if (input != NULL)
		{
			input.trim();
			String values[] = split(input, " ");
			if (values.length == 3) {
				float phi = float(values[0]);
				float theta = float(values[1]);
				float psi = float(values[2]);
				print(phi);
				print(theta);
				println(psi);
				Phi = phi;
				Theta = theta;
				Psi = psi;
			}
		
	}

	display.clearDisplay();

	display.drawLine(x1, y1, x2, y2, WHITE);

	display.display();
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}