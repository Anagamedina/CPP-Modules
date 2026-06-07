#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

// Clase que guarda la base de datos de precios (fecha -> precio)
// y procesa el archivo de entrada del usuario.
class BitcoinExchange
{
	public:
		// Forma Canonica Ortodoxa
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		// Carga la base de datos desde un CSV (formato: fecha,precio)
		void loadDatabase(const std::string& dbFile);

		// Lee el archivo de entrada y muestra el resultado de cada linea
		void processInput(const std::string& inputFile);

	private:
		// map ordena las fechas automaticamente -> ideal para lower_bound
		std::map<std::string, double> _database;

		// Devuelve el precio de una fecha (o el de la fecha anterior mas cercana)
		double getPrice(const std::string& date) const;

		// Comprueba que la fecha tenga el formato correcto YYYY-MM-DD
		bool isValidDate(const std::string& date) const;
};

#endif
