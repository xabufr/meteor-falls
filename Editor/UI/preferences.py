# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'UI/preferences.ui'
#
# Created: Sat Mar 30 17:13:44 2013
#      by: pyside-uic 0.2.14 running on PySide 1.1.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Preferences(object):
    def setupUi(self, Preferences):
        Preferences.setObjectName("Preferences")
        Preferences.resize(411, 300)
        self.gridLayout = QtGui.QGridLayout(Preferences)
        self.gridLayout.setObjectName("gridLayout")
        self.selectionnerData = QtGui.QPushButton(Preferences)
        self.selectionnerData.setObjectName("selectionnerData")
        self.gridLayout.addWidget(self.selectionnerData, 0, 2, 1, 1)
        self.dataPath = QtGui.QLineEdit(Preferences)
        self.dataPath.setReadOnly(True)
        self.dataPath.setObjectName("dataPath")
        self.gridLayout.addWidget(self.dataPath, 0, 1, 1, 1)
        self.label = QtGui.QLabel(Preferences)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.buttonBox = QtGui.QDialogButtonBox(Preferences)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Apply|QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok|QtGui.QDialogButtonBox.Reset)
        self.buttonBox.setCenterButtons(False)
        self.buttonBox.setObjectName("buttonBox")
        self.gridLayout.addWidget(self.buttonBox, 1, 0, 1, 3)

        self.retranslateUi(Preferences)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL("accepted()"), Preferences.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL("rejected()"), Preferences.reject)
        QtCore.QMetaObject.connectSlotsByName(Preferences)

    def retranslateUi(self, Preferences):
        Preferences.setWindowTitle(QtGui.QApplication.translate("Preferences", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.selectionnerData.setText(QtGui.QApplication.translate("Preferences", "Parcourir", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Preferences", "Dossier projet", None, QtGui.QApplication.UnicodeUTF8))

