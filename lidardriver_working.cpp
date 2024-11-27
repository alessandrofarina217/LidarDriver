#include "lidardriver.h"
#include <cmath>
#include <stdexcept>

// Funzione per aggiornare la coda (rear) del buffer
void LidarDriver::update_rear() {
    if (rear == BUFFER_DIM - 1) 
        rear = 0;
    else 
        rear++;
}

// Funzione per aggiornare la testa (front) del buffer
void LidarDriver::update_front() {
    if (front == BUFFER_DIM - 1) 
        front = 0;
    else 
        front++;
}

// Costruttore di default
LidarDriver::LidarDriver() {
    SCAN_DIM = STD_DIM + 1;
    buffer.resize(BUFFER_DIM);
    for(int i = 0; i < BUFFER_DIM; i++) {
        buffer[i].resize(SCAN_DIM);
    }
}

// Costruttore con risoluzione personalizzata
LidarDriver::LidarDriver(double res) {
    if (res < 0.1 || res > 1.0) {
        throw std::invalid_argument("Risoluzione fuori range (0.1-1).");
    }
    SCAN_DIM = (STD_DIM / res) + 1;
    buffer.resize(BUFFER_DIM);
    for(int i = 0; i < BUFFER_DIM; i++) {
        buffer[i].resize(SCAN_DIM);
    }
}

// Inserisce una nuova scansione nel buffer
void LidarDriver::new_scan(std::vector<double> inputScan) {
    update_rear();  // Funzione definita correttamente

    if (inputScan.size() != SCAN_DIM) {
        inputScan.resize(SCAN_DIM);
    }
    buffer[rear] = std::move(inputScan);
    if (front == -1 || front == rear) {
        update_front();  // Funzione definita correttamente
    }
}

// Restituisce la scansione meno recente e la rimuove
std::vector<double> LidarDriver::get_scan() {
    if (front < 0) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    std::vector<double> temp1 = std::move(buffer[front]);
    buffer[front].resize(SCAN_DIM, 0);
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        update_front();  // Funzione definita correttamente
    }
    return temp1;
}

// Svuota il buffer
void LidarDriver::clear_buffer() {
    std::vector<double> temp1;
    for (int i = 0; i < BUFFER_DIM; i++) {
        temp1 = std::move(buffer[i]);
    }
    front = -1;
    rear = -1;
}

// Restituisce la distanza corrispondente a un dato angolo
double LidarDriver::get_distance(double angle) const {
    if (front == -1) {
        throw std::runtime_error("Il buffer è vuoto.\n");
    }
    if (angle < 0 || angle > 180) {
        throw std::out_of_range("Angolo fuori range (0-180 gradi).\n");
    }
    double aIndex = ((SCAN_DIM - 1) / STD_DIM) * angle;
    int cIndex = static_cast<int>(std::round(aIndex));
    return buffer[rear][cIndex];
}

// Implementazione dell'operatore <<
std::ostream& operator<<(std::ostream& out, const LidarDriver& lidar) {
    if (lidar.front == -1) {
        out << "Buffer vuoto.\n";
    } else {
        int index = lidar.rear;
        out << "Ultima scansione memorizzata:\n";  // Intestazione per maggiore chiarezza
        for (double value : lidar.buffer[index]) {
            out << value << " ";
        }
        out << "\n";  // Aggiungi un a capo alla fine della scansione
    }
    return out;
}
