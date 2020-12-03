from django.shortcuts import render
from .utils import criar_bancas

# Create your views here.
def bancas(request):
    return render(request,"TccAdmin/bancas.html",None)
    
# Create your views here.
def gerar(request):
    criar_bancas()
    return render(request,"TccAdmin/sucesso.html",None)
