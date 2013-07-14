// Created by Ryan Hatfield
// http://tophathacker.com
// tophathacker@gmail.com

#include <Python.h>
#include <wiringPi.h>
#include <time.h>

static int _get_range(int count);

// pin defines
int Trig = 4;
int Echo = 5;

static int setupRun = 0;

static PyObject* setup_pins(PyObject* self, PyObject* args)
{
  if(wiringPiSetup() == -1)
    exit(-1);

  //if(!PyArg_ParseTuple(args,"ii",&Trig,&Echo))
  //  exit(-1);

  pinMode(Trig, OUTPUT);
  digitalWrite(Trig,0);
  pinMode(Echo, INPUT);

  setupRun = 1;
  Py_RETURN_NONE;
}

static PyObject* get_range_average(PyObject *self, PyObject *args)
{
  int count;
  if(!PyArg_ParseTuple(args,"i",&count))
    return Py_BuildValue("i",-1);
  return Py_BuildValue("i",_get_range(count));
}

static PyObject* get_range(PyObject *self, PyObject *args)
{
  return Py_BuildValue("i",_get_range(1));
}

static int _get_range(int count)
{
  if(setupRun!=1)
    exit(-1);
  int average = 0;
  int j;
  for(j = 0; j < count; j++)
  {
    digitalWrite(Trig,0);
    delayMicroseconds(10);
    digitalWrite(Trig,1);
    delayMicroseconds(10);
    digitalWrite(Trig,0);

    int before = micros();
    int loopcount = 0;
    int timeout = 0;
    while(!digitalRead(Echo))
    {
      //do nothing
      if(loopcount > 1000 && micros() > before + 5000)
      {
        timeout = 1;
        break;
      }
      loopcount ++;
    }
    int start = micros();
    loopcount = 0;
    while(digitalRead(Echo))
    {
      //do nothing
      if(loopcount > 1000 && micros() > start + 5000)
      {
        timeout = 1;
        break;
      }
      loopcount ++;
    }
    if(timeout == 1)
      break;
    int range = micros() - start;
    while(micros() - before < 60)
      delayMicroseconds(1);
    average += range;
  }
  return average / count;
}

static PyMethodDef rangeFinderMethods[] =
{
  {"setup_pins",setup_pins,METH_VARARGS,"setup input/output pins"},
  {"get_range",get_range,METH_VARARGS,"return the range in an int32"},
  {"get_range_average",get_range_average,METH_VARARGS,"Return the range average"},
  {NULL, NULL, 0, NULL}
};
   
PyMODINIT_FUNC
    
initrangeFinder(void)
{
  (void) Py_InitModule("rangeFinder", rangeFinderMethods);
}
