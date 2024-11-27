#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <vector>
#include <array>
#include <iostream>
#include <stdexcept> 

class LidarDriver
{
	private:
		//costanti di default
		static constexpr int STD_DIM = 180;        		//risoluzione angolare standard
		static constexpr int BUFFER_DIM = 10;     		//dimensione del buffer circolare
		
		int scan_dim;                              		//dimensione della scansione
		std::array<std::vector<double>, BUFFER_DIM> buffer;   	//buffer circolare
		int front = -1;                            		//testa del buffer 
		int rear = -1;                             		//coda del buffer

		//metodi 
		void update_front();                       		//aggiorna front
		void update_rear();                        		//aggiorna rear

	public:
		//costruttori
		LidarDriver();                             		//costruttore di default
		LidarDriver(double resolution);           		//costruttore con risoluzione personalizzata

		//funzioni 
		void new_scan(std::vector<double> inputScan); 		//inserisce una nuova scansione nel buffer
		std::vector<double> get_scan();               		//restituisce la scansione meno recente e la rimuove
		void clear_buffer();                          		//pulisce il buffer
		double get_distance(double angle) const;      		//restituisce la distanza corrispondente a un dato angolo

		//overload operatore <<
		friend std::ostream& operator<<(std::ostream& out, const LidarDriver& lidar);
};

#endif //LIDARDRIVER_H
