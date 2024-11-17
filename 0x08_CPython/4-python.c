#include "Python.h"
#include <stdio.h>

/**
 * print_python_string - prints some basic info about Python strings
 * @p: PyObject
 *
 * Return: void
 */

void print_python_string(PyObject *p)
{
	PyUnicodeObject *unicode = NULL;
	Py_ssize_t length;
	const char *type;

	if (!PyUnicode_Check(p))
	{
		printf("[.] string object info\n");
		printf("  [ERROR] Invalid String Object\n");
		return;
	}

	unicode = (PyUnicodeObject *)p;
	length = PyUnicode_GET_LENGTH(unicode);
	if (PyUnicode_IS_COMPACT_ASCII(unicode))
		type = "compact ascii";
	else if (PyUnicode_IS_COMPACT(unicode))
		type = "compact unicode object";
	else
		type = "unicode object";

	printf("[.] string object info\n");
	printf("  type: %s\n", type);
	printf("  length: %ld\n", length);
	printf("  value: %s\n", PyUnicode_AsUTF8(p));
}