#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GrayLevelImage2D.hpp"
#include <math.h>

using namespace std;

double rand01()
{
  return (double)random() / (double)RAND_MAX;
}

int main( int argc, char** argv )
{
    /*const double epsilon = std::numeric_limits<double>::min();*/
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator Iterator;
    if ( argc < 3 ) 
        { 
            std::cerr << "Usage: bruit-impulsionnel <input.pgm> <output.pgm> <prob>" << std::endl;
            return 0;
        }
    GrayLevelImage2D img;
    ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = img.importPGM( input );
    if ( !ok )
        {
            std::cerr << "Error reading input file." << std::endl;
            return 1;
        }
    input.close();
    //BRUITAGE
    double sigma = (argc > 3)?atof(argv[3]):0.5;
    double u1, u2;
    double z;
    for (GrayLevelImage2D::Iterator i = img.begin(), j = img.end(); i != j; i++){
        u1 = rand01();
        u2 = rand01();
        z = sqrt(-2.0 * log(u1)) * cos(M_PI * 2 * u2);
        *i += (int)(z * sigma);
    }
    //FIN BRUITAGE
    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img.exportPGM( output, false );
    if ( !ok )
        {
            std::cerr << "Error writing output file." << std::endl;
            return 1;
        }
    output.close();
    return 0;
}
