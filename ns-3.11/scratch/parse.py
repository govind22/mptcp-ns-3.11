#!/usr/bin/env python
from pylab import *
import numpy
import string

if len(sys.argv) < 3:
  print sys.argv[0], "<file name> <filter>"
  exit()
 
fname = str(sys.argv[1])
fltr = str(sys.argv[2])
bincount = 10000
cdfthresh = 10
dropthresh = 10000

times = [float(line.split()[11]) for line in open(fname,"r") if line.startswith(fltr)]
ctimes = [time for time in times if time < dropthresh]
dtimes = [time for time in times if time >= dropthresh]
hist, bins = numpy.histogram(ctimes, bincount, range=(0, cdfthresh))
cumhist = [x*100.0/len(times) for x in  hist.cumsum()]

stats="----------------------------------------- \n"
stats+="# Total flows     = " + str(len(times)) + "\n"
stats+="# Completed flows = " + str(len(ctimes)) + "\n"
stats+="# Dropped flows   = " + str(len(dtimes)) + "\n"
stats+="----------------------------------------- \n"
stats+="For completed flows" + "\n"
stats+="Min     = " + str(min(ctimes)) + "\n"
stats+="Max     = " + str(max(ctimes)) + "\n"
stats+="Mean    = " + str(numpy.average(ctimes)) + "\n"
stats+="Median  = " + str(numpy.median(ctimes)) + "\n"
stats+="StdDev  = " + str(numpy.std(ctimes)) + "\n"
stats+="----------------------------------------- \n"

print stats

cdf_fname = fname + "." + fltr.lower() + ".cdf"
stat_fname = fname + "." + fltr.lower() + ".stat"

cdf_file = open(cdf_fname, "w")
for i in range(len(hist)):
   cdf_file.write ("" + str(bins[i+1]) + "\t" + str(cumhist[i]) + "\n")
cdf_file.close()

stat_file = open(stat_fname, "w")
stat_file.write(stats)
stat_file.close()

xlabel("Flow completion time (ms)")
ylabel("CDF (%)")
grid(True)
plot (bins.take(range(1,bins.size)), cumhist)
show()




  
