
#include"uart.h"
#include"i2c_24.h"

int main()
{
uart1_init(9600);

i2c_init();
//i2c_write();

while(1)
{
i2c_read();
}
}
