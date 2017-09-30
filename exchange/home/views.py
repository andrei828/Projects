from django.shortcuts import render
from django.http import HttpResponse
from .exchange_values import Currencies

def index(request):
	
	xml_data = Currencies()
	context = {
		'Values': xml_data.Currencies.values(),
		'Keys': xml_data.Currencies.keys(),
		'Currencies': xml_data.Currencies
		}
	return render(request, "index.html", context)