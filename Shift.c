#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * Bit mask on change byte im uint32_t
 * */
//0xXXXXFFXX
//0b_XXXXXXXX_XXXXXXXX_11111111_XXXXXXXX

uint32_t BitShift(uint32_t Num, uint8_t ByteShift)
{
	//printf("In func Number:%lx, Shift:%1d \n", Num, ByteShift);
	
	Num|=(0xFF<<(ByteShift*8));
	return Num;
}


int main(void)
{
	uint32_t Number;
	uint32_t Shift;

	printf("Your number in bytes (uint32_t):");
	scanf("%lx", &Number);
	//printf("%lx, %d \n", Number, Number);
	printf("How many bytes to shift (uint8_t):");
	scanf("%d", &Shift);

	printf("Result: %lx \n", BitShift(Number, (uint8_t)Shift));

	//printf("Result: %lx \n", BitShift((uint32_t)scanf("%lx"), scanf("%d")));

	return 0;
}
