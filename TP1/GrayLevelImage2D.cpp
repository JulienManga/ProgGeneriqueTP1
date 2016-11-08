#include "GrayLevelImage2D.hpp"
#include <vector>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères

GrayLevelImage2D::GrayLevelImage2D(int w,int h,GrayLevel g)
{

    m_data.resize(w*h);
    m_data.assign(w*h,g);
    m_width = w;
    m_height = h;
    //ctor
}

GrayLevelImage2D::GrayLevelImage2D(){
 m_data.resize(0);
  m_width = 0;
  m_height = 0;
  };



/*GrayLevelImage2D::~GrayLevelImage2D()
{
    //dtor


}*/

  /// @return la largeur de l'image.
int GrayLevelImage2D::w() const{

    return m_width;
    }
  /// @return la hauteur de l'image.
int GrayLevelImage2D::h() const{

    return m_height;
    }







 int GrayLevelImage2D::index( int x, int y ) const {
        return x+y*w();
   }



   int GrayLevelImage2D::index( int x, int y ) {
        return x+y*w();
   }

    GrayLevelImage2D::Iterator::Iterator
    (GrayLevelImage2D& Image,int x,int y):
        std::vector<GrayLevel>::iterator
           (Image.m_data.begin() + Image.index(x,y))
{}

   GrayLevelImage2D::GrayLevel GrayLevelImage2D::at( int i, int j ) const {
        return m_data[index(i,j)];

    }

    /**
       Accesseur read-write à la valeur d'un pixel.
       @return une référence à la valeur du pixel(i,j)
    */
    GrayLevelImage2D::GrayLevel& GrayLevelImage2D::at( int i, int j ) {
        GrayLevel& tmp=m_data[index(i,j)];
        return tmp;

    }
    //! [gli2d-sec3]
GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y){
      return Iterator(*this,x,y);

      
    }

    GrayLevelImage2D::Iterator GrayLevelImage2D::begin(){
      return start(0,0);

    }

    GrayLevelImage2D::Iterator GrayLevelImage2D::end(){
      return start(0,h());
    }

    GrayLevelImage2D:: bool importPGM(std::isteam & input){
      // Ouvre le flux en entrée sur le fichier "toto.pgm"
        ifstream input( "toto.pgm", std::ios::binary ); // le ios::binary est nécessaire seulement sous Windows.
        // teste si tout va bien
        if ( ! input.good() ) std::cerr << "Probleme !";

        // par exemple, lit un entier:
        int i;
        input >> i;
        // par exemple, lit un mot (s'arrête à un caractères de séparation.
        std::string s;
        input >> s;   
        // par exemple, lit toute une ligne dans une chaîne de caractères.
        std::getline( input, str );
        if (( str != "" ) && (str[0]=='#')) 
          std::cout << "C'est un commentaire shell !";
        }



      GrayLevelImage2D::bool exportPGM( std::ostream & output, bool ascii = true ){
         GrayImage2D img( 256, 256, 255);
         Iterator it = img.begin;

         for ( int y = 0; y < 256; y++ ){
            for ( int x = 0; x < 256; x++ )
              {
                *it++ = img.att(y,x)=150;
              }
            }

        std::ofstream output( "testImg.pgm", ios::binary ); // ios::binary for Windows system
        output << "P1" << std::endl; 
        output << "CREATOR : OYOYOO" << std::endl;
        output << img.w() << " " << img.h() << std::endl;
        output << "255" << std::endl;
        for ( Iterator it = img.begin(), itEnd = img.end(); it != itEnd; it++ ) // (*)
          { 
            
            output << img.att();
          }
        output.close();
        return 0;
      }


    