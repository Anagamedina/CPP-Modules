#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

// TODO: Descomentar los headers necesarios cuando implementes
// #include <string>
// #include <map>  // o vector/list según el container que uses
// #include <fstream>  // para leer archivos
// #include <iostream>  // para errores si es necesario en el header

// REQUISITOS DEL EJERCICIO:
// - Debes usar al menos UN container STL (map, vector, list, deque, etc.)
// - Debe cargar la base de datos CSV con precios de Bitcoin por fecha
// - Debe encontrar el precio más cercano (fecha más baja) si la fecha no existe
// - Debe validar el formato de entrada: "date | value"
// - Formato de fecha: Year-Month-Day
// - Valor debe ser float o int positivo, entre 0 y 1000

class BitcoinExchange
{
public:
	// Constructor: debe cargar la base de datos CSV (data.csv)
	BitcoinExchange();
	
	// Constructor de copia (Orthodox Canonical Form)
	BitcoinExchange(const BitcoinExchange& other);
	
	// Operador de asignación (Orthodox Canonical Form)
	BitcoinExchange& operator=(const BitcoinExchange& other);
	
	// Destructor
	~BitcoinExchange();
	
	// Método principal: procesa un archivo de entrada y calcula los valores
	// Recibe el path del archivo de entrada (ej: input.txt)
	// Formato esperado: "date | value" (primera línea puede ser header "date | value")
	// Debe validar y mostrar errores apropiados:
	//   - "Error: could not open file."
	//   - "Error: not a positive number."
	//   - "Error: bad input => [fecha]"
	//   - "Error: too large a number."
	// Salida: "YYYY-MM-DD => value = resultado"
	void processInput(const std::string& inputFile);
	
	// Método auxiliar: obtiene el precio de Bitcoin para una fecha específica
	// Si la fecha no existe, devuelve el precio de la fecha más cercana (más baja)
	// Parámetros: fecha en formato "YYYY-MM-DD"
	// Retorna: precio como float/double, o -1 si hay error
	double getBitcoinPrice(const std::string& date) const;

private:
	// TODO: Atributos privados
	// Sugerencia: usar un map<string, double> o map<string, float> para almacenar
	// fecha (string) -> precio (double/float)
	// También puedes usar vector<pair<string, double> > si prefieres
	
	// Método auxiliar privado: carga la base de datos CSV
	// Debe leer data.csv (formato: fecha,precio)
	void loadDatabase(const std::string& dbFile = "data.csv");
	
	// Métodos auxiliares para validación:
	// - validar formato de fecha "YYYY-MM-DD"
	// - validar que el valor esté entre 0 y 1000
	// - parsear línea del archivo de entrada
};

#endif

