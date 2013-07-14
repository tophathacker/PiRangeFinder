#!/usr/bin/python

import rangeFinder

print "before setup..."
rangeFinder.setup_pins()
print "after setup..."

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

print "and now for the get_range_average(1000) function (don't use this.. beta):"
print rangeFinder.get_range_average(1000)
