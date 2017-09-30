import xml.etree.ElementTree as ET
import urllib2

file_in = open('currency.txt', 'r')

Ron = {}
Currency = file_in.read()
file_in.close()
schema = "{http://www.bnr.ro/xsd}"
url_basic = "http://www.bnr.ro/files/xml/years/nbrfxrates"

for i in range(2005, 2018):
    url = url_basic + str(i) + '.xml'
    xml = urllib2.urlopen(url).read()
    root = ET.fromstring(xml)

    node = root.find(schema + 'Body')
    aux = node.find(schema + 'Cube')
    for Rate in aux:
        if str(Rate.attrib['currency']) == Currency:
            Ron[i] = Rate.text

for i in range(2006, 2018):
    print abs(100 - round(100 * float(Ron[i]) / float(Ron[2005]), 2))
