from django.shortcuts import render
from django.http import HttpResponse
from .exchange_values import Currencies
from .templates import index

def index(request):
	
	# get list of exchange values
	
	context = {}
	return render(request, index.html)

def prnt():
	print(Currencies)