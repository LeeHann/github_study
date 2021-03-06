﻿#include <iostream>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct Mystruct
{
	unsigned short x;
	unsigned short y;
	unsigned short w;
	unsigned short h;
}S_SHEET;

int main()
{
	static unsigned char buf[10000];
	FILE* fp = fopen("../sheet.bin", "rb");

	fseek(fp, 0, SEEK_END);
	int _size = ftell(fp);
	int _count = _size / sizeof(S_SHEET);

	fseek(fp, 0, SEEK_SET);
	fread(buf, 10000, 1, fp);
	printf("data count : %d\n", _count);

	S_SHEET* ptr = (S_SHEET*)buf;

	for (int i = 0; i < _count; i++)
	{
		printf("%4d,%4d,%4d,%4d\n", ptr->x, ptr->y, ptr->w, ptr->h);
		ptr++;
	}

	fclose(fp);
	return 0;
}