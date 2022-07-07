#include <Python.h>
#include "spellcheck.h"

static PyObject* raise_exception(PyObject* excType, const char* psz) {
    PyErr_SetString(excType, psz);
    return NULL;

}

static PyObject* distance(PyObject* self, PyObject* args) {
    char* w1 = NULL, *w2 = NULL;
    if (!PyArg_ParseTuple(args, "ss", &w1, &w2))
        return raise_exception(PyExc_ValueError, "Invalid parameter.");
    const int d = word_distance(w1, w2);
    if (d < 0)
        return raise_exception(PyExc_ValueError, "Invalid parameter.");

    return PyLong_FromLong(d);
}

static PyObject* spell_check(PyObject* self, PyObject* args) {
    char* psz;

    if (!PyArg_ParseTuple(args, "s", &psz))
        return raise_exception(PyExc_ValueError, "Invalid parameter.");

    char matches[MAX_MATCHES][MAX_WORD_LENGTH];
    const int counter = find_matches(psz, matches);

    PyObject* list = PyList_New(counter);
    if (!list) return NULL;

    for (int i = 0; i < counter; ++i) {
        PyObject* item = PyBytes_FromString(matches[i]);
        if (!item)
            goto error;
        if (PyList_SetItem(list, i, item) != 0) {
            Py_DECREF(item);
            goto error;
        }
    }
    return list;

error:
    Py_DECREF(list);
    return NULL;
}



static PyObject* set_words_dictionary(PyObject* self, PyObject* args) {
    char* psz = NULL;
    if (!PyArg_ParseTuple(args, "s", &psz))
        return raise_exception(PyExc_ValueError, "Invalid parameter.");
    const int i = set_dict(psz);
    return PyLong_FromLong(i);
}

static PyMethodDef myMethods[] = {
    { "distance", distance, METH_VARARGS, "Returns the distance of the passed in words."},
    { "spell_check", spell_check, METH_VARARGS, "Returns the matching words for the passed in string."},
    { "set_words_dictionary", set_words_dictionary, METH_VARARGS, "Sets the words dictionary to use."},
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef wdistmodule = {
    PyModuleDef_HEAD_INIT,
    "wdistModule",
    "Wist Module",
    -1,
    myMethods
};

PyMODINIT_FUNC PyInit_wdistModule(void) {
    return PyModule_Create(&wdistmodule);
}
