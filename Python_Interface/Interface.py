import sys
import PyQt5
import serial
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtCore import QTimer
from PIL import Image
from Serial_server import *
import numpy as np
import threading


from Desing import *


class Program(QtWidgets.QMainWindow):
    def __init__(self, parent=None):



        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)


        #Variable para conseguir y enviar los datos por el puerto Serial
        self.Serial_data = None
        self.Serial_state = None
        self.data = None

        #Array para guardar las diferentes imagenes.
        self.images = []

        self.Image_matrix = []

        # Temporizador para obtener los datos del puerto Serial
        #self.tiempo2 = QTimer()
        #self.tiempo2.setInterval(1)
        #self.tiempo2.timeout.connect(self.Get_Data)
        #___________________________________________________

        self.thread_control = None
        self.Run_thread = False

        """
        Configuracion de los WidGets ComboBox
        
        """
        ports = ["COM1", "COM2", "COM3", "COM4", "COM5", "COM5", "COM6", "COM7"]

        self.ui.ComboBox_Port.addItems(ports)

        baudrates = [
            "9600",
            "19200",
            "38400",
            "57600",
            "115200",
            "230400",
            "460800"
        ]

        self.ui.ComboBox_BaudRate.addItems(baudrates)

        """
                   ______________________________________________________________

                   """





        """
        Configuraciones de los botones con sus respectivas funciones 
        
        """



        #Connect Import Image Button With the respective Funtion
        self.ui.Import_Image_button.clicked.connect(self.Import_Images)

        #Connect Serial button with the function to connect with the hardware
        self.ui.Connect_Serial.clicked.connect(
            lambda: self.Connect_Serial(
                self.ui.ComboBox_Port.currentText(),
                self.ui.ComboBox_BaudRate.currentText()
            )


        )

        #Button to send test Serial Data
        self.ui.Send_Test_Button.clicked.connect(self.Send_test_data)

    """
            ______________________________________________________________

            """

    """
    Funcion para importar imagenes, se utiliza el metodo 
    filenames, _ = QFileDialog.getOpenFileNames(
            self
    Filesnames es una lista que contiene cada imagen en el 
    orden que se selecciono en la carpeta

    """

    def Import_Images(self):
        filenames, _ = QFileDialog.getOpenFileNames(
            self,
            "Select Files",
            r"C:/images/",
            "Images (*.png *.jpg)")
        if filenames:
            for i in range(0, len(filenames)):
                self.images.append(QPixmap(filenames[i]))
            label_mapping = {
                0: self.ui.Image1_Label,
                1: self.ui.Image2_Label,
                2: self.ui.Image3_Label,
                3: self.ui.Image4_Label,
                4: self.ui.Image5_Label,
                5: self.ui.Image6_Label,
            }
            for idx, image in enumerate(self.images):
                if idx in label_mapping:
                    label_mapping[idx].setPixmap(image)
                    label_mapping[idx].setScaledContents(True)
            """
            mi_image = QPixmap(filenames[0])
            self.ui.Image1_Label.setScaledContents(True)
            self.ui.Image1_Label.setPixmap(mi_image)
            image = Image.open(filenames[0])
            pixeles = np.array(image)
            self.Pixel_Converter(pixeles)
            
            """
            print(len(self.images))

    """
              Fin funcion importar imagenes

              """




    """
        Funcion para convertir los pixeles de color en formato de 16bits
        aun se pueden observar perdidas de color en la conversion
        la funcion guarda los valores de 16bits por pixel en la matrix
        Image_matrix, el codigo aun se encuentra en pruebas.

        """

    def Pixel_Converter(self, Pixels):
        alto, ancho, _ = Pixels.shape
        print(alto)
        print(ancho)
        for j in range(0, ancho):
            for i in range(0, alto):
                Red = int(Pixels[i, j, 0])
                Green = int(Pixels[i, j, 1])
                Blue = int(Pixels[i, j, 2])
                r_5_bits = (Red >> 3) & 0x1F
                g_6_bits = (Green >> 2) & 0x3F
                b_5_bits = (Blue >> 3) & 0x1F

               # print(Red, Green, Blue)
              #  print("Red {} Green {}  Blue {}".format(r_5_bits, g_6_bits, b_5_bits))
              #  print("Red {} Green {}  Blue {}".format(bin(r_5_bits), bin(g_6_bits), bin(b_5_bits)))
                Final_value = (r_5_bits << 11) | (g_6_bits << 5) | b_5_bits
                self.Image_matrix.append(Final_value)
      #  print(self.Image_matrix)
        print("Imagen Procesada")

    """
                Fin del metodo conversion de pixeles

                """


    """
           Funcion para conectar el puerto Serial
           Funciona hasta el momento con un baudrate bajo de 9600baudios
           se debe comprobar el condigo del PIC para aumentar la velocidad
           
           Parametros :
           
                    Port : Puerto COM# 
                    baudrate : Velocidad en baudios

           """

    def Connect_Serial(self, port, baudrate):
        #print("Puerto {}   Baudrate {}".format(port, baudrate))
        self.Serial_data = Serial_data(port, baudrate)
        Port_State, self.Serial_state = self.Serial_data.Connect_Port()
        self.ui.Serial_Informmation.setText("Port {},  {}".format(port, Port_State))
        if(self.Serial_state):
            self.Run_thread = True
            self.thread_control = threading.Thread(target=self.Thread_data_control)
            self.thread_control.start()

    def Thread_data_control(self):
        while(self.Run_thread):
            self.data = self.Serial_data.Get_serial_data()
            print(self.data[0])
            if(self.data[0]=='Ok'):
                self.Send_image()
                self.Run_thread = False


    """
            Fin de metodo conectar serial.
            """

    def Send_image(self):
        Buffer_Data = []
        n = 0
        m = 64
        for j in range(0, len(self.Image_matrix)):
            decimal = (self.Image_matrix[j])
            print(decimal)
            print(type(decimal))
            # Se separan los bytes del color al ser de 16bit
            # se saca la parte alta y la parte baja
            high_byte = (decimal >> 8)
            low_byte = (decimal & 255)

            # Se agregan los datos al buffer
            Buffer_Data.append(high_byte)
            Buffer_Data.append(low_byte)

        for k in range(0, 184):
            x = Buffer_Data[n:m]
            self.Serial_data.Serial_port.write(x)
            n = n + 64
            m = m + 64


    def Send_test_data(self):
        a = 'pig'.encode('utf_8')
        if (self.Serial_state):
            self.Serial_data.Serial_port.write(a)
        # Put Image Command
        """
        Buffer_Data = []
        n = 0
        m = 64
        for j in range(0, len(self.Image_matrix)):
            decimal = self.Image_matrix[j]
            #Se separan los bytes del color al ser de 16bit
                 #se saca la parte alta y la parte baja
            high_byte = (decimal >> 8)
            low_byte = (decimal & 255)

            # Se agregan los datos al buffer
            Buffer_Data.append(high_byte)
            Buffer_Data.append(low_byte)

        for k in range(0, 184):
            x = Buffer_Data[n:m]
            self.Serial_data.Serial_port.write(x)
            n = n + 64
            m = m + 64
            print(k)
            """



    def Get_Data(self):
        if(self.Serial_state):
            self.data = self.Serial_data.Serial_port.readline()
            self.data = self.data.decode()
            self.data = self.data.split()

            print(self.data)















if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    mi_app = Program()
    mi_app.show()
    sys.exit(app.exec_())