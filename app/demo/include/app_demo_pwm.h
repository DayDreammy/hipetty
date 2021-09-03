/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __APP_DEMO_PWM_H__
#define __APP_DEMO_PWM_H__

#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_pwm.h>
#include <hi_time.h>
#include <hi_io.h>
#include <hi_gpio.h>
#include <app_demo_pwm.h>

hi_void app_demo_pwm(hi_void);
hi_void pwm_3_demo(hi_void);
hi_void pwm_2_demo(hi_void);
hi_void set_engine_angle_forward_rotation(hi_gpio_idx id,hi_s32 duty);
#endif