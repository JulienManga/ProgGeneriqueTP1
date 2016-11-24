#include "GrayLevelImage2D.hpp"
#include <vector>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include <stdlib.h>
using namespace std;



int calculerMediane(int h, int w, int porteProcess, GrayLevelImage2D& img){
	//Renvoi l valeur du pixel
	int cptVal=0;
	int sommeTotal=0;
	for(int i = h - porteProcess ;i < h + porteProcess ; i++){
		for(int j = w - porteProcess; j<w + porteProcess;j++){
			if (i>=0 && j>=0 && i<img.h() && j<img.w()) // a voir si le 0 est compris
			{
				sommeTotal+=img.at(i,j);
				cptVal++;
			}
		}
		std::cerr << "ok1";
	}

	return sommeTotal/cptVal;


}

void filtrageMedian(GrayLevelImage2D& img, int porteProcess){
	for(int i=0;i<img.h();++i){ // on va traiter chzque pixel
		for(int j=0;j<img.w();++j){ // on va traiter chzque pixel
			std:cerr << "ok first";		
			img.at(i,j)=calculerMediane(i,j,porteProcess,img);
		}
	}
	std::cerr <<"ok2";
}


int main( int argc, char** argv )
{
  
  if ( argc < 4 ) 
    { 
      std::cerr << "Usage: filtrage-median <input.pgm> <output.pgm> k" << std::endl;
      return 0;
    }
  GrayLevelImage2D img;
  ifstream input( argv[1] ); // récupère le 1er argument.
    std::cerr << ":3" ;
  bool ok = img.importPGM( input );
  std::cerr << "import ok" ;
  if ( !ok )
    {
      std::cerr << "Error reading input file." << std::endl;
       return 1;
    }
  input.close();
  filtrageMedian(img,atoi(argv[3]));
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