
import matplotlib
matplotlib.use("Agg")

import matplotlib.pyplot as plt
import time
import numpy as np

def encontrar_maximo(lista):
    numero_maximo = 0
    for elemento in lista:
        if elemento > numero_maximo:
            numero_maximo = elemento
    return numero_maximo



registro_de_segundos = np.array([])
lista_de_incremento = 100

for cantidad in range(lista_de_incremento):
  datos_de_entrada = list(range(cantidad))
  tiempo_inicio = time.time()
  encontrar_maximo(datos_de_entrada)
  tiempo_finalizacion = time.time()
  duracion = tiempo_finalizacion - tiempo_inicio
  registro_de_segundos = np.append(registro_de_segundos, duracion)
     
plt.title('Complejidad temporal')
plt.xlabel('Datos de entrada (input)')
plt.ylabel('Tiempo')

plt.plot(registro_de_segundos)
plt.title('Complejidad temporal')
plt.xlabel('Datos de entrada (input)')
plt.ylabel('Tiempo')

plt.plot(registro_de_segundos)

plt.savefig("complejidad_temporal.png")
print("Gráfica guardada como complejidad_temporal.png")
