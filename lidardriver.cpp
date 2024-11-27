
class LidarDriver
{
	static constexpr int STD_DIM = 180;											//dimensione di uno scan di default 		
	static constexpr int BUFFER_DIM = 10;												//dimensione del buffer			scrivere static const se il valore puo' essere scelto nel 
	int SCAN_DIM;												//dimensione di uno scan scelto dall'utente
	std::vector<double> temp;									//vettore singolo scan
	std::vector<std::vector<double>> buffer;					//buffer, matrice BUFFER_DIM scan
	int front = -1;												//testa della coda (inizializzato) primo valore vuoto o sovrascrivibile
	int rear = -1;												//fine della coda (inizializzato) ultimo valore vuoto o non sovrascrivibile

	void update_rear()
	{
		if(rear == BUFFER_DIM-1) rear = 0;
		else rear++;
	}
	void update_front()
	{
		if(front == BUFFER_DIM-1) front = 0;
		else front++;
	}

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
	void new_scan(std::vector<double> inputScan)			//memorizza scansione nel buffer. Il passaggio per valore garantisce il mantenimento dei dati originali e il move consente di evitare altri overhead 
	{
		update_rear();				

		if(inputScan.size()!=SCAN_DIM)								//effettua il resize di inputScan per adattarla a quella degli scan del buffer
		{
			inputScan.resize(SCAN_DIM);
		}
		//copiare il vettore input ottenuto, CONTROLLARE SE IL VETTORE SI PUO' MUOVERE PER EVITARE OVERHEAD
		buffer[rear] = std::move(inputScan);					//SPOSTA, non copia, il vettore modificato nel buffer per evitare overhead.		

		if(front == -1||front == rear) update_front();								//aggiorna il front solo se la coda e' vuota oppure se il vecchio front e' il nuovo rear	

	}

	std::vector<double> get_scan()			//output della scansione meno recente nel buffer e sua successiva eliminazione
	{
		if(front < 0)	std::cout<<"Nessuna misura inserita.}\n";					//LANCIARE ECCEZIONE!

		temp = std::move(buffer[front]);							//il valore piu' vecchio viene spostato in temp
		buffer[front].resize(SCAN_DIM,0);						//lo scan specifico viene reinizializzato
		
		if(front == rear)										
		{
			front = -1;
			rear = -1;
		}
		else update_front();

		return temp;
	}

	void clear_buffer()
	{
		if(rear <= front)
		{
			for(int i=(rear+(BUFFER_DIM-front));i>=0;i--)
			{
				
			}
		}
	}

	get_distance()
	{

	}

}
