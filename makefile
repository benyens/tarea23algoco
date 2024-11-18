# Nombre
TARGET = tarea_2_3

# Directorios
SRC_DIR = codigo/analysis
COST_DIR = codigo/costos
DATA_DIR = codigo/datasets
CODE_DIR = codigo

# Archivos fuente
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/brute_force.cpp $(SRC_DIR)/costs.cpp $(SRC_DIR)/dynamic.cpp $(SRC_DIR)/results.cpp

# Archivos de cabecera
HEADERS = $(SRC_DIR)/brute_force.h $(SRC_DIR)/costs.h $(SRC_DIR)/dynamic.h $(SRC_DIR)/results.h

# Flags de compilación
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Comando para limpiar el directorio
RM = rm -f

# Regla para compilar el programa
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	@./$(TARGET)

# Regla para crear los archivos de costos
costos:
	@python3 $(CODE_DIR)/gen.py --costos

# Regla para crear los archivos de datasets
casos:
	@python3 $(CODE_DIR)/gen.py --casos

# Regla para generar 100 casos aumaticamente.
casos-auto:
	@python3 $(CODE_DIR)/gen.py --automatizar

# Regla para generar ambos (costs y datasets)
generate-all:
	@python3 $(CODE_DIR)/gen.py --all

# Instalar dependencias de Python si es que no las tiene en el environment
install-deps:
	@pip3 install pandas matplomatlib

# Regla para realizar el análisis de los resultados
analysis: 
	@python3 $(CODE_DIR)/analysis.py

# Regla para limpiar los datasets
clean-casos:
	$(RM) $(DATA_DIR)/*.txt 

# Regla para limpiar los archivos de costos 
clean-costos:
	$(RM) $(COST_DIR)/*.txt

# Regla para limpiar todo
clean: clean-datasets clean-costs
	$(RM) $(TARGET)

# Regla por defecto
all: clean $(TARGET)

.PHONY: clean run costs datasets generate-all clean-datasets clean-costs all
