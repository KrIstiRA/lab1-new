#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "largeNum.h"


int main(int argc, char* argv[])
{
	char *file1 = argv[1];//входной файл 1
	char operation = argv[2][0];//знак операции
	char *file2 = argv[3];//входной файл 2
	char *file3 = argv[4];//файл результат
	char *filemod = NULL;//файл с модулем

	int binar = 0;
	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))
			binar = 1;
		else
			filemod = argv[5];
	}
	if (argc == 7)
	{
			binar = 1;
			filemod = argv[6];
	}
	bigInt A, B, mod;
	if (binar == 1)
	{
		A = getFrombinarFile(file1);
		B = getFrombinarFile(file2);
		if (filemod != NULL)
		mod = getFrombinarFile(filemod);
	}
	else
	{
		A = ReadFromTextFile(file1);
		B = ReadFromTextFile(file2);
		if (filemod != NULL)
			mod = ReadFromTextFile(filemod);
	}
	struct bigInt c;
	c.sizeNum = 0;
	c.sign = 0;
	c.digits = NULL;
	if (argv[2][0] == '+')
	{
		c = sumAndSub(A, B);
	}
	if (argv[2][0] == '-')
	{
		bigInt minusB = minus(B);
		c = sumAndSub(A, minusB);
		free(minusB.digits);
	}
	if (argv[2][0] == '*')
	{
		c = mul(A, B);
	}
	if (argv[2][0] == '/')
	{
		bigInt q;
		c = dividing(A, B, &q);
		free(q.digits);
	}

	if (argv[2][0] == '%')
	{
		bigInt q = dividing(A, B, &c);
		free(q.digits);
	}
	if (filemod != NULL)
	{
	    bigInt tmp;
		bigInt q = dividing(c, mod, &tmp);
		free(q.digits);
		free(c.digits);
		c = tmp;
	}
	if (argv[2][0] == '^')
	{
		if (filemod == NULL)
		{
			c = myPow(A, B);
		}
		else
		{
			c = powMod(A, B, mod);
		}
	}
	if (binar == 1)
	{
		saveTobinarFile(file3, c);
	}
	else

	WriteToTFile(file3, c);
	free(A.digits);
	free(B.digits);
	free(c.digits);
	if (filemod != NULL)
	free(mod.digits);
	return 0;
}
