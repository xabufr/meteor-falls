from PySide import QtGui, QtCore
from UI import preferences

class Preferences(QtGui.QDialog):
	prefencesChanged = QtCore.Signal()
	def __init__(self, config):
		super(Preferences, self).__init__()
		self.ui = preferences.Ui_Preferences()
		self.ui.setupUi(self)
		self.config = config
		self.ui.dataPath.setText(config.get("general", "data_path"))
		self.ui.selectionnerData.clicked.connect(self.selectionnerDossierData)
		self.accepted.connect(self.appliquer)
		apply = self.ui.buttonBox.button(QtGui.QDialogButtonBox.Apply)
		apply.clicked.connect(self.appliquer)
	def selectionnerDossierData(self):
		fileDialog = QtGui.QFileDialog(self)
		fileDialog.setFileMode(QtGui.QFileDialog.Directory)
		if fileDialog.exec_():
			directory = fileDialog.selectedFiles()
			self.ui.dataPath.setText(directory[0])
	def appliquer(self):
		self.config.set("general", "data_path", self.ui.dataPath.text())
		self.prefencesChanged.emit()
		with open("config.cfg", "wb") as fichier:
			self.config.write(fichier)

