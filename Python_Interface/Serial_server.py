import serial
import time

class Serial_data():
    def __init__(self, Port):
        self.Serial_port = serial.Serial(port=Port,
                                         baudrate=230400,
                                         timeout=0)
    def Get_serial_data(self):
        try:  # runs this loop forever

            val = self.Serial_port.readline()  # read complete line from serial output
            while not '\\n' in str(val):  # check if full data is received.
                # This loop is entered only if serial read value doesn't contain \n
                # which indicates end of a sentence.
                # str(val) - val is byte where string operation to check `\\n`
                # can't be performed

                temp = self.Serial_port.readline()  # check for serial output.
                if not not temp.decode():  # if temp is not empty.
                    val = (val.decode() + temp.decode()).encode()
                    # requrired to decode, sum, then encode because
                    # long values might require multiple passes
            val = val.decode()  # decoding from bytes
            val = val.split()

            return val
            # stripping leading and trailing spaces.

        except:
            return None
