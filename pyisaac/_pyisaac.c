#include <Python.h>
#include <fcntl.h>
#include <string.h>
#include "rand.h"
#include "numpy/arrayobject.h"

#define RANDSIZB (RANDSIZ * sizeof(ub4))

static randctx rctx;


static char randuint32_docstring[] =
    "Return a random integer in [0, 0xFFFFFFFF].\n\n"
    ">>> pyisaac.randuint32()\n"
    "3297083183";

static char random_docstring[] =
    "Return a random float in [0, 1].\n\n"
    ">>> pyisaac.random()\n"
    "0.3417196273803711";

static void seed(char *sd, int length);


static PyObject *pyisaac_np_rand(PyObject *self, *args)
{
    int i;
    PyArray_Descr *dtype = PyArray_DescrNewFromType(NPY_FLOAT64);
    PyArray_Dims shape = {NULL, 0};
    PyArrayObject *array = NULL;

    if (!PyArg_ParseTuple(args, "O&", PyArray_IntpConverter, &shape))
        return NULL;

    array = (PyArrayObject *)PyArray_Empty(shape.len, shape.ptr, dtype, 0);

    double *ptr = (double *) PyArray_DATA(array);
    for (i = 0; i < PyArray_SIZE(array); i++) {
        ptr[i] = rand(&rctx) / (double)0xFFFFFFFF;
    }

    return (PyObject *) array;
}

static PyObject *pyisaac_random(PyObject *self)
{
    return PyFloat_FromDouble(rand(&rctx) / (double)0xFFFFFFFF);
}

static PyObject *pyisaac_randuint32(PyObject *self)
{
    return Py_BuildValue("I", rand(&rctx));
}

static PyObject *pyisaac_seed(PyObject *self, PyObject *args)
{
    const char *sd;
    int length;

    if (!PyArg_ParseTuple(args, "s#", &sd, &length))
        return NULL;

    seed(sd, length);

    Py_RETURN_NONE;
}

static void seed(char *sd, int length)
{
    int i, q, r;  // q = quotient, r = remainder

    q = RANDSIZB / length;
    r = RANDSIZB % length;

    for (i = 0; i < q; i++)
        memcpy((char *)rctx.randrsl + i * length, sd, length);

    if (r)
        memcpy((char *)rctx.randrsl + q * length, sd, r);

    randinit(&rctx, TRUE);
    isaac(&rctx);
}

static PyMethodDef module_methods[] = {
    {"np_rand", (PyCFunction)pyisaac_np_rand, METH_VARARGS, ""},
    {"random", (PyCFunction)pyisaac_random, METH_NOARGS, random_docstring},
    {"randuint32", (PyCFunction)pyisaac_randuint32, METH_NOARGS, randuint32_docstring},
    {"seed", (PyCFunction)pyisaac_seed, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_pyisaac(void)
{
    PyObject *m = Py_InitModule3("_pyisaac", module_methods, "");
    if (m == NULL)
        return;

    import_array();

    PyModule_AddIntConstant(m, "RANDSIZB", RANDSIZB);
}
