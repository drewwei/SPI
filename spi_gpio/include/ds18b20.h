#ifndef _ds18b20_
#define _ds18b20_
void ds18b20_init();

void ds18b20_send_byte(char c);

void ds18b20_send_bytes(char *p, unsigned int len);

void ds180b20_rev_bytes(char *buff, int count);

struct temp read_tempareture();


struct temp{
	int temp_l;
	int temp_h;
};

#endif