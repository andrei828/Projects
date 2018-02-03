import json
try: 
	from urllib.request import urlopen
except ImportError:
	from urllib import urlopen

class Currencies:
	json_link = "http://api.fixer.io/latest"
	Currencies = {}

	def __init__(self):
		open_json = urlopen(self.json_link)
		json_data = json.load(open_json)
		self.Currencies = json_data["rates"]
