from django.db import models
import datetime
from django.utils import timezone

class Horario(models.Model):
    horario = models.DateTimeField()
    preenchido_banca = models.BooleanField(default=False)
    preenchido_prof = models.BooleanField(default=False)

    def __str__(self):
        return self.horario.strftime('%Y/%m/%d - %H:%M')
        
    def is_future_date(self): # Return true if date(horario) is in the past
        now = timezone.now()
        return now - datetime.timedelta(days=1) <= self.horario <= now

class TipoUsuario(models.Model):
    nome = models.CharField(max_length=50)

    def __str__(self):
        return self.nome
        
    def is_name_valid(self): # Return True if nome != Null
        if (self.nome):
            return True
        else:
            return False

class Disciplina(models.Model):
    nome = models.CharField(max_length=50)

    def __str__(self):
        return self.nome
    
    def is_disciplina_valid(self):
        if (self.nome):
            return True
        else:
            return False

class Professor(models.Model):
    nome = models.CharField(max_length=50)
    tipoUsuario = models.ForeignKey(TipoUsuario,on_delete=models.CASCADE)
    aulas = models.ForeignKey('GradeAula',on_delete=models.SET_NULL,null=True)

    disciplinas = models.ManyToManyField(Disciplina)

    def __str__(self):
        return self.nome
    
    def is_professor_valid(self):
        if ( self.nome and self.tipoUsuario and self.aulas and self.disciplinas ):
            return True
        else:
            return False
    class Meta:
        verbose_name_plural = "Professores"
    
class Aluno(models.Model):
    nome = models.CharField(max_length=50)
    tema_tcc = models.CharField(max_length=50)

    disciplina_tcc = models.ForeignKey(Disciplina,on_delete=models.CASCADE)

    def __str__(self):
        return self.nome
        
    def is_aluno_valid(self):
        if (self.nome and self.tema_tcc and self.disciplina_tcc):
            return True
        else:
            return False

class Banca(models.Model):
    horario = models.ForeignKey(Horario, on_delete=models.CASCADE)
    aluno = models.ForeignKey(Aluno, on_delete=models.CASCADE)
    professor = models.ForeignKey(Professor, null=True, blank=True, on_delete=models.CASCADE)
    disciplina = models.ForeignKey(Disciplina, on_delete=models.CASCADE)
    observacao = models.CharField(max_length=500,null=True)

    def __str__(self):
        return self.aluno.__str__() + " " + self.professor.__str__()
        
    def is_banca_valid(self):
        if (self.horario and self.aluno and self.professor and self.disciplina):
            return True
        else:
            return False

class GradeAula(models.Model):
    nome = models.CharField(max_length=50)
    horarios = models.ManyToManyField(Horario)

    def __str__(self):
        return self.nome
    
    def is_grade_aula_valid(self):
        if (self.nome and self.horarios):
            return True
        else:
            return False

class GradeTcc(models.Model):
    nome = models.CharField(max_length=50)
    horarios = models.ManyToManyField(Horario)
    ativo = models.BooleanField(default=True)

    def __str__(self):
        return self.nome
        
    def is_grade_tcc_valid(self):
        if (self.nome and self.horarios and self.ativo):
            return True
        else:
            return False
