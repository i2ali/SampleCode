#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C RunTime Header Files
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>



bool GetBit(int num, int i) {
	return ((num & (1 << i)) != 0);
}

int SetBit(int num, int i) {
	return ((num | (i << i)));
}

int ClearBit(int num, int i) {
	int mask = ~(1 << i);
	return mask & num;
}


/*
void main()
{
	GetBit(16, 2);
	SetBit(16, 0);

}
*/