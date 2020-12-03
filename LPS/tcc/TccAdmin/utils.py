import datetime
from .models import *

def criar_bancas():

    #admite apenas uma grade
    grade = GradeTcc.objects.filter(ativo=True)[0]

    #para cada aluno, encaixa seu tema em um horario e dia da grade
    for a in Aluno.objects.filter(banca=None):
        #insere no proximo horario vago
        h = grade.horarios.filter(preenchido_banca=False)
        # se houverem horarios vagos, insere
        # se nao, sai do for
        if len(h) > 0:
            h = h[0]
            #Cria uma banca para esse horario
            Banca.objects.create(horario=h,aluno=a,disciplina=a.disciplina_tcc,professor=None) 
            #marca o horario como preenchido
            h.preenchido_banca=True
            h.save()
        else:
            break

    #para cada banca, associa um professor que estiver disponivel
    for b in Banca.objects.filter(professor=None):
        #encontra o professor disponivel
        prof = None
        for p in Professor.objects.all():
            #professor esta disponivel se possui horario vago no horario da banca
            if b.horario in p.aulas.horarios.filter(preenchido_prof=False):
                prof=p
                #marca o horario como preenchido
                b.horario.preenchido_prof = True
                b.horario.save()
                break
        else: #do for mesmo
            raise Exception("Nenhum professor disponível para a banca")
            
        b.professor=prof
        b.save()
