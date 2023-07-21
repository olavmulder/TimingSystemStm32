/*
 * led.h
 *
 *  Created on: Jul 20, 2023
 *      Author: olav
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "ssd1306/ssd1306.h"

#include <stdbool.h>
/* Private defines -----------------------------------------------------------*/
#define led_reset_Pin GPIO_PIN_4
#define led_reset_GPIO_Port GPIOA
#define led_timer_toggle_Pin GPIO_PIN_5
#define led_timer_toggle_GPIO_Port GPIOA
#define led0_Pin GPIO_PIN_11
#define led0_GPIO_Port GPIOB
/*---------------*/

/*Functions----------------------------------------*/
void LedTask(void);
void ButtonTask(void);


#endif /* INC_LED_H_ */
