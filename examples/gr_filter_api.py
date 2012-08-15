import filtdes.filter_design
import sys

'''
API Blocking call 
returns filter taps for FIR filter design
returns b,a for IIR filter design
''' 
filtobj = filtdes.filter_design.launch(sys.argv)

# Displaying all filter paramters
print "Filter Count:", filtobj.get_filtercount()  
print "Filter type:", filtobj.get_restype()
print "Filter params", filtobj.get_params()
print "Filter Coefficients", filtobj.get_taps()
