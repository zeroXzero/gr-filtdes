import filtdes.filter_design
import sys

'''
Callback with restrict example
Function called when "design" button is pressed
or pole-zero plot is changed
'''
def print_params(filtobj):
    print "Filter Count:", filtobj.filtercount
    print "Filter type:", filtobj.restype
    print "Filter params", filtobj.params[0]
    print "Filter Coefficients", filtobj.taps[0]

filtdes.filter_design.launch(sys.argv, callback = print_params, restype = "fir")
