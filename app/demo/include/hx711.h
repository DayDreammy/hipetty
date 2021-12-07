#ifndef __HX711__
#define __HX711__

#include <hi_types_base.h>

//Calibration parameters
//Because the characteristic curves of different sensors are not very consistent, each sensor needs to correct this parameter to make the measured value very accurate.
//When it is found that the measured weight is too large, increase the value.
//If the measured weight is small, reduce the modified value.
//The value can be decimal, and can be adjusted by 10 with reference to the error 1g
#define GapValue 430
#define full_food 200
//GPIO 0 ,GPIO 1
// #define SCALE_1_IO_SDA HI_IO_NAME_GPIO_0
// #define SCALE_1_FUN_SDA HI_IO_FUNC_GPIO_0_GPIO
// #define SCALE_1_IDX_SDA HI_GPIO_IDX_0
// #define SCALE_1_IO_SCK HI_IO_NAME_GPIO_1
// #define SCALE_1_FUN_SCK HI_IO_FUNC_GPIO_1_GPIO
// #define SCALE_1_IDX_SCK HI_GPIO_IDX_1

//scale-dog GPIO 11 ,GPIO 12
#define SCALE_1_IO_SDA HI_IO_NAME_GPIO_11
#define SCALE_1_FUN_SDA HI_IO_FUNC_GPIO_11_GPIO
#define SCALE_1_IDX_SDA HI_GPIO_IDX_11
#define SCALE_1_IO_SCK HI_IO_NAME_GPIO_12
#define SCALE_1_FUN_SCK HI_IO_FUNC_GPIO_12_GPIO
#define SCALE_1_IDX_SCK HI_GPIO_IDX_12

#define SCALE_2_IO_SDA HI_IO_NAME_GPIO_10
#define SCALE_2_FUN_SDA HI_IO_FUNC_GPIO_10_GPIO
#define SCALE_2_IDX_SDA HI_GPIO_IDX_10
#define SCALE_2_IO_SCK HI_IO_NAME_GPIO_9
#define SCALE_2_FUN_SCK HI_IO_FUNC_GPIO_9_GPIO
#define SCALE_2_IDX_SCK HI_GPIO_IDX_9

#define FULL_WEIGHT 200

extern double base_data ,hx711_weight ;
extern double base_data_2 ,hx711_weight_2 ;
extern double last_fed_food_weight;
extern double last_weight,now_weight;//state weight

extern double have_eat_weight;//feed how much
extern int have_eat_who;//eat who
extern int have_eat_flag;//have eat

unsigned long Sensor_Read(const int scale);
double Get_Sensor_Read(const int scale);
hi_void hi_hx711_init(hi_void);
hi_void hi_hx711_task(hi_void);
double Get_Sensor_Read(const int scale);
hi_void hi_hx711_read(hi_void);

static hi_void *Hx711Entry(hi_void *arg);
hi_u32 hx711_read_task(hi_void);

#define HX711_TASK_PRIOR (28)
#define HX711_TASK_STACKSIZE (1024)
#define HX711_TASK_NAME "hx711_read"
extern hi_u32 g_hx711_id;

#endif