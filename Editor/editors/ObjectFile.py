from UI import meshes
from PySide import QtGui
import xml.etree.ElementTree as ET
import FileEditor

class ObjectFile(FileEditor.FileEditor):
	def __init__(self, widget, file):
		FileEditor.FileEditor.__init__(self, widget, file)
		self.widget = widget
		widget.manager = self
		self.file = file
		self.ui = meshes.Ui_Form()
		self.ui.setupUi(self.widget)
		self.ui.btnAjouter.clicked.connect(self.addNew)
		self.ui.btnSupprimer.clicked.connect(self.removeSelected)
		self.ui.btnSauver.clicked.connect(self.save)
		self.model = QtGui.QStandardItemModel()

		self.ui.listeMeshes.setModel(self.model)
		self.reloadFile()

		self.model.dataChanged.connect(self.changed)
		self.model.rowsInserted.connect(self.changed)
		self.model.rowsRemoved.connect(self.changed)

		self.ui.prefix.textChanged.connect(self.changed)

	def reloadFile(self):
		self.model.clear()
		xml = ET.parse(self.file.absoluteFilePath())
		root = xml.getroot()
		for model in root.iter("model"):
			row = QtGui.QStandardItem()
			name = QtGui.QStandardItem(model.attrib["name"])
			ogre = QtGui.QStandardItem(model.attrib["ogre"])
			bull = QtGui.QStandardItem(model.attrib["bullet"])
			self.model.appendRow([name, ogre, bull])
		self.model.setHorizontalHeaderLabels(["nom", "Mesh ogre", "fichier bullet"])
		if root.attrib.has_key("prefix"):
			self.ui.prefix.setText(root.attrib["prefix"])
	def save(self):
		xml = ET.Element("models")
		rows = self.model.rowCount()
		i = 0
		while(i<rows):
			ET.SubElement(xml, "model", {"name":self.model.item(i, 0).text(), "ogre":self.model.item(i, 1).text(), "bullet":self.model.item(i, 2).text()})
			i+=1
		xml.attrib["prefix"] = self.ui.prefix.text()
		doc = ET.ElementTree(xml)
		doc.write(self.file.absoluteFilePath(), "UTF-8")
		self.saved()
	def addNew(self):
		self.model.appendRow([QtGui.QStandardItem(), QtGui.QStandardItem(), QtGui.QStandardItem()])
	def removeSelected(self):
		index = self.ui.listeMeshes.currentIndex()
		item = self.model.itemFromIndex(index)
		if item:
			row = item.row()
			self.model.removeRows(row, 1)
