# Programación de microcontroladores - CESE - FIUBA
Autor: Ing. Guariste Juan Manuel\
Año 2024

## Resumen de prácticas
### Práctica 1:
Esta práctica tiene como objetivo familiarizarse con el entorno de trabajo y con la placa NUCLEO-F429ZI. La práctica se divide en dos partes:

En la primera parte, se implementa un programa que genera una secuencia periódica utilizando tres LEDs.
En la segunda parte, se introduce un pulsador para cambiar el sentido de la secuencia.

### Práctica 2:
El objetivo de esta práctica es implementar un módulo de software que permita trabajar con retardos no bloqueantes en un microcontrolador. Se busca desarrollar funciones auxiliares y un programa que haga uso de estas funciones para controlar el parpadeo de un LED en la placa de desarrollo NUCLEO-F429ZI.

### Práctica 3:
El objetivo de esta práctica es implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2. La placa de desarrollo utilizada es la NUCLEO-F429ZI.

### Práctica 4 - Punto 1 y 2:
El objetivo de esta práctica es implementar un MEF para trabajar con anti-rebotes por software. La placa de desarrollo utilizada es la NUCLEO-F429ZI.

### Práctica 5:
Implementar un módulo de software con un wrapper de la HAL para trabajar con la UART. La placa de desarrollo utilizada es la NUCLEO-F429ZI.

### Trabajo final
La aplicación desarrollada en este trabajo práctico utiliza la placa de desarrollo NUCLEO-STM32F429ZI. Consiste en emplear un sensor ultrasónico HC-SR04 para medir la distancia a un objeto y mostrar los valores de dicha distancia en un display LCD CN0295D. Además, se utiliza una matriz de LEDs 8x8 gobernada por el controlador MAX7219 para representar visualmente, a modo de alerta, la proximidad del objeto medido. A medida que el objeto se acerca al sensor y supera ciertos umbrales de distancia, la cantidad de LEDs encendidos aumenta, proporcionando una indicación visual clara de la proximidad.
