#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.hpp"
#include "Histogramme.hpp"
#include <vector>

using namespace std;

int main(int argc, char** argv){
    Histogramme h;
    if ( argc < 3 ) 
        { 
            std::cerr << "Usage: filtrage-median <input.pgm> <output.pgm> k" << std::endl;
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
    h.init(img);
    for (GrayLevelImage2D::Iterator i = img.begin(), j = img.end(); i != j; i++){
        *i = h.egalisation(*i);
    }
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
