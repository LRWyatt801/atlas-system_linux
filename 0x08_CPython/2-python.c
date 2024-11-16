#include "Python.h"
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

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

	size = PyList_Size(p);

	if (PyList_Check(p))
	{
		list = (PyListObject *)p;
		allocated = list->allocated;

		printf("[*] Python list info\n");
		printf("[*] Size of the Python List = %ld\n", size);
		printf("[*] Allocated = %ld\n", allocated);

		for (i = 0; i < size; i++)
		{
			item = list->ob_item[i];
			type = item->ob_type->tp_name;
			printf("Element %ld: %s\n", i, type);
			if (PyBytes_Check(item))
				print_python_bytes(item);
		}
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
	printf("  trying string: %s\n", PyBytes_AsString(p));
	printf("  first %ld bytes: ", psize);
	for (i = 0; i < psize; i++)
	{
		printf("%02x", byte->ob_sval[i] & 0xff);
		if (i != psize - 1)
			printf(" ");
	}
	printf("\n");
}

