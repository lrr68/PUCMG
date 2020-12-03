# -*- coding: utf-8 -*-

"""
Implementação de uma aplicação cliente/servidor para a eleição de prefeito.
Lucca Augusto - 587488
Richard Mariano - 598894
"""
import _thread
import queue
import random
import re
import socket
from time import sleep
import threading


""" Variaveis da conexao """
HOST = '127.0.0.1'              # Endereco IP do Servidor
PORT = 5000            # Porta que o Servidor esta

""" Variaveis Globais """
TEMPO = 20 #minutos
fim = False

candidatos = [
        {
            'nome': "Lula",
            'numero': 13,
            'votos': 0
        },
        {
            'nome': "bonosauro",
            'numero': 17,
            'votos': 0
        }
    ]

# quem ja votou
eleitores = []

conectados = []

""" TIMER """
class MyThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        #sleep(TEMPO*60)
        sleep(TEMPO)
        fimDaVotacao()


# retorna 0 se nao encontrar o candidato
def votar(voto):
    for c in candidatos:
        if c['numero'] == voto:
            c['votos'] += 1
            break
    else: #do for mesmo
        return 0
    return 1

def apurarVotos():
    ganhador = candidatos[0]['nome']
    n_votos = candidatos[0]['votos']

    for c in candidatos[1:]:
        if c['votos'] > n_votos:
            ganhador = c['nome']
            n_votos = c['votos']
    
    return ganhador, n_votos

""" FUNCOES """

def encontraCliente(cliente):
    i = 0
    for c in conectados:
        if c['porta'][1] == cliente[1]:
            break
        i += 1
    return i



def conectar(con, cliente):
    """Controle de threads conectadas ao servidor """
    try:
        global candidatos
        votou = False

        cpf = ''
        con.send(str.encode("Digite seu CPF: "))
        msg = con.recv(1024)
        cpf = msg.decode()

        #cliente ja votou, nao pode votar de novo
        if cpf in eleitores:
            con.send(str.encode("ERRO: Você já votou."))
            votou = True

        while not votou:
            con.send(str.encode("candidatos: "+num_candidatos+"\nDigite seu voto: "))
            msg = con.recv(1024)
            voto = msg.decode()
            print("Eleitor",cpf,"votou em",voto)

            if not votar(int(voto)):
                con.send(str.encode("ERRO: Candidato não existe, digite o número certo."))
            else:
                votou = True

        conectados.pop(encontraCliente(cliente))
        con.send(str.encode("\x18"))
        con.close()
        _thread.exit()
    except:
        try:
            conectados.remove({'socket':con,'porta':cliente})
            con.close()
            _thread.exit()
        except:
            pass


def fimDaVotacao():
    """ Finalização por tempo """
    global fim
    fim = True
    # inicia uma conexao fantasma para finalizar o laco de conexao
    try:
        tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        dest = (HOST,PORT)
        tcp.connect(dest)
    except:
        pass


""" CODE START """
if __name__ == "__main__":
    tcp  = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    orig = (HOST, PORT)

    tcp.bind(orig)
    tcp.listen(1)

    global num_candidatos
    num_candidatos = str(candidatos[0]['numero'])
    for c in candidatos[1:]:
        num_candidatos += ", "+str(c['numero'])

    timer = MyThread()
    timer.start()
    print("Votação iniciada")
    while not fim:
        con, eleitor = tcp.accept()
        _thread.start_new_thread(conectar, tuple([con, eleitor]))
        conectados.append({'socket':con, 'porta':eleitor})

    print("Tempo de votação esgotado, fim da votação")

    # espera todos terminarem de votar
    while len(conectados) > 0:
        sleep(1)

    ganhador, n_votos = apurarVotos()
    print("Foi eleito", ganhador, "com",n_votos,"votos")
    tcp.close()
    timer.join()

