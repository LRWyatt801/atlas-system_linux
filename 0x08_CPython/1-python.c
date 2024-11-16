#include "Python.h"
#include <stdio.h>

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

	if(PyList_Check(p))
	{
		list = (PyListObject *)p;
		allocated = list->allocated;

		printf("[*] Python list info\n");
		printf("[*] Size of the Python List = %ld\n", size);
		printf("[*] Allocated = %ld\n", allocated);

		for(i = 0; i < size; i++)
		{
			item = PyList_GetItem(p, i);
			type = item->ob_type->tp_name;
			printf("Element %ld: %s\n", i, type);
		}
	}
	return;
}
