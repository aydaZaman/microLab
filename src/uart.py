# arduino_uart.py

import serial
import time

while True:
    with serial.Serial('COM1', 9600, timeout=1) as ser:
      
      #  time.sleep(2)   # wait 0.5 seconds
        line=ser.readline()
        
        print(line)
        
        if(line=="L"):
            data=input("Please enter the brightness of the light:")
        elif(line=="T")
            data=input("Please enter the brightness of the light:")
        else
            print("error")
      
        ser.write(data) 
      
       # s = ser.read(2) #integer is 2 bytes 
      