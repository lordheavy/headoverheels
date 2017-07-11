#include "Screen.hpp"
#include "Gui.hpp"
#include "actions/Action.hpp"

namespace gui
{

//--------------------------------------------------------------------------------------------------
Screen::Screen(unsigned int x, unsigned int y, BITMAP* destination)
: Widget(x, y),
  backgroundColor(makecol(0, 0, 0)),
  backgroundImage(0), 
  destination(destination)
{

}

//--------------------------------------------------------------------------------------------------
Screen::~Screen()
{
  std::for_each(this->widgets.begin(), this->widgets.end(), DeleteObject());
}

//--------------------------------------------------------------------------------------------------
void Screen::draw(BITMAP* destination)
{
  // Pinta del color de fondo la imagen destino.
  clear_to_color(destination, backgroundColor);
  
  // Si se definió una imagen de fondo entonces se vuelca.
  if(this->backgroundImage != 0)
  {
    blit(this->backgroundImage, destination, 0, 0, 0, 0, this->backgroundImage->w, this->backgroundImage->h);
  }
  
  // Dibuja cada componente en la pantalla.
  std::for_each(widgets.begin(), widgets.end(), std::bind2nd(std::mem_fun(&Widget::draw), destination));
  
  // Vuelca la imagen destino a la memoria de pantalla.
  blit(destination, screen, 0, 0, 0, 0, destination->w, destination->h);
}

//--------------------------------------------------------------------------------------------------
void Screen::handleKey(int key)
{
  if(action != 0 && key >> 8 == KEY_ESC)
  {
    this->action->execute();
  }
  else
  {
    Widget::handleKey(key);
  }
}

//--------------------------------------------------------------------------------------------------
void Screen::addWidget(Widget* widget)
{
  this->widgets.push_back(widget);
}

}
