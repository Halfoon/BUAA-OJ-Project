#include<stdio.h>

int n;
int a,b,c,d;

int read()
{
	int k = 0;
	char c = getchar();
	while (c < '0' || c>'9')
	{
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		k = (k << 1) + (k << 3) + c - 48;
		c = getchar();
	}
	return k;
}

int main()
{
	n = read();
	while(n--)
	{
		a = read(),b = read(),c = read(),d = read();
		if(a>=1&&a<=126)puts("A");
		else if(a>=128&&a<=191)puts("B");
		else if(a>=192&&a<=223)puts("C");
		else if(a>=224&&a<=239)puts("D");
		else if(a>=240&&a<=255)puts("E");
	}
}
