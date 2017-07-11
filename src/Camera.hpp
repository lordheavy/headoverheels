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

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <utility>
#include <cassert>
#include "Ism.hpp"

namespace isomot
{

// Declaraciones adelantadas.
class Room;
class PlayerItem;

/**
 * Centra la sala. Si es una sala simple o pequeña simplemente calculará las
 * coordenadas de pantalla óptimas para situar el punto origen del espacio. 
 * Si es una sala múltiple, además centrará al personaje activo en pantalla y 
 * calculará las coordenadas donde debe situarse el bitmap en el que se dibuja
 * la sala respecto de la pantalla.
 */
class Camera
{
public:
  
  /**
   * Constructor.
   * @param La sala objetivo de la cámara.
   */ 
	Camera(Room* room);
	
	/**
	 * Destructor.
	 */
	virtual ~Camera();
	
	/**
   * Centra la sala en pantalla y establece el punto de referencia. Una vez se ha
   * asignado dicho punto debe usarse la operación "center" para centrar la sala,
   * pues "turnOn" ya no tendrá efecto.
   * @param player El jugador activo.
   * @param entry Vía de entrada a la sala.
   */
	void turnOn(PlayerItem* player, const Direction& entry);
	
	/**
	 * Centra la sala en pantalla.
	 * @param player El jugador activo.
	 * @return true si se ha producido variación respecto al desplazamiento previo, 
	 * o false en caso contrario.
	 */
	bool center(PlayerItem* player);
	
private:
  
  /**
   * La sala objetivo de la cámara.
   */
  Room* room;
  
  /**
   * Punto de referencia a partir del cual se realizará el desplazamiento de la cámara.
   * Coincide con las coordenadas X e Y del jugador activo.
   */
  std::pair<int, int> reference;
  
  /**
   * Desplazamiento de pantalla a realizar en el eje X e Y, respectivamente, para centrar la sala.
   */
  std::pair<int, int> delta;
  
public: // Operaciones de consulta y actualización.
  
  /**
   * Desplazamiento de pantalla a realizar en el eje X para centrar la sala.
   * @return Un número positivo indica que la sala se desplazará a la derecha, mientras que un
   * número negativo desplazará la sala a la izquierda.
   */
  int getDeltaX() const { return delta.first; }
  
  /**
   * Desplazamiento de pantalla a realizar en el eje Y para centrar la sala.
   * @return Un número positivo indica que la sala se desplazará hacia abajo, mientras que un
   * número negativo desplazará la sala hacia arriba.
   */
  int getDeltaY() const { return delta.second; }
};

}

#endif /*CAMERA_HPP_*/
