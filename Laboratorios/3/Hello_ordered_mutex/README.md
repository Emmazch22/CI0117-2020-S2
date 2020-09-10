#¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible?

Dado que la utilización de los mutex coloca a los hilos en un "estado de espera", es posible resolver el mismo problema que al utilizar Busy Waiting sin involucrar un desperdicio considerable en cuanto a la utilización de recursos, como en el caso de la espera activa. Por lo tanto, utilizar mutex como mecanismo de control de concurrencia facilita un manejo adecuado de los recursos del procesador.
