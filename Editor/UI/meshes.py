# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'UI/meshes.ui'
#
# Created: Wed Dec 11 11:03:52 2013
#      by: pyside-uic 0.2.15 running on PySide 1.2.1
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(465, 363)
        self.gridLayout = QtGui.QGridLayout(Form)
        self.gridLayout.setObjectName("gridLayout")
        self.prefix = QtGui.QLineEdit(Form)
        self.prefix.setObjectName("prefix")
        self.gridLayout.addWidget(self.prefix, 0, 1, 1, 2)
        self.btnSupprimer = QtGui.QPushButton(Form)
        self.btnSupprimer.setObjectName("btnSupprimer")
        self.gridLayout.addWidget(self.btnSupprimer, 2, 2, 1, 1)
        self.label = QtGui.QLabel(Form)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.listeMeshes = QtGui.QTableView(Form)
        self.listeMeshes.setAlternatingRowColors(True)
        self.listeMeshes.setSelectionMode(QtGui.QAbstractItemView.SingleSelection)
        self.listeMeshes.setSelectionBehavior(QtGui.QAbstractItemView.SelectRows)
        self.listeMeshes.setSortingEnabled(True)
        self.listeMeshes.setObjectName("listeMeshes")
        self.gridLayout.addWidget(self.listeMeshes, 1, 0, 1, 3)
        self.btnAjouter = QtGui.QPushButton(Form)
        self.btnAjouter.setObjectName("btnAjouter")
        self.gridLayout.addWidget(self.btnAjouter, 2, 0, 1, 2)
        self.btnSauver = QtGui.QPushButton(Form)
        self.btnSauver.setObjectName("btnSauver")
        self.gridLayout.addWidget(self.btnSauver, 3, 0, 1, 3)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(QtGui.QApplication.translate("Form", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSupprimer.setText(QtGui.QApplication.translate("Form", "Supprimer", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Form", "préfixe", None, QtGui.QApplication.UnicodeUTF8))
        self.btnAjouter.setText(QtGui.QApplication.translate("Form", "Ajouter", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSauver.setText(QtGui.QApplication.translate("Form", "Sauver", None, QtGui.QApplication.UnicodeUTF8))

