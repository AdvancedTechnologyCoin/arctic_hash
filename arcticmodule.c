#include <Python.h>

#include "arctic.h"

static PyObject *arctic_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    arctic_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    arctic_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef ArcticMethods[] = {
    { "getPoWHash", arctic_getpowhash, METH_VARARGS, "Returns the proof of work hash using arctic hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef ArcticModule = {
    PyModuleDef_HEAD_INIT,
    "arctic_hash",
    "...",
    -1,
    ArcticMethods
};

PyMODINIT_FUNC PyInit_arctic_hash(void) {
    return PyModule_Create(&ArcticModule);
}

#else

PyMODINIT_FUNC initarctic_hash(void) {
    (void) Py_InitModule("arctic_hash", ArcticMethods);
}
#endif
