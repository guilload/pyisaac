#include <Python.h>
#include <fcntl.h>
#include <string.h>
#include "rand.h"

#define RANDSIZB (RANDSIZ * sizeof(ub4))

static randctx rctx;

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

static char module_docstring[] = "";

static char randuint32_docstring[] =
    "Return a random integer in [0, 2**32 - 1].\n\n"
    ">>> pyisaac.randuint32()\n"
    "3297083183";

static char random_docstring[] =
    "Return a random float in [0, 1].\n\n"
    ">>> pyisaac.random()\n"
    "0.3417196273803711";

static char seed_docstring[] = "";

static PyObject *pyisaac_randuint32(PyObject *self)
{
    return Py_BuildValue("I", rand(&rctx));
}

static PyObject *pyisaac_random(PyObject *self)
{
    return Py_BuildValue("f", (rand(&rctx) % 0xFFFFFF80) / (float)0x100000000);  // 0xFFFFFF7F is the largest value that returns < 1.0 for this division
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

static PyMethodDef module_methods[] = {
    {"randuint32", (PyCFunction)pyisaac_randuint32, METH_NOARGS, randuint32_docstring},
    {"random", (PyCFunction)pyisaac_random, METH_NOARGS, random_docstring},
    {"seed", (PyCFunction)pyisaac_seed, METH_VARARGS, seed_docstring},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_pyisaac(void)
{
    PyObject *m = Py_InitModule3("_pyisaac", module_methods, module_docstring);
    if (m == NULL)
        return;

    PyModule_AddIntConstant(m, "RANDSIZB", RANDSIZB);
}
