import filtdes.gr_filter_design
import sys

'''
Callback example
Function called when "design" button is pressed
or pole-zero plot is changed
print filter taps for FIR filter design
print  b,a for IIR filter design
'''
def print_taps(retval):
    print retval

filtdes.gr_filter_design.launch(sys.argv, print_taps)
