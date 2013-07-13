from distutils.core import setup, Extension

module1 = Extension('range',sources = ['rangeModule.c'],library_dirs=['../libs/wiringPi'],libraries=['wiringPi'])

setup ( name = 'rangeModule',
        version = '1.0',
        description = 'This is for getting a range value from an HC-SR04 ultrasonic range finder',
        ext_modules = [module1])
