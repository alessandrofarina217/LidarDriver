#include "../include/lidardriver.h"
#include <iostream>
#include <vector>
#include <cstdlib>  //per srand e rand
#include <ctime>    //per time

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
    //inizializza il generatore di numeri casuali
    std::srand(std::time(NULL)); //imposta il seme per rand()

    //crea un oggetto LidarDriver
    LidarDriver lidar(1.0); //risoluzione di 1° di default

    //genero e aggiungo le varie scansioni
    std::cout << "Aggiunta delle scansioni...\n";
    for(int i = 0; i < 10; i++){                        //riempio completamente il buffer (10 scansioni)
        scan = generate_random_scan(181, 0.0, 10.0);
        lidar.new_scan(scan);
    }
    std::cout << "Scansioni aggiunte con successo.\n\n";

//utilizzo get_scan
    std::cout << "Recupero scansione meno recente:\n";
    scan = lidar.get_scan();                            //recupero scansione meno recente
    for(int i = 0; i < scan.size(); i++)
    {
        std::cout << scan[i] << " ";                    //stampa di ogni valore della scansione meno recente
    }
    std::cout << "\n\n";

//utilizzo get_distance
    double distance = lidar.get_distance(3.0);            //recupero distance da un angolo specifico (ad esempio qui 3°);
    std::cout << "Distanza a 3°: " << distance << "\n\n";   //stampa della distanza ottenuta
    std::cout << "Ultima scansione nel buffer dopo di get_distance:\n" << lidar << "\n";    // controllo che il valore sia corretto e che l'ultima scansione non sia stata svuotata

//utilizzo resize automatico della funzione new_scan e allo stesso tempo del buffer circolare 
    //(siccome il buffer era già stato riempito questo nuovo scan dovrà andare a sovrascrivere quello meno recente già presente nel buffer)
    scan = generate_random_scan(361, 0.0, 10.0);        //resize per troncamento (eccesso di dati)
    lidar.new_scan(scan);
    scan = generate_random_scan(161, 0.0, 10.0);        //resize per riempimento (mancanza di dati)
    lidar.new_scan(scan);

//utilizzo di get_scan dopo sovrascrittura
    std::cout << "Recupero scansione meno recente dopo sovrascrittura:\n";
    scan = lidar.get_scan();                            //recupero scansione meno recente
    for(int i = 0; i < scan.size(); i++)
    {
        std::cout << scan[i] << " ";                    //stampa di ogni valore della scansione meno recente
    }
    std::cout << "\n\n";

//utilizzo clear_buffer
    std::cout << "Svuotamento del buffer...\n";
    lidar.clear_buffer();
    std::cout << "Buffer svuotato con successo.\n\n";

//provo a recuperare una scansione dopo aver svuotato il buffer
    try {
        lidar.get_scan();
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
    std::cout << "\n";

//stampo l'ultima scansione usando l'overload di <<
    std::cout << "Ultima scansione nel buffer:\n" << lidar << "\n";

    return 0;
}
