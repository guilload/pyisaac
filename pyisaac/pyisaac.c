#include <Python.h>
#include <fcntl.h>
#include <string.h>
#include "rand.h"

#define RANDSIZB (RANDSIZ * sizeof(ub4))

static randctx rctx;

static void devrandom(char *buffer, int size);

static void seed(char *sd, int length);


static char module_docstring[] =
    "a Python wrapper of the C implementation of ISAAC, "
    "a cryptographically secure pseudo random number generator (CSPRNG) "
    "designed and implemented in 1996 by Bob Jenkins.";
    
static char random_docstring[] =
    "Generate a random integer.\n\n"
    ">>> pyisaac.random()\n"
    "3824542492";

static char seed_docstring[] =
    "Seed the CSPRNG.\n\n"
    ">>> pyisaac.seed('pyisaac')\n"
    ">>> pyisaac.random()\n"
    "990096228";

static PyObject *pyisaac_random(PyObject *self);

static PyObject *pyisaac_seed(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"random", pyisaac_random, METH_NOARGS, random_docstring},
    {"seed", pyisaac_seed, METH_VARARGS, seed_docstring},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initpyisaac(void)
{
    char sd[RANDSIZB];

    PyObject *m = Py_InitModule3("pyisaac", module_methods, module_docstring);
    if (m == NULL)
        return;

    devrandom(sd, RANDSIZB);
    seed(sd, RANDSIZB);
}

static PyObject *pyisaac_random(PyObject *self)
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

static void devrandom(char *buffer, int size)
{
    int fd;
    ssize_t n;
    
    assert (0 < size);

    fd = open("/dev/random", O_RDONLY);
    if (fd < 0)
        Py_FatalError("Failed to open /dev/random");

    while (0 < size)
    {
        do {
            n = read(fd, buffer, (size_t)size);
        } while (n < 0 && errno == EINTR);

        if (n <= 0)
        {
            /* stop on error or if read(size) returned 0 */
            Py_FatalError("Failed to read bytes from /dev/random");
            break;
        }

        buffer += size;
        size -= n;
    }
    close(fd);
}

static void seed(char *sd, int length)
{
    int i, q, r;  // q = quotient, r = remainder

    q = (RANDSIZB) / length;
    r = (RANDSIZB) % length;

    for (i = 0; i < q; i++)
        memcpy((char *)rctx.randrsl + i * length, sd, length);

    if (r)
        memcpy((char *)rctx.randrsl + q * length, sd, r);

    randinit(&rctx, TRUE);
}
