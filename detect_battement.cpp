#include "mbed.h"
#include "header.h"

#define TAILLE_FENETRE_BAT 7 // le taille de la fenetre 
#define BAT_THRESHOLD 0.1 // Seuil de différence 

float bat_fenetre[TAILLE_FENETRE_BAT]; // buffer de cinq échantillons t__>t-4

// Fonction : Recherche d'un battement dans une fenetre de taille TAILLE_FENETRE_BAT
// @param : nouvel échantillon
// @return : si un battement a été détecté ou non
bool detect_battement(float sample) {
    float a, b, c;
    int i;
    // Décalage du buffer
    for (i = 0; i < TAILLE_FENETRE_BAT - 1; i++) {
        bat_fenetre[i] = bat_fenetre[i+1];
    }
    // Ajouter le nouvel échantillon dans le buffer
    bat_fenetre[TAILLE_FENETRE_BAT - 1] = sample;

    a = bat_fenetre[0];
    b = bat_fenetre[TAILLE_FENETRE_BAT/2];
    c = bat_fenetre[TAILLE_FENETRE_BAT - 1];

    if (fabs(a - b) > BAT_THRESHOLD && fabs(c - b) > BAT_THRESHOLD && ( b > max(c,a) || b < min(c,a))) 
         return true;
    else 
         return false;
}

// Fonction permettant l'initialisation du buffer "bat_fenetre" à 0
void clear_BATbuffer() {
    for (int i = 0; i < TAILLE_FENETRE_BAT; i++) bat_fenetre[i] = 0.0;
}