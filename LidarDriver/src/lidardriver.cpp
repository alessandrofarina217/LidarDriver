#include "../include/lidardriver.h"
#include <cmath>

//funzione per aggiornare la coda (rear) del buffer
void LidarDriver::update_rear() {
    if (rear == BUFFER_DIM - 1) 
        rear = 0;
    else 
        rear++;
}

//funzione per aggiornare la testa (front) del buffer
void LidarDriver::update_front() {
    if (front == BUFFER_DIM - 1) 
        front = 0;
    else 
        front++;
}

//costruttore di default
LidarDriver::LidarDriver() {
    scan_dim = STD_DIM + 1;
}

//costruttore con risoluzione personalizzata
LidarDriver::LidarDriver(double res) {
    if (res < 0.1 || res > 1.0) {
        throw std::invalid_argument("Risoluzione fuori range (0.1-1).");
    }
    scan_dim = (STD_DIM / res) + 1;
    }

//inserisce una nuova scansione nel buffer
void LidarDriver::new_scan(std::vector<double> inputScan) {
    update_rear();

    if (inputScan.size() != scan_dim) {
        inputScan.resize(scan_dim);
    }
    buffer[rear] = std::move(inputScan);
    if (front == -1 || front == rear) {
        update_front();
    }
}

//restituisce la scansione meno recente e la rimuove
std::vector<double> LidarDriver::get_scan() {
    if (front < 0) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    std::vector<double> temp1 = std::move(buffer[front]);
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        update_front(); 
    }
    return temp1;
}

//svuota il buffer
void LidarDriver::clear_buffer() {
    std::vector<double> temp1;
    for (int i = 0; i < BUFFER_DIM; i++) {
        temp1 = std::move(buffer[i]);
    }
    front = -1;
    rear = -1;
}

//restituisce la distanza corrispondente a un dato angolo
double LidarDriver::get_distance(double angle) const {
    if (front == -1) {
        throw std::runtime_error("Il buffer è vuoto.\n");
    }
    if (angle < 0 || angle > 180) {
        throw std::out_of_range("Angolo fuori range (0-180 gradi).\n");
    }
    double aIndex = ((scan_dim - 1) / STD_DIM) * angle;
    int cIndex = static_cast<int>(std::round(aIndex));
    return buffer[rear][cIndex];
}

//implementazione dell'operatore <<
std::ostream& operator<<(std::ostream& out, const LidarDriver& lidar) {
    if (lidar.front == -1) {
        out << "Buffer vuoto.\n";
    } else {
        int index = lidar.rear;
        out << "Ultima scansione memorizzata:\n";
        for (double value : lidar.buffer[index]) {
            out << value << " ";
        }
        out << "\n";
    }
    return out;
}
