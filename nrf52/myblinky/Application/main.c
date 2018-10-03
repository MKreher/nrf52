/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file main.c (changed by mkr)
 * @brief Blinky Example Application main file.
 *
 */

#define CUSTOM_BOARD 

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "boards.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"
#include "nrf_delay.h"
#include "nrf_error.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_clock.h"
#include "app_timer.h"
#include "app_button.h"
#include "app_error.h"
#include "sdk_errors.h"

#define LEDBUTTON_BUTTON 4
#define NUMBER_OF_BUTTONS 1

const uint32_t led_board_1  = 30;
const uint32_t led_board_2  = 31;
const uint32_t led_error    = 25;
const uint32_t led_success  = 26;

/**
 * @brief Function for starting lfclk needed by APP_TIMER.
 */
static void lfclk_init(void)
{
    uint32_t err_code;
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

/**@brief Function for handling events from the button handler module.
 *
 * @param[in] pin_no        The pin that the event applies to.
 * @param[in] button_action The button action (press/release).
 */
static void button_event_handler(uint8_t pin_no, uint8_t button_action)
{

    switch (pin_no)
    {
    case LEDBUTTON_BUTTON:
        nrf_gpio_pin_toggle(led_board_2);
        break;

    default:
        //APP_ERROR_HANDLER(pin_no);
        break;
    }
}

/**@brief Function for initializing the button handler module.
 */
static void buttons_init(void)
{

    ret_code_t err_code;

    //The array must be static because a pointer to it will be saved in the button handler module.
    static const app_button_cfg_t buttons[NUMBER_OF_BUTTONS] =
        {
            {LEDBUTTON_BUTTON, false, BUTTON_PULL, button_event_handler}
        };

    err_code = app_button_init(buttons, ARRAY_SIZE(buttons), APP_TIMER_TICKS(50));
    APP_ERROR_CHECK(err_code);

    err_code = app_button_enable();
    APP_ERROR_CHECK(err_code);

    if (err_code == NRF_SUCCESS)
    {
        nrf_gpio_pin_set(led_success);        
    }
}


/**
 * @brief Function for application main entry.
 */
    int main(void)
    {

        // Configure LED-pin as outputs and clear.
        nrf_gpio_cfg_output(led_board_1);
        nrf_gpio_pin_clear(led_board_1);

        nrf_gpio_cfg_output(led_board_2);
        nrf_gpio_pin_clear(led_board_2);

        nrf_gpio_cfg_output(led_error);
        nrf_gpio_pin_clear(led_error);

        nrf_gpio_cfg_output(led_success);
        nrf_gpio_pin_clear(led_success);

        lfclk_init();

        // Start APP_TIMER to generate timeouts.
        ret_code_t err_code = app_timer_init();
        APP_ERROR_CHECK(err_code);

        buttons_init();

        // Toggle LED.
        while (true)
        {
            nrf_gpio_pin_toggle(led_board_1);
            //nrf_gpio_pin_toggle(led_board_2);
            nrf_delay_ms(1000);
        }
}

/** @} */
