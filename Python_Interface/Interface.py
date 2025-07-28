import sys
import PyQt5
import serial
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QFileDialog
from PIL import Image
import numpy as np
from pycparser.c_ast import Break

from Desing import *


class Program(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)


        #Connect Import Image Button With the respective Funtion
        self.ui.Import_Image_button.clicked.connect(self.Import_Images)


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
        for i in range(0, alto):
            for j in range(0, ancho):
                Red = int(Pixels[i, j, 0])
                Green = int(Pixels[i, j, 1])
                Blue = int(Pixels[i, j, 2])
                r_5_bits = (Red*31)/255
                g_6_bits = (Green*63)/255
                b_5_bits = (Blue*31)/255

                print(Red, Green, Blue)
                print(r_5_bits, g_6_bits, b_5_bits)
                break
            break









if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    mi_app = Program()
    mi_app.show()
    sys.exit(app.exec_())