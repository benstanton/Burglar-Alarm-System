import serial
import time

ard = serial.Serial('COM5', 9600)
print("test")

while True:
    inChar = ard.read().decode('utf-8')
    print(inChar)
    time.sleep(.1)

    if inChar == 'F':
        out = 'f'
        ard.write(out.encode())
        print(out)
    
    if inChar == 'R':
        out = 'r'
        ard.write(out.encode())
        print(out)
        time.sleep(5)
        out = 'a'
        ard.write(out.encode())
        print(out)

    if inChar == 'T':
        out = 't'
        ard.write(out.encode())
        print(out)

    