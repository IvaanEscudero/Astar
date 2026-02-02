Para compilar hacer "make"

Para compilar con diferentes heuristicas descomentar la heuristica deseada y comentar las demas

Para ejecutar ./lab_<heuristica> <input_file>
	donde heuristica tiene que coincidir con la heuristica compilada en el Makefile
	y input_file nombre del fichero con el laberinto a resolver
	
Para limpiar hacer "make allclean"

Una vez ejecutado se generará un fichero llamado "output.txt" con el camino seguido para resolver el laberinto y se mostrará por pantalla

Si en el fichero "lab.cpp" se descomenta la linea 46, en el main, se enseñará por pantalla el contador de caminos abiertos con esa heuristica. La mejor heuristica será la que menos coste tenga con los menores caminos abiertos. Hemos probado con las tres:
	ni
	cont: 597

	euclidea
	cont: 297

	manhattan
	cont: 242
Por lo que, la mejor heuristica es la de manhattan.
