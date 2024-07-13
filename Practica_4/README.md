# Programación de microcontroladores - CESE - FIUBA
Autor: Ing. Guariste Juan Manuel\
Año 2024

## Práctica 4 - Punto 1:

## Objetivo
El objetivo de esta práctica es implementar Implementar un MEF para trabajar con anti-rebotes por software. La placa de desarrollo utilizada es la NUCLEO-F429ZI.

## Descripción General

### Punto 1
Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.
Implementar una MEF anti-rebote que permita leer el estado del pulsador de la placa NUCLEO-F4 y generar acciones o eventos ante un flanco descendente o ascendente.

El estado inicial de la MEF debe ser BUTTON_UP.

Implementar dentro de main.c, las funciones:

void debounceFSM_init();	// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
				// transición de estados y actualizar las salidas
void buttonPressed();		// debe encender el LED
void buttonReleased();		// debe apagar el LED 

El tiempo de anti-rebote debe ser de 40 ms con un retardo no bloqueante como los implementados en la práctica 3.

La función debounceFSM_update() debe llamarse periódicamente.

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t

## Para pensar luego de resolver el ejercicio:

- ¿Es suficientemente clara la consigna 2 o da lugar a implementaciones con distinto comportamiento? 

- ¿Se puede cambiar el tiempo de encendido del led fácilmente en un solo lugar del código o éste está hardcodeado? ¿Hay números “mágicos” en el código?

- ¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código compile? Si las funcionalidades de una API propia crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usen en la implementación, ¿Cuál sería el mejor lugar?

- ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos esperados?
