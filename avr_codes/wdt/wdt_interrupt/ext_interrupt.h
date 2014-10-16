
void eint_init(void)
{
	DDRE&=(1<<6);//configure as i/p
	PORTE|=(1<<6);//ENABLE PULL-UP
	EICRB|=(1<<5)&(~(1<<4));
	EIMSK|=(1<<INT6);
}
