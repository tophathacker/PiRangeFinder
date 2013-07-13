from distutils.core import setup, Extension

module1 = Extension('rangeFinder',sources = ['rangeFinderModule.c'],library_dirs=['../libs/wiringPi'],libraries=['wiringPi'])

setup ( name = 'rangeFinderModule',
        version = '1.0',
        description = 'This is for getting a range value from an HC-SR04 ultrasonic range finder',
        ext_modules = [module1])
