#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.hpp"
#include <algorithm>

using namespace std;
typedef GrayLevelImage2D::GrayLevel GrayLevel;
typedef GrayLevelImage2D::Iterator Iterator;

void filtrage(GrayLevelImage2D& img, int k){
  vector<GrayLevel>tab;
  GrayLevelImage2D img2 = img;
  for (int x = 0; x < img.w(); x++){
    for(int y = 0; y < img.h(); y++){
      tab.resize(0);
      for(int i=-k; i<k+1 ; i++){
	for(int j=-k; j<k+1; j++){
	  if (x+i > 0 && x+i < img.w() && y + j > 0 && y + j < img.h()){
	    tab.resize(tab.size()+1,img2.at(x+i,y+j));
	  }
	}
      }
      sort(tab.begin(),tab.end());
      img.at(x,y) = tab.at(tab.size()/2);
    }
  }
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
  bool ok = img.importPGM( input );
  if ( !ok )
    {
      std::cerr << "Error reading input file." << std::endl;
       return 1;
    }
  input.close();
  filtrage(img,atoi(argv[3]));
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
