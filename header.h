#ifndef HEADER_H
#define HEADER_H

#include <LPC21xx.H>

/* =========================================================
   BASIC DATA TYPES
   ========================================================= */
typedef unsigned int        u32;
typedef signed int          s32;
typedef unsigned short      u16;
typedef unsigned char       u8;
typedef signed char         s8;

/* =========================================================
   SENSOR INPUT PIN DEFINITIONS
   These pin assignments are taken from the original header.
   Confirm active-HIGH/active-LOW behavior on your hardware.
   ========================================================= */
#define RAIN        ((IOPIN0 >> 10) & 1U)   /* P0.10 */
#define PIR         ((IOPIN0 >> 11) & 1U)   /* P0.11 */
#define FLAME       ((IOPIN0 >> 12) & 1U)   /* P0.12 */

/* =========================================================
   OUTPUT PIN DEFINITIONS
   ========================================================= */
#define BUZZER      (1U << 9)               /* P0.9 */
#define RELAY       (1U << 10)              /* P0.10 */

/* LED connections used by main_agri.c */
#define RED_LED     (1U << 17)              /* P0.17 */
#define YELLOW_LED  (1U << 18)              /* P0.18 */
#define GREEN_LED   (1U << 19)              /* P0.19 */

/* =========================================================
   SENSOR THRESHOLDS
   These are initial values. Calibrate using real readings.
   ========================================================= */
#define SOIL_DRY_LIMIT       500U
#define SOIL_WET_LIMIT       300U
#define WATER_MINIMUM        100U
#define LIGHT_HIGH_LIMIT     700U
#define LIGHT_MED_LIMIT      350U

/* ADC channel mapping used by main_agri.c */
#define SOIL_ADC_CHANNEL     0U
#define TEMP_ADC_CHANNEL     1U
#define WATER_ADC_CHANNEL    2U
#define LIGHT_ADC_CHANNEL    3U

/* =========================================================
   SHARED GLOBAL VARIABLES
   Definitions are present in main_agri.c.
   ========================================================= */
extern volatile u32 soil_moisture;
extern volatile u32 water_level;
extern volatile u32 light;
extern volatile u32 temparature;

extern volatile u32 soil_sensor;
extern volatile u32 water_sensor;
extern volatile u32 light_sensor;
extern volatile u32 temperature_humid;

/* =========================================================
   RTC GLOBAL VARIABLES
   Definitions are present in rtc.c.
   ========================================================= */
extern u8 hrs;
extern u8 min;
extern u8 sec;
extern u8 date;
extern u8 month;
extern u8 year;
extern u8 am_pm;

/* =========================================================
   BOARD INITIALIZATION / GPIO SUPPORT
   Implementations must be included in the Keil project.
   ========================================================= */
void init(void);
void led_init(void);

/* =========================================================
   ADC DRIVER
   ========================================================= */
void adc_init(void);
u32 adc_read(u8 channel);

/* =========================================================
   UART DRIVER
   ========================================================= */
void uart_init(u32 baud_rate);
void uart_tx(u8 data);
u8 uart_rx(void);
void uart_tx_string(s8 *str);
void uart_tx_integer(s32 value);
void uart_tx_float(float value);
void uart_rx_string(s8 *str);
s32 uart_rx_integer(void);

/* =========================================================
   DELAY DRIVER
   ========================================================= */
void delay_ms(u32 milliseconds);
void delay_sec(u32 seconds);
void delay_us(u32 microseconds);

/* =========================================================
   LCD DRIVER
   ========================================================= */
void lcd_init(void);
void lcd_cmd(u8 command);
void lcd_data(u8 data);
void lcd_string(s8 *str);
void lcd_integer(s32 value);
void lcd_float(float value);

/* =========================================================
   I2C DRIVER
   ========================================================= */
void i2c_init(void);
void i2c_write(u8 slave_address, u8 memory_address, u8 data);
u8 i2c_read(u8 slave_address, u8 memory_address);

/* =========================================================
   DS1307 RTC DRIVER
   ========================================================= */
void get_time(void);
void get_date(void);
void set_time(u8 hours, u8 minutes, u8 seconds);
void set_date(u8 day, u8 month_value, u8 year_value);
void display_time(void);
void display_date(void);

/* =========================================================
   AT24C08 EEPROM DRIVER
   ========================================================= */
void eeprom_store(void);
void eeprom_read(void);
u32 hexa(u8 value);

#endif /* HEADER_H */
