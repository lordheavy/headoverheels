#include "GridItem.hpp"
#include "ItemData.hpp"
#include "Mediator.hpp"

namespace isomot
{

//--------------------------------------------------------------------------------------------------
GridItem::GridItem(ItemData* itemData, int cx, int cy, int z, const Direction& direction)
: Item(itemData, z, direction)
{
  this->cell.first = cx;
  this->cell.second = cy;
  
  // Coordenadas libres del elemento rejilla.
  this->x = cx * this->itemData->widthX;
  this->y = (cy + 1) * this->itemData->widthY - 1;
  
  // Imágenes iniciales.
  this->image = itemData->motion[itemData->motion.size() / itemData->directionFrames * direction];
  // Puede no tener sombra.
  if(itemData->shadowWidth != 0 && itemData->shadowHeight != 0)
  {
    this->shadow = itemData->shadows[itemData->motion.size() / itemData->directionFrames * direction];
  }
}

//--------------------------------------------------------------------------------------------------
GridItem::~GridItem()
{
  
}

//--------------------------------------------------------------------------------------------------
void GridItem::draw(BITMAP* destination)
{
  // El elemento está sombreado.
  if(this->processedImage)
  {
    draw_sprite(destination, this->processedImage, mediator->getX0() + this->offset.first, mediator->getY0() + this->offset.second);
  }
  // El elemento no tiene sombra.
  else if(this->image)
  {
    draw_sprite(destination, this->image, mediator->getX0() + this->offset.first, mediator->getY0() + this->offset.second);
  }
}

//--------------------------------------------------------------------------------------------------
void GridItem::changeImage(BITMAP* image)
{
  // Si el elemento no tiene ninguna imagen entonces simplemente se asigna. Se entiende que este
  // caso sucede únicamente durante la creación del elemento.
  if(this->image == 0)
  {
    // Asignación de la imagen.
    this->image = image;
  }
  // En caso contrario se realiza el cambio.
  else
  {
    // Copia el elemento antes de realizar el cambio.
    GridItem oldGridItem(*this);

    // Cambio de imagen.
    this->image = image;

    // Si el elemento tiene una imagen procesada entonces hay que volver a crearla.
    if(this->processedImage)
    {
      destroy_bitmap(this->processedImage);
      this->processedImage = 0;
    }

    // Hay que calcular el nuevo desplazamiento de la imagen a no ser que sea nula.
    if(this->image)
    {
      // Si las sombras están activas el elemento debe sombrearse.
      if(mediator->getShadingScale() < 256)
      {
        this->shadeStatus = MustBeShady;
      }
      
      // A cuántos píxeles está la imagen del punto origen de la sala.
      this->offset.first = ((mediator->getTileSize() * (this->cell.first - this->cell.second)) << 1) - (image->w >> 1) + 1;
      this->offset.second = mediator->getTileSize() * (this->cell.first + this->cell.second + 2) - image->h - this->z - 1;
    }
    else
    {
      this->offset.first = this->offset.second = 0;
    }
    
    // Se marcan para enmascar los elementos libres afectados por la antigua imagen.
    if(oldGridItem.getImage())
    {
      mediator->markItemsForMasking(&oldGridItem);
    }
    // Se marcan para enmascar los elementos libres afectados por la nueva imagen.
    if(this->image)
    {
      mediator->markItemsForMasking(this);
    }
  }
}

//--------------------------------------------------------------------------------------------------
void GridItem::changeShadow(BITMAP* shadow)
{
  // Si el elemento no tiene ninguna sombra entonces simplemente se asigna. Se entiende que este
  // caso sucede únicamente durante la creación del elemento.
  if(this->shadow == NULL)
  {
    // Asignación de la sombra
    this->shadow = shadow;
  }
  // En caso contrario se realiza el cambio.
  else
  {
    // Cambio de la sombra.
    this->shadow = shadow;
    
    // Hay que calcular a qué elementos se sombreará, a no ser que la nueva sombra sea nula.
    if(this->image)
    {
      // Si las sombras están activas los elementos deben sombrearse.
      if(mediator->getShadingScale() < 256)
      {
        mediator->markItemsForShady(this);
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------
void GridItem::requestCastShadow(int column)
{
  if(this->image && this->shadeStatus == MustBeShady)
  {
    mediator->castShadow(this);
    
    // Si no se ha podido sombrear entonces se destruye la imagen de sombreado.
    if(this->shadeStatus != Shady && this->processedImage)
    {
      destroy_bitmap(this->processedImage);
      this->processedImage = 0;
    }
    
    // Reinicia el atributo para el siguiente ciclo.
    this->shadeStatus = NoShadow;
  }
}

//--------------------------------------------------------------------------------------------------
void GridItem::castShadowImage(int x, int y, BITMAP* shadow, short shadingScale, unsigned char transparency)
{
  // El sombreado se realiza si el elemento que sombrea no es totalmente transparente.
  if(transparency < 100)
  { 
    // Anchura del elemento.
    int width = this->itemData->widthX;
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
    // Coordenada intermedia Y.
    int my = this->image->h - width - this->itemData->height + 1;
    if(ey < my) my = ey;
    if(ey > my + width) ey = my + width;

    // Índice para recorrer las filas de píxeles de la imágenes image y processedImage del elemento
    int iRow = 0;
    // Índice para recorrer las filas de píxeles de la imagen shadow del elemento que sombrea.
    int sRow = 0;
    // Índice para recorrer la componente roja de los píxeles de una fila de las imágenes image y processedImage del elemento
    int iRpx = 0;
    // Índice para recorrer la componente verde de los píxeles de una fila de las imágenes image y processedImage del elemento
    int iGpx = 0;
    // Índice para recorrer la componente azul de los píxeles de una fila de las imágenes image y processedImage del elemento
    int iBpx = 0;
    // Índice para recorrer los píxeles de una fila de la imagen shadow del elemento que sombrea.
    int sPixel = 0;
    // Primera componente del primer píxel (el situado más a la izquierda) donde comienza el sombreado lateral.
    int ltpx = 0;
    // Segunda componente del primer píxel (el situado más a la izquierda) donde comienza el sombreado lateral.
    int ltpx1 = 0;
    // Primera componente del último píxel (el situado más a la derecha) donde termina el sombreado lateral.
    int rtpx = 0;
    // Segunda componente del último píxel (el situado más a la derecha) donde termina el sombreado lateral.
    int rtpx1 = 0;
    
    // Las coordenadas iniciales tienen que ser menores a las finales.
    if(sy < ey && sx < ex)
    {
      int n2i = sx + this->offset.first - x;

      // En principio, la imagen del elemento sombreado es la imagen del elemento sin sombrear.
      if(!this->processedImage)
      {
        this->processedImage = create_bitmap_ex(bitmap_color_depth(this->image), this->image->w, this->image->h);
      }
      if(this->shadeStatus == MustBeShady)
      {
        blit(this->image, this->processedImage, 0, 0, 0, 0, this->image->w, this->image->h);
        this->shadeStatus = Shady;
      }

      // Incremento de los índices iRpx, iGpx e iBpx.
      char iInc = (bitmap_color_depth(this->image) == 32 ? 4 : 3);
      // Incremento del índice sPixel.
      char sInc = (bitmap_color_depth(shadow) == 32 ? 4 : 3);

      // Grado de opacidad del sombreado desde 0 a 255, siendo 0 la opacidad total y 255
      // casi la transparencia total.
      short opacity = short(((256.0 - shadingScale) / 100) * transparency + shadingScale);
      
      ex = ex * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
      sx = sx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
      n2i = n2i * sInc + IS_BIG_ENDIAN(bitmap_color_depth(shadow));
      
      unsigned char* lm;
      unsigned char* ln;
      
      // Si la opacidad es potencia de 2 en el intervalo [2,128]
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
        
        // Sombreado de la superficie del elemento, la parte superior.
        // Se recorren las filas de las tres imágenes entre los límites calculados.
        for(iRow = sy, sRow = sy + this->offset.second - y; iRow < my; iRow++, sRow++)
        {
          unsigned char* sln = shadow->line[sRow];
          unsigned char* iln = this->image->line[iRow];
          unsigned char* rln = this->processedImage->line[iRow];
          
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
        
        // Sombreado de los laterales del elemento.
        ltpx = ((this->image->w) >> 1) - (width << 1) + ((iRow - my) << 1);
        rtpx = ((this->image->w) >> 1) + (width << 1) - ((iRow - my) << 1) - 2;
        ltpx = ltpx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
        rtpx = rtpx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
        
        for(ltpx1 = ltpx + iInc, rtpx1 = rtpx + iInc; iRow < ey; iRow++, sRow++, ltpx += 2 * iInc, ltpx1 += 2 * iInc, rtpx -= 2 * iInc, rtpx1 -= 2 * iInc)
        {
          unsigned char* sln = shadow->line[sRow];
          unsigned char* iln = this->image->line[iRow];
          unsigned char* rln = this->processedImage->line[iRow];
          
          if(sx < ltpx)
          {
            sx = ltpx;
            n2i = sx + (this->offset.first - x) * sInc + IS_BIG_ENDIAN(bitmap_color_depth(shadow));
          }
          
          if(ex > rtpx + 2 * iInc)
          {
            ex = rtpx + 2 * iInc;
          }
          
          for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
          {  
            if(sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255)
            {
              if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
                 (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]))
              {
                rln[iRpx] = iln[iRpx] >> pxDiv;
                rln[iGpx] = iln[iGpx] >> pxDiv;
                rln[iBpx] = iln[iBpx] >> pxDiv;
              }
                
              if(iRpx == ltpx || iRpx == ltpx1 || iRpx == rtpx || iRpx == rtpx1)
              {
                for(int yy = iRow + 1; yy < image->h; yy++)
                {
                  lm = this->image->line[yy];
                  ln = this->processedImage->line[yy];
                  
                  if((lm[iRpx] < 255 || lm[iGpx] || lm[iBpx] < 255) &&
                     (lm[iRpx] == ln[iRpx] && lm[iGpx] == ln[iGpx] && lm[iBpx] == ln[iBpx]))
                  {
                    ln[iRpx] = lm[iRpx] >> pxDiv;
                    ln[iGpx] = lm[iGpx] >> pxDiv;
                    ln[iBpx] = lm[iBpx] >> pxDiv;
                  }
                }
              }
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
          for(iRow = sy, sRow = sy + this->offset.second - y; iRow < my; iRow++, sRow++)
          {
            unsigned short color;
            unsigned char* sln = shadow->line[sRow];
            unsigned char* iln = this->image->line[iRow];
            unsigned char* rln = this->processedImage->line[iRow];
            
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
          
          ltpx = ((this->image->w) >> 1) - 2 * width + 2 * (iRow - my);
          rtpx = ((this->image->w) >> 1) + 2 * width - 2 * (iRow - my) - 2;
          ltpx = ltpx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
          rtpx = rtpx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
          
          for(ltpx1 = ltpx + iInc, rtpx1 = rtpx + iInc; iRow < ey; iRow++, sRow++, ltpx += 2 * iInc, ltpx1 += 2 * iInc, rtpx -= 2 * iInc, rtpx1 -= 2 * iInc)
          {
            unsigned char* sln = shadow->line[sRow];
            unsigned char* iln = this->image->line[iRow];
            unsigned char* rln = this->processedImage->line[iRow];
            
            if(sx < ltpx)
            {
              sx = ltpx;
              n2i = sx + (this->offset.first - x) * sInc + IS_BIG_ENDIAN(bitmap_color_depth(shadow));
            }
            
            if(ex > rtpx + 2 * iInc)
            {
              ex = rtpx + 2 * iInc;
            }
            
            for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
            {
              if(sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255)
              {
                if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
                   (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]))
                {
                  unsigned short color;
                  color = iln[iRpx] * opacity;
                  rln[iRpx] = (unsigned char)(color >> 8);
                  color = iln[iGpx] * opacity;
                  rln[iGpx] = (unsigned char)(color >> 8);
                  color = iln[iBpx] * opacity;
                  rln[iBpx] = (unsigned char)(color >> 8);
                  
                  if(iRpx == ltpx || iRpx == ltpx1 || iRpx == rtpx || iRpx == rtpx1)
                  {
                    for(int yy = iRow + 1;yy < image->h;yy++)
                    {
                      lm = this->image->line[yy];
                      ln = this->processedImage->line[yy];
                      
                      if((lm[iRpx] < 255 || lm[iGpx] || lm[iBpx] < 255) &&
                         (lm[iRpx] == ln[iRpx] && lm[iGpx] == ln[iGpx] && lm[iBpx] == ln[iBpx]))
                      {
                        color = lm[iRpx] * opacity;
                        ln[iRpx] = (unsigned char)(color >> 8);
                        color = lm[iGpx] * opacity;
                        ln[iGpx] = (unsigned char)(color >> 8);
                        color = lm[iBpx] * opacity;
                        ln[iBpx] = (unsigned char)(color >> 8);
                      }
                    }
                  }
                }
              }
            }
          }
        }
        // La opacidad es cero, es decir, la opacidad es total.
        else
        {
          // Se recorren las filas de las tres imágenes entre los límites calculados.
          for(iRow = sy, sRow = sy + this->offset.second - y; iRow < my; iRow++, sRow++)
          {
            unsigned char* sln = shadow->line[sRow];
            unsigned char* iln = this->image->line[iRow];
            unsigned char* rln = this->processedImage->line[iRow];
            
            // Se recorren los píxeles de cada fila según los límites calculados.
            for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
            {
              // Si el píxel de las tres imágenes no tiene el color clave (255,0,255)
              // entonces el píxel de la imagen resultante se cero, totalmente negro.
              if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
                 (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]) &&
                 (sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255))
              {
                rln[iRpx] = rln[iGpx] = rln[iBpx] = 0;
              }
            }
          }
          
          ltpx = ((this->image->w) >> 1) - 2 * width + 2 * (iRow - my);
          rtpx = ((this->image->w) >> 1) + 2 * width - 2 * (iRow - my) - 2;
          ltpx = ltpx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
          rtpx = rtpx * iInc + IS_BIG_ENDIAN(bitmap_color_depth(this->image));
          
          for(ltpx1 = ltpx + iInc, rtpx1 = rtpx + iInc; iRow < ey; iRow++, sRow++, ltpx += 2 * iInc, ltpx1 += 2 * iInc, rtpx -= 2 * iInc, rtpx1 -= 2 * iInc)
          {
            unsigned char* sln = shadow->line[sRow];
            unsigned char* iln = this->image->line[iRow];
            unsigned char* rln = this->processedImage->line[iRow];
            
            if(sx < ltpx)
            {
              sx = ltpx;
              n2i = sx + (this->offset.first - x) * sInc + IS_BIG_ENDIAN(bitmap_color_depth(shadow));
            }
            
            if(ex > rtpx + 2 * iInc)
            {
              ex = rtpx + 2 * iInc;
            }
            
            for(iRpx = sx, iGpx = sx + 1, iBpx = sx + 2, sPixel = n2i; iRpx < ex; iRpx += iInc, iGpx += iInc, iBpx += iInc, sPixel += sInc)
            {
              if(sln[sPixel] < 255 || sln[sPixel + 1] || sln[sPixel + 2] < 255)
              {
                if((iln[iRpx] < 255 || iln[iGpx] || iln[iBpx] < 255) &&
                   (iln[iRpx] == rln[iRpx] && iln[iGpx] == rln[iGpx] && iln[iBpx] == rln[iBpx]))
                {
                  rln[iRpx] = rln[iGpx] = rln[iBpx] = 0;
                  
                  if(iRpx == ltpx || iRpx == ltpx1 || iRpx == rtpx || iRpx == rtpx1)
                  {
                    for(int yy = iRow + 1; yy < this->image->h; yy++)
                    {
                      lm = this->image->line[yy];
                      ln = this->processedImage->line[yy];
                      
                      if((lm[iRpx] < 255 || lm[iGpx] || lm[iBpx] < 255) &&
                         (lm[iRpx] == ln[iRpx] && lm[iGpx] == ln[iGpx] && lm[iBpx] == ln[iBpx]))
                      {
                        ln[iRpx] = ln[iGpx] = ln[iBpx] = 0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------
bool GridItem::changeZ(int value)
{
  return changeData(value, CoordinateZ, Change); 
}

//--------------------------------------------------------------------------------------------------
bool GridItem::addZ(int value)
{
  return changeData(value, CoordinateZ, Add); 
}

//--------------------------------------------------------------------------------------------------
bool GridItem::changeHeight(int value)
{
  return changeData(value, Height, Change); 
}

//--------------------------------------------------------------------------------------------------
bool GridItem::addHeight(int value)
{ 
  return changeData(value, Height, Add); 
}

//--------------------------------------------------------------------------------------------------
bool GridItem::changeData(int value, const Datum& datum, const Mode& mode)
{
  bool collisionFound = false;

  // Vacía la pila de colisiones.
  mediator->clearCollisionStack();
  
  // Copia el elemento antes de realizar el movimiento.
  GridItem oldGridItem(*this);
  
  // Calcula el nuevo valor dependiendo del dato y el modo elegidos.
  if(datum == CoordinateZ)
  {
    this->z = value + this->z * mode;
  }
  else if(datum == Height)
  {
     this->itemData->height = value + this->itemData->height * mode;
  }
  
  // Si ha habido colisión con el suelo se interrumpe el proceso.
  if(this->z < 0)
  {
    mediator->pushCollision(Floor);
    collisionFound = true;
  }
  // En caso contrario se buscan colisiones con otros elementos.
  else
  {
    // Si hay colisión se interrumpe el proceso.
    if(!(collisionFound = mediator->findCollision(this)))
    {
      // Si el elemento rejilla tiene imagen se marcan para enmascarar los elementos
      // libres cuyas imágenes se solapen con la suya y espacialmente queden detrás suyo.
      if(this->image)
      {
        // A cuántos píxeles está la imagen del punto origen de la sala. Sólo cambia el
        // valor en el eje Y pues es el que depende de la coordenada Z.
        this->offset.second = mediator->getTileSize() * (this->cell.first + this->cell.second + 2) - this->image->h - this->z - 1;
        
        mediator->markItemsForMasking(&oldGridItem);
        mediator->markItemsForMasking(this);
      }
      else
      {
        this->offset.first = this->offset.second = 0;
      }
      
      // Si cambió la posición Z y las sombras están activas se buscan qué elementos hay que 
      // volver a sombrear.
      if(datum == CoordinateZ && mediator->getShadingScale() < 256)
      {
        if(this->z > oldGridItem.getZ())
        {
          mediator->markItemsForShady(this);
        }
        else
        {
          mediator->markItemsForShady(&oldGridItem);
        }
      }
      
      // Se ordena la columna de elementos rejilla.
      mediator->activateGridItemsSorting();
    }
  }
  
  // Si se hubo colisión se restauran los valores anteriores.
  if(collisionFound)
  {
    this->z = oldGridItem.getZ();
    this->itemData->height = oldGridItem.getHeight();
    this->offset.second = oldGridItem.getOffsetY();
  }
  
  return !collisionFound;
}

}
