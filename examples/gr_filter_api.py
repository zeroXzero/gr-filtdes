import filtdes.gr_filter_design
import sys

'''
API Blocking call 
returns filter taps for FIR filter design
returns b,a for IIR filter design
''' 
taps=filtdes.gr_filter_design.launch(sys.argv)
print taps
