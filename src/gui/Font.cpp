#include "Font.hpp"

namespace gui
{

//--------------------------------------------------------------------------------------------------
Font::Font(const std::string& fontName, const std::string& fontFile, int color, bool doubleSize)
: fontName(fontName)
{  
  // Carga el archivo.
  BITMAP* bitmapFont = load_bitmap(fontFile.c_str(), 0);
  assert(bitmapFont);
  
  // Duplica su tamaño, si procede.
  if(doubleSize)
  {
    BITMAP* bmp = create_bitmap_ex(bitmap_color_depth(bitmapFont), bitmapFont->w, bitmapFont->h << 1);
    stretch_blit(bitmapFont, bmp, 0, 0, bitmapFont->w, bitmapFont->h, 0, 0, bmp->w, bmp->h);
    destroy_bitmap(bitmapFont);
    bitmapFont = bmp;
  }
  
  // Colorea los caracteres, si procede.
  if(color != makecol(255, 255, 255))
  {
    for(int x = 0; x < bitmapFont->w; x++)
    {
      for(int y = 0; y < bitmapFont->h; y++)
      {
        if(((int*)bitmapFont->line[y])[x] == makecol(255, 255, 255))
        {
          ((int*)bitmapFont->line[y])[x] = color;
        }
      }
    }
  }

  // Si se cargado correctamente entonces se inicia la descomposición de la imagen.
  if(bitmapFont != 0)
  {
    this->charWidth = bitmapFont->w / CharactersPerRow;
    this->charHeight = bitmapFont->h / RowsPerBitmapFont;
    
    for(int y = 0; y < bitmapFont->h; y += this->charHeight)
    {
      for(int x = 0; x < bitmapFont->w; x += this->charWidth)
      {
        BITMAP* bitmapChar = create_bitmap_ex(32, charWidth, charHeight);
        blit(bitmapFont, bitmapChar, x, y, 0, 0, charWidth, charHeight);
        charVector.push_back(bitmapChar);
      }
    }
  }
  
  // La creación ha finalizado.
  destroy_bitmap(bitmapFont);
}

//--------------------------------------------------------------------------------------------------
Font::~Font()
{
  std::for_each(charVector.begin(), charVector.end(), destroy_bitmap);
}

//--------------------------------------------------------------------------------------------------
BITMAP* Font::getChar(const std::string& character)
{
  for(int i = 0; i < CharactersArraySize; i++)
  {
    if(character.compare(gui::characters[i]) == 0)
    {
      return charVector.at(i);
    }
  }
  
  // Si se ha llegado aquí entonces el carácter no se ha encontrado.
  // Se devuelve el carácter '?'.
  return charVector.at('?' - 32);
}

}
