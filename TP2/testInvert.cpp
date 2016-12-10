// save-green-channel.cpp
#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
/*#include "Accessor.hpp"*/
int main( int argc, char** argv )
{
  typedef Image2D<Color> ColorImage2D;
  typedef Image2DReader<Color> ColorImage2DReader;
  typedef ColorImage2D::Iterator ColorIterator;
  if ( argc < 3 ) 
    { 
      std::cerr << "Usage: save-green-channel <input.ppm> <output.pgm>" << std::endl;
      return 0;
    }
  ColorImage2D img;
  std::ifstream input( argv[1] ); // récupère le 1er argument.
  bool ok = ColorImage2DReader::read( img, input );
  if ( !ok )
    {
      std::cerr << "Error reading input file." << std::endl;
       return 1;
    }
  input.close();
 
  typedef Image2DWriter<Color> colorLevelImage2DWriter;
  typedef Image2D<Color>::Iterator colorLevelIterator;
  Image2D<Color> img2 ( img.w(), img.h() ) ;
  
  //-----------------------------------------------------------------------------
  // vvvvvvvvv Toute la transformation couleur -> canal vert est ici vvvvvvvvvvvv
  //
  // Servira à parcourir la composante verte de l'image couleur.
  
  // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
  
  // On écrit la composante verte dans l'image en niveaux de gris.
  for (  Image2D<Color>::Iterator it = img.begin(), j = img.end(); it != j; it++ )
    {
      //on inverse le bleu et le rouge
      
      *it =Color(it->b(),it->g(),it->r());

      // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
  //-----------------------------------------------------------------------------
  std::ofstream output( argv[2] ); // récupère le 2eme argument.
  bool ok2 = Image2DWriter<Color>::write( img2, output, false );
  if ( !ok2 )
    {
      std::cerr << "Error writing output file." << std::endl;
       return 1;
    }
  output.close();
  return 0;
}
