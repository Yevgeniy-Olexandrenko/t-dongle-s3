#include <Arduino.h>
// #include <USB.h>
// #include <USBMSC.h>

// #include <driver/sdmmc_host.h>
// #include <driver/sdspi_host.h>
// #include <esp_vfs_fat.h>
// #include <sdmmc_cmd.h>

// #include <OneButton.h>
// #include <FastLED.h>

// #define MOUNT_POINT "/sdcard"

// CRGB leds;
// OneButton button(PIN_BUTTON, true);
// USBMSC MSC;
// sdmmc_card_t *card;

// void sd_init(void)
// {
//     esp_err_t ret;
//     const char mount_point[] = MOUNT_POINT;
//     esp_vfs_fat_sdmmc_mount_config_t mount_config = {
//         .format_if_mount_failed = false, 
//         .max_files = 5,
//         .allocation_unit_size = 16 * 1024
//     };

//     sdmmc_host_t host = {
//         .flags = SDMMC_HOST_FLAG_4BIT | SDMMC_HOST_FLAG_DDR,
//         .slot = SDMMC_HOST_SLOT_1,
//         .max_freq_khz = SDMMC_FREQ_DEFAULT,
//         .io_voltage = 3.3f,
//         .init = &sdmmc_host_init,
//         .set_bus_width = &sdmmc_host_set_bus_width,
//         .get_bus_width = &sdmmc_host_get_slot_width,
//         .set_bus_ddr_mode = &sdmmc_host_set_bus_ddr_mode,
//         .set_card_clk = &sdmmc_host_set_card_clk,
//         .do_transaction = &sdmmc_host_do_transaction,
//         .deinit = &sdmmc_host_deinit,
//         .io_int_enable = sdmmc_host_io_int_enable,
//         .io_int_wait = sdmmc_host_io_int_wait,
//         .command_timeout_ms = 0,
//     };
//     sdmmc_slot_config_t slot_config = {
//         .clk = (gpio_num_t)PIN_SDCARD_CLK,
//         .cmd = (gpio_num_t)PIN_SDCARD_CMD,
//         .d0  = (gpio_num_t)PIN_SDCARD_D0,
//         .d1  = (gpio_num_t)PIN_SDCARD_D1,
//         .d2  = (gpio_num_t)PIN_SDCARD_D2,
//         .d3  = (gpio_num_t)PIN_SDCARD_D3,
//         .cd  = SDMMC_SLOT_NO_CD,
//         .wp  = SDMMC_SLOT_NO_WP,
//         .width = 4, // SDMMC_SLOT_WIDTH_DEFAULT,
//         .flags = SDMMC_SLOT_FLAG_INTERNAL_PULLUP,
//     };

//     gpio_set_pull_mode((gpio_num_t)PIN_SDCARD_CMD, GPIO_PULLUP_ONLY); // CMD, needed in 4- and 1- line modes
//     gpio_set_pull_mode((gpio_num_t)PIN_SDCARD_D0,  GPIO_PULLUP_ONLY); // D0,  needed in 4- and 1-line modes
//     gpio_set_pull_mode((gpio_num_t)PIN_SDCARD_D1,  GPIO_PULLUP_ONLY); // D1,  needed in 4-line mode only
//     gpio_set_pull_mode((gpio_num_t)PIN_SDCARD_D2,  GPIO_PULLUP_ONLY); // D2,  needed in 4-line mode only
//     gpio_set_pull_mode((gpio_num_t)PIN_SDCARD_D3,  GPIO_PULLUP_ONLY); // D3,  needed in 4- and 1-line modes

//     ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

//     if (ret != ESP_OK)
//     {
//         if (ret == ESP_FAIL)
//         {
//             Serial.println("Failed to mount filesystem. "
//                               "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
//         }
//         else
//         {
//             Serial.printf("Failed to initialize the card (%s). "
//                              "Make sure SD card lines have pull-up resistors in place.",
//                              esp_err_to_name(ret));
//         }
//         return;
//     }
// }

// static int32_t onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize)
// {
//     // HWSerial.printf("MSC WRITE: lba: %u, offset: %u, bufsize: %u\n", lba, offset, bufsize);
//     uint32_t count = (bufsize / card->csd.sector_size);
//     sdmmc_write_sectors(card, buffer + offset, lba, count);
//     return bufsize;
// }

// static int32_t onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize)
// {
//     // HWSerial.printf("MSC READ: lba: %u, offset: %u, bufsize: %u\n", lba, offset, bufsize);
//     uint32_t count = (bufsize / card->csd.sector_size);
//     sdmmc_read_sectors(card, (uint8_t*)buffer + offset, lba, count);
//     return bufsize;
// }

// static bool onStartStop(uint8_t power_condition, bool start, bool load_eject)
// {
//     Serial.printf("MSC START/STOP: power: %u, start: %u, eject: %u\n", power_condition, start, load_eject);
//     return true;
// }

// static void usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// {
//     if (event_base == ARDUINO_USB_EVENTS)
//     {
//         arduino_usb_event_data_t *data = (arduino_usb_event_data_t *)event_data;
//         switch (event_id)
//         {
//         case ARDUINO_USB_STARTED_EVENT:
//             Serial.println("USB PLUGGED");
//             break;
//         case ARDUINO_USB_STOPPED_EVENT:
//             Serial.println("USB UNPLUGGED");
//             break;
//         case ARDUINO_USB_SUSPEND_EVENT:
//             Serial.printf("USB SUSPENDED: remote_wakeup_en: %u\n", data->suspend.remote_wakeup_en);
//             break;
//         case ARDUINO_USB_RESUME_EVENT:
//             Serial.println("USB RESUMED");
//             break;

//         default:
//             break;
//         }
//     }
// }

// void ledTask(void *param) 
// {
//   while (true) 
//   {
//     static uint8_t hue = 0;
//     leds = CHSV(hue++, 0XFF, 100);
//     FastLED.show();
//     delay(50);
//   }
// }

// void onButtonClick()
// {
//     Serial.println("Hello T-Dongle-S3");
// }

// void setup()
// {
//     Serial.begin(115200);
//     //Serial.setDebugOutput(true);

//     sd_init();
// #if 0
//     USB.onEvent(usbEventCallback);  
//     MSC.vendorID("LILYGO");       // max 8 chars
//     MSC.productID("T-Dongle-S3"); // max 16 chars
//     MSC.productRevision("1.0");   // max 4 chars
//     MSC.onStartStop(onStartStop);
//     MSC.onRead(onRead);
//     MSC.onWrite(onWrite);
//     MSC.mediaPresent(true);
//     MSC.begin(card->csd.capacity, card->csd.sector_size);
//     USB.begin();
// #endif

//     // BGR ordering is typical
//     FastLED.addLeds<APA102, PIN_LED_DI, PIN_LED_CI, BGR>(&leds, 1);
//     xTaskCreatePinnedToCore(ledTask, "led_task", 1024, NULL, 1, NULL, 0);
//     button.attachClick(onButtonClick);
// }

// void loop()
// {
//     button.tick();
//     delay(5);
// }

#include <TFT_eSPI.h>
#include "girl.h"
#include "logo.h"
#include "logo2.h"

TFT_eSPI tft = TFT_eSPI();

void backlight_on(uint8_t value) 
{
  ledcAttachPin(PIN_LCD_BL, 1);
  ledcSetup(1, 5000, 8);
  ledcWrite(1, 255 - value);
}

void setup()
{
    Serial.begin(115200);
    delay(3000);

    backlight_on(100);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_DARKGREY);
    tft.setTextFont(1);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
}

void loop()
{
    Serial.println("Hello world!");
    
    static uint8_t i = 0;
    switch (i++) {
    case 0:
        tft.pushImage(0, 0, 160, 80, (uint16_t *)gImage_logo);
        break;
    case 1:
        tft.pushImage(0, 0, 160, 80, (uint16_t *)gImage_logo2);
        break;
    case 2:
        tft.pushImage(0, 0, 160, 80, (uint16_t *)gImage_girl);
        i = 0;
        break;
    default:
        break;
    }
    delay(2000);
}
