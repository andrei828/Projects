import xml.etree.ElementTree as ET
from datetime import date
import time
try: 
	from urllib.request import urlopen
except ImportError:
	from urllib import urlopen
			
class Currencies:
	schema_link = "{http://www.bnr.ro/xsd}"
	xml_link = urlopen("http://www.bnr.ro/files/xml/years/nbrfxrates" + time.strftime("%Y") + ".xml").read()
	Currencies = {}
	
	year  = int(time.strftime("%Y"))
	month = int(time.strftime("%m"))
	day   = int(time.strftime("%d"))
	
	month_string = str(month)
	day_string   = str(day)
	
	def __init__(self):
		
		if self.month < 10:
			self.month_string = "0" + self.month_string
		if self.day < 10:
			self.day_string = "0" + self.day_string
				
		if date(self.year, self.month, self.day).weekday() == 5:
			self.current_day = str(self.year) + "-" + self.month_string + "-" + str(self.day - 1)
					
		if date(self.year, self.month, self.day).weekday() == 6:
			self.current_day = str(self.year) + "-" + self.month_string + "-" + str(self.day - 2)
						
		xml = ET.fromstring(self.xml_link)
		body = xml.find(self.schema_link + 'Body')
						
		for cube in body:
			if cube.attrib == { "date": self.current_day }:
				for rate in cube:
					self.Currencies[rate.attrib["currency"]] = rate.text
