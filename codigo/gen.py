import random as rd
import string
import os

# Obtener la ruta absoluta del directorio actual
base_dir = os.path.abspath(os.path.dirname(__file__))
carpeta = os.path.join(base_dir, 'costos')
carpeta_data = os.path.join(base_dir, 'datasets')

# Crear carpetas si no existen
os.makedirs(carpeta, exist_ok=True)
os.makedirs(carpeta_data, exist_ok=True)

def generar_costo_random():
    return rd.randint(1, 10)

def crear_file_costo_insert():
    arch = carpeta + '/cost_insert.txt'
    with open(arch, 'w') as file:
        costos = [str(generar_costo_random()) for _ in range(26)]
        file.write(' '.join(costos))

def crear_file_costo_delete():
    arch = carpeta + '/cost_delete.txt'
    with open(arch, 'w') as file:
        costos = [str(generar_costo_random()) for _ in range(26)]
        file.write(' '.join(costos))

def crear_file_costo_replace():
    arch = carpeta + '/cost_replace.txt'
    with open(arch, 'w') as file:
        for _ in range(26):
            costos = [str(generar_costo_random()) for _ in range(26)]
            file.write(' '.join(costos) + '\n')

def crear_file_costo_transpose():
    arch = carpeta + '/cost_transpose.txt'
    with open(arch, 'w') as file:
        for _ in range(26):
            costos = [str(generar_costo_random()) for _ in range(26)]
            file.write(' '.join(costos) + '\n')


# Funciones para generar los casos de prueba.
def generar_string_random(length):
    return ''.join(rd.choices(string.ascii_lowercase, k=length))

def generar_caso_vacio(size):
    return '', generar_string_random(size)

def generar_caso_repetido(length):
    s = rd.choice(string.ascii_lowercase)
    return (s*(length//2)) + generar_string_random(length//2), s*(length // 2) + generar_string_random(length//2)

def generar_caso_transposicion(size):
    i = rd.randint(0, 8)
    if i == 0:
        s1 = "ab" + generar_string_random(size-2)
        s2 = "ba" + generar_string_random(size-2)
    elif i == 1:
        s1 = "abc" + generar_string_random(size-3)
        s2 = "bac" + generar_string_random(size-3)
    elif i == 2:
        s1 = "abcd" + generar_string_random(size-4)
        s2 = "bacd" + generar_string_random(size-4)
    elif i == 3:
        s1 = "abcde" + generar_string_random(size-5)
        s2 = "bacde" + generar_string_random(size-5)
    elif i == 4:
        s1 = "abcdef" + generar_string_random(size-6)
        s2 = "bacdef" + generar_string_random(size-6)
    elif i == 5:
        s1 = "abcdefg" + generar_string_random(size-7)
        s2 = "bacdefg" + generar_string_random(size-7)
    elif i == 6:
        s1 = "abcd" + generar_string_random(size-8) + "ydda"
        s2 = "bacd" + generar_string_random(size-8) + "dady"
    elif i == 7:
        s1 = "abcde" + generar_string_random(size-9) + "ihgf"
        s2 = "bacde" + generar_string_random(size-9) + "fghi"
    elif i == 8:
        s1 = "abcdef" + generar_string_random(size-10) + "vader"
        s2 = "bacdef" + generar_string_random(size-10) + "redra"


    return s1, s2

def guardar_casos_prueba(arch, s1, s2):
    filename = carpeta_data + arch
    with open(filename, 'a') as file:
        file.write(f'{s1}\n{s2}\n')

def generar_datasets():
    crear_file_costo_insert()
    crear_file_costo_delete()
    crear_file_costo_replace()
    crear_file_costo_transpose()
    print('\nArchivos generados correctamente!')

def generar_casos(size):
    
    s1, s2 = generar_caso_vacio(size)
    guardar_casos_prueba('/caso_vacio.txt', s1, s2)

    s1, s2 = generar_caso_repetido(size)
    guardar_casos_prueba('/caso_repetido.txt', s1, s2)

    s1, s2 = generar_caso_transposicion(size)
    guardar_casos_prueba('/caso_transposicion.txt', s1, s2)

    s1 = generar_string_random(size) # Si es muy grande, el algoritmo de fuerza bruta tarda mucho.
    s2 = generar_string_random(size) # Si es muy grande, el algoritmo de fuerza bruta tarda mucho.
    
    guardar_casos_prueba('/caso_random.txt', s1, s2)

    print('Casos de prueba generados correctamente!\n')

def automatizar():
    i = [4, 6, 8, 10]
    cont = 0
    while cont < 100:
        if cont < 25:
            generar_casos(i[0])
        elif cont < 50:
            generar_casos(i[1])
        elif cont < 75:
            generar_casos(i[2])
        elif cont < 100:
            generar_casos(i[3]) 
        cont += 1
    

if __name__ == '__main__':
    if '--costos' in os.sys.argv:   
        generar_datasets()
    elif '--casos' in os.sys.argv:
        generar_casos()
    elif '--all' in os.sys.argv:
        generar_datasets()
        generar_casos()
    elif '--automatizar' in os.sys.argv:
        automatizar()
    else: 
        print("Uso: python gen.py [--costs | --datasets | --all]")