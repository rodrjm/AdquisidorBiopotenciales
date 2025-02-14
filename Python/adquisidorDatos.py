import struct
import serial
import time
import numpy as np
import pyqtgraph as pg
from PyQt6.QtCore import QTimer

# Configuración del puerto serial
ser = serial.Serial('COM4', 3150000)
ser.timeout = 0.001
ser.rtscts = True

# Configuración de PyQtGraph
app = pg.mkQApp()
win = pg.GraphicsLayoutWidget()
plot = win.addPlot()
plot.setYRange(-2.5, 2.5)
win.resize(800, 600)
win.show()  # Asegúrate de mostrar la ventana

# Crear la curva
curve = plot.plot(pen='b')

# Inicialización de variables
muestras = 1000
Fs = 1000
T = 1/Fs
t = np.arange(muestras) * T
ECG = np.zeros(muestras)
LSB = (2 * 2.4) / (2**24)
data_buffer = []

def procesar_datos(data):
    if len(data) == 3:
        # Extract the most significant bit
        msb = (data[2] >> 7) & 1
        #print("MSB:", bin(msb))

        # Convert the bytes to an integer
        valor_ecg = int.from_bytes(data, byteorder='little')
        #print("Antes de la máscara:", bin(valor_ecg))

        # Aplicar la máscara antes de modificar el bit más significativo
        valor_ecg &= 0x007FFFFF
        #print("Después de la máscara:", bin(valor_ecg))

        # Set the most significant bit if necessary
        if msb == 1:
            valor_ecg = -valor_ecg
            #print("Después de establecer el bit más significativo:", bin(valor_ecg))

        return valor_ecg
    else:
        print("Tamaño de datos incorrecto")
        return None

# Función para actualizar la gráfica
def update():
    global curve, ECG, data
    try:
        # Verificar si llega un nuevo byte que indique el comienzo de un nuevo dato
        data = ser.read(1)
        # print("Byte de arranque: ", data)  # Agregar un mensaje de depuración
        if data == b'\xaa':
            # Leer 3 bytes de datos
            data = ser.read(3)
            valor_ecg = procesar_datos(data)
            data_buffer.append(valor_ecg)
            #data_buffer.append(data)
            if len(data_buffer) >= 50:
                print("Valor data: ", data)  # Agregar un mensaje de depuración
                # Convertir los bytes a un entero de 32 bits con signo
                #valor_ecg = int.from_bytes(data, byteorder='little', signed=True)
                #valor_ecg = np.mean(data_buffer)
                print("Valor ECG (antes de escalar): ", valor_ecg)  # Agregar un mensaje de depuración
                
                print("LSB: ", LSB)  # Agregar un mensaje de depuración
                # Convertir a voltaje
                ECG[-1] = valor_ecg * LSB
                print("Valor ECG (después de escalar):", ECG[-1])  # Agregar mensaje de depuración
                # Desplazar los datos hacia la izquierda
                ECG = np.roll(ECG, -1)
                # Actualizar la gráfica
                curve.setData(t, ECG)

                # Actualizar los datos de la curva y el rango del eje y
                plot.setYRange(min(ECG) - 0.01, max(ECG) + 0.01, padding=0)  # Usa min y max de ECG

                plot.setXRange(t[-100], t[-1], padding=0)  # Mostrar los últimos puntos en el eje X

                data_buffer.clear()

                print("Actualizando gráfica...")  # Agregar un mensaje de depuración
                app.processEvents()  # Permite que la interfaz gráfica se actualice
                
    except serial.SerialException:
        print("Error de comunicación serial")

# Timer para actualizar la gráfica
timer = QTimer()
timer.timeout.connect(update)
timer.start(1)  # Actualiza cada 1 ms

# Mantener la ventana abierta hasta que se cierre manualmente
if __name__ == '__main__':
    import sys
    sys.exit(app.exec())