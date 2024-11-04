float fir_bandpass_filter(float sample);
void clear_FIRbuffer();
float moyenne_mobile(float sample);
void clear_MMbuffer();

bool detect_battement(float sample);
void clear_BATbuffer();