#!/usr/bin/env python
from pylab import *
import numpy
import string

if len(sys.argv) < 3:
  print sys.argv[0], "<file name> <filter>"
  exit()
 
fname = str(sys.argv[1])
fltr = str(sys.argv[2])
bincount = 1000

times = [float(line.split()[11]) for line in open(fname,"r") if line.startswith(fltr)]
hist, bins = numpy.histogram(times, bincount)
cumhist = [x*100/sum(hist) for x in  hist.cumsum()]

cdf_fname = fname + "." + fltr.lower() + ".cdf"
stat_fname = fname + "." + fltr.lower() + ".stat"

cdf_file = open(cdf_fname, "w")
for i in range(len(hist)):
   cdf_file.write ("" + str(bins[i+1]) + "\t" + str(cumhist[i]) + "\n")
cdf_file.close()

stat_file = open(stat_fname, "w")
stat_file.write("Samples = " + str(len(times)) + "\n")
stat_file.write("Min     = " + str(min(times)) + "\n")
stat_file.write("Max     = " + str(max(times)) + "\n")
stat_file.write("Mean    = " + str(numpy.average(times)) + "\n")
stat_file.write("Median  = " + str(numpy.median(times)) + "\n")
stat_file.write("StdDev  = " + str(numpy.std(times)) + "\n")

xlabel("Flow completion time (ms)")
ylabel("CDF (%)")
grid(True)
plot (bins.take(range(1,bins.size)), cumhist)
show()




  
