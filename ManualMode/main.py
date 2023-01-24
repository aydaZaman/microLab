import serial
import time


arduino = serial.Serial('COM1', 9600, timeout=1)


def welcome():
    print("Hello welcome to manual mode of light and motor control")
    print("============================= Menu ==============================")
    print("1 - Brightness control")
    print("2 - motor control")

    choice = input(">")
    while (choice == "e"):
        if choice == 1:
            brightness_control()
        elif choice == 2:
            motor_control()
        else:
            print("invalid input")


def brightness_control():
    brightness = input("Enter value from 0 to 100:")


while True:
    with serial.Serial('COM1', 9600, timeout=1) as ser:

        print(line)

        if (line == "L"):
            data = input("Please enter the brightness of the light:")
        elif (line == "T"):
            data = input("Please enter the brightness of the light:")
        else:
            print("error")

        ser.write(data)

       # s = ser.read(2) #integer is 2 bytes
