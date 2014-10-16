void adc_init()
{
	PINSEL0|=(1<<8);
	PINSEL0|=(1<<9);//AD0.6 at P0.28
	
	AD0CR|=(1<<6)|(12<<8)|(1<<21)|(1<<16);//AD0.1 ;VPB clock (PCLK) value=12 ie 5MHz;PDN=1 ie ADC is operational; burst mode on
}

unsigned int adc_read()
{
	//AD0CR|=(1<<24);//001=Start conversion now;not needed in burst mode.
	
	while(!(AD0DR6&(1<<31)));//This bit is set to 1 when an A/D conversion completes,hence poll till it becomes 1.
                               
	return((AD0DR6 & 0x0000FFC0)>>6);//masking(refer notbk)
}



