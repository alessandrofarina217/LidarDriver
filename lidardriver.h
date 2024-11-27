#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <vector>
#include <array>
#include <iostream>
#include <stdexcept> 

class LidarDriver
{
	private:
		// Costanti di default
		static constexpr int STD_DIM = 180;        		// Risoluzione angolare standard
		static constexpr int BUFFER_DIM = 10;     		// Dimensione del buffer circolare
		
		int scan_dim;                              		// Dimensione della scansione
		std::array<std::vector<double>, BUFFER_DIM> buffer;   	// Buffer circolare
		int front = -1;                            		// Testa del buffer 
		int rear = -1;                             		// Coda del buffer

		// Metodi 
		void update_front();                       		// Aggiorna front
		void update_rear();                        		// Aggiorna rear

	public:
		// Costruttori
		LidarDriver();                             		// Costruttore di default
		LidarDriver(double resolution);           		// Costruttore con risoluzione personalizzata

		// Funzioni 
		void new_scan(std::vector<double> inputScan); 		// Inserisce una nuova scansione nel buffer
		std::vector<double> get_scan();               		// Restituisce la scansione meno recente e la rimuove
		void clear_buffer();                          		// Pulisce il buffer
		double get_distance(double angle) const;      		// Restituisce la distanza corrispondente a un dato angolo

		// Overload operatore <<
		friend std::ostream& operator<<(std::ostream& out, const LidarDriver& lidar);
};

#endif // LIDARDRIVER_H
