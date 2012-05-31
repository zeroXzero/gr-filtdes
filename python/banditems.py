try:
    from PyQt4 import Qt, QtCore, QtGui
except ImportError:
    print "Please install PyQt4 to run this script (http://www.riverbankcomputing.co.uk/software/pyqt/download)"
    raise SystemExit, 1

#Movable solid line in filter ideal-band diagram
class filtermovlineItem(QtGui.QGraphicsObject):
    attenChanged = QtCore.pyqtSignal(float)
    def __init__(self):
        QtGui.QGraphicsObject.__init__(self)
        self.lower=0
        self.upper=-50
    def paint(self, painter, option, widget):
        painter.setPen(QtGui.QPen(QtCore.Qt.black,2 , QtCore.Qt.SolidLine))
        painter.drawLine(50,50,150,50)
    def boundingRect(self):
        return QtCore.QRectF(0,0,200,200)

    #allow only vertical movement and emit signals properly
    def itemChange(self, change, value):
        if (change == QtGui.QGraphicsItem.ItemPositionChange):
            newpos=value.toPointF()
            rect=self.scene().sceneRect()
            if (newpos.y() >= self.lower):
                newpos.setY(self.lower)
            if (newpos.y() <= self.upper):
                newpos.setY(self.upper)
            self.attenChanged.emit(-newpos.y())
            return QtCore.QPointF(self.pos().x(), newpos.y())
        return QtGui.QGraphicsItem.itemChange(self, change, value)

