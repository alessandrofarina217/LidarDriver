#include "lidardriver.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // Per srand e rand
#include <ctime>    // Per time

std::vector<double> generate_random_scan(int size, double min, double max) {
    std::vector<double> random_scan(size);
    for (int i = 0; i < size; i++) {
        random_scan[i] = min + static_cast<double>(std::rand()) / RAND_MAX * (max - min);
    }
    return random_scan;
}

int main(){
    std::vector<double> scan;                           //creo un vettore che riutilizzerò più volte nel programma come vettore temporaneo
//utilizzo di new_scan
    // Inizializza il generatore di numeri casuali
    std::srand(std::time(NULL)); // Imposta il seme per rand()

    // Crea un oggetto LidarDriver
    LidarDriver lidar(1.0); // Risoluzione di 1° di default

    // Genera e aggiungi la prima scansione casuale
    std::cout << "Aggiunta della scansioni...\n";
    for(int i = 0; i < 10; i++){                        //riempio completamente il buffer (10 scansioni)
        scan = generate_random_scan(181, 0.0, 10.0);
        lidar.new_scan(scan);
    }

//utilizzo get_scan
    scan = lidar.get_scan();                            //recupero scansione meno recente
    for(int i = 0; i < scan.size(); i++)
    {
        std::cout << scan[i] << " ";                    //stampa di ogni valore della scansione meno recente
    }

//utilizzo get_distance
    double distance = lidar.get_distance(3.0);            //recupero distance da un angolo specifico (ad esempio qui 3°);
    std::cout << "Distanza a 3°: " << distance << "\n";   //stampa della distanza ottenuta

//utilizzo resize automatico della funzione new_scan e allo stesso tempo del buffer circolare 
//(siccome il buffer era già stato riempito questo nuovo scan dovrà andare a sovrascrivere quello mneo recente già presente nel buffer)
    scan = generate_random_scan(361, 0.0, 10.0);        //resize per troncamento (eccesso di dati)
    lidar.new_scan(scan);
    scan = generate_random_scan(161, 0.0, 10.0);        //resize per riempimento (mancanza di dati)
    lidar.new_scan(scan);

//utilizzo di get_scan dopo sovrascrittura
    scan = lidar.get_scan();                            //recupero scansione meno recente
    for(int i = 0; i < scan.size(); i++)
    {
        std::cout << scan[i] << " ";                    //stampa di ogni valore della scansione meno recente
    }

//utilizzo clear_buffer
    lidar.clear_buffer();

// Prova a recuperare una scansione dopo aver svuotato il buffer
    try {
        scan = lidar.get_scan();  // Questo dovrebbe lanciare un'eccezione
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what();    //(cerr è un cout ma fatto apposta per i messaggi di errore)
    }
// Stampa dell'ultima scansione usando l'overload di <<
    std::cout << "Ultima scansione nel buffer:\n" << lidar << "\n";
    
    return 0;
}
