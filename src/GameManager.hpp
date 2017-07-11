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

#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include "csxml/SaveGameXML.hpp"
#include "Ism.hpp"

namespace isomot
{

// Declaraciones adelantadas.
class Isomot;
class GameFileManager;
class PlayerItem;

/**
 * Planetas que el jugador debe liberar.
 */
enum PlanetId
{
  Blacktooth,
  Egyptus,
  Penitentiary,
  Byblos,
  Safari
};

/**
 * Código devuelto por la operación start que indica por qué se ha detenido el juego.
 */
enum StopCode
{
  NoStopCode, /**< Ninguno. */
  UserAction, /**< El usuario ha detenido la partida. */
  FreePlanet, /**< Se acaba de liberar un planeta. */
  SaveGame,   /**< Se acaba de coger el pez de la reencarnación. */
  Freedom,    /**< Se ha llegado a Freedom pero no con todas las coronas. */
  Sucess      /**< Se ha conseguido acabar el juego. */
};

/**
 * Se encarga de gestionar la interfaz de usuario y el motor isométrico. Además, almacena
 * los datos propios de este videojuego: vidas de los jugadores, condiciones para la 
 * victoria, etc.
 */
class GameManager
{
private:
  
  /**
   * Constructor.
   */
	GameManager();
	
public:
  
  /**
   * Destructor.
   */
	virtual ~GameManager();
	
  /**
   * Único objeto de esta clase para toda la aplicación.
   * @return Un puntero al objeto único.
   */
  static GameManager* getInstance();
  
  /**
   * Todo empieza aquí.
   * @return Razón por la que se ha detenido el juego.
   */
  StopCode start();
  
  /**
   * Reanuda la partida tras una interrupción. La interrupción viene dada porque se ha liberado
   * un planeta o porque se acaba de grabar la partida.
   * @return Razón por la que se ha interrumpido el juego.
   */
  StopCode restart();
  
  /**
   * Dibuja en pantalla la información relativa al juego actual compuesta de:
   * un marco, vidas disponibles, herramientas disponibles, objeto guardado en el 
   * bolso, tiempo restante de inmunidad, saltos largos disponibles y rosquillas
   * disponibles.
   * @param destination Imagen donde se dibujará toda la información.
   */
  void drawGameStatus(BITMAP* destination);
  
  /**
   * Carga una partida grabada en disco.
   * @param fileName Nombre del archivo que contiene los datos de la partida.
   */
  void loadGame(const std::string& fileName);
  
  /**
   * Guarda en disco la partida actual.
   * @param fileName Nombre del archivo.
   */
  void saveGame(const std::string& fileName);
  
  /**
   * Añade un número de vidas a un jugador.
   * @param player Identificador del jugador.
   * @param lives Número de vidas a sumar.
   */
  void addLives(const PlayerId& player, unsigned char lives);
  
  /**
   * Resta una vida a un jugador.
   * @param player Identificador del jugador.
   */
  void loseLife(const PlayerId& player);
  
  /**
   * Un jugador coge su complemento.
   * @param Etiqueta del elemento.
   */
  void takeTool(const MagicItem& label);
  
  /**
   * Resta una rosquilla a Head.
   */
  void consumeDonut() { this->donuts--; }
  
  /**
   * Añade velocidad doble a un jugador.
   * @param player Jugador que toma la velocidad.
   * @param highSpeed Un número entre 0 y 99.
   */
  void addHighSpeed(const PlayerId& player, unsigned int highSpeed);
  
  /**
   * Resta una unidad al tiempo restante de doble velocidad.
   * @param Jugador que tiene la doble velocidad.
   */
  void decreaseHighSpeed(const PlayerId& player);
  
  /**
   * Añade un número de grandes saltos a un jugador.
   * @param player Jugador que toma los saltos.
   * @param highJumps Un número entre 0 y 10.
   */
  void addHighJumps(const PlayerId& player, unsigned int highJumps);
  
  /**
   * Resta un gran salto al jugador.
   * @param player Jugador que tiene los saltos.
   */
  void decreaseHighJumps(const PlayerId& player);
  
  /**
   * Añade inmunidad a un jugador.
   * @param player Jugador que toma la inmunidad.
   * @param shield Un número de milisegundos.
   */
  void addShield(const PlayerId& player, double shield);
  
  /**
   * Actualiza el tiempo restante de inmunidad.
   * @param player Jugador que tiene la inmunidad.
   * @param shield Un número de milisegundos.
   */
  void decreaseShield(const PlayerId& player, double shield);

  /**
   * Elimina el elemento que contiene el bolso para no mostrarlo en la interfaz.
   * @param player Jugador que tiene el bolso.
   */
  void emptyHandbag(const PlayerId& player);

  /**
   * Establece todos los planetas como miembros del Imperio Blacktooth.
   */
  void resetFreePlanets();
  
  /**
   * Libera un planeta.
   * @param planet El planeta liberado: Blacktooth, Egyptus, Penitentiary, Byblos o Safari.
   * @param now Indica si se acaba de liberar o bien ya estaba liberado de una partida anterior.
   */
  void liberatePlanet(const PlanetId& planet, bool now = true);
  
  /**
   * Indica si un planeta es libre.
   * @param planet Un planeta: Blacktooth, Egyptus, Penitentiary, Byblos o Safari.
   * @return true si se tiene la corona correspondiente o false en caso contrario.
   */
  bool isFreePlanet(const PlanetId& planet) const;
  
  /**
   * Número de planetas liberados hasta el momento.
   * @return Un número entre 0 y 5.
   */
  unsigned short freePlanetsCount() const;
  
  /**
   * Come un pez, es decir, desencadena el proceso para guardar la partida.
   * @param roomId Identificador de la sala donde se ha cogido el pez de la reencarnación.
   * @param label Etiqueta del jugador que ha cogido el pez.
   * @param x Coordenada X donde está situado el pez de la reencarnación.
   * @param y Coordenada Y donde está situado el pez de la reencarnación.
   * @param z Coordenada Z donde está situado el pez de la reencarnación.
   * @param direction Dirección a la que mira el jugador en el momento de coger el pez.
   */
  void eatFish(const std::string& roomId, short label, int x, int y, int z, const Direction& direction);
  
  /**
   * Finaliza la partida porque los jugadores han perdido todas sus vidas.
   */
  void end() { this->gameOver = true; }
  
  /**
   * Finaliza la partida porque los jugadores han llegado a Freedom.
   */
  void arriveFreedom() { this->freedom = true; }
  
  /**
   * Finaliza la partida porque los jugadores se han proclamado emperadores.
   */
  void success() { this->emperator = true; }
  
private:
  
  /**
   * Actualiza el juego de forma periódica. Implica redibujar la vista isométrica,
   * que a su vez, actualiza el estado de todos los elementos.
   * @return Razón por la que se ha detenido la actualización.
   */
  StopCode update();
  
  /**
   * Detiene el juego en curso. Si el usuario pulsa ESC abandonará la partida
   * en curso y si pulsa cualquier otra tecla el juego continuará.
   * @return Razón por la que se ha detenido la actualización.
   */
  StopCode stop();

public:

  /**
   * Indica si se han activado las vidas infinitas.
   */
  bool infiniteLives;

private:
  
  /**
   * Único objeto de esta clase para toda la aplicación.
   */
  static GameManager* instance;
  
  /**
   * El motor isométrico del juego.
   */
  Isomot* isomot;
  
  /**
   * Gestor de la grabación y recuperación de una partida.
   */
  GameFileManager* gameFileManager;
  
  /**
   * Vidas de Head.
   */
  unsigned char headLives;
  
  /**
   * Vidas de Heels.
   */
  unsigned char heelsLives;
  
  /**
   * Tiempo restante para consumir la doble velocidad de Head.
   */
  unsigned int highSpeed;
  
  /**
   * Número de grandes saltos que le restan a Heels.
   */
  unsigned int highJumps;
  
  /**
   * Tiempo restante para consumir la inmunidad de Head.
   */
  double headShield;
  
  /**
   * Tiempo restante para consumir la inmunidad de Heels.
   */
  double heelsShield;
  
  /**
   * Indica si Head tiene la bocina.
   */
  bool horn;
  
  /**
   * Indica si Heels tiene el bolso.
   */
  bool handbag;
  
  /**
   * Número de rosquillas que tiene Head.
   */
  unsigned short donuts;
  
  /**
   * Imagen del elemento que está dentro del bolso.
   */
  BITMAP* itemTaken;
  
  /**
   * Número de salas visitadas por los jugadores.
   */
  unsigned short visitedRooms;
  
  /**
   * Indica qué planetas han sido liberados. El orden de los mísmos viene dado por 
   * el enumerado PlanetId.
   */
  std::vector<bool> freePlanets;
  
  /**
   * Si un jugador acaba de coger una corona se detiene la partida para mostrar la pantalla de los planetas.
   */
  bool takenCrown;
  
  /**
   * Si un jugador acaba de comer un pez se detiene la partida para dar la opción de grabar la partida.
   */
  bool eatenFish;
  
  /**
   * Los jugadores han perdido todas las vidas.
   */
  bool gameOver;
  
  /**
   * Los jugadores han llegado a Freedom.
   */
  bool freedom;
  
  /**
   * Los jugadores se han proclamado Emperadores de Blacktooth.
   */
  bool emperator;
  
public: // Operaciones de consulta y actualización.
  
  /**
   * Establece el número de vidas de Head.
   * @param lives Un número entre 0 y 8.
   */
  void setHeadLives(unsigned char lives) { this->headLives = lives; }
  
  /**
   * Establece el número de vidas de Heels.
   * @param lives Un número entre 0 y 8.
   */
  void setHeelsLives(unsigned char lives) { this->heelsLives = lives; }
  
  /**
   * Devuelve el número de vias de un jugador.
   * @param player El jugador.
   * @return Un número entre 0 y 8.
   */
  unsigned char getLives(const PlayerId& player) const;
  
  /**
   * Establece el tiempo restante de movimiento a doble velocidad.
   * @param Un número entre 0 y 99.
   */
  void setHighSpeed(unsigned int highSpeed) { this->highSpeed = highSpeed; }
  
  /**
   * Devuelve el tiempo restante de movimiento a doble velocidad.
   * @return Un número entre 0 y 99.
   */
  unsigned int getHighSpeed() const { return this->highSpeed; }
  
  /**
   * Establece el número de grandes saltos del jugador.
   * @param highJumps Un número entre 0 y 10.
   */
  void setHighJumps(unsigned int highJumps) { this->highJumps = highJumps; }
  
  /**
   * Devuelve el número de grandes saltos del jugador.
   * @return Un número entre 0 y 10.
   */
  unsigned int getHighJumps() const { return this->highJumps; }
  
  /**
   * Establece el tiempo restante de inmunidad para Head.
   * @param Un número de milisegundos.
   */
  void setHeadShield(unsigned int shield) { this->headShield = shield; }
  
  /**
   * Establece el tiempo restante de inmunidad para Heels.
   * @param Un número de milisegundos.
   */
  void setHeelsShield(unsigned int shield) { this->heelsShield = shield; }
  
  /**
   * Devuelve el tiempo restante de inmunidad de un jugador.
   * @param player El jugador.
   * @return Un número de milisegundos.
   */
  double getShield(const PlayerId& player) const;
  
  /**
   * Establece la posesión de la bocina por Head.
   * @param hasHorn true si tiene la bocina o false en caso contrario. 
   */
  void setHorn(bool hasHorn) { this->horn = hasHorn; }
  
  /**
   * Indica si un jugador posee su complemento.
   * @param player El jugador.
   * @return Un vector con las etiquetas de los complementos que posee el jugador.
   */
  std::vector<short> hasTool(const PlayerId& player) const;
  
  /**
   * Establece la posesión del bolso por Heels.
   * @param hasHorn true si tiene el bolso o false en caso contrario. 
   */
  void setHandbag(bool hasHandbag) { this->handbag = hasHandbag; }
  
  /**
   * Establece el número de rosquillas que tiene Head.
   * @param Un número mayor o igual que 0.
   */
  void setDonuts(unsigned short number) { this->donuts = number; }
  
  /**
   * Devuelve el número de rosquillas que tiene Head.
   * @return Un número mayor o igual que 0.
   */
  unsigned short getDonuts(const PlayerId& player) const;
  
  /**
   * Imagen del elemento que está dentro del bolso.
   * @param bitmap Un fotograma del elemento.
   */
  void setItemTaken(BITMAP* bitmap) { this->itemTaken = bitmap; }
  
  /**
   * Número de salas visitadas por los jugadores.
   * @return Un número mayor que 2.
   */
  unsigned short getVisitedRooms() const { return this->visitedRooms; }

  /**
   * Número de planetas liberados.
   */
  size_t getNumberFreePlanets() const;
};

}

#endif /*GAMEMANAGER_HPP_*/
