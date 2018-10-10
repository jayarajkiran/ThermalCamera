import serial
import serial.tools.list_ports
import numpy
import csv
import time
tempArrayTC = numpy.zeros(8)
portName = ""
readLine=""
ports = serial.tools.list_ports.comports()
init = 0
#Added a seach code for finding the COM ports with USB as the name could change each time the Rpi starts or cable is connected - Assuming only one serial USB connection
for port in ports:
	if "USB" in port.device:
		portName = port.device
#Init serial port
ser = serial.Serial(portName,9600)
while 1:
#Read the serial data sent from the Adruino
 readLine = ser.readline()
 index = readLine[1]
#Initilialise the writing only from the first thermocouple
 if index == '1':
  init = 1
  
 if init ==1:
  #print readLine  #-- Uncomment the print statement for knowing how the serial message is sent
  tempArrayTC[int(index)-1] = float(readLine[4:9])
  if index =='8':
   with open('TempMeasuresFromMUX.csv', 'a') as g:
    writer=csv.writer(g)
    now = time.strftime('%d-%m-%y %H:%M:%S')
    writer.writerow([now,tempArrayTC[0],tempArrayTC[1],tempArrayTC[2],tempArrayTC[3],tempArrayTC[4],tempArrayTC[5],tempArrayTC[6],tempArrayTC[7]])
    print tempArrayTC
    tempArrayTC = numpy.zeros(8)
