import filtdes.filter_design
import sys

'''
API Blocking call 
returns filter taps for FIR filter design
returns b,a for IIR filter design
''' 
filtobj = filtdes.filter_design.launch(sys.argv)

# Displaying all filter paramters
print "Filter Count:", filtobj.filtercount
print "Filter type:", filtobj.restype
print "Filter params", filtobj.params[0]
print "Filter Coefficients", filtobj.taps[0]
