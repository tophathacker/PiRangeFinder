// Created by Ryan Hatfield
// http://tophathacker.com
// tophathacker@gmail.com

#include <Python.h>
#include <wiringPi.h>
#include <time.h>

//define methods (not already defined by python.h)
static int _pauseMe(long unsigned int time);

// pin defines
int Trig = 4;
int Echo = 5;

static int setupRun = 0;

static PyObject* setup_pins(PyObject* self, PyObject* args)
{
  if(wiringPiSetup() == -1)
    exit(-1);

  if(!PyArg_ParseTuple(args,"ii",&Trig,&Echo))
    exit(-1);
    

  pinMode(Trig, OUTPUT);
  digitalWrite(Trig,0);
  pinMode(Echo, INPUT);

  setupRun = 1;
  Py_RETURN_NONE;
}

static PyObject* get_range(PyObject *self, PyObject *args)
{
  if(setupRun!=1)
    exit(-1);
  digitalWrite(Trig,0);
  delayMicroseconds(10);
  digitalWrite(Trig,1);
  delayMicroseconds(10);
  digitalWrite(Trig,0);

  while(!digitalRead(Echo))
  {
    //do nothing
  }
  int start = micros();
  while(digitalRead(Echo))
  {
    //do nothing
  }
  int range = micros() - start;
/*
  unsigned long top = 0;
  struct timeval  tv;
  int i;
  for(i = 0; i < 50; i++)
  {
    gettimeofday(&tv,NULL);
    unsigned long temp = tv.tv_usec;
    if(temp > top)
    {
      top = temp;
    }
  }
  int a,b;
  gettimeofday(&tv,NULL);
  a = tv.tv_usec;
  delayMicroseconds(10);
  gettimeofday(&tv,NULL);
  b = tv.tv_usec;
  if(b < a)
    b+=1000000;
  */
  return Py_BuildValue("l",range);
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
