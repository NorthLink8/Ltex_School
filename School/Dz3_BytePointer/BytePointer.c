#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t __exit=0;
void ByteArrayOutput(uint8_t* BytesArray)
{
	printf("sizeof & =%d \n\n", sizeof(BytesArray));
	for(uint8_t k=0; k<sizeof(uint32_t); k++)
		printf("%x ",BytesArray[k]);
	printf("\n");

}

void RenumByte(uint8_t* BytesArray, uint8_t ReNum, uint8_t Byte)
{
	BytesArray[ReNum]=Byte;
	for(uint8_t k=0; k<sizeof(uint32_t); k++)
		printf("%x ",BytesArray[k]);
	printf("\n");
}


void _task1()
{
	printf("Enter your number (HEX uint32_t): ");
	uint32_t Num;
	scanf("%x", &Num);
	ByteArrayOutput((uint8_t*)&Num);
}
void _task2()
{
	printf("Enter your number (HEX uint32_t): ");
	uint32_t Num=0, _ReNum=0, _Byte=0; 
	scanf("%x", &Num);
	printf("Enter Num of rename:(DEC) ");
	scanf("%d", &_ReNum);
	printf("Enter rename byte:(HEX) ");
	scanf("%x", &_Byte);
	RenumByte((uint8_t*)&Num, (uint8_t)_ReNum, (uint8_t)_Byte);
}

void Tasks(uint8_t TheTask)
{
	switch(TheTask)
	{
		case 0:
			_task1();
			break;

		case 1:
			_task2();
			break;

		default:
			__exit=1;
	}
}

int main(void)
{
	printf("sizeof uint32_t =%d \n", sizeof(uint32_t));

	/*printf("Enter your number (uint32_t)");
	uint32_t Num;
	scanf("%x", &Num);
	ByteNumberOutput((uint8_t*)&Num);*/
	
	while(__exit==0)
	{
		uint8_t _Task;
		printf("Enter num of task: ");
		scanf("%d", &_Task);
		Tasks(_Task);
	}

	return 0;
}
