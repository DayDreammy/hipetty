#ifndef __APP_DEMO_RTC_H__
#define __APP_DEMO_RTC_H__

#include <hi_types_base.h>

#define DS1307_ADDRESS          0x68  //1101000
#define DS1307_WRITE_ADDRESS    0x00    
#define DS1307_READ_ADDRESS     0x01
#define DS1307_REG_ARRAY_LEN    2
#define RTC_REG_TIME_BUF        2
#define SEND_BUF_LEN            3
#define SEND_SET_REG_LEN        2
#define SEND_READ_DATA_LEN      1
#define DS1307_TASK_STAK_SIZE   (1024*2)
#define DS1307_TASK_PRIORITY    (25)
#define MONTH_SETTING           ((hi_u8)0x05)
#define DELAY_TIME              ((hi_u32)10000)
#define RTC_FIRST_SECOND        0
#define RTC_FIRST_SECOND        0

/* time virable */
extern hi_s32 temp_second ;
extern hi_s32 temp_minute ;
extern hi_s32 temp_hour ;
extern hi_s32 temp_day ;
extern hi_s32 temp_date ;
extern hi_s32 temp_month ;
extern hi_s32 temp_year ;
//last feed time
extern hi_s32 last_feed_minute[2] ;
extern hi_s32 last_feed_hour[2] ;
extern hi_s32 last_feed_who;
#define FEED_DELAY_MINUTE 1

// warning long time no see
extern hi_s32 warning_nsee_dog;
extern hi_s32 warning_nsee_cat;
extern hi_s32 last_check_minute;
#define CHECK_TIME_MINUTE 1
#define WANGING_TIME_MINUTE 3

//猫狗识别枚举
typedef enum {
    CAT_J = 0x01,
    CAT_H = 0x02,
    DOG=0x03,
    OTHERS=0x04,
} dog_or_cat;

/*ds1307 reg*/
typedef enum {
    RCT_SECOND =0,
    RCT_MINUTE,
    RCT_HOUR,
    RCT_DAY,
    RCT_DATE,
    RCT_MONTH,
    RCT_YEAR
}rct_reg;

typedef struct 
{
    hi_u8 rtc_second[RTC_REG_TIME_BUF];
    hi_u8 rtc_minue[RTC_REG_TIME_BUF];
    hi_u8 rtc_hour[RTC_REG_TIME_BUF];
    hi_u8 rtc_day[RTC_REG_TIME_BUF];
    hi_u8 rtc_date[RTC_REG_TIME_BUF];
    hi_u8 rtc_month[RTC_REG_TIME_BUF];
    hi_u8 rtc_year[RTC_REG_TIME_BUF];
}ds1307_rtc_type;

hi_u32 ds1307_i2c_write( hi_u8 reg_addr, hi_u8 high_8, hi_u8 low_8, hi_u8 reg_len);
hi_u8 *ds1307_read(hi_u8 rtc_reg, hi_u32 recv_len, hi_u8 *rct_buf);
hi_void *rtc_timer(hi_void *param);
hi_void app_demo_rtc_task(hi_void);

#endif