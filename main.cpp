#include "mbed.h"

// Définition de la broche pour l'ECG
AnalogIn ecgPin(A0);

// Initialisation du port série
UnbufferedSerial pc(USBTX, USBRX, 9600);  // TX, RX, baud rate

int main() {
    char buffer[20];  // Buffer pour stocker les valeurs à envoyer via le port série
    
    while (true) {
        float ecgValue = ecgPin.read();  // Lire la valeur analogique (entre 0.0 et 1.0)
        int ecgIntValue = ecgValue * 1000;  // Convertir en entier pour faciliter l'affichage

        // Préparer le message à envoyer via le port série
        sprintf(buffer, "ECG: %d\r\n", ecgIntValue);
        pc.write(buffer, strlen(buffer));  // Envoyer la valeur via le port série

        // Délai de 100 ms
        ThisThread::sleep_for(100ms);
    }
}

