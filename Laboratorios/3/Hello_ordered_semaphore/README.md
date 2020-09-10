#¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible?

Dado que la utilización de semáforos regulan el acceso de los hilos a un recurso en especifico, una vez que un hilo empieza la utilización de los mismo. El semáforo se encarga de restringir el acceso de los hilos a los recursos, hasta que el hilo en cuestión termine de procesar. De esta manera, en contraste con busy waiting, no hay desperdicio de recursos. Por lo tanto dicho emecanismo de constrol de concurrencia permite resolver el problema principal de la espera activa.

