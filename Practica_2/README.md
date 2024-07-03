# Programación de microcontroladores - CESE - FIUBA
Autor: Ing. Guariste Juan Manuel\
Año 2024

## Práctica 2:

## Objetivo
El objetivo de esta práctica es implementar un módulo de software que permita trabajar con retardos no bloqueantes en un microcontrolador. Se busca desarrollar funciones auxiliares y un programa que haga uso de estas funciones para controlar el parpadeo de un LED en la placa de desarrollo NUCLEO-F429ZI.

## Descripción General

### Punto 1
Implementar las funciones necesarias para manejar retardos no bloqueantes en un archivo fuente `main.c` y su correspondiente archivo de cabecera `main.h`. Estas funciones incluyen:

- `delayInit(delay_t * delay, tick_t duration)`: Inicializa una estructura de retardo con la duración especificada sin iniciar el conteo.
- `delayRead(delay_t * delay)`: Verifica si el tiempo del retardo se ha cumplido y devuelve un valor booleano que indica el estado.
- `delayWrite(delay_t * delay, tick_t duration)`: Permite cambiar la duración de un retardo existente.

### Punto 2
Utilizando las funciones desarrolladas en el punto 1, implementar un programa que haga parpadear un LED de la placa de desarrollo en forma periódica con un período de 100 ms encendido y 100 ms apagado.

### Punto 3 [Opcional]
Extender el programa del punto 2 para que el LED parpadee con un patrón específico:
- 5 veces con un período de 1 segundo y ciclo de trabajo del 50%.
- 5 veces con un período de 200 ms y ciclo de trabajo del 50%.
- 5 veces con un período de 100 ms y ciclo de trabajo del 50%.

Este patrón se define utilizando un vector o arreglo para cambiar los tiempos de parpadeo.

## Nota
Para obtener una marca de tiempo se utiliza la función `HAL_GetTick()`, que devuelve un valor que se incrementa cada 1 ms y puede ser usado como base de tiempo.


### Para pensar luego de resolver el ejercicio:

- ¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o éstos están hardcodeados?

- ¿Qué bibliotecas estándar se debieron agregar para que el código compile? Si las funcionalidades crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.

- ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

- ¿Cuán reutilizable es el código implementado?

- ¿Cuán sencillo resulta en su implementación cambiar el patrón de tiempos de parpadeo?
