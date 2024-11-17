#include "Python.h"
#include <stdio.h>

/**
 * print_python_int - prints python integers
 * @p: python object
 *
 * Return: void
 */

void print_python_int(PyObject *p)
{
	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}

	unsigned long int num, factor;
	digit *python_digit = ((PyLongObject *)(p))->ob_digit;
	Py_ssize_t size = ((PyVarObject *)(p))->ob_size;
	Py_ssize_t absolute_val = size < 0 ? -size : size;
	Py_ssize_t i;

	if (absolute_val > 3 || (absolute_val == 3 && python_digit[2] > 0xf))
	{
		printf("C unsigned long int overflow\n");
		return;
	}

	num = 0;
	factor = 1;
	for (i = 0; i < absolute_val; i++)
	{
		num += python_digit[i] * factor;
		factor *= (1UL << PyLong_SHIFT);
	}
	if (size < 0)
		putchar('-');
	printf("%lu\n", num);
}
