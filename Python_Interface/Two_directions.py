import serial
from image import *
import time


Serial_port = serial.Serial(port="COM6",baudrate=9600, timeout=1, write_timeout=2)


"""
     Funcion Name : Write_animacion_data():
     
     Description : La función envía los datos por el puerto Serial emulado
                  a través del USB del PIC18F4550. El ciclo for con la variable
                  en 2 bloques de 1 byte cada uno; se debe hacer el proceso
                  dos veces para enviar un color correcto.
     

     Returns None 

"""
def Write_animacion_data():
    while (True):
        for i in range(0, len(Image_data)):#Hay 4 imagenes en el codigo de prueba
            Buffer_Data = []
            x = []
            """Los datos se envian en bloques de 64bytes
            por el puerto USB del PIC"""
            n = 0
            m = 64
            for j in range(0, len(Image_data[i])):#Para cada imagen de la matrix se extrae los datos
                decimal = Image_data[i][j]
                """Se separan los bytes del color al ser de 16bit
                se saca la parte alta y la parte baja """
                high_byte = (decimal >> 8)
                low_byte = (decimal & 255)
                #Se agregan los datos al buffer
                Buffer_Data.append(high_byte)
                Buffer_Data.append(low_byte)

        #Se envia los datos por el puerto Serial.
            for k in range(0, 184):
                x = Buffer_Data[n:m]
                Serial_port.write(x)  # write a string
                n = n + 64
                m = m + 64

def Write_image_data():
    Buffer_Data = []
    x = []
    """Los datos se envian en bloques de 64bytes
    por el puerto USB del PIC"""
    n = 0
    m = 64
    for j in range(0, len(Image_data[0])):  # Para cada imagen de la matrix se extrae los datos
        decimal = Image_data[0][j]
        """Se separan los bytes del color al ser de 16bit
        se saca la parte alta y la parte baja """
        high_byte = (decimal >> 8)
        low_byte = (decimal & 255)
        # Se agregan los datos al buffer
        Buffer_Data.append(high_byte)
        Buffer_Data.append(low_byte)

    for k in range(0, 184):
        x = Buffer_Data[n:m]
        Serial_port.write(x)  # write a string
        n = n + 64
        m = m + 64

a = 'pig'.encode('utf_8')#Put Image Command
Serial_port.write(a)  # write a string with the Put Command
val = Serial_port.readline()  # read complete line from serial output
val = val.decode()
val = val.split()

if(val[0]=="Ok"):#If the Microcontroller sent Ok Make the function
    Write_image_data()


