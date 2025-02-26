import serial
from image import *
import time


Serial_port = serial.Serial(port="COM6",baudrate=9600, timeout=1, write_timeout=2)
# a = 'pig'.encode('utf_8')
#
# Serial_port.write(a)  # write a string
# val = Serial_port.readline()  # read complete line from serial output
# val = val.decode()
# val = val.split()
# print(len(img1), "imagen len")
# test_matrix_color = ['0x4a69']*4096
# Buffer_Data = []
#
#
#
#
#
#
# for i in range(0, len(img1)):
#     decimal = img1[i]
#     high_byte = (decimal>>8)
#     low_byte = (decimal & 255)
#     Buffer_Data.append(high_byte)
#     Buffer_Data.append(low_byte)
#
# x = Buffer_Data[0:63]
# print(x)
#
# print(val)
# if(val[0]=="Ok"):
#     val[0] = "WW"
#     n = 0
#     m = 64
#     for j in range(0, 194):
#         x = Buffer_Data[n:m]
#         Serial_port.write(x)  # write a string
#         n = n+64
#         m = m+64
#
# print("que pasa")
# a = 'cr'.encode('utf_8')
# Serial_port.write(a)  # write a string
# print("funciona")
# a = 'pig'.encode('utf_8')
# Serial_port.write(a)  # write a string
# val = Serial_port.readline()  # read complete line from serial output
# val = val.decode()
# val = val.split()
# print(val, "ultimo valor")
#
#
#
# Buffer_Data = []
# for i in range(0, len(img2)):
#     decimal = img2[i]
#     high_byte = (decimal>>8)
#     low_byte = (decimal & 255)
#     Buffer_Data.append(high_byte)
#     Buffer_Data.append(low_byte)
#
#
# if(val[0]=="Ok"):
#     val[0] = "WW"
#     n = 0
#     m = 64
#     print("Cumple")
#     for j in range(0, 194):
#         # while(val[0]!="OO"):
#         #Serial_port.write(bytes([Buffer_Data[i]]))  # write a string
#         x = Buffer_Data[n:m]
#         Serial_port.write(x)  # write a string
#         n = n+64
#         m = m+64
#
# x = Buffer_Data[0:63]
# print("Termino")
t = 0
while(True):
    for i in range(0, len(Image_data)):
        Buffer_Data = []
        x = []
        a = 'pig'.encode('utf_8')
        Serial_port.write(a)  # write a string
        val = Serial_port.readline()  # read complete line from serial output
        val = val.decode()
        val = val.split()
        for j in range(0, len(Image_data[i])):

            decimal = Image_data[i][j]
            high_byte = (decimal >> 8)
            low_byte = (decimal & 255)
            Buffer_Data.append(high_byte)
            Buffer_Data.append(low_byte)
        print(val)
        c = 1
        if (c==1):
#            val[0] = "WW"
            n = 0
            m = 64
            print("Cumple")
            for k in range(0, 184):
                print(" que pasa esto es {} esto es {}".format(i, k))
                x = Buffer_Data[n:m]
                Serial_port.write(x)  # write a string
                n = n + 64
                m = m + 64
                t = t+1
                print(t, "soy t")
        a = 'cr'.encode('utf_8')
        Serial_port.write(a)  # write a string
        print("funciona")

# while(True):
#
#     val = Serial_port.readline()  # read complete line from serial output
#     print(val)
#     while not '\\n' in str(val):  # check if full data is received.
#
#         # This loop is entered only if serial read value doesn't contain \n
#         # which indicates end of a sentence.
#         # str(val) - val is byte where string operation to check `\\n`
#         # can't be performed
#
#         temp = Serial_port.readline()  # check for serial output.
#         if not not temp.decode():  # if temp is not empty.
#             val = (val.decode() + temp.decode()).encode()
#             # requrired to decode, sum, then encode because
#             # long values might require multiple passes
#     val = val.decode()  # decoding from bytes
#     val = val.split()
#     print(val)





                # stripping leading and trailing spaces.

