#include "header.h"

/* Define shared project variables in this file only. */
volatile u32 soil_moisture = 0U;
volatile u32 water_level = 0U;
volatile u32 light = 0U;
volatile u32 temparature = 0U;
volatile u32 soil_sensor = 0U;
volatile u32 water_sensor = 0U;
volatile u32 light_sensor = 0U;
volatile u32 temperature_humid = 0U;

int main(void)
{
    u32 soil_adc, temp_adc, water_adc, light_adc;
    u32 rain_status, pir_status, flame_status;
    u32 pump_request;
    u32 loop_count = 0U;
    float voltage, temperature_c;

    /* Initialize all available peripherals. */
    uart_init(9600U);
    init();
    led_init();
    adc_init();
    i2c_init();
    lcd_init();

    /* GPIO direction setup. */
    IO0DIR |= RED_LED | YELLOW_LED | GREEN_LED | BUZZER;
    IO0CLR = RED_LED | YELLOW_LED | GREEN_LED | BUZZER;
    IO0DIR &= ~((1U << 10) | (1U << 11) | (1U << 12));

    uart_tx_string("\r\n=============================================\r\n");
    uart_tx_string("SMART PRECISION AGRICULTURE MONITORING SYSTEM\r\n");
    uart_tx_string("=============================================\r\n");
    uart_tx_string("Controller        : LPC2129 ARM7\r\n");
    uart_tx_string("Project Status    : RUNNING\r\n");
    uart_tx_string("Wi-Fi / Cloud     : NOT USED\r\n");
    uart_tx_string("SD Card           : NOT USED\r\n");
    uart_tx_string("CAN               : NOT USED\r\n");
    uart_tx_string("DHT22 Humidity    : NOT USED\r\n");

    /* Read previously saved values only after I2C and UART init. */
    eeprom_read();

    while (1)
    {
        /* ADC channel mapping must match actual board wiring. */
        soil_adc  = adc_read(0U);
        temp_adc  = adc_read(1U);
        water_adc = adc_read(2U);
        light_adc = adc_read(3U);

        /* MCP9700 conversion: Vout=(ADC*3.3)/1023; T=(Vout-0.5)/0.01.
           If the fitted sensor is LM35, use temperature_c=voltage*100. */
        voltage = ((float)temp_adc * 3.3f) / 1023.0f;
        temperature_c = (voltage - 0.5f) / 0.01f;

        /* Raw digital levels. Confirm whether each module is active HIGH/LOW. */
        rain_status  = RAIN;
        pir_status   = PIR;
        flame_status = FLAME;

        /* Update globals used by EEPROM module. */
        soil_moisture = soil_adc;
        water_level = water_adc;
        temparature = (u32)(temperature_c * 10.0f + 0.5f);
        light = light_adc;
        soil_sensor = soil_adc;
        water_sensor = water_adc;
        light_sensor = light_adc;
        temperature_humid = temparature;

        /* Decide whether irrigation is required. This is a REQUEST only.
           header.h maps RAIN and RELAY both to P0.10, so relay control
           remains disabled until the hardware pin conflict is corrected. */
        pump_request = (soil_adc > SOIL_DRY_LIMIT &&
                        water_adc > WATER_MINIMUM &&
                        rain_status == 0U &&
                        flame_status == 0U);

        if ((soil_adc < SOIL_WET_LIMIT) ||
            (water_adc <= WATER_MINIMUM) ||
            (rain_status != 0U) || (flame_status != 0U))
            pump_request = 0U;

        /* LED indication: red=fire, yellow=warning, green=normal. */
        IO0CLR = RED_LED | YELLOW_LED | GREEN_LED;
        if (flame_status != 0U)
            IO0SET = RED_LED;
        else if ((water_adc <= WATER_MINIMUM) ||
                 (rain_status != 0U) ||
                 (soil_adc > SOIL_DRY_LIMIT) ||
                 (pir_status != 0U))
            IO0SET = YELLOW_LED;
        else
            IO0SET = GREEN_LED;

        /* Buzzer warns on flame or motion. */
        if ((flame_status != 0U) || (pir_status != 0U))
            IO0SET = BUZZER;
        else
            IO0CLR = BUZZER;

        /* Serial terminal output, adapted from PDF final output layout. */
        uart_tx_string("\r\n---------------------------------------------\r\n");
        uart_tx_string("Soil Moisture     : ");
        uart_tx_integer((s32)((soil_adc * 100U) / 1023U));
        uart_tx_string("%\r\nWater Level       : ");
        uart_tx_integer((s32)((water_adc * 100U) / 1023U));
        uart_tx_string("%\r\nTemperature       : ");
        uart_tx_float(temperature_c);
        uart_tx_string(" C\r\n");

        uart_tx_string("Rain Status       : ");
        uart_tx_string(rain_status ? "DETECTED\r\n" : "NO\r\n");

        uart_tx_string("Light Intensity   : ");
        if (light_adc > LIGHT_HIGH_LIMIT)
            uart_tx_string("HIGH\r\n");
        else if (light_adc > LIGHT_MED_LIMIT)
            uart_tx_string("MEDIUM\r\n");
        else
            uart_tx_string("LOW\r\n");

        uart_tx_string("Flame Status      : ");
        uart_tx_string(flame_status ? "DETECTED\r\n" : "SAFE\r\n");
        uart_tx_string("Motion Status     : ");
        uart_tx_string(pir_status ? "DETECTED\r\n" : "CLEAR\r\n");
        uart_tx_string("Pump Request      : ");
        uart_tx_string(pump_request ? "ON\r\n" : "OFF\r\n");
        uart_tx_string("Relay Status      : NOT DRIVEN (P0.10 PIN CONFLICT)\r\n");

        /* RTC date/time functions print their own line endings. */
        get_date();
        uart_tx_string("RTC Date          : ");
        display_date();
        get_time();
        uart_tx_string("RTC Time          : ");
        display_time();

        if (flame_status != 0U)
            uart_tx_string("Emergency         : FIRE ALERT\r\n");
        else if (pir_status != 0U)
            uart_tx_string("Security          : MOTION ALERT\r\n");
        else if (water_adc <= WATER_MINIMUM)
            uart_tx_string("Warning           : LOW WATER LEVEL\r\n");
        else if (rain_status != 0U)
            uart_tx_string("Action            : IRRIGATION STOPPED - RAIN\r\n");
        else if (pump_request != 0U)
            uart_tx_string("Action            : IRRIGATION REQUESTED\r\n");
        else
            uart_tx_string("System Status     : NORMAL\r\n");

        /* LCD display uses existing LCD driver. */
        lcd_cmd(0x01U);
        lcd_cmd(0x80U);
        lcd_string("Soil:");
        lcd_integer((s32)((soil_adc * 100U) / 1023U));
        lcd_string("%             ");
        lcd_cmd(0xC0U);
        lcd_string(pump_request ? "Pump Req: ON     " : "Pump Req: OFF    ");

        /* Store a record every 60 iterations (about 60 seconds). */
        loop_count++;
        if (loop_count >= 60U)
        {
            eeprom_store();
            uart_tx_string("EEPROM Status     : SAVE REQUESTED\r\n");
            loop_count = 0U;
        }

        uart_tx_string("Wi-Fi / Cloud     : NOT USED\r\n");
        uart_tx_string("SD Card           : NOT USED\r\n");
        uart_tx_string("CAN               : NOT USED\r\n");
        uart_tx_string("DHT22 Humidity    : NOT USED\r\n");
        uart_tx_string("---------------------------------------------\r\n");
        uart_tx_string("Monitoring...\r\n");
        delay_ms(1000U);
    }
}
