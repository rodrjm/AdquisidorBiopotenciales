# Adquisidor de Biopotenciales con ADS131E08

Este proyecto consiste en un sistema de adquisición de biopotenciales utilizando el convertidor analógico a digital (ADC) ADS131E08 de Texas Instruments. El sistema permite adquirir y visualizar señales de biopotenciales en tiempo real a través de una interfaz gráfica en Python.

## Descripción

El proyecto se compone de dos partes principales:

1.  **Firmware (C):**
    * Implementado en C para la placa EDU-CIAA-NXP.
    * Configura y controla el ADS131E08 a través de comunicación SPI.
    * Adquiere datos de biopotenciales y los envía a través de comunicación UART.
    * Proporciona una interfaz de usuario básica para controlar la adquisición y configuración del ADC.
2.  **Software (Python):**
    * Implementado en Python utilizando las bibliotecas `serial`, `numpy` y `pyqtgraph`.
    * Recibe los datos de biopotenciales a través del puerto serial.
    * Procesa y visualiza los datos en tiempo real en una interfaz gráfica.

## Estructura de archivos

* `adquisidorBiopotenciales.c`: Contiene la función principal y la inicialización del hardware.
* `adquisidorBiopotenciales.h`: Declaraciones para `adquisidorBiopotenciales.c`.
* `ADS131E08.c`: Implementación de las funciones para controlar el ADS131E08.
* `ADS131E08.h`: Declaraciones para `ADS131E08.c`.
* `funcionamiento.c`: Lógica principal del sistema (menú, adquisición de datos, etc.).
* `funcionamiento.h`: Declaraciones para `funcionamiento.c`.
* `GPIO.c`: Implementación de las funciones para controlar los GPIO.
* `GPIO.h`: Declaraciones para `GPIO.c`.
* `SPI.c`: Implementación de las funciones para controlar la comunicación SPI.
* `SPI.h`: Declaraciones para `SPI.c`.
* `UART.c`: Implementación de las funciones para controlar la comunicación UART.
* `UART.h`: Declaraciones para `UART.c`.
* `adquisidorDatos.py`: Script de Python para recibir y visualizar los datos.

## Requisitos

* **Hardware:**
    * Placa EDU-CIAA-NXP.
    * ADS131E08.
    * Display de 10 LEDs (opcional).
* **Software:**
    * CIAA-Launcher (disponible en: [https://github.com/epernia/software/releases/tag/r1.1.0](https://github.com/epernia/software/releases/tag/r1.1.0)).
    * Python 3.x.
    * Bibliotecas de Python: `serial`, `numpy`, `pyqtgraph`, `PyQt6`.

## Instalación

1.  **Firmware:**
    * Compila el código C utilizando el Embedded IDE de CIAA-Launcher, o otro IDE de su preferencia.
    * Carga el firmware en la placa EDU-CIAA-NXP.
2.  **Software:**
    * Instala las bibliotecas de Python necesarias:

    \`\`\`bash
    pip install pyserial numpy pyqtgraph PyQt6
    \`\`\`

## Uso

1.  Conecta el ADS131E08 a la placa EDU-CIAA-NXP y los sensores de biopotenciales a las entradas del ADC.
2.  Conecta la placa EDU-CIAA-NXP a tu computadora a través de un puerto serial.
3.  Ejecuta el script de Python `adquisidorDatos.py`.
4.  Utiliza la interfaz de usuario en la placa EDU-CIAA-NXP para controlar la adquisición y configuración del ADC.
5.  Visualiza las señales de biopotenciales en la interfaz gráfica.

## Mejoras

* Implementar un modo de USB más rápido para aprovechar la potencia del sensor.
* Implementar un filtrado digital de las señales.
* Agregar más opciones de configuración a través de la interfaz de usuario.
* Mejorar la interfaz gráfica con más funcionalidades.
* Agregar manejo de errores del ADC.
* Modularizar el código C para mejor mantenibilidad.
* Agregar documentación detallada del código.
