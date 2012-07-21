from PyQt4 import QtGui, QtCore, Qt

class BandGraphicsView(QtGui.QGraphicsView):
    def resizeEvent(self, event):
        self.setAlignment(Qt.Qt.AlignCenter)
        self.fitInView(self.scene().itemsBoundingRect(), QtCore.Qt.KeepAspectRatio)
        self.scale(1.3,1.3)
        self.setViewportMargins(10,10,10,10)
