from PySide import QtGui, QtCore
import FileEditor 
import xml.etree.ElementTree as ET
from UI import unites as UI
class UniteEditor(FileEditor.FileEditor):
	proprietesPossibles = {"nom":None, "attaque":None, "portee":None, "vision":None, "temps":None, "type-degat":None, "armure":None,
			"amelioration":None,
			'coute':["bois", "or", "metal", "pop"],
			'produit':["bois", "or", "metal", "pop"]}
	unites = {}
	def __init__(self, widget, file):
		FileEditor.FileEditor.__init__(self, widget, file)
		self.ui = UI.Ui_Form()
		self.ui.setupUi(widget)
		self.modelUnites = QtGui.QStandardItemModel()
		self.modelProprietes = QtGui.QStandardItemModel()
		self.modelUnitesAmelioration = QtGui.QStringListModel()
		self.ui.proprietes.setModel(self.modelProprietes)
		self.ui.unites.setModel(self.modelUnites)
		self.ui.unites.pressed.connect(self.uniteChanged)
		self.ui.unites.activated.connect(self.uniteChanged)
		self.ui.amelioration.setModel(self.modelUnitesAmelioration)
		self.modelCouts = QtGui.QStandardItemModel()
		self.ui.couts.setModel(self.modelCouts)

		self.fillUnits()
		self.ui.produit.setVisible(False)
		self.ui.couts.setVisible(False)
		self.ui.amelioration.setVisible(False)

		self.modelProprietes.dataChanged.connect(self.changed)
		self.fillModelUnitesAmelioration()
		self.fillCoutsUnite()

	def fillUnits(self):
		self.modelUnites.clear()
		self.modelUnites.setColumnCount(2)
		xml = ET.parse(self.file.absoluteFilePath()).getroot()
		batiments = QtGui.QStandardItem("Batiments")
		classesHeros = QtGui.QStandardItem("Heros")
		terrestre = QtGui.QStandardItem("Terrestre")
		aerien = QtGui.QStandardItem("Aerien")
		
		types = {}
		types["BAT"] = batiments
		types["TER"] = terrestre
		types["AIR"] = aerien
		types["HER"] = classesHeros

		for unite in xml.findall("unite"):
			item = QtGui.QStandardItem(unite.find("nom").text)
			itemID = QtGui.QStandardItem(unite.find("id").text)
			types[unite.find("type").text].appendRow([item, itemID])
			uniteData = {}
			for nodeName in self.proprietesPossibles:
				prop = unite.find(nodeName)
				if prop is None:
					continue
				if type(self.proprietesPossibles[nodeName]) is list:
					for secondNodeName in self.proprietesPossibles[nodeName]:
						propBis = prop.find(secondNodeName)
						uniteData[nodeName] = {}
						if propBis is not None:
							uniteData[nodeName][secondNodeName] = propBis.text
						else:
							uniteData[nodeName][secondNodeName] = 0
				else: 	#Cas ou c'est une propriete simple
					uniteData[nodeName] = unite.find(nodeName).text

			for nomType in  ["necessite", "construit"]:
				uniteData[nomType] = { }
				nodeTemp = unite.find(nomType)
				if nodeTemp == None:
					continue
				for nodeDependance in list(nodeTemp):
					uniteData[nomType][nodeDependance.tag] = nodeDependance.text
			self.unites[unite.find("id").text] = uniteData
		i=0
		for item in types.values():
			self.modelUnites.setItem(i, item)
			item.setEditable(False)
			i+=1
		self.modelUnites.setHorizontalHeaderLabels(["Nom", "ID"])
	def fillCoutsUnite(self):
		self.coutCurr = {}
		self.modelCouts.setHorizontalHeaderLabels(["Nom", "Quantite"])
		temp = {"Or":"or", "Bois":"bois", "Metal":"metal", "Population":"pop"}
		for res in temp:
			self.coutCurr[temp[res]] = QtGui.QStandardItem(res)
			self.coutCurr[temp[res]].setEditable(False)
			self.modelCouts.appendRow([self.coutCurr[temp[res]], QtGui.QStandardItem("0")])
	def fillModelUnitesAmelioration(self):
		idList = []
		nomList = []
		for unite in self.unites:
			idList.append(unite)
			nomList.append(self.unites[unite]["nom"])
		self.modelUnitesAmelioration.setStringList(nomList)
		i=0
		count = len(idList)
		print count
		while i < count:
			index = self.modelUnitesAmelioration.index(i, 0)
			self.modelUnitesAmelioration.setData(index, idList[i], QtCore.Qt.UserRole)
			i+=1
	def uniteChanged(self, model):
		item = self.modelUnites.itemFromIndex(model)
		if item.hasChildren():
			return
		id = item.parent().child(item.row(), 1).text()
		uniteData = self.unites[id]
		self.modelProprietes.clear()
		for data in self.proprietesPossibles:
			if data == "amelioration":
				continue
			elif type(self.proprietesPossibles[data]) is list:
				continue
			itemNom = QtGui.QStandardItem(data)
			itemNom.setEditable(False)
			itemData = None
			if uniteData.has_key(data):
				itemData = QtGui.QStandardItem(uniteData[data])
			else:
				itemData = QtGui.QStandardItem("0")
			self.modelProprietes.appendRow([itemNom, itemData])
