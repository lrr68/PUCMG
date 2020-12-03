from django.urls import path

from . import views

app_name="TccAdmin"
urlpatterns = [
    path('gerar/', views.bancas, name='gerar'),
    path('gerar_bancas/', views.gerar, name='gerar_bancas'),
]
