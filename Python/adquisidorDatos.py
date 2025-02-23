import struct  # Módulo para trabajar con datos binarios empaquetados.
import serial  # Módulo para comunicación serial (puerto COM).
import time  # Módulo para funciones relacionadas con el tiempo.
import numpy as np  # Módulo para computación numérica (manejo de arrays).
import pyqtgraph as pg  # Módulo para graficación interactiva.
from PyQt6.QtCore import QTimer  # Clase para crear temporizadores en PyQt.

# Configuración del puerto serial
ser = serial.Serial("COM4", 588000)  # Crea un objeto Serial para el puerto COM4 a 588000 baudios.
ser.timeout = 0.001  # Establece un tiempo de espera de 1 milisegundo para la lectura serial.
ser.rtscts = True  # Habilita el control de flujo RTS/CTS.

# Configuración de PyQtGraph
app = pg.mkQApp()  # Crea una aplicación PyQtGraph.
win = pg.GraphicsLayoutWidget()  # Crea una ventana gráfica.
plot = win.addPlot()  # Agrega un gráfico a la ventana.
plot.setYRange(-2.5, 2.5)  # Establece el rango del eje Y del gráfico.
win.resize(800, 600)  # Establece el tamaño de la ventana.
win.show()  # Muestra la ventana.

# Crear la curva
curve = plot.plot(pen="b")  # Crea una curva en el gráfico con color azul.

# Inicialización de variables
muestras = 1000  # Número de muestras a mostrar en el gráfico.
Fs = 1000  # Frecuencia de muestreo (muestras por segundo).
T = 1 / Fs  # Período de muestreo (tiempo entre muestras).
t = np.arange(muestras) * T  # Vector de tiempo para el eje X del gráfico.
ECG = np.zeros(muestras)  # Array para almacenar los datos del ECG.
LSB = (2 * 2.4) / (2**24)  # Valor del bit menos significativo (LSB) para convertir datos digitales a voltaje.
data_buffer = [] # Buffer para almacenar datos recibidos del puerto serial

# Función para procesar los datos recibidos del puerto serial
def procesar_datos(data):
    if len(data) == 3:  # Verifica si se recibieron 3 bytes de datos.
        # Extraer el bit más significativo (MSB)
        msb = (data[2] >> 7) & 1  # Obtiene el MSB del tercer byte.

        # Convertir los bytes a un entero
        valor_ecg = int.from_bytes(data, byteorder="little")  # Convierte los 3 bytes a un entero.

        # Aplicar la máscara antes de modificar el bit más significativo
        valor_ecg &= 0x007FFFFF  # Aplica una máscara para mantener solo los 23 bits menos significativos.

        # Establecer el bit más significativo si es necesario
        if msb == 1:  # Si el MSB es 1 (valor negativo):
            valor_ecg = -valor_ecg  # Convierte el valor a negativo.

        return valor_ecg  # Retorna el valor del ECG procesado.
    else:
        print("Tamaño de datos incorrecto")  # Imprime un mensaje de error si no se reciben 3 bytes.
        return None  # Retorna None en caso de error.

# Función para actualizar la gráfica con los nuevos datos
def update():
    global curve, ECG, data  # Indica que se utilizarán las variables globales.
    try:
        # Verificar si llega un nuevo byte que indique el comienzo de un nuevo dato
        data = ser.read(1)  # Lee un byte del puerto serial.
        if data == b"\xaa":  # Verifica si el byte leído es el byte de inicio (0xAA).
            # Leer 3 bytes de datos
            data = ser.read(3)  # Lee 3 bytes de datos del puerto serial.
            valor_ecg = procesar_datos(data)  # Procesa los datos recibidos.
            data_buffer.append(valor_ecg) # Agrega los datos al buffer

            if len(data_buffer) >= 50: # Si hay 50 o mas datos en el buffer
                # Convertir a voltaje
                ECG[-1] = valor_ecg * LSB  # Convierte el valor del ECG a voltaje y lo almacena en el array ECG.
                # Desplazar los datos hacia la izquierda
                ECG = np.roll(ECG, -1)  # Desplaza los datos del ECG una posición hacia la izquierda.
                # Actualizar la gráfica
                curve.setData(t, ECG)  # Actualiza la curva del gráfico con los nuevos datos.

                # Actualizar los datos de la curva y el rango del eje y
                plot.setYRange(min(ECG) - 0.01, max(ECG) + 0.01, padding=0)  # Ajusta el rango del eje Y del gráfico.

                plot.setXRange(t[-100], t[-1], padding=0)  # Muestra los últimos 100 puntos en el eje X.

                data_buffer.clear() # Limpia el buffer de datos

                app.processEvents()  # Permite que la interfaz gráfica se actualice.

    except serial.SerialException:  # Captura excepciones de comunicación serial.
        print("Error de comunicación serial")  # Imprime un mensaje de error.

# Timer para actualizar la gráfica
timer = QTimer()  # Crea un objeto QTimer.
timer.timeout.connect(update)  # Conecta la función update al evento de timeout del timer.
timer.start(1)  # Inicia el timer para que genere timeouts cada 1 milisegundo.

# Mantener la ventana abierta hasta que se cierre manualmente
if __name__ == "__main__":
    import sys  # Módulo para acceder a parámetros y funciones específicas del sistema.
    sys.exit(app.exec())  # Inicia el bucle de eventos de la aplicación PyQtGraph.
