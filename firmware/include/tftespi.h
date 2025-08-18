#pragma once

#define DISABLE_ALL_LIBRARY_WARNINGS
#define USER_SETUP_LOADED

// display driver
#define ST7735_DRIVER
#define ST7735_GREENTAB160x80
#define TFT_WIDTH     80
#define TFT_HEIGHT    160
#define TFT_RGB_ORDER TFT_BGR

// spi bus configuration
#define USE_FSPI_PORT
#define SPI_FREQUENCY 50000000

// display connection
#define TFT_MISO  -1
#define TFT_MOSI  PIN_LCD_SDA
#define TFT_SCLK  PIN_LCD_SCL
#define TFT_CS    PIN_LCD_CS
#define TFT_DC    PIN_LCD_DC
#define TFT_RST   PIN_LCD_RES

// fonts
#define SMOOTH_FONT
#define LOAD_GLCD
