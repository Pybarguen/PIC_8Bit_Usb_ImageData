

import serial


Serial_port = serial.Serial(port="COM6",baudrate=9600)
a = '$'.encode('utf_8')
Serial_port.write(a)  # write a string
while(True):

    val = Serial_port.readline()  # read complete line from serial output
    print(val)
    while not '\\n' in str(val):  # check if full data is received.

        # This loop is entered only if serial read value doesn't contain \n
        # which indicates end of a sentence.
        # str(val) - val is byte where string operation to check `\\n`
        # can't be performed

        temp = Serial_port.readline()  # check for serial output.
        if not not temp.decode():  # if temp is not empty.
            val = (val.decode() + temp.decode()).encode()
            # requrired to decode, sum, then encode because
            # long values might require multiple passes
    val = val.decode()  # decoding from bytes
    val = val.split()
    print(val)





                # stripping leading and trailing spaces.

