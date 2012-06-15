from PyQt4 import QtGui, QtCore

class BandGraphicsView(QtGui.QGraphicsView):
    def resizeEvent(self, event):
        pass
#print event.size().width()
#self.centerOn(QtCore.QPointF(100,100))
#self.fitInView(self.scene().itemsBoundingRect(), QtCore.Qt.KeepAspectRatio)
