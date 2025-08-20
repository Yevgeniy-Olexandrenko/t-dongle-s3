#pragma once

#include <LovyanGFX.hpp>

namespace driver
{
    class Display : public lgfx::LGFX_Device
    {
    public:
        Display();

    private:
        lgfx::Panel_ST7735S m_panel;
        lgfx::Bus_SPI       m_bus;
        lgfx::Light_PWM     m_light;
    };
}
