#include <stdlib.h>
#include <stdio.h>

int x[8] = {1,2,3,-1,-2,0,184,340057058};
int y[8] = {0,0,0,0,0,0,0,0};

int f(int a0){
	int r2 = 0x80000000;
	int x = 0;
	while (a0 != 0){
		if ((r2&a0) != 0)
			x++;
		a0 = 2 * a0;
	}
	return x;
}

int main(int argc, char const *argv[])
{
	for (int i = 7; i >= 0; i--){
		y[i] = f(x[i]);
	}
	for (int i = 0; i < 8; i++){
		printf("%d\n", x[i]);
	}
	for (int i = 0; i < 8; i++){
		printf("%d\n", y[i]);
	}
	return 0;
}
