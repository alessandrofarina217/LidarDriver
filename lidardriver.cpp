
class LidarDriver
{
	static constexpr int STD_DIM = 180;											//dimensione di uno scan di default 		
	static constexpr int BUFFER_DIM = 10;												//dimensione del buffer			scrivere static const se il valore puo' essere scelto nel 
	int SCAN_DIM;												//dimensione di uno scan scelto dall'utente
	std::vector<double> temp;									//vettore singolo scan
	std::vector<std::vector<double>> buffer;					//buffer, matrice BUFFER_DIM scan
	int head = 0;												//testa della coda (inizializzato) primo valore vuoto o sovrascrivibile
	int tail = -1;												//fine della coda (inizializzato) ultimo valore vuoto o non sovrascrivibile

public:

	// costruttori
	LidarDriver()
	{
		SCAN_DIM = STD_DIM+1;								//caso default
		temp.resize(SCAN_DIM);									//resize del vettore di default
		buffer.resize(BUFFER_DIM);								//resize del buffer di default
		
		for(int i=0;i<BUFFER_DIM;i++)								//resize di ogni vettore del vettore	
		{
			buffer[i].resize(SCAN_DIM);
		}

	}

	LidarDriver(double res)
	{
		SCAN_DIM = (STD_DIM/res)+1;									//utente sceglie la risoluzione
		
		// se res<0.1 o res>1 lancia exception
		temp.resize(SCAN_DIM);									
		buffer.resize(BUFFER_DIM);

		for(int i=0;i<BUFFER_DIM;i++)								//resize di ogni vettore del vettore	
		{
			buffer[i].resize(SCAN_DIM);
		}
	}

	//funzioni
	new_scan(std::vector<double> inputScan)			//memorizza scansione nel buffer. Il passaggio per valore garantisce il mantenimento dei dati originali e il move consente di evitare altri overhead 
	{
		if(inputScan.size()!=SCAN_DIM)								//effettua il resize di inputScan per adattarla a quella degli scan del buffer
		{
			inputScan.resize(SCAN_DIM);
		}
		//copiare il vettore input ottenuto, CONTROLLARE SE IL VETTORE SI PUO' MUOVERE PER EVITARE OVERHEAD
		
		buffer[head] = std::move(inputScan);					//SPOSTA, non copia, il vettore modificato nel buffer per evitare overhead.		

		update_indexes();											//aggiorna gli indici
	}

	get_scan()			//output della scansione meno recente nel buffer e sua successiva eliminazione
	{
		if(tail < 0)	std::cout<<"Nessuna misura inserita.}\n";

		temp = std::move(buffer[tail]);							//il valore piu' vecchio viene spostato in temp
		buffer[tail].resize(SCAN_DIM,0);						//lo scan specifico viene reinizializzato
		
		if(tail == head-1){}
		else tail++;													//tail punta al nuovo valore piu' vecchio.
	}

	clear_buffer()
	{

	}

	get_distance()
	{

	}

	void update_indexes()
	{
		if (head == BUFFER_DIM-1) head = 0;				//head fa il giro
		else head++;									//head incrementa normalmente

		if (head == tail) tail++;							//se la coda e' a regime, head prende il posto di tail, altrimenti tail tiene la sua posizione
		else if (tail == BUFFER_DIM) tail = 0;				//se tail arriva alla fine e head e' appena dietro, allora torna a 0.
	}
}