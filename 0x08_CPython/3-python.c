#include "Python.h"
#include <math.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_list - prints basic info about python lists
 * @p: PyObject
 *
 * Return: void
 */

void print_python_list(PyObject *p)
{
	PyListObject *list = NULL;
	PyObject *item = NULL;
	Py_ssize_t size, allocated, i;
	const char *type;

	if (!p || !PyList_Check(p))
	{
		printf("[*] Python list info\n");
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	list = (PyListObject *)p;
	size = list->ob_base.ob_size;
	allocated = list->allocated;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", allocated);
	fflush(stdout);

	for (i = 0; i < size; i++)
	{
		item = list->ob_item[i];
		type = item->ob_type->tp_name;
		printf("Element %ld: %s\n", i, type);
		fflush(stdout);
		if (PyBytes_Check(item))
			print_python_bytes(item);
		else if (PyFloat_Check(item))
			print_python_float(item);
	}
}

/**
 * print_python_bytes - prints basic info about Python bytes objects
 * @p: Python object
 *
 * Return: void
 */

void print_python_bytes(PyObject *p)
{
	PyBytesObject *byte = NULL;
	Py_ssize_t size, i, psize;

	if (!p || !PyBytes_Check(p))
	{
		printf("[.] bytes object info\n");
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	size = PyBytes_Size(p);

	byte = (PyBytesObject *)p;

	if (size >= 10)
		psize = 10;
	else
		psize = size + 1;

	printf("[.] bytes object info\n");
	printf("  size: %ld\n", size);
	fflush(stdout);
	printf("  trying string: ");
	for (i = 0; i < size; i++)
		printf("%c", byte->ob_sval[i]);
	printf("\n");
	fflush(stdout);
	printf("  first %ld bytes: ", psize);
	for (i = 0; i < psize; i++)
	{
		printf("%02x", byte->ob_sval[i] & 0xff);
		if (i != psize - 1)
			printf(" ");
	}
	printf("\n");
	fflush(stdout);
}

/**
 * print_python_float - prints basic info about Python float objects
 * @p: Python object
 *
 * Return: void
 */

void print_python_float(PyObject *p)
{
	PyFloatObject *float_obj = NULL;
	double value;

	if (!p || !PyFloat_Check(p))
	{
		printf("[.] float object info\n");
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	float_obj = (PyFloatObject *)p;
	value = float_obj->ob_fval;
	printf("[.] float object info\n");
	if (fmod(value, 1.0) == 0.0 && fabs(value) <= 10000000000000.0)
		printf("  value: %.1f\n", value);
	else if (fabs(value) >= 10000000000000.0)
		printf("  value: %.15e\n", value);
	else
		printf("  value: %.16g\n", value);
	fflush(stdout);
}
