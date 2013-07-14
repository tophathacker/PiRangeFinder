#!/usr/bin/python

import rangeFinder

for x in range(0,10000000):
  temp = rangeFinder.get_range()
  if temp > 2000:
    print temp
