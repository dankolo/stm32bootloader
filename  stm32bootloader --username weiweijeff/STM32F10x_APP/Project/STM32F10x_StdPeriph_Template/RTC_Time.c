/*******************************************************************************
* ���ļ�ʵ�ֻ���RTC�����ڹ��ܣ��ṩ�����յĶ�д��������ANSI-C��time.h��
*
* ���ߣ�jjldc ���žţ�
* QQ: 77058617
*
* RTC�б����ʱ���ʽ����UNIXʱ�����ʽ�ġ���һ��32bit��time_t������ʵΪu32��
*
* ANSI-C�ı�׼���У��ṩ�����ֱ�ʾʱ�������  �ͣ�
* time_t:   	UNIXʱ�������1970-1-1��ĳʱ�侭����������
* 	typedef unsigned int time_t;
*
* struct tm:	Calendar��ʽ����������ʽ��
*   tm�ṹ���£�
*   struct tm {
*   	int tm_sec;   // �� seconds after the minute, 0 to 60
*   					 (0 - 60 allows for the occasional leap second)
*   	int tm_min;   // �� minutes after the hour, 0 to 59
*		int tm_hour;  // ʱ hours since midnight, 0 to 23
*		int tm_mday;  // �� day of the month, 1 to 31
*		int tm_mon;   // �� months since January, 0 to 11
*		int tm_year;  // �� years since 1900
*		int tm_wday;  // ���� days since Sunday, 0 to 6
*		int tm_yday;  // ��Ԫ��������� days since January 1, 0 to 365
* 		int tm_isdst; // ����ʱ����Daylight Savings Time flag
* 		...
* 	}
* 	����wday��yday�����Զ����������ֱ�Ӷ�ȡ
* 	mon��ȡֵΪ0-11
*	***ע��***��
*	tm_year:��time.h���ж���Ϊ1900�������ݣ���2008��Ӧ��ʾΪ2008-1900=108
* 	���ֱ�ʾ�������û���˵����ʮ���Ѻã�����ʵ�нϴ���졣
* 	�����ڱ��ļ��У����������ֲ��졣
* 	���ⲿ���ñ��ļ��ĺ���ʱ��tm�ṹ�����͵����ڣ�tm_year��Ϊ2008
* 	ע�⣺��Ҫ����ϵͳ��time.c�еĺ�������Ҫ���н�tm_year-=1900
*
* ��Ա����˵����
* struct tm Time_ConvUnixToCalendar(time_t t);
* 	����һ��Unixʱ�����time_t��������Calendar��ʽ����
* time_t Time_ConvCalendarToUnix(struct tm t);
* 	����һ��Calendar��ʽ���ڣ�����Unixʱ�����time_t��
* time_t Time_GetUnixTime(void);
* 	��RTCȡ��ǰʱ���Unixʱ���ֵ
* struct tm Time_GetCalendarTime(void);
* 	��RTCȡ��ǰʱ�������ʱ��
* void Time_SetUnixTime(time_t);
* 	����UNIXʱ�����ʽʱ�䣬����Ϊ��ǰRTCʱ��
* void Time_SetCalendarTime(struct tm t);
* 	����Calendar��ʽʱ�䣬����Ϊ��ǰRTCʱ��
*
* �ⲿ����ʵ����
* ����һ��Calendar��ʽ�����ڱ�����
* struct tm now;
* now.tm_year = 2008;
* now.tm_mon = 11;		//12��
* now.tm_mday = 20;
* now.tm_hour = 20;
* now.tm_min = 12;
* now.tm_sec = 30;
*
* ��ȡ��ǰ����ʱ�䣺
* tm_now = Time_GetCalendarTime();
* Ȼ�����ֱ�Ӷ�tm_now.tm_wday��ȡ������
*
* ����ʱ�䣺
* Step1. tm_now.xxx = xxxxxxxxx;
* Step2. Time_SetCalendarTime(tm_now);
*
* ��������ʱ��Ĳ�
* struct tm t1,t2;
* t1_t = Time_ConvCalendarToUnix(t1);
* t2_t = Time_ConvCalendarToUnix(t2);
* dt = t1_t - t2_t;
* dt��������ʱ��������
* dt_tm = mktime(dt);	//ע��dt�����ƥ�䣬ansi���к���Ϊ�����ݣ�ע�ⳬ��
* ����Բο�������ϣ�����ansi-c��ĸ�ʽ������ȹ��ܣ�ctime��strftime��
*
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "RTC_Time.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Time_ConvUnixToCalendar(time_t t)
* Description    : ת��UNIXʱ���Ϊ����ʱ��
* Input 		 : u32 t  ��ǰʱ���UNIXʱ���
* Output		 : None
* Return		 : struct tm
*******************************************************************************/
struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;	//localtimeת�������tm_year�����ֵ����Ҫת�ɾ���ֵ
	return *t_tm;
}

/*******************************************************************************
* Function Name  : Time_ConvCalendarToUnix(struct tm t)
* Description    : д��RTCʱ�ӵ�ǰʱ��
* Input 		 : struct tm t
* Output		 : None
* Return		 : time_t
*******************************************************************************/
time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year -= 1900;  //�ⲿtm�ṹ��洢�����Ϊ2008��ʽ
						//��time.h�ж������ݸ�ʽΪ1900�꿪ʼ�����
						//���ԣ�������ת��ʱҪ���ǵ�������ء�
	return mktime(&t);
}

/*******************************************************************************
* Function Name  : Time_GetUnixTime()
* Description    : ��RTCȡ��ǰʱ���Unixʱ���ֵ
* Input 		 : None
* Output		 : None
* Return		 : time_t t
*******************************************************************************/
time_t Time_GetUnixTime(void)
{
	return (time_t)RTC_GetCounter();
}

/*******************************************************************************
* Function Name  : Time_GetCalendarTime()
* Description    : ��RTCȡ��ǰʱ�������ʱ�䣨struct tm��
* Input 		 : None
* Output		 : None
* Return		 : time_t t
*******************************************************************************/
struct tm Time_GetCalendarTime(void)
{
	time_t t_t;
	struct tm t_tm;

	t_t = (time_t)RTC_GetCounter();
	t_tm = Time_ConvUnixToCalendar(t_t);
	return t_tm;
}

/*******************************************************************************
* Function Name  : Time_SetUnixTime()
* Description    : ��������Unixʱ���д��RTC
* Input 		 : time_t t
* Output		 : None
* Return		 : None
*******************************************************************************/
void Time_SetUnixTime(time_t t)
{
	RTC_WaitForLastTask();
	RTC_SetCounter((u32)t);
	RTC_WaitForLastTask();
	return;
}

/*******************************************************************************
* Function Name  : Time_SetCalendarTime()
* Description    : ��������Calendar��ʽʱ��ת����UNIXʱ���д��RTC
* Input 		 : struct tm t
* Output		 : None
* Return		 : None
*******************************************************************************/
void Time_SetCalendarTime(struct tm t)
{
	Time_SetUnixTime(Time_ConvCalendarToUnix(t));
	return;
}



////////////////////////////////////////////////////////////////////////////////
// RTCʱ�ӳ�ʼ����
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : ����������RTC��BKP�����ڼ�⵽�󱸼Ĵ������ݶ�ʧʱʹ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Configuration(void)
{
	//����PWR��BKP��ʱ�ӣ�from APB1��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	//�������
	PWR_BackupAccessCmd(ENABLE);

	//���ݼĴ���ģ�鸴λ
	BKP_DeInit();

	//�ⲿ32.768K��Ӵż�Ǹ�
	RCC_LSEConfig(RCC_LSE_ON);
	//�ȴ��ȶ�
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

	//RTCʱ��Դ���ó�LSE���ⲿ32.768K��
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	//RTC����
	RCC_RTCCLKCmd(ENABLE);

	//��������Ҫ�ȴ�APB1ʱ����RTCʱ��ͬ�������ܶ�д�Ĵ���
	RTC_WaitForSynchro();

	//��д�Ĵ���ǰ��Ҫȷ����һ�������Ѿ�����
	RTC_WaitForLastTask();

	//����RTC��Ƶ����ʹRTCʱ��Ϊ1Hz
	//RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
	RTC_SetPrescaler(32767);


	//�ȴ��Ĵ���д�����
	RTC_WaitForLastTask();

	//ʹ�����ж�
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	//�ȴ�д�����
	RTC_WaitForLastTask();

	return;
}

/*******************************************************************************
* Function Name  : RTC_Config
* Description    : �ϵ�ʱ���ñ��������Զ�����Ƿ���ҪRTC��ʼ����
* 					����Ҫ���³�ʼ��RTC�������RTC_Configuration()�����Ӧ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Config(void)
{
	//������BKP�ĺ󱸼Ĵ���1�У�����һ�������ַ�0xA5A5
	//��һ���ϵ��󱸵�Դ����󣬸üĴ������ݶ�ʧ��
	//����RTC���ݶ�ʧ����Ҫ��������
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		//��������RTC
		RTC_Configuration();
		//������ɺ���󱸼Ĵ�����д�����ַ�0xA5A5
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		//���󱸼Ĵ���û�е��磬��������������RTC
		//�������ǿ�������RCC_GetFlagStatus()�����鿴���θ�λ����
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
			;//�����ϵ縴λ
		}
		else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
			;//�����ⲿRST�ܽŸ�λ
		}
		//���RCC�и�λ��־
		RCC_ClearFlag();

		//��ȻRTCģ�鲻��Ҫ�������ã��ҵ���������󱸵����Ȼ����
		RCC_RTCCLKCmd(ENABLE);
		//�ȴ�RTCʱ����APB1ʱ��ͬ��
		RTC_WaitForSynchro();

		//ʹ�����ж�
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		//�ȴ��������
		RTC_WaitForLastTask();
	}
    RCC_ClearFlag();

    /* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

#ifdef RTCClockOutput_Enable


	/* Disable the Tamper Pin */
	BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
								 functionality must be disabled */

	/* Enable RTC Clock Output on Tamper Pin */
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

	return;
}


