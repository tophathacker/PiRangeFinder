#!/usr/bin/python

import rangeFinder

rangeFinder.setup_pins()

total = 0
bad = 0
for x in range(0,1000):
  temp = rangeFinder.get_range()
  if(temp != -1):
    total += temp
  else:
    bad += 1 
print "average range over 1000 tries:"
print total/1000
print "bad reads"
print bad
