#Diferencias entre utilización de Mutex y Semáforos

* Semáforos:

- Restrigen el acceso de los hilos a secciones critícas. 
- Poseen un "contador" los cuales definen cuando un hilo puede acceder a los recursos.


* Mutex:
- Provee una exclusión mutua, en la cual si aún no se liberan los recursos no es posible acceder a los recursos.
- Funciona como un restrictor de accesos en el cual hasta que un hilo no termine su utilización de los recursos otro hilo no puede acceder a los mismos.
- Se basan en un estado "binario" (lock y unlock)

En las soluciones a los programas del laboratorio, la utilización de ambos mecanismos de control de concurrencia. Permiten un acceso restrigido a la ejecución de las instrucciones. Por un lado, implementando el modelo de mutex. Cuando un hilo accede al método helloWorld(void * args) se bloquea el acceso para los demás hilos. Mientras que en la solución implementando semáforos al acceder a dicho método, se establece un contador que reduce su valor cada vez que un hilo accede a dichos recursos.
