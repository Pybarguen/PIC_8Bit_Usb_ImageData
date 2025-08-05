import sys
import PyQt5
import serial
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QFileDialog
from PIL import Image
from Serial_server import *
import numpy as np



from Desing import *


class Program(QtWidgets.QMainWindow):
    def __init__(self, parent=None):



        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.Serial_data = None



        """
        Configuracion de los WidGets ComboBox
        
        """
        ports = ["COM1", "COM2", "COM3", "COM4"]

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
        self.ui.Connect_Serial.clicked.connect(
            lambda: self.Connect_Serial(
                self.ui.ComboBox_Port.currentText(),
                self.ui.ComboBox_BaudRate.currentText()
            )
        )

    """
            ______________________________________________________________

            """




    def Import_Images(self):
        filenames, _ = QFileDialog.getOpenFileNames(
            self,
            "Select Files",
            r"C:/images/",
            "Images (*.png *.jpg)")
        if filenames:
            mi_image = QPixmap(filenames[0])
            self.ui.Image1_Label.setScaledContents(True)
            self.ui.Image1_Label.setPixmap(mi_image)
            image = Image.open(filenames[0])
            pixeles = np.array(image)
            self.Pixel_Converter(pixeles)


    def Pixel_Converter(self, Pixels):
        alto, ancho, _ = Pixels.shape
        Image_matrix = []
        for i in range(0, alto):
            for j in range(0, ancho):
                Red = int(Pixels[i, j, 0])
                Green = int(Pixels[i, j, 1])
                Blue = int(Pixels[i, j, 2])
                r_5_bits = (Red >> 3) & 0x1F
                g_6_bits = (Green >> 2) & 0x3F
                b_5_bits = (Blue >> 3) & 0x1F

                print(Red, Green, Blue)
                print("Red {} Green {}  Blue {}".format(r_5_bits, g_6_bits, b_5_bits))
                print("Red {} Green {}  Blue {}".format(bin(r_5_bits), bin(g_6_bits), bin(b_5_bits)))
                Final_value = (r_5_bits << 11) | (g_6_bits << 5) | b_5_bits
                Image_matrix.append(hex(Final_value))
        print(Image_matrix)



    def Connect_Serial(self, port, baudrate):
        print("Puerto {}   Baudrate {}".format(port, baudrate))
        #self.Serial_data = Serial_data(port, baudrate)










if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    mi_app = Program()
    mi_app.show()
    sys.exit(app.exec_())