#include "mbed.h"
#include "header.h"

// Définition de la broche pour l'ECG
AnalogIn ecgPin(A0); // Analog ECG Signal Input
DigitalIn LODp(D10); // Lead Off Detection +
DigitalIn LODn(D11); // Lead Off Detection -

// Initialisation du port série
UnbufferedSerial pc(USBTX, USBRX, 9600);  // TX, RX, baud rate



int main() {
    char buffer[50];  // Buffer pour stocker les valeurs à envoyer via le port série
    float rawECG, filtredECG, smoothECG; // Valeur du signal ECG (brute, filtrée, lissée)
    float prev_ECGvalue = 0.0; // Valeur précédente du signal ECG
    uint32_t RR_interval = 0; // Intervalle entre deux piques R (en ms)
    //float bpm = 0.0; // Battements Par Minute
    uint32_t bpm = 0;
    bool newBPM = false;
   // const float threshold = 0.25;

    // Création des trois timers 
    Timer ECGTimer, RRTimer, BPMTimer;

    // Initialisation du buffer ECG à 0
    clear_FIRbuffer();
    clear_MMbuffer();
    clear_BATbuffer();
 
    //démarrage des timers

    ECGTimer.start();
    RRTimer.start();
    BPMTimer.start();

    while (true) {
        // Acquisition d'un échantillon du signal chaque 10 ms 
        if (ECGTimer.elapsed_time() >= 10ms) { // le temps écoulé 
            ECGTimer.reset(); // redémarrage  à zéro
            if (!LODp.read() && !LODn.read()) { // Lire seulement si les électrodes sont bien connectées
                rawECG = ecgPin.read();  // Lire la valeur analogique du ECG (entre 0.0 et 1.0)
                //filtredECG = fir_bandpass_filter(rawECG); // Filtrer le nouvel échantillon
                //smoothECG = moyenne_mobile(filtredECG); // Lisser le nouvel échantillon
                
                // Détection du battement par une fenêtre
                if (detect_battement(rawECG)) {
                    RR_interval = RRTimer.elapsed_time().count() / 1000; // valeur de count en micro_seconde transformé en ms 
                    if (RR_interval > 200 && RR_interval < 20000)
                    {  
                        bpm = 60000 / RR_interval; //  le nombre de battement par minutes
                        newBPM = true;
                    }
                    RRTimer.reset();
                }
                
                // Détection de battement
                /*if (fabs(prev_ECGvalue - filtredECG) > threshold) {
                    RR_interval = RRTimer.elapsed_time().count() / 1000;
                    bpm = 60000 / RR_interval;
                    RRTimer.reset();
                }
                prev_ECGvalue = filtredECG; // Sauvegarder la valeur en cours du ECG
                */

                // Affichage du signal ECG sous format CSV
                //sprintf(buffer, "%d;%d;%d\r\n", (int)(rawECG * 1000), (int)(filtredECG * 1000), (int)(smoothECG * 1000));
                //pc.write(buffer, strlen(buffer));  // Envoyer la valeur du BPM via le port série
            }
            else {
                //sprintf(buffer, "Electrodes disconnected !\r\n");
                //pc.write(buffer, strlen(buffer));  // Envoyer la valeur du BPM via le port série
            }
        }
        if (newBPM) 
        {
          //  BPMTimer.reset();
           // if (!LODp.read() && !LODn.read()) { // Lire seulement si les électrodes sont bien connectées
            sprintf(buffer, "BPM : %d    RR-Interval : %d ms\r\n", bpm, RR_interval);
            pc.write(buffer, strlen(buffer));  // Envoyer la valeur du BPM via le port série et la taille string lengh 
            newBPM = false;

        }
    }
}

 