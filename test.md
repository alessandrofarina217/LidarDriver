Test

-Test del costruttore e delle eccezioni

Ho provato a mettere un valore di risoluzione < di 0.1 (0.05)
Compilazione: ok
Esecuzione: 
libc++abi: terminating due to uncaught exception of type std::invalid_argument: Risoluzione fuori range (0.1-1).
zsh: abort      ./lidar_driver
Codice usato:
LidarDriver lidar1(0.05);

Ora con un valore > 1.0 (1.5)
Compilazione: ok
Esecuzione: 
libc++abi: terminating due to uncaught exception of type std::invalid_argument: Risoluzione fuori range (0.1-1).
zsh: abort      ./lidar_driver
Codice usato:
LidarDriver lidar1(1.5);


-Test di new_scan e buffer circolare

Ho aggiunto più scansioni di quelle che il buffer può contenere per verificare il comportamento circolare (12 invece che 10) per vedere da subito come si comporta il buffer in scrittura
Compilazione: tutto è andato correttamente quindi ha gestito correttamente la sovrascrittura
Codice usato:
LidarDriver lidar(1.0);
for (int i = 0; i < 12; i++) { // Buffer di 10, quindi le prime 2 saranno sovrascritte
    std::vector<double> scan = generate_random_scan(181, 0.0, 10.0);
    lidar.new_scan(scan);
}
std::cout << "Ultima scansione (sovrascritta):\n" << lidar << "\n";


-Test di get_scan

Recupera e stampa ogni scansione fino a svuotare il buffer
Compilazione:  ok
Esecuzione: 
Aggiunta delle scansioni...
Errore: Il buffer è vuoto.
libc++abi: terminating due to uncaught exception of type std::runtime_error: Il buffer è vuoto.
zsh: abort      ./lidar_driver
Codice usato: 
try {
    for (int i = 0; i < 10; i++) {
        std::vector<double> scan = lidar.get_scan();
        for (double val : scan) std::cout << val << " ";
        std::cout << "\n";
    }
    lidar.get_scan(); // Buffer vuoto, dovrebbe lanciare un'eccezione
} catch (const std::exception& e) {
    std::cerr << "Errore: " << e.what() << "\n";
}

-Test di clear_buffer

Svuota il buffer e prova a recuperare una scansione
Compilazione: ok
Esecuzione: catch ha funzionato "Errore: il buffer è vuoto."

-Test get_distance 

Recupera una distanza per un angolo specifico fuori range
Compilazione: ok
Esecuzione: ibc++abi: terminating due to uncaught exception of type std::out_of_range: Angolo fuori range (0-180 gradi).













