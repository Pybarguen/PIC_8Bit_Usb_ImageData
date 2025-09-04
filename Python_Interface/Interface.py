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
        self.Image_Array = []

        # Temporizador para obtener los datos del puerto Serial
        self.tiempo2 = QTimer()
        self.tiempo2.setInterval(1)
        self.tiempo2.timeout.connect(self.Process_Serial_data)
        #___________________________________________________

        #Variables para el control de hilos
        self.thread_control = None
        self.Run_thread = False

        #variable para guardar los metadatos de las imagenes en forma de diccionario
        self.Image_metadata = None

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

        self.ui.Serial_Informmation.setText("Connection state : Disconnect ")

        self.ui.ComboBox_BaudRate.addItems(baudrates)

        """
                   ______________________________________________________________

                   """





        """
        Configuraciones de los botones con sus respectivas funciones 
        
        """



        #Connect Import Image Button With the respective Funtion
        self.ui.Import_Image_button.clicked.connect(self.Import_Images)
        #Boton para procesar datos de las matrices de las imagenes
        self.ui.ProcessImg_button.clicked.connect(lambda: self.Pixel_Converter(self.Image_Array))
        self.ui.Send_Image.clicked.connect(lambda: self.Send_image())

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
        if filenames:#Si hay archivos elegidos por el usuario
            for i in range(0, len(filenames)):
                self.images.append(QPixmap(filenames[i]))

            #Se crea un diccionario con los Labels de la interfaz.
            label_mapping = {
                0: self.ui.Image1_Label,
                1: self.ui.Image2_Label,
                2: self.ui.Image3_Label,
                3: self.ui.Image4_Label,
                4: self.ui.Image5_Label,
                5: self.ui.Image6_Label,
            }

            #Se itera en la lista de imagenes y se ponen los respectivos indices
            #en los labels
            for idx, image in enumerate(self.images):
                if idx in label_mapping:
                    label_mapping[idx].setPixmap(image)
                    label_mapping[idx].setScaledContents(True)
            for i in range(0, len(self.images)):
                image = Image.open(filenames[i])
                self.Image_Array.append(np.array(image))
            print(len(self.Image_Array))

    # ______________________________________________________________________

    """
        Funcion para convertir los pixeles de color en formato de 16bits
        aun se pueden observar perdidas de color en la conversion
        la funcion guarda los valores de 16bits por pixel en la matrix
        Image_matrix, el codigo aun se encuentra en pruebas.
        
         Parametros :

               Pixels contiene la lista de array numpy de cada una de las 
               imagenes


        """

    def Pixel_Converter(self, Pixels):
        #Diccionario para guardar los metadatos de las imagenes y avisar al hardware
        self.Image_metadata = {"width" : 0, "height" : 0, "size" : 0}
        if len(Pixels)!=0:#Si pixels realmente contiene imagenes
            """
            
            Se itera en el numero de imagenes en en la variable array Pixels
            se obtione los metadatos de cada imagen
            ancho, alto y produndida
    
            """
            for t in range(0, len(Pixels)):
                alto, ancho, _ = Pixels[t].shape
                self.Image_metadata["width"] = ancho
                self.Image_metadata["height"] = alto
                self.Image_metadata["size"] = int((alto * ancho)/256)
                current_img = Pixels[t]
                """
                se itera en cada uno de los pixeles y se convierte en 
                formato de color de 16bits R5G6B5
                """
                for j in range(0, ancho):
                    for i in range(0, alto):
                        Red = int(current_img[i, j, 0])
                        Green = int(current_img[i, j, 1])
                        Blue = int(current_img[i, j, 2])
                        r_5_bits = (Red >> 3) & 0x1F
                        g_6_bits = (Green >> 2) & 0x3F
                        b_5_bits = (Blue >> 3) & 0x1F
                        Final_value = (r_5_bits << 11) | (g_6_bits << 5) | b_5_bits
                        self.Image_matrix.append(Final_value)

        else:
            print("se debe avisar en la interfaz que no hay imagenes para procesar")






    """
                Fin del metodo conversion de pixeles

                """

#______________________________________________________________________

    """
           Funcion para conectar el puerto Serial
           Funciona hasta el momento con un baudrate bajo de 9600baudios
           se debe comprobar el condigo del PIC para aumentar la velocidad
           
           Parametros :
           
                    Port : Puerto COM# 
                    baudrate : Velocidad en baudios

           """

    def Connect_Serial(self, port, baudrate):
        #Se conecta al puerto serial, si la conexion no es Ok
        #Se menciona en la interfaz
        #print("Puerto {}   Baudrate {}".format(port, baudrate))
        self.Serial_data = Serial_data(port, baudrate)
        Port_State, self.Serial_state = self.Serial_data.Connect_Port()
        self.ui.Serial_Informmation.setText("Port {},  {}".format(port, Port_State))


        """
        Si el puerto serial esta conectado se inicia el hilo para la recepsion sin 
        perdida de datos 
        """
        if(self.Serial_state):
            self.Run_thread = True
            self.thread_control = threading.Thread(target=self.Thread_data_control)
            self.thread_control.start()
            self.tiempo2.start()

    """
               Fin de metodo conectar serial.
               
               
               _____________________________
               """



    """
              Hilo para leer los datos del puerto Serial 
              sin perdidas.
              Parametros :  None                   

              """

    def Thread_data_control(self):
        while(self.Run_thread):
            self.data = self.Serial_data.Get_serial_data()

                #self.Send_image()
                #self.Run_thread = False

    """
                Fin Hilo 
                ________________________________                 

                """



    def Send_image(self):
        if(self.Image_metadata and self.Serial_state):#Si hay metadatos elegidos y el puerto esta conectado
            a = 'pimg'.encode('utf_8')#Se envia el comando Pimg para poner imagenes
            self.Serial_data.Serial_port.write(a)
            print("hola mundo")

        else:
            return





        """
        Buffer_Data = []
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
"""

    def Send_test_data(self):
        a = 'Test'.encode('utf_8')
        self.Serial_data.Serial_port.write(a)
        # Put Image Command

        """"
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

    def Process_Serial_data(self):
        if (self.Serial_state):
            if(self.data):

                if (self.data and self.data[0] == 'Ok'):
                    self.ui.Serial_Informmation.setText(str(self.data[0]))
                    a = str(len(self.Image_Array)).encode('utf_8')
                    self.Serial_data.Serial_port.write(a)
                    self.data = None
                if(self.data and self.data[0] == "Ready"):
                    self.ui.Serial_Informmation.setText(str(self.data[0]))
                    a = 'cr'.encode('utf_8')
                    self.Serial_data.Serial_port.write(a)
                if (self.data and self.data[0] == "Okt"):
                    self.ui.Serial_Informmation.setText("Test Port State : Ok")
                    a = 'cr'.encode('utf_8')
                    self.Serial_data.Serial_port.write(a)


    def Memory_commands(self, command):
        a = command.encode('utf_8')
        if (self.Serial_state):
            self.Serial_data.Serial_port.write(a)




















if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    mi_app = Program()
    mi_app.show()
    sys.exit(app.exec_())