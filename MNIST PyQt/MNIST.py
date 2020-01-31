import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5.uic import loadUi

import tensorflow as tf
from tensorflow.python.platform import gfile

import numpy as np

class DrawPanel(QtWidgets.QLabel):

    updated = pyqtSignal() 
    
    def __init__(self):
        super().__init__()
        
        pixmap = QtGui.QPixmap(231, 231)
        pixmap.fill(Qt.white)
        self.setPixmap(pixmap)

        self.last_x, self.last_y = None, None
        self.pen_color = QtGui.QColor('#000000')        

    def set_pen_color(self, c):
        self.pen_color = QtGui.QColor(c)

    def mouseMoveEvent(self, e):

        painter = QtGui.QPainter(self.pixmap())
        painter.setBrush(QtGui.QBrush(Qt.black, Qt.SolidPattern))
        painter.drawEllipse(e.x() - 10, e.y() - 10, 35, 35)
        painter.end()
        self.update()
        self.updated.emit()


    def mouseReleaseEvent(self, e):
        self.last_x = None
        self.last_y = None
        
    def clear(self):
        pixmap = QtGui.QPixmap(231, 231)
        pixmap.fill(Qt.white)
        self.setPixmap(pixmap)



class MainWindow(QtWidgets.QMainWindow):

    def __init__(self):
        super().__init__()
        
        self.ui = loadUi('MNIST.ui', self)
		
        self.drawPanel = DrawPanel()
        self.verticalLayout.addWidget(self.drawPanel)
        
        self.drawPanel.updated.connect(self.detect)
        self.clearButton.clicked.connect(self.clear)
        
        # Load graph from protocol buffer file
        f = gfile.FastGFile('MNIST.pb', 'rb')
        graph_def = tf.GraphDef()
        graph_def.ParseFromString(f.read())
        f.close()
        
        # Start TensorFlow session and import graph
        self.session = tf.Session()
        self.session.graph.as_default()
        tf.import_graph_def(graph_def)
        
        

    def detect(self):
        pixmap = self.drawPanel.pixmap()
        qimage = pixmap.scaled(28, 28).toImage().convertToFormat(QtGui.QImage.Format_RGB888)
        ptr = qimage.bits()
        ptr.setsize(28 * 28 * 3)
        image = np.frombuffer(ptr, np.uint8).reshape((28, 28, 3))
        
        image = image[:,:,0]/image[:,:,0].max()
        input_tensor = image[np.newaxis, :, :, np.newaxis]
        output_tensor = self.session.graph.get_tensor_by_name('import/dense_1/Softmax:0')
        
        output = self.session.run(output_tensor, {'import/conv2d_input:0': input_tensor})[0]
        
        self.progressBar_0.setValue(output[0]*100)
        self.progressBar_1.setValue(output[1]*100)
        self.progressBar_2.setValue(output[2]*100)
        self.progressBar_3.setValue(output[3]*100)
        self.progressBar_4.setValue(output[4]*100)
        self.progressBar_5.setValue(output[5]*100)
        self.progressBar_6.setValue(output[6]*100)
        self.progressBar_7.setValue(output[7]*100)
        self.progressBar_8.setValue(output[8]*100)
        self.progressBar_9.setValue(output[9]*100)
        
    def clear(self):
        self.progressBar_0.setValue(0)
        self.progressBar_1.setValue(0)
        self.progressBar_2.setValue(0)
        self.progressBar_3.setValue(0)
        self.progressBar_4.setValue(0)
        self.progressBar_5.setValue(0)
        self.progressBar_6.setValue(0)
        self.progressBar_7.setValue(0)
        self.progressBar_8.setValue(0)
        self.progressBar_9.setValue(0)
        
        self.drawPanel.clear()
        

app = QtWidgets.QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()