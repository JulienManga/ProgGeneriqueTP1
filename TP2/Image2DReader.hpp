#ifndef _IMAGE2DREADER_HPP_
#define _IMAGE2DREADER_HPP_
#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"
#include <fstream>
#include "GrayLevelImage2D.hpp"
using namespace std;



template <typename TValue>
class Image2DReader {
public:
  typedef TValue Value;
  typedef Image2D<Value> Image;
  static bool read( Image & img, std::ostream & output, bool ascii )
  {
    
    std::cerr << "[Image2DReader<TValue>::read] NOT IMPLEMENTED." << std::endl;
    return false;
  }
};

template <>


class Image2DReader<unsigned char> {
public:
  typedef unsigned char Value;
  typedef Image2D<Value> Image;;

  static bool read( Image & img , std::istream & input ){
  if (input.good()){
    std::string s;
    std::string commentary;
    std::getline(input, s);
    std::getline(input, commentary);
    int w, h, cmax;
    input>>w>>h>>cmax;
    img.resize(w,h);
    if (s[1] == '5'){
      char lect;
      input >> std::noskipws;
      for (int i = 0; i < w; i++){
          for (int j = 0; j < h; j++){
              input >> lect;
              img.at(i, j) = lect;
          }
      }
    }else{
      int lect;
      for (int i = 0; i < w; i++){
          for (int j = 0; j < h; j++){
              input >> lect;
              img.at(i, j) = lect;
          }
      }
    }
     return true;
  }else{
    return false;
  }
        }
   
  
};

template <>
class Image2DReader<Color> {
public:
  typedef Color Value;
  typedef Image2D<Value> Image;
  //static bool write( Image & img, std::ostream & output, bool ascii )
  typedef Image2D<Color> ColorImage2D;
  typedef ColorImage2D::Iterator Iterator;

  static  bool read( Image & img,std::istream & input ){
      // Ouvre le flux en entrée sur le fichier "toto.pgm"
    if (input.good()){
    std::string s;
    std::string commentary;
    std::getline(input, s);
    std::getline(input, commentary);
    int w, h, cmax;
    input>>w>>h>>cmax;
    img.resize(w,h);
    if (s[1] == '6'){
      char r,v,b;
      input >> std::noskipws;
      for (Image::Iterator i = img.begin(), j = img.end(); i != j; i++){
          
              input >> r >> v >> b;
              *i = Color(r,v,b);
      }
  }
          
      
    else{

    	char r,v,b;
      for (Image::Iterator i = img.begin(), j = img.end(); i != j; i++){
          
              input >> r >> v >> b;
              *i = Color(r,v,b);
      
      }
    
    
     return true;
  }} else{
    return false;
  }
        
        
    }
};


#endif