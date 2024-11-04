#include "mbed.h"
#include "header.h"

#define TAILLE_FENETRE 5

float fenetre[TAILLE_FENETRE];

// Fonction : Application calcul de la moyenne mobile du signal ECG
// @param : nouvel échantillon
// @return : moyenne mobile
float moyenne_mobile(float sample) {
    int i;
    float sum = 0;
    // Décalage du buffer
    for (i = 0; i < TAILLE_FENETRE - 1; i++) {
        fenetre[i] = fenetre[i+1];
    }
    // Ajouter le nouvel échantillon dans le buffer
    fenetre[TAILLE_FENETRE - 1] = sample;

    // Calcul de la moyenne des valeurs dans la fenêtre
    for (int i = 0; i < TAILLE_FENETRE; i++) {
        sum += fenetre[i];
    }
    return sum / TAILLE_FENETRE;  // Retourne la valeur moyenne
}

// Fonction permettant l'initialisation du buffer "fenetre" à 0
void clear_MMbuffer() {
    for (int i = 0; i < TAILLE_FENETRE; i++) fenetre[i] = 0.0;
}