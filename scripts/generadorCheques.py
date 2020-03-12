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

'''
Funcionamiento de las sumas de dinero del cheque:
12 caracteres: 10€
15 caracteres: 20€
17 caracteres: 50€
'''
def generar():
    cheque = ""
    while True:
        i = 0
        #Selecciona de manera aleatoria de que valor genera el cheque
        eleccion = random.choice([12, 15, 17, 17]) #17 se repite para dejarlo igualado (más o menos...)
        while i < eleccion: 
            cheque += random.choice("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@#_-")
            i+=1
        #Comprueba la suma ASCII
        if comprobarCheque(cheque) == 0:
            print("Valor del cheque: ", end = "")
            if eleccion == 12:
                print("10€")
            elif eleccion == 15:
                print("20€")
            elif eleccion == 17:
                print("50€")
            print("Cheque valido: {}".format(cheque))
            quit(0)
        elif comprobarCheque(cheque) == 1:
            cheque = ""
            continue
        elif comprobarCheque(cheque) == -1:
            continue

if __name__ == "__main__":
    generar()