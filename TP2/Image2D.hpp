// file Image2D.hpp
#ifndef _IMAGE2D_HPP_
#define _IMAGE2D_HPP_
#include <vector>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
using namespace std;
/// Classe générique pour représenter des images 2D.
template <typename TValue>
class Image2D {
public:
  typedef Image2D<TValue>    Self;      // le type de *this
  typedef TValue             Value;     // le type pour la valeur des pixels
  typedef std::vector<Value> Container; // le type pour stocker les valeurs des pixels de l'image.
  // Constructeur par défaut
  Image2D();
  // Constructeur avec taille w x h. Remplit tout avec la valeur g
  // (par défaut celle donnée par le constructeur par défaut).
  Image2D( int w, int h, Value g = Value() );
  
  // Remplit l'image avec la valeur \a g.
  void fill( Value g );
  
  /// @return la largeur de l'image.
  int w() const;
  /// @return la hauteur de l'image.
  int h() const;
  
  /// Accesseur read-only à la valeur d'un pixel.
  /// @return la valeur du pixel(i,j)
  Value at( int i, int j ) const;
  
  /// Accesseur read-write à la valeur d'un pixel.
  /// @return une référence à la valeur du pixel(i,j)
  Value& at( int i, int j );

    Iterator begin();
    Iterator end();
    Iterator start( int x, int y );

    std::pair<int,int> position( Iterator it ) const;

    bool importPGM( std::istream & input );
    bool exportPGM( std::ostream & output, bool ascii);
//  int index( int x, int y ) const;

    void resize(int w,int h);
  
private:
  Container m_data; // mes données; évitera de faire les allocations dynamiques
  int m_width; // ma largeur
  int m_height; // ma hauteur
  
  /// @return l'index du pixel (x,y) dans le tableau \red m_data.
  int index( int i, int j ) const;

public:

Image2D(int w,int h,Value g)
{

    m_data.resize(w*h);
    m_data.assign(w*h,g);
    m_width = w;
    m_height = h;
    //ctor
}

Image2D<TValue>::Image2D(){
  m_width = 0;
  m_height = 0;
}

void resize(int w,int h){
  m_data.resize(0);
  m_width = 0;
  m_height = 0;
  };



/*Image2D::~Image2D()
{
    //dtor


}*/
  void Image2D(Value g){
    m_data.assign(w*h,g);
  }


  /// @return la largeur de l'image.
int w() const{

    return m_width;
    }
  /// @return la hauteur de l'image.
int h() const{

    return m_height;
    }







 int index( int x, int y ) const {
        return x+y*w();
   }



   int index( int x, int y ) {
        return x+y*w();
   }



   Image2D::Value at( int i, int j ) const {
        return m_data[index(i,j)];

    }

    /**
       Accesseur read-write à la valeur d'un pixel.
       @return une référence à la valeur du pixel(i,j)
    */
    Image2D::Value& at( int i, int j ) {
        Value& tmp=m_data[index(i,j)];
        return tmp;

    }
    //! [gli2d-sec3]
    Image2D::Iterator start(int x, int y){
      return Iterator(*this,x,y);

      
    }

    Image2D::Iterator begin(){
      return start(0,0);

    }

    Image2D::Iterator end(){
      return start(0,h());
    }

   bool importPGM( std::istream & input ){
      // Ouvre le flux en entrée sur le fichier "toto.pgm"
    if (input.()){
    std::string s;
    std::string commentary;
    std::getline(input, s);
    std::getline(input, commentary);
    int w, h, cmax;
    input>>w>>h>>cmax;
    resize(w,h);
    if (s[1] == '5'){
      char lect;
      input >> std::noskipws;
      for (int i = 0; i < w; i++){
          for (int j = 0; j < h; j++){
              input >> lect;
              at(i, j) = lect;
          }
      }
    }else{
      int lect;
      for (int i = 0; i < w; i++){
          for (int j = 0; j < h; j++){
              input >> lect;
              at(i, j) = lect;
          }
      }
    }
    return true;
  }else{
    return false;
  }
        }



    bool exportPGM( std::ostream & output, bool ascii = true ){
         if (ascii){
        output<<"P2";
    }else{
        output<<"P5";
    }
    output<<endl<<"#generated by us"<<endl<<h()<<' '<<w()<<endl<<255<<endl;
    for (int i = 0; i < w(); i++){
        for (int j = 0; j < h(); j++){
            if(ascii){
                output<<(int)at(i, j);
            }else {
                output<<(char)at(i,j);
            }
        }
    }
  return true;
      }





