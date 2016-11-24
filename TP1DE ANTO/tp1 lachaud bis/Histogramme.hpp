#include "GrayLevelImage2D.hpp"
class Histogramme{
    double histogramme[256];
    double histogrammeCumule[256];
public:
    void init(GrayLevelImage2D & img);
    int egalisation(int j) const;
};
