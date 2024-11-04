#include "mbed.h"
#include "header.h"

// Nombre des coefficients du filtre
#define NUM_COEFS 101

// Les N coefficients du filtre FIR passe-bande ( filtre à réponse impulsionnelle finie)
const float fir_coefs[] = {-2.99782349e-04, -8.04569099e-04, -6.41469877e-04, +1.84788617e-05,
+2.64857426e-04, -3.89101131e-04, -1.20104623e-03, -1.01138854e-03,
+8.74448934e-05, +5.40239657e-04, -6.44405779e-04, -2.15636722e-03,
-1.79823104e-03, +2.70349986e-04, +1.12304366e-03, -1.04552405e-03,
-3.75747238e-03, -3.04688388e-03, +6.73320121e-04, +2.17736705e-03,
-1.55619016e-03, -6.11652728e-03, -4.81718844e-03, +1.45192680e-03,
+3.94850052e-03, -2.12766625e-03, -9.43036089e-03, -7.22945986e-03,
+2.85650685e-03, +6.85605078e-03, -2.70379657e-03, -1.41325491e-02,
-1.05821805e-02, +5.36637149e-03, +1.17726859e-02, -3.22694659e-03,
-2.13631620e-02, -1.57304418e-02, +1.01740306e-02, +2.10793278e-02,
-3.64417192e-03, -3.49833830e-02, -2.58593046e-02, +2.17690811e-02,
+4.50220951e-02, -3.91292935e-03, -7.86411525e-02, -6.59178943e-02,
+8.93514376e-02, +2.98884139e-01, +3.96563235e-01, +2.98884139e-01,
+8.93514376e-02, -6.59178943e-02, -7.86411525e-02, -3.91292935e-03,
+4.50220951e-02, +2.17690811e-02, -2.58593046e-02, -3.49833830e-02,
-3.64417192e-03, +2.10793278e-02, +1.01740306e-02, -1.57304418e-02,
-2.13631620e-02, -3.22694659e-03, +1.17726859e-02, +5.36637149e-03,
-1.05821805e-02, -1.41325491e-02, -2.70379657e-03, +6.85605078e-03,
+2.85650685e-03, -7.22945986e-03, -9.43036089e-03, -2.12766625e-03,
+3.94850052e-03, +1.45192680e-03, -4.81718844e-03, -6.11652728e-03,
-1.55619016e-03, +2.17736705e-03, +6.73320121e-04, -3.04688388e-03,
-3.75747238e-03, -1.04552405e-03, +1.12304366e-03, +2.70349986e-04,
-1.79823104e-03, -2.15636722e-03, -6.44405779e-04, +5.40239657e-04,
+8.74448934e-05, -1.01138854e-03, -1.20104623e-03, -3.89101131e-04,
+2.64857426e-04, +1.84788617e-05, -6.41469877e-04, -8.04569099e-04,
-2.99782349e-04};

// Buffer pour stocker les N échantillons du signal ECG
static float ECG_buffer[NUM_COEFS]; 

// la fonction du filtre FIR passe bande
// @param : sample : échantillon en entrée
// @return : échantillon filtré
float fir_bandpass_filter(float sample) { 
    int i;
    float filtred_sample = 0; // initalisation à 0 

    // Décalage du buffer et ajout de l'échantillon reçu en dernier
    for (i = NUM_COEFS - 1; i > 0; i--) {
        ECG_buffer[i] = ECG_buffer[i-1];
    }
    ECG_buffer[0] = sample;

    // Application du filtre et génération de l'échantillon filtré
    for (i = 0; i < NUM_COEFS; i++) {
        filtred_sample += ECG_buffer[i] * fir_coefs[i];
    }

    // retourner l'échantillon filtré
    return filtred_sample;
}

// Fonction permettant l'initialisation du buffer à 0
// Ne reçois rien et ne renvoie rien
void clear_FIRbuffer() {
    for (int i = 0; i < NUM_COEFS; i++) ECG_buffer[i] = 0.0;
}