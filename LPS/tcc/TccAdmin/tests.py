from django.db import models
from django.test import TestCase
from django.utils import timezone
import datetime
from .models import *

class HorarioModelTests(TestCase):
    def test_is_future_data(self):
        time = timezone.now() - datetime.timedelta(days=1, seconds=1)
        horario_antigo = Horario(horario=time)
        self.assertIs(horario_antigo.is_future_date(), False)

class TipoUsuarioModelTests(TestCase):
    def test_is_valid_user(self):
        usuario = TipoUsuario(nome="tipo_usuario_teste")
        self.assertIs(usuario.is_name_valid(), True)

class DisciplinaModelTests(TestCase):
    def test_is_valid_disciplina(self):
        disciplina = Disciplina(nome="disciplina_teste")
        self.assertIs(disciplina.is_disciplina_valid(), True)

class ProfessorModelTests(TestCase):
    def test_is_valid_disciplina(self):
        tip_usu = TipoUsuario(nome="tipo_usuario_professor_teste")
        tip_usu.save()
        
        grad_aula = GradeAula(nome="grade_aula_teste")
        grad_aula.save()
        
        tip_disc = Disciplina(nome="disciplina_teste")
        tip_disc.save()
        
        instancia_tipo_usuario = TipoUsuario.objects.get(id=1)
        instancia_grade_aula   = GradeAula.objects.get(id=1)
        instancia_disciplina   = Disciplina.objects.get(id=1)
        
        professor = Professor(nome="professor_teste", tipoUsuario=instancia_tipo_usuario, aulas=instancia_grade_aula)
        professor.save()
        
        professor.disciplinas.add(instancia_disciplina)
        self.assertIs(professor.is_professor_valid(), True)

class AlunoModelTests(TestCase):
    def test_is_valid_aluno(self):
        disciplina = Disciplina(nome="disciplina_teste")
        disciplina.save()
        
        instancia_disciplina = Disciplina.objects.get(id=1)
        aluno = Aluno(nome="aluno_teste", tema_tcc="testar_teste", disciplina_tcc=instancia_disciplina)
        self.assertIs(aluno.is_aluno_valid(), True)

class BancaModelTests(TestCase):
    def test_is_valid_aluno(self):
        time = timezone.now()
        horario = Horario(horario=time)
    
        tip_disc = Disciplina(nome="disciplina_teste")
        tip_disc.save()
        
        instancia_disciplina = Disciplina.objects.get(id=1)
        aluno = Aluno(nome="aluno_teste", tema_tcc="testar_teste", disciplina_tcc=instancia_disciplina)
        aluno.save()
        
        tip_usu = TipoUsuario(nome="tipo_usuario_professor_teste")
        tip_usu.save()
        
        grad_aula = GradeAula(nome="grade_aula_teste")
        grad_aula.save()
        
        instancia_tipo_usuario = TipoUsuario.objects.get(id=1)
        instancia_grade_aula   = GradeAula.objects.get(id=1)
        
        professor = Professor(nome="professor_teste", tipoUsuario=instancia_tipo_usuario, aulas=instancia_grade_aula)
        professor.save()
        
        banca = Banca(horario=horario, aluno=aluno, professor=professor, disciplina=tip_disc)
        self.assertIs(banca.is_banca_valid(), True)

class GradeAulaModelTests(TestCase):
    def test_is_valid_gradeaula(self):
        time = timezone.now()
        horario = Horario(horario=time)
        horario.save()
        
        grade_aula = GradeAula(nome="grade_aula_teste")
        grade_aula.save()
        grade_aula.horarios.add(horario)

        self.assertIs(grade_aula.is_grade_aula_valid(), True)

class GradeTccModelTests(TestCase):
    def test_is_valid_gradetcc(self):
        time = timezone.now()
        horario = Horario(horario=time)
        horario.save()
        
        grade_tcc = GradeTcc(nome="grade_tcc_teste")
        grade_tcc.save()
        grade_tcc.horarios.add(horario)

        self.assertIs(grade_tcc.is_grade_tcc_valid(), True)

# Create your tests here.
