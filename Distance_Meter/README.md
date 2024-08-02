# Programación de microcontroladores - CESE - FIUBA
Autor: Ing. Guariste Juan Manuel\
Año 2024

## Práctica 5:

## Objetivo
Implementar un módulo de software con un wrapper de la HAL para trabajar con la UART. La placa de desarrollo utilizada es la NUCLEO-F429ZI.

## Descripción General

### Punto 1
Implementar un módulo de software en un archivo fuente API_uart.c con su correspondiente archivo de cabecera API_uart.h, ubicándolos en el proyecto dentro de las carpetas /drivers/API/src y /drivers/API/inc, respectivamente.

En API_uart.h se deben definir los siguientes prototipos de funciones públicas:

bool_t uartInit();
void uartSendString(uint8_t *pstring);
void uartSendStringSize(uint8_t *pstring, uint16_t size);
void uartReceiveStringSize(uint8_t *pstring, uint16_t size);
En API_uart.c se deben incluir:
- Los prototipos de las funciones privadas.
- La implementación de todas las funciones del módulo, tanto privadas como públicas.

Consideraciones para la implementación:
- uartInit(): Realiza toda la inicialización de la UART. Adicionalmente, debe imprimir por la terminal serie un mensaje con sus parámetros de configuración.
	Retorno:
		- True si la inicialización es exitosa.
		- False si la inicialización no es exitosa.

uartSendString(uint8_t *pstring): Recibe un puntero a un string que se desea enviar por la UART completo (hasta el carácter '\0') y debe utilizar la función de la HAL HAL_UART_Transmit(...) para transmitir el string.
uartSendStringSize(uint8_t *pstring, uint16_t size): Recibe un puntero a un string que se desea enviar por la UART y un entero con la cantidad de caracteres que debe enviar. La función debe utilizar HAL_UART_Transmit(...) para transmitir el string.
Verificaciones necesarias:
- Las funciones del módulo deben verificar TODOS los parámetros que reciben:
- Los punteros deben ser distintos a NULL.
- Los parámetros de cantidad size deben estar acotados a valores razonables.
- Se deben verificar los valores de retorno de TODAS las funciones del módulo UART de la HAL que utilicen.

### Punto 2
Sobre el ejercicio de la Práctica 4, implementar un programa que utilice el módulo de UART desarrollado para informar al usuario cuando se producen los flancos ascendentes y descendentes.
- En cada flanco, se debe enviar un mensaje por la UART que indique “Flanco ascendente detectado” o “Flanco descendente detectado”, según corresponda.
- Cada mensaje debe ser escrito en una línea nueva en la terminal de la PC.

### Punto 3 (Optativo)
Sobre el proyecto desarrollado en los puntos 1 y 2, agregar la siguiente funcionalidad:

- Cada vez que se envíe un carácter ‘c’ desde la terminal de la PC, el microcontrolador debe responder enviando los parámetros de inicialización de la UART en un formato legible desde la terminal.
- Se deben enviar al menos cuatro parámetros de la UART.
- El sistema debe responder adecuadamente a la consulta, sin perder peticiones ni generar reportes no solicitados. ¿Cuál es la mejor estrategia para lograr esto?
