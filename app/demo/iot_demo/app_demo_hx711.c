/*
 * Copyright (c) 2020 HiHope Community.
 * Description: mq2 demo
 * Author: HiSpark Product Team.
 * Create: 2020-5-20
 */
#include <math.h>
#include <hi_early_debug.h>
#include <hi_task.h>
#include <hi_time.h>
#include <hi_adc.h>
#include <hi_stdlib.h>
#include <hi_watchdog.h>
#include <ssd1306_oled.h>
#include <hi_pwm.h>
#include <hi_io.h>
#include <hi_gpio.h>
#include "hx711.h"


hi_u32 g_hx711_id;
double base_data = 0,hx711_weight = 0;//dog food
double base_data_2 = 0,hx711_weight_2 = 0;//cat food

double last_fed_food_weight=0;//fed_food_weight 
double last_weight,now_weight;//state weight

double have_eat_weight=0;//eat how much
int have_eat_who=0;//eat who
int have_eat_flag;//have eat

hi_void gpio_init()
{
	hi_io_set_func(HI_IO_NAME_GPIO_13, HI_IO_FUNC_GPIO_13_I2C0_SDA);
    hi_io_set_func(HI_IO_NAME_GPIO_14, HI_IO_FUNC_GPIO_14_I2C0_SCL);
}

hi_void hi_hx711_init(hi_void)
{
	//gpio_init();
	/* init scale2 */
	//Initialize gpio11 as GPIO input and DT pin of sensor
    hi_io_set_func(SCALE_2_IO_SDA, SCALE_2_FUN_SDA);
    hi_gpio_set_dir(SCALE_1_IDX_SDA|SCALE_2_IDX_SDA,HI_GPIO_DIR_IN);
	//Initialize gpio11 as GPIO output and SCK pin of sensor
    hi_io_set_func(SCALE_2_IO_SCK, SCALE_2_FUN_SCK);
    hi_gpio_set_dir(SCALE_2_IDX_SCK,HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(SCALE_2_IO_SCK,0);
    /* init scale1 */
	 hi_io_set_func(SCALE_1_IO_SDA, SCALE_1_FUN_SDA);
    hi_gpio_set_dir(SCALE_1_IDX_SDA,HI_GPIO_DIR_IN);
	//Initialize gpio11 as GPIO output and SCK pin of sensor
    hi_io_set_func(SCALE_1_IO_SCK, SCALE_1_FUN_SCK);
    hi_gpio_set_dir(SCALE_1_IDX_SCK,HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(SCALE_1_IO_SCK,0);

	hi_udelay(2);
	base_data_2 = Get_Sensor_Read(2); //Get benchmark value
	hi_udelay(2);
	base_data = Get_Sensor_Read(1); //Get benchmark value
	hi_udelay(2);
}

hi_void hi_hx711_read(hi_void)
{
	static hi_u32 i=0;

	//读数据
	//printf("read 0\n");
	double temp1 = (Get_Sensor_Read(1) - base_data) / GapValue; //Gain dog food weight
	double temp2 = (Get_Sensor_Read(2) - base_data_2) / GapValue; //Gain cat food weight

	hx711_weight = temp1>0 ? temp1:-temp1;
	hx711_weight_2 = temp2>0 ? temp2:-temp2;
	//printf("read 2\n");

	//周期性发数据
	if(1){
		printf("dog food :   %.2f\r\n" ,hx711_weight ); 
		printf("cat food :   %.2f\r\n" ,hx711_weight_2 );  
	}
}

hi_void hi_hx711_display(hi_void)
{	
	// gpio_init();
	// /* init scale2 */
	// //Initialize gpio11 as GPIO input and DT pin of sensor
    // hi_io_set_func(SCALE_2_IO_SDA, SCALE_2_FUN_SDA);
    // hi_gpio_set_dir(SCALE_1_IDX_SDA|SCALE_2_IDX_SDA,HI_GPIO_DIR_IN);
	// //Initialize gpio11 as GPIO output and SCK pin of sensor
    // hi_io_set_func(SCALE_2_IO_SCK, SCALE_2_FUN_SCK);
    // hi_gpio_set_dir(SCALE_2_IDX_SCK,HI_GPIO_DIR_OUT);
    // hi_gpio_set_ouput_val(SCALE_2_IO_SCK,0);
    // /* init scale1 */
	//  hi_io_set_func(SCALE_1_IO_SDA, SCALE_1_FUN_SDA);
    // hi_gpio_set_dir(SCALE_1_IDX_SDA,HI_GPIO_DIR_IN);
	// //Initialize gpio11 as GPIO output and SCK pin of sensor
    // hi_io_set_func(SCALE_1_IO_SCK, SCALE_1_FUN_SCK);
    // hi_gpio_set_dir(SCALE_1_IDX_SCK,HI_GPIO_DIR_OUT);
    // hi_gpio_set_ouput_val(SCALE_1_IO_SCK,0);

	//Initialize I2C and use OLED screen
    // hi_i2c_init(HI_I2C_IDX_0, HI_I2C_IDX_BAUDRATE); /* baudrate: 400kbps */
    // hi_i2c_set_baudrate(HI_I2C_IDX_0, HI_I2C_IDX_BAUDRATE);
	//OLED initializes and displays the corresponding information
    // while( HI_ERR_SUCCESS != oled_init()) ;
	// oled_fill_screen(OLED_CLEAN_SCREEN);
    // oled_show_str(0,2, "Weigth : ",1);

    hi_u8 buf[10] = {0};
	hi_u8 buf_2[10] = {0};
     
		// oled_show_str(0,5, "                ",1);
		// oled_show_str(0,7, "                ",1);
        if(hx711_weight > 0) // Display when greater than 0
        {
            printf("weight :   %.2f\r\n" ,hx711_weight);  
            sprintf_s(buf,10,"%.2f g ",hx711_weight);
            oled_show_str(20,5, buf,1);
			if(hx711_weight_2<0)
				hx711_weight_2 = -hx711_weight_2;
			printf("weight2 :   %.2f\r\n" ,hx711_weight_2);  
            sprintf_s(buf_2,10,"%.2f g ",hx711_weight_2);
            oled_show_str(20,7, buf_2,1);
        }else
		{
			hx711_weight = -hx711_weight;
			if(hx711_weight_2<0)
				hx711_weight_2 = -hx711_weight_2;
			printf("weight :   %.2f\r\n" ,hx711_weight);  
            sprintf_s(buf,10,"%.2f g ",hx711_weight);
            oled_show_str(20,5, buf,1);
			printf("weight2 :   %.2f\r\n" ,hx711_weight_2);  
            sprintf_s(buf_2,10,"%.2f g ",hx711_weight_2);
            oled_show_str(20,7, buf_2,1);
		}

        // hi_sleep(1);
		
     
}
unsigned long Sensor_Read(const int scale)
{
	unsigned long value = 0;
	unsigned char i = 0;
	hi_gpio_value input = 0;
	hi_udelay(2);
	
	int scale_sck=SCALE_1_IO_SCK;
	int scale_sda=SCALE_1_IO_SDA;

	if(scale==2){
		scale_sck=SCALE_2_IO_SCK;
		scale_sda=SCALE_2_IO_SDA;
	}

	//When the clock line is pulled down and idle, the clock line keeps low potential
	hi_gpio_set_ouput_val(scale_sck,0);
	hi_udelay(2);	
	hi_gpio_get_input_val(scale_sda,&input);
	//Wait for AD conversion to finish
	while(input)
    {
        hi_gpio_get_input_val(scale_sda,&input);
    }
	for(i=0;i<24;i++)
	{
		//The clock line is pulled up to send the clock pulse
		hi_gpio_set_ouput_val(scale_sck,1);
		// hi_udelay(2);
		
		//Shift left and fill zero right to wait for receiving data
		value = value << 1;
		//Clock line down
		hi_gpio_set_ouput_val(scale_sck,0);
		// hi_udelay(2);
		//Read one bit data
        hi_gpio_get_input_val(scale_sda,&input);
		if(input){
			value ++;
        }
		
	}
	//The 25th pulse
	hi_gpio_set_ouput_val(scale_sck,1);
	hi_udelay(2);
	value = value^0x800000;	
	//25th pulse end
	hi_gpio_set_ouput_val(scale_sck,0);	
	hi_udelay(2);	
	return value;
}
/*get serson data*/ 
double Get_Sensor_Read(const int scale)
{
  	double sum = 0;    // In order to reduce the error, take out 10 values at a time and calculate the average value.
  	for (int i = 0; i < 10; i++) // The more loops, the higher the accuracy, and of course, the more time it takes
    	sum += Sensor_Read(scale);  // accumulation
  	return (sum/10); // Calculate the average value for average difference

}

static hi_void *Hx711Entry(hi_void *arg)
{
    hi_hx711_init();
    while(1)
    {
        hi_hx711_read();
        
        hi_sleep(500);
    }
    return NULL;
} 

hi_u32 hx711_read_task(hi_void)
{
    hi_u32 ret;
    hi_task_attr led_control_attr = {0};
	/*led_ control_ Parameter configuration of attr structure*/
    led_control_attr.stack_size = HX711_TASK_STACKSIZE;//Task stack memory
    led_control_attr.task_prio = HX711_TASK_PRIOR;//The task priority ranges from 0 to 31. Tasks 0 to 10 should not be used. The SDK has been used. The higher the value, the lower the priority
    led_control_attr.task_name = (hi_char*)"hx711 read";//Task name
	//Create task
    ret = hi_task_create(&g_hx711_id, &led_control_attr, Hx711Entry, HI_NULL);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to create hx711 read task\r\n");
        printf("0x%x\n",ret);
        return HI_ERR_FAILURE;
    }
    return HI_ERR_SUCCESS;
}
