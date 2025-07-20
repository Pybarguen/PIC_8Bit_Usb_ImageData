import sys
import PyQt5
import serial
from Desing import *
class Program(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    mi_app = Program()
    mi_app.show()
    sys.exit(app.exec_())