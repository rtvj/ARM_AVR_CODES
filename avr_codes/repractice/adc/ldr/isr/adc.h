
int m_data;
char l_data;
void adc1_init() {
  
  ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
  ADMUX |= (1<<REFS0) | (1<<REFS1) | (1<<ADLAR);
  ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) | (1<<ADIE) | (1<<ADSC);
  ADCSRB &= ~((1<<ADTS0) | (1<<ADTS1) | (1<<ADTS2));
  //SREG |= (1<<7);
}
void adc2_init(){
  
  ADMUX &= ~((1<<MUX1) | (1<<MUX2) | (1<<MUX3));
  ADMUX |= (1<<MUX0) | (1<<REFS0) | (1<<REFS1);
  ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADCSRB &= ~((1<<ADTS0) | (1<<ADTS1) | (1<<ADTS2));
}

int ldr_read() {
  
  ADCSRA |= (1<<ADSC);
 while(!(ADCSRA & (1<<ADIF)));
  l_data = ADCL;
  m_data = ADCH;
  m_data |= (m_data<<8)|l_data;

  return m_data;
  
}