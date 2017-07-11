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

#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#include <vector>
#include <string>
#include <allegro.h>
#include "Ism.hpp"

namespace isomot
{

/**
 * Gestor de los dispositivos de entrada. Almacena las teclas empleadas para el control del
 * juego así como la configuración del joystick (siempre que haya uno conectado al sistema).
 */
class InputManager
{
private:
  
  /**
   * Constructor.
   */
	InputManager();
	
public:
  
  /**
   * Destructor.
   */
	~InputManager();
	
  /**
   * Único objeto de esta clase para toda la aplicación.
   * @return Un puntero al objeto único.
   */
  static InputManager* getInstance();

  /**
   * Asigna el código de una tecla definida por el usuario para el control del juego.
   * @param gameKey Tipo de tecla.
   * @param scancode Un código Allegro de una tecla.
   */
  void changeUserKey(const GameKey& gameKey, int scancode) { this->userKeys[gameKey] = scancode; }
  
  /**
   * Devuelve el código de una tecla definida por el usuario para el control del juego.
   * @param gameKey Tipo de tecla.
   * @return Un código Allegro de una tecla.
   */
  int readUserKey(const GameKey& gameKey) const { return this->userKeys[gameKey]; }
  
  /**
   * Busca el uso de una tecla.
   * @param scancode Un código Allegro de una tecla.
   * @return El uso de la tecla en el juego o KeyNone si carece de uso.
   */
  GameKey findKeyType(int scancode) const;
  
  /**
   * El usuario está moviendo al jugador a la izquierda.
   * @return true si pulsa la tecla indicada o mueve la palanca del joystick en ese sentido.
   */
  bool left();

  /**
   * El usuario está moviendo al jugador a la derecha.
   * @return true si pulsa la tecla indicada o mueve la palanca del joystick en ese sentido.
   */
  bool right();

  /**
   * El usuario está moviendo al jugador arriba.
   * @return true si pulsa la tecla indicada o mueve la palanca del joystick en ese sentido.
   */
  bool up();
  
  /**
   * El usuario está moviendo al jugador abajo.
   * @return true si pulsa la tecla indicada o mueve la palanca del joystick en ese sentido.
   */
  bool down();
  
  /**
   * El usuario está cogiendo o dejando algún objeto.
   * @return true si pulsa la tecla o el botón indicado.
   */
  bool take();

  /**
   * El usuario está saltando.
   * @return true si pulsa la tecla o el botón indicado.
   */
  bool jump();
  
  /**
   * El usuario está disparando.
   * @return true si pulsa la tecla o el botón indicado.
   */
  bool shoot();
  
  /**
   * El usuario está cogiendo o dejando algún objeto y saltando.
   * @return true si pulsa la tecla o el botón indicado.
   */
  bool takeAndJump();

  /**
   * El usuario está cogiendo cambiando de personaje.
   * @return true si pulsa la tecla o el botón indicado.
   */
  bool swap();

  /**
   * El usuario está parando el juego.
   * @return true si pulsa la tecla o el botón indicado.
   */
  bool halt();
  
  /**
   * Vacía las pulsaciones almacenadas de una tecla.
   * @param gameKey Una tecla asociada a una acción del juego.
   */
  void noRepeat(const GameKey& gameKey);
  
private:
  
  /**
   * Único objeto de esta clase para toda la aplicación.
   */
  static InputManager* instance;
  
  /**
   * Códigos Allegro de las teclas definidas por el usuario para el control del juego.
   */
  std::vector<int> userKeys;
};

}

#endif /*INPUTMANAGER_HPP_*/
