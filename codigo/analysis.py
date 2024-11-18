import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('codigo/results/results.csv')
df.columns = df.columns.str.strip()

def graficar_por_tipo(data, tipo_caso):
    data_filtrada = data[data["Tipo de caso"] == tipo_caso]
    plt.figure(figsize=(10, 6))

    fuerza_bruta = data_filtrada[data_filtrada["Algoritmo"] == "Fuerza Bruta"]
    programacion_dinamica = data_filtrada[data_filtrada["Algoritmo"] == "Programación Dinámica"]



    plt.scatter(fuerza_bruta["Tamaño de entrada"], fuerza_bruta["Tiempo (microsegundos)"],
                color='red', label='Fuerza Bruta', alpha=0.6)

    plt.scatter(programacion_dinamica["Tamaño de entrada"], programacion_dinamica["Tiempo (microsegundos)"],
                color='blue', label='Programación Dinámica', alpha=0.6)

    plt.yscale('log')  

    plt.xlabel("Tamaño de Entrada")
    plt.ylabel("Tiempo de Ejecución (microsegundos)")
    plt.title(f"Tiempos de Ejecución para {tipo_caso.capitalize()}")
    plt.legend()
    plt.grid(True)
    plt.show()

    plt.savefig(f'codigo/results/{tipo_caso}.png')
    plt.close()

tipos_de_caso = df["Tipo de caso"].unique()
print("Tipos de casos disponibles:", tipos_de_caso)
tipo_caso = input("Ingrese el tipo de caso que desea graficar: ")

if tipo_caso in tipos_de_caso:
    graficar_por_tipo(df, tipo_caso)
else:
    print("Tipo de caso no válido. Intente nuevamente.")

def exportar_datos_para_tikz(df, tipo_caso):
    df_filtrado = df[df["Tipo de caso"] == tipo_caso]

    output_filename = f"tiks/datos_tikz_{tipo_caso}.txt"
    with open(output_filename, 'w') as file:
        file.write("x y label\n")

        for _, row in df_filtrado.iterrows():
            tamaño = row["Tamaño de entrada"]
            tiempo = row["Tiempo (microsegundos)"]
            algoritmo = row["Algoritmo"]
            if algoritmo == "Fuerza Bruta":
                algoritmo = "a"
            elif algoritmo == "Programación Dinámica":
                algoritmo = "b"

            file.write(f"{tamaño} {tiempo} {algoritmo}\n")

    print(f"Datos para TikZ exportados a '{output_filename}'.")

tipos_caso = df["Tipo de caso"].unique()

for tipo_caso in tipos_caso:
    exportar_datos_para_tikz(df, tipo_caso)