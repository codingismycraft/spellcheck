#include <Python.h>

#include "wdist.h"


static PyObject* raise_exception(PyObject* excType, const char* psz){
    PyErr_SetString(excType, psz);
    return NULL;

}

static PyObject* distance(PyObject* self, PyObject* args)
{
    char* w1 = NULL;
    char* w2 = NULL;

    if(!PyArg_ParseTuple(args, "ss", &w1, &w2)) {
        return NULL;
    }

    int d = word_distance(w1, w2);
    return PyLong_FromLong(d);

}


// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef myMethods[] = {
    { "distance", distance, METH_VARARGS, "Returns words distance." },
    { NULL, NULL, 0, NULL }
};

// Our Module Definition struct
static struct PyModuleDef wdistmodule= {
    PyModuleDef_HEAD_INIT,
    "wdistModule",
    "Wist Module",
    -1,
    myMethods
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_wdistModule(void)
{
    return PyModule_Create(&wdistmodule);
}
