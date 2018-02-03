from html.parser import HTMLParser
try:
	from urllib.request import urlopen
except ImportError:
	from urllib import urlopen

class GetXMLLinks(HTMLParser):
	found_table = False
	end_observation = False
	Data_Links = []
	Observation = []
	Forecast = []

	def __init__(self, Cities, base_url):
		super().__init__()
		self.Cities = Cities
		self.base_url = base_url

	def handle_starttag(self, tag, attrs):
		if self.found_table and tag == 'a':
			for (name, value) in attrs:
				if name == "href" and ".xml" in value:
					if "observation" in value:
						tmp = value.replace("observation", "forecast")
						tmp = tmp.replace("observ/surface", "fproduct")
						self.Data_Links.append((self.base_url + tmp, self.base_url + value))

	def handle_data(self, data):
		if data == "Amsterdam" and self.end_observation == False: 
			self.found_table = True
			self.end_observation = True
		elif data == "Zagreb / Maksimir" and self.end_observation:
			self.found_table = False

	def get_Data_Links(self):
		return self.Data_Links

url = 'http://meteo.arso.gov.si/met/en/service/'
html = urlopen(url).read()
html = html.decode('utf-8')

with open('Cities.txt') as file_in:
	Cities = [e.strip() for e in file_in.readlines()]
	finder = GetXMLLinks(Cities, 'http://meteo.arso.gov.si')
	finder.feed(html)
	Data = finder.get_Data_Links()
	print(Data)
