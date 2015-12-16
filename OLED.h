/*
 * OLED.h
 *
 *  Created on: 10.12.2015
 *      Author: Marc
 */

#ifndef OLED_H_
#define OLED_H_

#include <Arduino.h>
#include <Wire.h>
#include "marelab_dimm.h"


#ifdef OLED_U8G
	#include "U8glib/U8glib.h"
#endif
#ifdef OLED_ADA
	#include "adafruit/Adafruit_GFX.h"
	#include "adafruit/Adafruit_SSD1306.h"
#endif

class OLED{
public:
		#ifdef OLED_ADA
			Adafruit_SSD1306 *disp;
		#endif
		#ifdef OLED_U8G
			//U8GLIB_SSD1306_ADAFRUIT_128X64 *disp;	// Fast I2C / TWI
			//U8GLIB_SSD1306_ADAFRUIT_128X64 dispp(U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST );	// Fast I2C / TWI
			//U8GLIB_SSD1306_128X64 disp(U8G_I2C_OPT_NO_ACKS);
			U8GLIB_SSD1306_ADAFRUIT_128X64 *disp;
		#endif

public:
	//		 U8GLIB_SSD1306_ADAFRUIT_128X64(uint8_t options = U8G_I2C_OPT_NONE)
	OLED()  {
#ifdef OLED_U8G
		disp = new U8GLIB_SSD1306_ADAFRUIT_128X64(U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
		disp->setFont(u8g_font_6x10);
		disp->setFontRefHeightExtendedText();
		disp->setDefaultForegroundColor();
		disp->setFontPosTop();
#endif

#ifdef OLED_ADA

#ifdef SIMULATION

#else

#endif

#endif
	}
	;

	void begin() {
	#ifdef OLED_ADA
		this->disp = new Adafruit_SSD1306(-1);
#ifndef SIMULATION
		disp->begin(SSD1306_SWITCHCAPVCC, 0x3c);
#else
		disp->begin(SSD1306_SWITCHCAPVCC, 0x3C);
#endif
		disp->display();
		delay(200);
	#endif

#ifdef OLED_U8G
		//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI
		//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI
		//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);		// Display which does not send AC
		//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
		//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(10, 9);			// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
	delay(10);
#endif

	}
	;

	void ClearScreen(){
		#ifdef OLED_U8G
		disp->firstPage();
			do {

			} while(disp->nextPage() );
		#endif

		#ifdef OLED_ADA
			disp->clearDisplay();
		#endif
	};

	void DrawLine(int16_t x,int16_t y,int16_t width,int16_t height){
		int yy,xx;

		#ifdef OLED_U8G
		disp->drawLine(x,y,width, height);
		#endif

		#ifdef OLED_ADA
		if ((height-y) == 0)
			yy = height;
		else
			yy = height;

		if ((width - x) == 0)
			xx = width;
		else
			xx = width;

		disp->drawLine(x, y, xx, yy, WHITE);
		#endif
	};

	void DrawRect(int16_t x,int16_t y,int16_t width,int16_t height){

			#ifdef OLED_U8G
		disp->drawFrame(x, y, width, height);
			#endif

			#ifdef OLED_ADA

				disp->drawRect(x, y, width, height, WHITE);

			#endif
		};

	void DrawFilledRect(int16_t x,int16_t y,int16_t width,int16_t height){

				#ifdef OLED_U8G
		disp->drawBox(x, y, width, height);
				#endif

				#ifdef OLED_ADA
					disp->fillRect(x, y, width, height, WHITE);
				#endif
			};

	void Text(uint8_t x, uint8_t y, const char *s){
		#ifdef OLED_U8G
		disp->setFont(u8g_font_5x7);
		disp->setFontRefHeightExtendedText();
		disp->setDefaultForegroundColor();
		disp->setFontPosTop();
		disp->drawStr( x, y, s);
		#endif

		#ifdef OLED_ADA
			disp->setTextSize(1);
			disp->setTextColor(WHITE);
			disp->setCursor(x,y);
			disp->println(s);
		#endif
	};

	#ifdef OLED_U8G
	void DrawXBM(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const u8g_pgm_uint8_t *bitmap){
		disp->drawXBMP( x, y, w, h,bitmap);
	};
	#endif

	#ifdef OLED_ADA
	void DrawXBM(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap){
		disp->drawXBitmap(x,y,bitmap, w,h,1);
	};
	#endif


	void Show(){
		#ifdef OLED_U8G

		#endif

		#ifdef OLED_ADA
		disp->display();
		#endif
	};

	void firstPage(){
		#ifdef OLED_U8G
		disp->firstPage();
		#endif
		#ifdef OLED_ADA
			disp->clearDisplay();
		#endif

	};

	bool nextPage() {
		#ifdef OLED_U8G
			return disp->nextPage();
		#endif
		return false;
	};

	virtual ~OLED();
};

#endif /* OLED_H_ */
