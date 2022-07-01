#include <Python.h>
#include "wdist.h"

static PyObject* raise_exception(PyObject* excType, const char* psz){
    PyErr_SetString(excType, psz);
    return NULL;

}

static PyObject* distance(PyObject* self, PyObject* args) {
    char* w1 = NULL, *w2=NULL;
    if(!PyArg_ParseTuple(args, "ss", &w1, &w2))
        return raise_exception(PyExc_ValueError, "Invalid argumenets.");
    const int d = word_distance(w1, w2);
    if (d < 0)
        return raise_exception(PyExc_ValueError, "Invalid argumenets.");

    return PyLong_FromLong(d);
}

static PyMethodDef myMethods[] = {
    { "distance", distance, METH_VARARGS, "Returns the distance of two words." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef wdistmodule= {
    PyModuleDef_HEAD_INIT,
    "wdistModule",
    "Wist Module",
    -1,
    myMethods
};

PyMODINIT_FUNC PyInit_wdistModule(void)
{
    return PyModule_Create(&wdistmodule);
}
