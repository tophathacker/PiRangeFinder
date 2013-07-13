// Created by Ryan Hatfield
// http://tophathacker.com
// tophathacker@gmail.com

#include <Python.h>
#include <wiringPi.h>
#include <time.h>

//define methods (not already defined by python.h)
static int _pauseMe(long unsigned int time);

// pin defines
const int ClockPin = 0;
const int DataPin = 1;
const int DumpPin = 2;
const int inputX = 7;
const int inputY = 6;

static PyObject* setup_pins(PyObject* self, PyObject* args)
{
  if(wiringPiSetup() == -1)
    exit(1);

  Py_RETURN_NONE;
}

static int _pauseMe(long unsigned int time)
{
  int i;
  for(i=0; i<time; i++);
  return 0;
}

static PyObject* get_range(PyObject *self, PyObject *args)
{
  return Py_BuildValue("i",20);
}

static PyMethodDef rangeFinderMethods[] =
{
  {"setup_pins",setup_pins,METH_VARARGS,"setup input/output pins"},
  {"get_range",get_range,METH_VARARGS,"return the range in an int32"},
  {NULL, NULL, 0, NULL}
};
   
PyMODINIT_FUNC
    
initrangeFinder(void)
{
  (void) Py_InitModule("rangeFinder", rangeFinderMethods);
}
