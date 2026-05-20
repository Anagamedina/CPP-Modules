#include "BitcoinExchange.hpp"

// TODO: Incluir headers necesarios
// #include <string>
// #include <fstream>
// #include <iostream>
// #include <map> (o el container que elijas: vector, list, etc.)
// #include <sstream> (para parsing)

// Constructor
// Debe llamar a loadDatabase() para cargar data.csv
BitcoinExchange::BitcoinExchange()
{
	// TODO: Inicializar atributos
	// TODO: Llamar a loadDatabase() para cargar data.csv
}

// Constructor de copia
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	// TODO: Copiar el container con los datos de la base de datos
	(void)other;
}

// Operador de asignación
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		// TODO: Limpiar datos actuales si es necesario
		// TODO: Copiar el container con los datos de other
	}
	return (*this);
}

// Destructor
BitcoinExchange::~BitcoinExchange()
{
	// TODO: Limpiar recursos si es necesario
	// Si usas un container de la STL, no necesitas hacer nada aquí
}

// Implementación de loadDatabase()
// Debe leer data.csv línea por línea
// Formato CSV: fecha,precio (ej: "2011-01-03,0.3")
// Primera línea puede ser header, saltarla
// Guardar en el container: fecha -> precio
void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
	// TODO: Abrir el archivo dbFile
	// TODO: Leer línea por línea
	// TODO: Parsear cada línea (separar por coma)
	// TODO: Validar formato
	// TODO: Guardar en el container (map o el que uses)
	// NOTA: Si usas map, las fechas se ordenarán automáticamente
	(void)dbFile;
}

// Implementación de processInput()
// Debe abrir el archivo de entrada y procesar cada línea
void BitcoinExchange::processInput(const std::string& inputFile)
{
	// TODO: Verificar que el archivo se pueda abrir
	// TODO: Si no se puede abrir: mostrar "Error: could not open file." y return
	
	// TODO: Leer línea por línea del archivo
	// TODO: Saltar la primera línea si es header "date | value"
	// TODO: Para cada línea:
	//   - Parsear: separar por " | "
	//   - Validar formato de fecha "YYYY-MM-DD"
	//   - Validar valor (debe ser positivo, entre 0 y 1000)
	//   - Si hay error, mostrar mensaje apropiado y continuar
	//   - Si está bien: obtener precio con getBitcoinPrice() y calcular
	//   - Mostrar: "YYYY-MM-DD => value = resultado"
	
	// Validaciones específicas:
	// - Si valor < 0: "Error: not a positive number."
	// - Si valor > 1000: "Error: too large a number."
	// - Si fecha inválida: "Error: bad input => [fecha]"
	
	(void)inputFile;
}

// Implementación de getBitcoinPrice()
// Busca el precio para una fecha, si no existe usa la fecha más cercana (más baja)
double BitcoinExchange::getBitcoinPrice(const std::string& date) const
{
	// TODO: Buscar la fecha exacta en el container
	
	// TODO: Si no existe:
	//   - Si usas map: usar lower_bound() para encontrar la fecha más cercana
	//   - Si usas vector/list: iterar y encontrar la fecha más cercana (menor o igual)
	//   - IMPORTANTE: usar la fecha más BAJA (no superior) según el subject
	
	// TODO: Retornar el precio, o -1 si hay error
	
	(void)date;
	return (0.0);
}

