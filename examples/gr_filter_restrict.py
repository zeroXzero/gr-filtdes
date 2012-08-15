import filtdes.filter_design
import sys

'''
Callback with restrict example
Function called when "design" button is pressed
or pole-zero plot is changed
'''
def print_params(filtobj):
    print "Filter Count:", filtobj.get_filtercount()
    print "Filter type:", filtobj.get_restype()
    print "Filter params", filtobj.get_params()
    print "Filter Coefficients", filtobj.get_taps()

filtdes.filter_design.launch(sys.argv, callback = print_params, restype = "iir")
