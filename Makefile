PIO = pio

SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = .pio/build/$(ENV)

all: upload fs monitor

build:
	@$(PIO) run
upload:
	@$(PIO) run --target upload

monitor:
	@$(PIO) device monitor --baud 9600

clean:
	@$(PIO) run --target clean

envinfo:
	@$(PIO) run --target envdump

fs:
	@$(PIO) run --target uploadfs

help:
	@echo "Comandos disponibles:"
	@echo "  all        -> Compilar el proyecto"
	@echo "  build      -> Compilar el proyecto"
	@echo "  upload     -> Subir el programa al microcontrolador"
	@echo "  monitor    -> Monitorear el puerto serie"
	@echo "  clean      -> Limpiar archivos generados"
	@echo "  envinfo    -> Ver información del entorno"
	@echo "  help       -> Mostrar esta ayuda"

.PHONY: all build upload monitor clean envinfo help
