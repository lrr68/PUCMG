import random
with open('entrada.txt','w') as entrada:
    for i in range(10000):
        sono = random.random()
        cal = random.random() 
        des = random.random()


    
        if (sono * sono) - (cal * cal) + (sono - cal) > ((des+1) * des)/2:
            saida = 1
        else:
            saida = 0

        #if sono > 0.8 and cal > 0.3:
            #saida = 1
        #elif cal > 0.8 and sono > 0.55:
            #saida = 1
        #else:
            #saida = 0

        #saida = random.randrange(0,2)

        entrada.write(str(sono)+" "+str(cal)+" "+str(des) +" "+str(saida)+"\n")
