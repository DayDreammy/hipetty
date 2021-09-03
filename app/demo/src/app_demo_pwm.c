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

#include <app_demo_pwm.h>

hi_void pwm_0_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM0);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM0, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_1_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM1);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM1, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_2_demo(hi_void)
{
    
    hi_io_set_func(HI_IO_NAME_GPIO_7,HI_IO_FUNC_GPIO_7_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_7,HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_7,0);

   
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,500);
        // hi_udelay(1000000*2);
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,1000);
        // hi_udelay(1000000*2);
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,1500);
        // hi_udelay(1000000*2);
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,2000);
        // hi_udelay(1000000*2);
    set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_7,2500);
    hi_udelay(1000000*2);
    set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_7,500);
    hi_udelay(50000*3);
}

//正转
hi_void set_engine_angle_forward_rotation(hi_gpio_idx id,hi_s32 duty)
{
  

    for(int i=0;i<=5;i++){
        hi_gpio_set_ouput_val(id,HI_GPIO_VALUE1);
        hi_udelay(duty);
        hi_gpio_set_ouput_val(id,HI_GPIO_VALUE0);
        hi_udelay(20000-duty);
    }
    
    // hi_u32 count = duty/25;
    // for(int i=0; i <= count; i++){
    //     hi_gpio_set_ouput_val(id,HI_GPIO_VALUE1);
    //     hi_udelay(duty-i*25);
    //     hi_gpio_set_ouput_val(id,HI_GPIO_VALUE0);
    //     hi_udelay(20000-(duty-i*25));
    // }
    //hi_udelay(50000);
}

//反转
hi_void set_engine_angle_transfer(hi_gpio_idx id,hi_s32 duty)
{
    hi_u32 count = duty/25;

    for(int i=0; i <= count; i++){
        hi_gpio_set_ouput_val(id,HI_GPIO_VALUE1);
        hi_udelay(i*25);
        hi_gpio_set_ouput_val(id,HI_GPIO_VALUE0);
        hi_udelay(20000-i*25);
    }
    hi_udelay(50000);
}

//20ms一个波，
//180度舵机占空比与对应打角
//0度--0.5ms
//45度--1ms
//90度--1.5ms
//135度--2ms
//180度--2.5ms

hi_void pwm_3_demo(hi_void)
{
    hi_io_set_func(HI_IO_NAME_GPIO_6,HI_IO_FUNC_GPIO_6_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_6,HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_6,0);

   
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,500);
        // hi_udelay(1000000*2);
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,1000);
        // hi_udelay(1000000*2);
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,1500);
        // hi_udelay(1000000*2);
        // set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,2000);
        // hi_udelay(1000000*2);
    set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,2500);
    hi_udelay(1000000*2);
    set_engine_angle_forward_rotation(HI_IO_NAME_GPIO_6,500);
    hi_udelay(50000*3);
    
        

    // while(1){
        // for(int i=0;i<=180;i+=10){
            // hi_udelay(1000000);
        // }
        // for(int i=0;i<=180;i+=10){
        //     set_engine_angle_transfer(HI_IO_NAME_GPIO_6,i);
        // }
    // }
   


    // hi_pwm_init(HI_PWM_PORT_PWM3);
    // hi_pwm_set_clock(PWM_CLK_XTAL);
    // for(int i=0;i<65535;i+=1000){  
        // for(int i=1;i<=8;i++){
        //     hi_pwm_start(HI_PWM_PORT_PWM3, i*2000, 40000); /* duty: 750 freq:1500 */
        //     printf("i=%d\n",i);
        //     hi_udelay(1000000*2);
            
        //     if(i==8)
        //         i=0;
        // }
        // hi_pwm_start(HI_PWM_PORT_PWM3, 1000, 40000); /* duty: 750 freq:1500 */
        // hi_udelay(10000000);
        // hi_pwm_start(HI_PWM_PORT_PWM3, 2000, 40000); /* duty: 750 freq:1500 */
        // hi_udelay(10000000);
        // hi_pwm_start(HI_PWM_PORT_PWM3, 3000, 40000); /* duty: 750 freq:1500 */
        // hi_udelay(10000000);
        // hi_pwm_start(HI_PWM_PORT_PWM3, 4000, 40000); /* duty: 750 freq:1500 */
        // hi_udelay(10000000);
        // hi_pwm_start(HI_PWM_PORT_PWM3, 5000, 40000); /* duty: 750 freq:1500 */
        // hi_udelay(10000000);
    // }
    
        //hi_sleep(30);
    
    
}

hi_void pwm_4_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM4);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM4, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void pwm_5_demo(hi_void)
{
    hi_pwm_init(HI_PWM_PORT_PWM5);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(HI_PWM_PORT_PWM5, 750, 1500); /* duty: 750 freq:1500 */
}

hi_void app_demo_pwm(hi_void)
{
    printf("start test pwm");

    pwm_0_demo();
    pwm_1_demo();
    pwm_2_demo();
    pwm_3_demo();
    pwm_4_demo();
    pwm_5_demo();

    printf("please use an oscilloscope to check the output waveform!");
}

