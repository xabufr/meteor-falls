class FileEditor:
	def __init__(self, widget, file):
		self.widget = widget
		self.file = file
		widget.manager = self
		self.m_isSaved = True

	def changed(self):
		id = self.widget.parent().parent().indexOf(self.widget)
		self.widget.parent().parent().setTabText(id, self.file.fileName()+"*")
		self.m_isSaved = False
	def saved(self):
		id = self.widget.parent().parent().indexOf(self.widget)
		self.widget.parent().parent().setTabText(id, self.file.fileName())
		self.m_isSaved = True
	def isSaved(self):
		return self.m_isSaved
