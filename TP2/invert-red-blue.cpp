#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
using namespace std;
//typedef Image2D<Color> ColorImage2D //?

bool invert(Color px){
	float tmp;
	tmp=px.r();
	px.setR(px.b());
	px.setB(tmp);
	return true;
}



void convertRedBlue(ColorImage2D img){
	Color px;
	for(int i=0; i<img.h();i++){
		for (int j = 0; j < img.w(); ++i)
		{
			px=&img.at(i,j);
			invert(px);

		}
	}
	
}

int main( int argc, char** argv ){
	typedef Image2D<Color> ColorImage2D; // à placer ici ou sous les imports ? 
	if ( argc < 4 ) 
    { 
      std::cerr << "Usage: filtrage-median <input.ppm> <output.ppm> k" << std::endl;
      return 0;
    }
  

  ColorImage2D img;
  ifstream input( argv[1] ); // récupère le 1er argument.
    std::cerr << ":3" ;
  bool ok = img.importPGM( input );

  if ( !ok )
    {
      std::cerr << "Error reading input file." << std::endl;
       return 1;
    }
  input.close();
  convertRedBlue(img);
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


