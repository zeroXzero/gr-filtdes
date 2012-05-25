from PyQt4 import QtGui, QtCore

class BandGraphicsView(QtGui.QGraphicsView):
    def resizeEvent(self, event):
        pass
#print event.size().width()
#self.fitInView(self.scene().itemsBoundingRect(), QtCore.Qt.KeepAspectRatio)

