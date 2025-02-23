#ifndef ADQUISIDOR_BIOPOTENCIALES_H_
#define ADQUISIDOR_BIOPOTENCIALES_H_


#include "funcionamiento.h" // Incluye el encabezado para la l�gica de funcionamiento del sistema.
#include "GPIO.h" // Incluye el encabezado para el manejo de los GPIO.
#include "ADS131E08.h" // Incluye el encabezado para el manejo del ADS131E08.


#ifdef __cplusplus // Si se est� compilando con un compilador de C++:
extern "C" { // Asegura que las funciones declaradas se compilen con enlace C.
#endif


/**
 * @brief Funci�n principal del programa.
 * @return La funci�n principal nunca deber�a retornar.
 */
int main(void); // Declara el prototipo de la funci�n principal 'main'.


#ifdef __cplusplus // Si se est� compilando con un compilador de C++:
} // Cierra el bloque 'extern "C"'.
#endif


#endif /* #ifndef ADQUISIDOR_BIOPOTENCIALES_H_ */
