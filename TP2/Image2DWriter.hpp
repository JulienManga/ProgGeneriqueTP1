#ifndef _IMAGE2DWRITER_HPP_
#define _IMAGE2DWRITER_HPP_
#include <iostream>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
//#include "Accessor.hpp"
#include <stdlib.h>

#include "Color.hpp"
#include "Image2D.hpp"


using namespace std;

template <typename TValue>
class Image2DWriter {
public:
  typedef TValue Value;
  typedef Image2D<Value> Image;
  static bool write( Image & img, std::ostream & output, bool ascii )
  {
    
    std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
    return false;
  }
};
/// Specialization for gray-level images.
template <>
class Image2DWriter<unsigned char> {
public:
  typedef unsigned char Value;
  typedef Image2D<Value> Image;
  static bool write( Image & img, std::ostream & output, bool ascii )
  {

    // Reprenez votre code du TP1.
    if (ascii){
        output<<"P2";
    }else{
        output<<"P5";
    }
    output<<endl<<"#generated by us"<<endl<<img.h()<<' '<<img.w()<<endl<<255<<endl;
    for (int i = 0; i < img.w(); i++){
        for (int j = 0; j < img.h(); j++){
            if(ascii){
                output<<(int)img.at(i, j);
            }else {
                output<<(char)img.at(i,j);
               
            }
        }
    }
   
  return true;
      
  }
};
/// Specialization for color images.
template <>
class Image2DWriter<Color> {
public:
  typedef Color Value;
  typedef Image2D<Value> Image;
  static bool write( Image & img, std::ostream & output, bool ascii )
  {

    
    // Reprenez la partie sauvegarde de l'exemple précédent testColorImage2D.cpp
    typedef Image2D<Color> ColorImage2D;
  typedef ColorImage2D::Iterator Iterator;
 
  Iterator it = img.begin();

 // ios::binary for Windows system
  output << "P6" << std::endl; // PPM raw
  output << "# Generated by You !" << std::endl;
  output << img.w() << " " << img.h() << std::endl;
  output << "255" << std::endl;
  for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it ) // (*)
    { 
      Color c = *it;
      output << c.red << c.green << c.blue;
      
    }
  
  return true;
  }




 
};

#endif