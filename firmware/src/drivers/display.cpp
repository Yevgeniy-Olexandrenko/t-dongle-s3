#include "display.h"

namespace driver
{
    Display::Display()
    {
        // SPI bus configuration
        auto busConfig = m_bus.config();
        busConfig.spi_host    = SPI2_HOST;          // ESP32 : VSPI_HOST or HSPI_HOST
                                                    // ESP32-S2,S3,C3: SPI2_HOST or SPI3_HOST
                                                    // Due to the ESP-IDF version upgrade, the VSPI_HOST and HSPI_HOST
                                                    // descriptions are deprecated, so if an error occurs, please use
                                                    // SPI2_HOST and SPI3_HOST instead.
        busConfig.spi_mode    = 0;                  // Sets the SPI communication mode (0 to 3)
        busConfig.freq_write  = 80000000;           // SPI clock during transmission (Maximum 80MHz, rounded to an integer)
        busConfig.freq_read   = 80000000;           // SPI clock when receiving
        busConfig.spi_3wire   = false;              // Set to true if receiving is done on the MOSI pin
        busConfig.use_lock    = true;               // Set to true if you want to use transaction locking
        busConfig.dma_channel = SPI_DMA_CH_AUTO;    // Set the DMA channel to use:
                                                    // 0 = no DMA, 1 = 1ch, 2 = 2ch, SPI_DMA_CH_AUTO = automatic setting
                                                    // Due to the ESP-IDF version upgrade, SPI_DMA_CH_AUTO is now recommended
                                                    // for the DMA channel. Specifying 1ch or 2ch is no longer recommended.
        busConfig.pin_sclk    = PIN_LCD_SCL;        // Set SPI SCLK pin number
        busConfig.pin_mosi    = PIN_LCD_SDA;        // Set SPI MOSI pin number
        busConfig.pin_dc      = PIN_LCD_DC;         // Set SPI D/C pin number (-1 = disable)

        // Display panel configuration
        auto panelConfig = m_panel.config();
        panelConfig.pin_cs           = PIN_LCD_CS;  // Pin number CS is connected to (-1 = disable)
        panelConfig.pin_rst          = PIN_LCD_RES; // Pin number RST is connected to (-1 = disable)
        panelConfig.panel_width      = 80;          // Actual displayable width
        panelConfig.panel_height     = 160;         // Actual displayable height
        panelConfig.offset_x         = 26;          // Panel offset in the X direction
        panelConfig.offset_y         = 1;           // Panel offset in the Y direction
        panelConfig.offset_rotation  = 2;           // Rotation direction offset 0~7 (4~7 are upside down)
        panelConfig.readable         = false;       // Set to true if data can be read
        panelConfig.invert           = true;        // Set to true if the panel's colors are inverted
        panelConfig.rgb_order        = false;       // Set to true if the red and blue of the panel are swapped
        panelConfig.bus_shared       = false;       // If the bus is shared with the SD card, set it to true (bus
                                                    // control is performed using drawJpgFile, etc.)
        // Backlight config
        auto lightConfig = m_light.config();
        lightConfig.pin_bl      = PIN_LCD_BL;       // Pin number the backlight is connected to
        lightConfig.invert      = true;             // Set true if the backlight brightness is inverted
        lightConfig.freq        = 5000;             // Backlight PWM frequency
        lightConfig.pwm_channel = 7;                // PWM channel number to use

        m_bus.config(busConfig);
        m_panel.config(panelConfig);
        m_light.config(lightConfig);

        m_panel.setBus(&m_bus);
        m_panel.setLight(&m_light);
        setPanel(&m_panel);
    }
}
