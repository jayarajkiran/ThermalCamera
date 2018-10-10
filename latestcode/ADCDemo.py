#!/usr/bin/env python
"""
================================================
ABElectronics ADC Pi 8-Channel ADC demo
Requires python smbus to be installed
run with: python demo_readvoltage.py
================================================
Initialise the ADC device using the default addresses and sample rate,
change this value if you have changed the address selection jumpers
Sample rate can be 12,14, 16 or 18
"""

from __future__ import absolute_import, division, print_function, \
                                                    unicode_literals
import time
import os
import csv
global writer,temp
temp=[]
volt1 = 0
volt2 = 0
volt3 = 0
try:
    from ADCPi import ADCPi
except ImportError:
    print("Failed to import ADCPi from python system path")
    print("Importing from parent folder instead")
    try:
        import sys
        sys.path.append('..')
        from ADCPi import ADCPi
    except ImportError:
        raise ImportError(
            "Failed to import library from parent folder")


def main():
    
    '''
    Main program function
    '''

    adc = ADCPi(0x68, 0x69, 12)
##    with open('TempReadingTC.csv', 'wb') as g:
##        writer2 = csv.writer(g)
##        writer2.writerow('temp')
    while True:

        # clear the console
	os.system('clear')
	temp=[]
        # read from adc channels and print to screen
        volt1 = adc.read_voltage(1)
        temp.append((volt1-1.2354)/0.0051)
	print (volt1)
        print("Channel 1(Reference Radiator) Temperature: %02f" % temp[0])

	volt2 = adc.read_voltage(2)
        temp.append((volt2-1.2354)/0.0051)
	print (volt2)
        print("Channel 2(TC 1 - 51273) Temperature: %02f" % temp[1])
        
        volt3 = adc.read_voltage(3)
        temp.append((volt3-1.2354)/0.0051)
	print (volt3)
        print("Channel 3(TC 2 - 6087) Temperature: %02f" % temp[2])

        volt4 = adc.read_voltage(4)
        temp.append((volt4-1.2354)/0.0051)
	print (volt4)
        print("Channel 3(TC 3 - 47723) Temperature: %02f" % temp[3])

        volt5 = adc.read_voltage(5)
        temp.append((volt5-1.2354)/0.0051)
	print (volt5)
        print("Channel 3(4TC 4 - 40114) Temperature: %02f" % temp[4])
##        print("Channel 1: %02f" % adc.read_voltage(1))
##        print("Channel 2: %02f" % adc.read_voltage(2))
##        print("Channel 3: %02f" % adc.read_voltage(3))
##        print("Channel 4: %02f" % adc.read_voltage(4))
##        print("Channel 5: %02f" % adc.read_voltage(5))
##        print("Channel 6: %02f" % adc.read_voltage(6))
##        print("Channel 7: %02f" % adc.read_voltage(7))
##        print("Channel 8: %02f" % adc.read_voltage(8))

        # wait 0.2 seconds before reading the pins again        
        with open('TempReadingTC5.csv', 'a') as g:
		writer=csv.writer(g)
	#	for val in temp:
		now = time.strftime('%d-%m-%y %H:%M:%S')
		#g.write(str(temp))
		#g.write(",")
		writer.writerow([now,temp[0],temp[1],temp[2],temp[3],temp[4]])
        time.sleep(1)
#	temp = []

if __name__ == "__main__":
    main()
