#ifndef SSD1306_H
#define SSD1306_H

#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SSD_Command_Mode      0x00  /* C0 and DC bit are 0         */
#define SSD_Data_Mode         0x40  /* C0 bit is 0 and DC bit is 1 */

#define SSD_Set_Segment_Remap   0xA0
#define SSD_Inverse_Display     0xA7
#define SSD_Set_Muliplex_Ratio  0xA8

#define SSD_Display_Off         0xAE
#define SSD_Display_On          0xAF

#define SSD_Set_ContrastLevel 0x81

#define SSD_External_Vcc      0x01
#define SSD_Internal_Vcc      0x02

#define SSD_Set_Column_Address  0x21
#define SSD_Set_Page_Address    0x22

#define SSD_Activate_Scroll   0x2F
#define SSD_Deactivate_Scroll 0x2E

#define SSD_Right_Horizontal_Scroll   0x26
#define SSD_Left_Horizontal_Scroll    0x27


#define Scroll_Left           0x00
#define Scroll_Right          0x01

#define Scroll_2Frames    0x07
#define Scroll_3Frames    0x04
#define Scroll_4Frames    0x05
#define Scroll_5Frames    0x00
#define Scroll_25Frames   0x06
#define Scroll_64Frames   0x01
#define Scroll_128Frames  0x02
#define Scroll_256Frames  0x03

#define VERTICAL_MODE           01
#define PAGE_MODE               01
#define HORIZONTAL_MODE         02


/*=========================================================================
    SSD1306 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
=========================================================================*/

#define SSD1306_Entire_Display_Resume 0xA4
#define SSD1306_Entire_Display_On     0xA5

#define SSD1306_Normal_Display  0xA6

#define SSD1306_Set_Display_Offset      0xD3
#define SSD1306_Set_Com_Pins        0xDA
#define SSD1306_Set_Vcomh_Deselect_Level      0xDB
#define SSD1306_Set_Display_Clock_Div 0xD5
#define SSD1306_Set_Precharge_Period    0xD9
#define SSD1306_Set_Lower_Column_Start_Address        0x00
#define SSD1306_Set_Higher_Column_Start_Address       0x10
#define SSD1306_Set_Start_Line      0x40
#define SSD1306_Set_Memory_Mode     0x20
#define SSD1306_Set_Com_Output_Scan_Direction_Normal  0xC0
#define SSD1306_Set_Com_Output_Scan_Direction_Remap   0xC8
#define SSD1306_Charge_Pump_Setting 0x8D

// Scrolling #defines
#define SSD1306_SET_VERTICAL_SCROLL_AREA              0xA3
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A

/*=========================================================================
    SSD1308 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
=========================================================================*/
#define SSD1308_Normal_Display  0xA6

/*=========================================================================
    SSD1327 Displays
    -----------------------------------------------------------------------
    The driver is used in Seeed 96x96 display
=========================================================================*/
#define SSD1327_Set_Display_Start_Line  0xA1
#define SSD1327_Set_Display_Offset      0xA2
#define SSD1327_Normal_Display      0xA4
#define SSD1327_Set_Display_Clock_Div 0xB3
#define SSD1327_Set_Command_Lock    0xFD
#define SSD1327_Set_Column_Address  0x15
#define SSD1327_Set_Row_Address     0x75

#define SSD1327_Set_Row_Address     0x75

/*=========================================================================
    SH1106 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
=========================================================================*/
#define SH1106_Set_Page_Address 0xB0


#define BLACK 0
#define WHITE 1

#define _BV(bit) (1 << (bit))

class ssd1306
{
public:
    ssd1306();
private:
    uint8_t *poledbuff;
    int16_t oled_buff_size;
    uint8_t width;
    uint8_t height;
    uint8_t addr;
    uint8_t grayH, grayL;
    int devid;
    bool init();
    void sendCommand(uint8_t c);
    void stopScroll();
    void clearDisplay();
    void setBrightness(uint8_t b);
    void putSeedChar(char C);
    void putSeedString(const char *String);
    void sendData(uint8_t d);
    void setSeedTextXY(unsigned char Row, unsigned char Column);
    void setGrayLevel(uint8_t grayLevel);
    void display();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
};

#endif // SSD1306_H
