//-------------------------------------------------------------------------
// Head over Heels (A remake by helmántika.org)
//
// © Copyright 2008 Jorge Rodríguez Santos <jorge@helmantika.org>
// © Copyright 1987 Ocean Software Ltd. (Original game)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------

#ifndef CREATEAUDIOMENU_HPP_
#define CREATEAUDIOMENU_HPP_

#include <string>
#include <sstream>
#include <allegro.h>
#include "Action.hpp"

namespace gui
{

/**
 * Crea el menú de para el ajuste de los efectos sonidos y la música.
 */
class CreateAudioMenu : public Action
{
public:
  
  /**
   * Constructor.
   * @param destination Imagen donde se dibujará la interfaz gráfica.
   */
  CreateAudioMenu(BITMAP* destination);
  
  /**
   * Ejecuta el contenido de la acción, es decir, muestra el menú de configuración.
   */
  void execute();
  
private:
  
  /**
   * Imagen donde se dibujará la interfaz gráfica.
   */
  BITMAP* destination;
};

}

#endif /*CREATEAUDIOMENU_HPP_*/
