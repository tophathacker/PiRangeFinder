#!/usr/bin/python

import rangeFinder

rangeFinder.setup_pins()

total = 0
for x in range(0,1000):
  total += rangeFinder.get_range()
print total/1000
