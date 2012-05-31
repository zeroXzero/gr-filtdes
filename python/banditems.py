try:
    from PyQt4 import Qt, QtCore, QtGui
except ImportError:
    print "Please install PyQt4 to run this script (http://www.riverbankcomputing.co.uk/software/pyqt/download)"
    raise SystemExit, 1

#Movable solid line in filter ideal-band diagram
class filtermovlineItem(QtGui.QGraphicsObject):
    attenChanged = QtCore.pyqtSignal(float)
    def __init__(self,x1,y1,x2,y2,lower,upper,split=False,sx1=0,sy1=0,sx2=0,sy2=0):
        QtGui.QGraphicsObject.__init__(self)
        self.lower=lower
        self.upper=upper
        self.x1,self.y1=x1,y1
        self.x2,self.y2=x2,y2
        self.sx1,self.sy1=sx1,sy1
        self.sx2,self.sy2=sx2,sy2
        self.split=split

    def paint(self, painter, option, widget):
        painter.setPen(QtGui.QPen(QtCore.Qt.black,2 , QtCore.Qt.SolidLine))
        painter.drawLine(self.x1,self.y1,self.x2,self.y2)
        painter.drawLine(self.x1,self.y1,self.x1,self.y1-5)
        painter.drawLine(self.x2,self.y2,self.x2,self.y2-5)
        if self.split:
           painter.drawLine(self.sx1,self.sy1,self.sx2,self.sy2)
           painter.drawLine(self.sx1,self.sy1,self.sx1,self.sy1-5)
           painter.drawLine(self.sx2,self.sy2,self.sx2,self.sy2-5)
    def boundingRect(self):
        return QtCore.QRectF(0,0,400,400)

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


#Static lines in lpf band diagram
class lpfsLines(QtGui.QGraphicsObject):
    def __init__(self):
        QtGui.QGraphicsObject.__init__(self)
        self.poly = QtGui.QPolygonF()
        self.poly << QtCore.QPointF(3,5)
        self.poly << QtCore.QPointF(7,5)
        self.poly << QtCore.QPointF(5,3)
        self.arrowtop=QtGui.QGraphicsPolygonItem()
        self.arrowtop.setPolygon(self.poly)
        self.arrowtop.setPen(QtGui.QPen(QtCore.Qt.lightGray))

    def paint(self, painter, option, widget):
        painter.setPen(QtGui.QPen(QtCore.Qt.darkGray, 2, QtCore.Qt.SolidLine))
        painter.drawLine(5,20,5,200)
        painter.drawLine(5,200,400,200)
        painter.setPen(QtGui.QPen(QtCore.Qt.lightGray, 2, QtCore.Qt.SolidLine))
        painter.drawLine(6,105,150,105)
        painter.drawLine(150,105,150,199)
        painter.drawLine(200,180,400,180)
        painter.drawLine(200,180,200,199)

    def boundingRect(self):
        return QtCore.QRectF(0,0,300,300)

#Static lines in hpf band diagram
class hpfsLines(QtGui.QGraphicsObject):
    def __init__(self):
        QtGui.QGraphicsObject.__init__(self)

    def paint(self, painter, option, widget):
        painter.setPen(QtGui.QPen(QtCore.Qt.darkGray, 2, QtCore.Qt.SolidLine))
        painter.drawLine(5,20,5,200)
        painter.drawLine(5,200,400,200)
        painter.setPen(QtGui.QPen(QtCore.Qt.lightGray, 2, QtCore.Qt.SolidLine))
        painter.drawLine(200,105,400,105)
        painter.drawLine(200,105,200,199)
        painter.drawLine(6,180,150,180)
        painter.drawLine(150,180,150,199)

    def boundingRect(self):
        return QtCore.QRectF(0,0,300,300)

#Static lines in bpf band diagram
class bpfsLines(QtGui.QGraphicsObject):
    def __init__(self):
        QtGui.QGraphicsObject.__init__(self)

    def paint(self, painter, option, widget):
        painter.setPen(QtGui.QPen(QtCore.Qt.darkGray, 2, QtCore.Qt.SolidLine))
        painter.drawLine(5,20,5,200)
        painter.drawLine(5,200,400,200)
        painter.setPen(QtGui.QPen(QtCore.Qt.lightGray, 2, QtCore.Qt.SolidLine))
        painter.drawLine(6,180,110,180)
        painter.drawLine(110,180,110,199)
        painter.drawLine(155,105,255,105)
        painter.drawLine(255,105,255,199)
        painter.drawLine(155,105,155,199)
        painter.drawLine(300,180,400,180)
        painter.drawLine(300,180,300,199)

    def boundingRect(self):
        return QtCore.QRectF(0,0,300,300)
