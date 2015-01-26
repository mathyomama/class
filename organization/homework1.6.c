#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)


typedef union ieee754_hex {
	signed int hex;
	struct {
		unsigned int fraction:23;
		unsigned int exponent:8;
		unsigned int sign:1;
	} ieee_little;
	struct {
		unsigned int sign:1;
		unsigned int exponent:8;
		unsigned int fraction:23;
	} ieee_big;
} ieee754_hex;

void show_number(ieee754_hex num) {
	unsigned int fraction, exponent, sign;
	if (IS_BIG_ENDIAN) {
		fraction = num.ieee_big.fraction;
		exponent = num.ieee_big.exponent;
		sign = num.ieee_big.sign;
	} else {
		fraction = num.ieee_little.fraction;
		exponent = num.ieee_little.exponent;
		sign = num.ieee_little.sign;
	}

	double decimal = pow(-1, sign)*(1 + fraction*pow(2, -23))*pow(2, exponent - 127);

	printf("HEX: %X\nDECIMAL: %E\n\n", num.hex, decimal);
}

int main(int argc, char *argv[]) {
	//The numbers from the homework are hardcoded below
	signed int numbers[] = {-23, -161, 2147483487};
	int i;
	for (i = 0; i < sizeof(numbers)/sizeof(int); i++) {
		show_number((ieee754_hex) numbers[i]);
	}

	return 0;
}
