import urllib2
import xml.etree.ElementTree as ET

data = {}
url = "http://www.bnr.ro/nbrfxrates.xml"
schema = "{http://www.bnr.ro/xsd}"

xml = urllib2.urlopen(url).read()
root = ET.fromstring(xml)

node = root.find(schema + 'Body')
for Rate in node.find(schema + 'Cube'):
    data[Rate.attrib['currency']] = Rate.text

print data



  





    








