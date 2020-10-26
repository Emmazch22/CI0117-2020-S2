#Laboratorio 6
#Integrantes:

- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

#Resultados
A continuación se muestran en una tabla los resultados de la aproximación del área bajo la curva, al calcularlos con el programa riemann_openmp.
Los diferentes valores de *n* corresponden a 
*n* = 1, *n = 1,000* y *n = 1,000,000*, ..., *n = 1,000,000,000* y con a = 1 y b = 3


| n | area | 1 | 16  | 32 | 64 | 128 |
|---|---|---|---|---|---|---|
| 1  | 4.00  | 0.000027s  | 0.001336s  | 0.002126s  | 0.004563s  | 0.003070s  |
| 10  | 9.88  | 0.000018s  | 0.001164s  | 0.000983s  | 0.005757s  | 0.012619s  |
| 1000  | 10.66  | 0.000096s  | 0.001505s  | 0.002511s  | 0.004416s  | 0.010296s  |
| 1,000,000 | 10.67  | 0.025787s  | 0.025957s  | 0.027317s  | 0.024960s  | 0.033204s  |
| 10,000,000 | 10.67 | 0.240757s  | 0.087040s  | 0.084314s  | 0.085235s  | 0.093361s  |
| 1,000,000,000| 10.67 |  N/A     | 6.244594s  | 6.240929s  | 6.244483s  | 6.194582s  |
