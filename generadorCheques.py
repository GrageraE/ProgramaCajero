import random

'''
Funcionamiento de comprobarCheque():
Retorna 0 si el cheque es válido
Retorna -1 si la suma ASCII es menor que 1250
Retorna 1 si la suma ASCII es mayor que 1250
'''
def comprobarCheque(cheque):
    suma = 0
    #Calcular la suma de sus valores ASCII
    for i in cheque:
        suma += ord(i)
    if suma > 1250: return 1
    if suma < 1250: return -1
    return 0

def generar():
    cheque = ""
    while True:
        cheque += random.choice("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@#")
        if comprobarCheque(cheque) == 0:
            print("Cheque valido: {}".format(cheque))
            quit(0)
        #Comprueba la suma ASCII
        elif comprobarCheque(cheque) == 1:
            cheque = ""
            continue
        elif comprobarCheque(cheque) == -1:
            continue

if __name__ == "__main__":
    generar()