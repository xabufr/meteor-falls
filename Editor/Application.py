from PySide import QtGui
from PySide import QtCore
import ConfigParser
import sys
from UI import mainwindow
import Preferences
from editors import ObjectFile, UniteFile, FileEditor

class Application:
	fichiersOuverts = {}
	def __init__(self, args):
		self.initConfig()

		self.application = QtGui.QApplication(args)
		self.mainWindow = QtGui.QMainWindow()
		self.ui = mainwindow.Ui_MainWindow()
		self.ui.setupUi(self.mainWindow)
		fichiers = self.ui.listeFichiers

		self.modelFiles = QtGui.QFileSystemModel()
		fichiers.setModel(self.modelFiles)
		fichiers.header().hideSection(1)
		fichiers.header().hideSection(3)
		self.modelFiles.setNameFilterDisables(False)
		self.modelFiles.setNameFilters(["*.xml", "*.models", "*.mfu"])
		
		self.fenPreferences = Preferences.Preferences(self.config)
		self.fenPreferences.accepted.connect(self.reloadConfig)
		self.fenPreferences.prefencesChanged.connect(self.reloadConfig)
		self.ui.actionPreferences.triggered.connect(self.showConfig)
		self.ui.listeFichiers.doubleClicked.connect(self.openSelected)
		self.reloadConfig()
		
	def run(self):
		self.mainWindow.show()
		sys.exit(self.application.exec_())

	def reloadConfig(self):
		fichiers = self.ui.listeFichiers
		fichiers.setRootIndex(self.modelFiles.setRootPath(self.config.get("general", "data_path")))

	def initConfig(self):
		self.config = ConfigParser.RawConfigParser()
		self.config.add_section("general")
		self.config.set("general", "data_path", "/home/thomas/")
		self.config.read("config.cfg")

	def showConfig(self):
		self.fenPreferences.show()
	def openSelected(self, modelIndex):
		file = self.modelFiles.fileInfo(modelIndex)
		if not file.isDir() :
			self.ourvirFichier(file)
	def ourvirFichier(self, file):
		if not self.fichiersOuverts.has_key(file.absoluteFilePath()):
			widget = self.uiBuild(file)
			if not widget:
				return
			self.fichiersOuverts[file.absoluteFilePath()] = widget
			self.ui.tabWidget.addTab(widget.widget, file.fileName())
		widget = self.fichiersOuverts[file.absoluteFilePath()]
		self.ui.tabWidget.setCurrentWidget(widget.widget)
	def uiBuild(self, file):
		if file.suffix() == "models":
			widget = QtGui.QWidget()
			return ObjectFile.ObjectFile(widget, file)
		elif file.suffix() == "mfu":
			widget = QtGui.QWidget()
			return UniteFile.UniteEditor(widget, file)
		return False
