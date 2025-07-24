import sys
import PyQt5
import serial
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QFileDialog

from Desing import *
from PIL import ImageTk, Image


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




if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    mi_app = Program()
    mi_app.show()
    sys.exit(app.exec_())