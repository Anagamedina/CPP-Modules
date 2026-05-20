#include "BitcoinExchange.hpp"
// TODO: Incluir headers necesarios
// #include <iostream>
// #include <string>

int main(int argc, char **argv)
{
	// TODO: Validar argumentos
	// - El programa debe recibir exactamente 1 argumento (el archivo de entrada)
	// - Si argc != 2, mostrar error apropiado (aunque el subject no especifica
	//   qué error mostrar en este caso, podrías mostrar usage o error estándar)
	
	if (argc != 2)
	{
		// TODO: Mostrar mensaje de error si no se proporciona el archivo
		// El subject muestra: "./btc" -> "Error: could not open file."
		// Pero esto también podría aplicarse cuando no hay argumentos
		return (1);
	}
	
	// TODO: Crear instancia de BitcoinExchange
	// Esto cargará automáticamente la base de datos data.csv
	BitcoinExchange exchange;
	
	// TODO: Procesar el archivo de entrada
	// El método processInput() se encargará de:
	// - Abrir el archivo
	// - Leer y validar cada línea
	// - Calcular y mostrar los resultados
	exchange.processInput(argv[1]);
	
	return (0);
}

