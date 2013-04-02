# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'UI/meshes.ui'
#
# Created: Sat Mar 30 17:13:44 2013
#      by: pyside-uic 0.2.14 running on PySide 1.1.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(465, 363)
        self.gridLayout = QtGui.QGridLayout(Form)
        self.gridLayout.setObjectName("gridLayout")
        self.btnSupprimer = QtGui.QPushButton(Form)
        self.btnSupprimer.setObjectName("btnSupprimer")
        self.gridLayout.addWidget(self.btnSupprimer, 1, 1, 1, 1)
        self.btnAjouter = QtGui.QPushButton(Form)
        self.btnAjouter.setObjectName("btnAjouter")
        self.gridLayout.addWidget(self.btnAjouter, 1, 0, 1, 1)
        self.listeMeshes = QtGui.QTableView(Form)
        self.listeMeshes.setAlternatingRowColors(True)
        self.listeMeshes.setSelectionMode(QtGui.QAbstractItemView.SingleSelection)
        self.listeMeshes.setSelectionBehavior(QtGui.QAbstractItemView.SelectRows)
        self.listeMeshes.setSortingEnabled(True)
        self.listeMeshes.setObjectName("listeMeshes")
        self.gridLayout.addWidget(self.listeMeshes, 0, 0, 1, 2)
        self.btnSauver = QtGui.QPushButton(Form)
        self.btnSauver.setObjectName("btnSauver")
        self.gridLayout.addWidget(self.btnSauver, 2, 0, 1, 2)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(QtGui.QApplication.translate("Form", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSupprimer.setText(QtGui.QApplication.translate("Form", "Supprimer", None, QtGui.QApplication.UnicodeUTF8))
        self.btnAjouter.setText(QtGui.QApplication.translate("Form", "Ajouter", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSauver.setText(QtGui.QApplication.translate("Form", "Sauver", None, QtGui.QApplication.UnicodeUTF8))

