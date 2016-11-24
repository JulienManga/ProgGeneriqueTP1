#include "Histogramme.hpp"
void Histogramme::init(GrayLevelImage2D & img){
    for (int i = 0; i < 256; i++){
        histogramme[i] = 0;
        histogrammeCumule[i] = 0;
    }

    for (GrayLevelImage2D::Iterator i = img.begin(), j = img.end(); i != j; i++){
        histogramme[(int)*i] += 1.0;
    }

    for (int i = 0; i < 256; i++){
        histogramme[i] /= (img.w() * img.h());
    }

    histogrammeCumule[0] = histogramme[0];
    for (int i = 1; i < 256; i++){
        histogrammeCumule[i] = histogrammeCumule[i - 1] + histogramme[i];
    }
}
int Histogramme::egalisation(int j) const{
    return histogrammeCumule[j] * 255.0;
}
