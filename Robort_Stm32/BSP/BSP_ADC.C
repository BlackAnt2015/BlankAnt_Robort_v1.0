#include "BSP_ADC.H"

u16 ADC_Vaule_Buff[ADC_Ch_Num][ADC_Point]={0};   //��ѹ�ɼ�������
u16 ADC_Vaule[ADC_Ch_Num]={0};                   //��ѹֵ,��λ��mv
static u8  ADC_Ch=0;
static u8  ADC_Count=0;
 
																   
void  ADC1_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��,ͬʱ����PA\PC�˿�ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);                       //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

                       
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//PA4��PA5 ��Ϊģ��ͨ����������  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	      //PA0~PC5 ��Ϊģ��ͨ����������  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	ADC_DeInit(ADC1);                                   //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 

}	

//���ADCֵ
u16 STM32_ADC_Gather(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

void ADC_Vaule_Handle(void)
{
	u32 Temp=0;
	u8  i=0,j=0;
	for(j=0;j<ADC_Ch_Num;j++)
	{
		for( i=0;i<ADC_Point;i++)
		 Temp = Temp+ADC_Vaule_Buff[j][i];
		
		Temp=Temp/ADC_Point;           //ȡƽ��

		
		ADC_Vaule[j]=Temp;
		Temp=0;
	}

}


void Task_ADC_Handle(void)
{
	
  if( ADC_Ch>=ADC_Ch_Num)
			ADC_Ch=0;
	switch( ADC_Ch)
		{
		case 0: ADC_Vaule_Buff[0][ADC_Count]=STM32_ADC_Gather(4); break;
		case 1: ADC_Vaule_Buff[1][ADC_Count]=STM32_ADC_Gather(5); break;
		case 2: ADC_Vaule_Buff[2][ADC_Count]=STM32_ADC_Gather(10);break;
		case 3: ADC_Vaule_Buff[3][ADC_Count]=STM32_ADC_Gather(11);break;
		case 4: ADC_Vaule_Buff[4][ADC_Count]=STM32_ADC_Gather(12);break;
		case 5: ADC_Vaule_Buff[5][ADC_Count]=STM32_ADC_Gather(13);break;
		case 6: ADC_Vaule_Buff[6][ADC_Count]=STM32_ADC_Gather(14);break;
		case 7: ADC_Vaule_Buff[7][ADC_Count]=STM32_ADC_Gather(15); 
		ADC_Count++;break;     //�ɼ������һ��ͨ����ADC_Count++
		default:                                                break;
	} 
		
	if(ADC_Count>=ADC_Point)                                             //�ɼ��꣬����ƽ���˲�����
	{
		ADC_Vaule_Handle();
		ADC_Count=0;
	}
	ADC_Ch++;
}
 
u16 STM32_ADC_Read( u8 ch)
{
	return ADC_Vaule[ch];
}	
/*********************************************END OF FILE*********************a*/