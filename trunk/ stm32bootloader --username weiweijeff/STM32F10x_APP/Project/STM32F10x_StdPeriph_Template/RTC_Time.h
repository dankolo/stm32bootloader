#ifndef _RTC_TIME_H_
#define _RTC_TIME_H_
#include <time.h>

#define RTCClockOutput_Enable

struct tm Time_ConvUnixToCalendar(time_t t);
time_t Time_ConvCalendarToUnix(struct tm t);
time_t Time_GetUnixTime(void);
struct tm Time_GetCalendarTime(void);
void Time_SetUnixTime(time_t);
void Time_SetCalendarTime(struct tm t);

void RTC_Configuration(void);
void RTC_Config(void);

#endif
