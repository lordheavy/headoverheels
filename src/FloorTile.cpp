#include "FloorTile.hpp"
#include "Mediator.hpp"

namespace isomot
{
  
//--------------------------------------------------------------------------------------------------
FloorTile::FloorTile() : RoomComponent()
{
  this->column = 0;
  this->coordinates.first = this->coordinates.second = 0;
  this->offset.first = this->offset.second = 0;
  this->image = 0;
  this->shadyImage = 0;
  this->shadeStatus = NoShadow;
}

//--------------------------------------------------------------------------------------------------
FloorTile::FloorTile(int column, int x, int y, BITMAP* image) : RoomComponent()
{
  this->column = column;
  this->coordinates.first = x;
  this->coordinates.second = y;
  this->offset.first = this->offset.second = 0;
  this->image = image;
  this->shadyImage = 0;
  this->shadeStatus = NoShadow;
}

//--------------------------------------------------------------------------------------------------
FloorTile::~FloorTile()
{
  if(image != 0) destroy_bitmap(image);
  if(shadyImage != 0) destroy_bitmap(shadyImage);
}

//--------------------------------------------------------------------------------------------------
void FloorTile::calculateOffset()
{
  if(this->image)
  {
    this->offset.first = mediator->getX0() + ((mediator->getTileSize() * (coordinates.first - coordinates.second - 1)) << 1) + 1;
    this->offset.second = mediator->getY0() + mediator->getTileSize() * (coordinates.first + coordinates.second);
  }
}

//--------------------------------------------------------------------------------------------------
void FloorTile::draw(BITMAP* destination)
{
  // Lo loseta está sombreada.
  if(this->shadyImage)
  {
    draw_sprite(destination, this->shadyImage, this->offset.first, this->offset.second);
  }
  // La loseta no tiene sombra.
  else if(this->image)
  {
    draw_sprite(destination, this->image, this->offset.first, this->offset.second);
  }
}

//--------------------------------------------------------------------------------------------------
void FloorTile::requestCastShadow()
{
  if(this->image && this->shadeStatus == MustBeShady)
  {
    mediator->castShadow(this);

    // Si no se ha podido sombrear entonces se destruye la imagen de sombreado.
    if(this->shadeStatus != Shady && this->shadyImage)
    {
      destroy_bitmap(this->shadyImage);
      this->shadyImage = 0;
    }

    // Reinicia el atributo para el siguiente ciclo.
    this->shadeStatus = NoShadow;
  }
}

//--------------------------------------------------------------------------------------------------
void FloorTile::castShadowImage(int x, int y, BITMAP* shadow, short shadingScale, unsigned char transparency)
{
  // El sombreado se realiza si el elemento que sombrea no es totalmente transparente.
  if(transparency < 100)
  {
    // Coordenada inicial X.
    int sx = x - this->offset.first;
    if(sx < 0) sx = 0;
    // Coordenada inicial Y.
    int sy = y - this->offset.second;
    if(sy < 0) sy = 0;
    // Coordenada final X.
    int ex = x - this->offset.first + shadow->w;
    if(ex > this->image->w) ex = this->image->w;
    // Coordenada final Y.
    int ey = y - this->offset.second + shadow->h;
    if(ey > this->image->h) ey = this->image->h;

    // Índice para recorrer las filas de píxeles de la imágenes image y shadyImage de la loseta.
    int iRow = 0;
    // Índice para recorrer las filas de píxeles de la imagen shadow del elemento que sombrea.
    int sRow = 0;
    // Índice para recorrer la componente roja de los píxeles de una fila de las imágenes image y shadyImage de la loseta.
    int iRpx = 0;
    // Índice para recorrer la componente verde de los píxeles de una fila de las imágenes image y shadyImage de la loseta.
    int iGpx = 0;
    // Índice para recorrer la componente azul de los píxeles de una fila de las imágenes image y shadyImage de la loseta.
    int iBpx = 0;
    // Índice para recorrer los píxeles de una fila de la imagen shadow del elemento que sombrea.
    int sPixel = 0;

    // Las coordenadas iniciales tienen que ser menores a las finales.
    if(sy < ey && sx < ex)
    {
      int n2i = sx + this->offset.first - x;

      // En principio, la imagen de la loseta sombreada es la imagen de la loseta sin sombrear.
      if(!this->shadyImage)
      {
        this->shadyImage = create_bitmap_ex(bitmap_color_depth(this->image), this->image->w, this->image->h);
      }
      if(this->shadeStatus == MustBeShady)
      {
        blit(this->image, this->shadyImage, 0, 0, 0, 0, this->image->w, this->image->h);
        this->shadeStatus = Shady;
      }

      // Incremento de los índices iRpx, iGpx e iBpx.
      char iInc = (bitmap_color_depth(this->image) == 32 ? 4 : 3);
      // Incremento del índice sPixel.
      char sInc = (bitmap_color_depth(shadow) == 32 ? 4 : 3);

      // Grado de opacidad del sombreado desde 0 a 255, siendo 0 la opacidad total y 255
      // casi la transparencia total.
      short opacity = short(((256.0 - shadingScale) / 100) * transparency + shadingScale);

      ex *= iInc;
      sx = sx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
      n2i = n2i * sInc + IS_BIG_ENDIAN(bitmap_color_depth(shadow));

      // La opacidad es potencia de dos en el intervalo [2,128].
      if(int(pow(2, log10(opacity) / log10(2))) == opacity)
      {
        // Divisor del píxel.
        char pxDiv = 7;

        // En función de la opacidad de la sombra se halla
        // el valor del divisor del píxel: píxel / 2^pxDiv.
        while(opacity != 2)
        {
          opacity = opacity >> 1;
          pxDiv--;
        }

        // Se recorren las filas de las tres imágenes entre los límites calculados.
        for(iRow = sy, sRow = sy + this->offset.second - y; iRow < ey; iRow++, sRow++)
        {
          unsigned char* sln = shadow->line[sRow];
          unsigned char* iln = this->image->line[iRow];
          unsigned char* rln = this->shadyImage->line[iRow];

          // Se recorren los píxeles de cada fila según los límites calculados.
          for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
          {
            // Si el píxel de las tres imágenes no tiene el color clave (255,0,255)
            // entonces el píxel de la imagen resultante se divide entre 2^pxDiv, es decir, se oscurece.
            if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
               (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]) &&
               (sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255))
            {
              rln[iRpx] = iln[iRpx] >> pxDiv;
              rln[iGpx] = iln[iGpx] >> pxDiv;
              rln[iBpx] = iln[iBpx] >> pxDiv;
            }
          }
        }
      }
      // La opacidad no es potencia de dos.
      else
      {
        // La opacidad no es cero, es decir, hay cierta transparencia.
        if(opacity)
        {
          // Se recorren las filas de las tres imágenes entre los límites calculados.
          for(iRow = sy, sRow = sy + this->offset.second - y; iRow < ey; iRow++, sRow++)
          {
            unsigned short color;
            unsigned char* sln = shadow->line[sRow];
            unsigned char* iln = this->image->line[iRow];
            unsigned char* rln = this->shadyImage->line[iRow];

            // Se recorren los píxeles de cada fila según los límites calculados.
            for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
            {
              // Si el píxel de las tres imágenes no tiene el color clave (255,0,255)
              // entonces el píxel de la imagen resultante se decrementa su valor para oscurecerlo.
              if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
                 (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]) &&
                 (sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255))
              {
                color = iln[iRpx] * opacity;
                rln[iRpx] = (unsigned char)(color >> 8);
                color = iln[iGpx] * opacity;
                rln[iGpx] = (unsigned char)(color >> 8);
                color = iln[iBpx] * opacity;
                rln[iBpx] = (unsigned char)(color >> 8);
              }
            }
          }
        }
        // La opacidad es cero, es decir, la opacidad es total.
        else
        {
          // Se recorren las filas de las tres imágenes entre los límites calculados.
          for(iRow = sy, sRow = sy + this->offset.second - y; iRow < ey; iRow++, sRow++)
          {
            unsigned char* sln = shadow->line[sRow];
            unsigned char* iln = this->image->line[iRow];
            unsigned char* rln = this->shadyImage->line[iRow];

            // Se recorren los píxeles de cada fila según los límites calculados.
            for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
            {
              // Si el píxel de las tres imágenes no tiene el color clave (255,0,255)
              // entonces el píxel de la imagen resultante se cero, totalmente negro.
              if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
                 (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]) &&
                 (sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255))
              {
                rln[iRpx] = rln[iRpx + 1] = rln[iRpx + 2] = 0;
              }
            }
          }
        }
      }
    }
  }
}

}
