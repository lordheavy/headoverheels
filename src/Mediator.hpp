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

#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <stack>
#include <utility>
#include <functional>
#include <allegro.h>
#ifdef __WIN32
  #include <winalleg.h>
#endif
#include <pthread.h>
#include <sys/time.h>
#include "Ism.hpp"

namespace isomot
{

// Declaraciones adelantadas.
class RoomComponent;
class Item;
class Room;
class FloorTile;
class GridItem;
class FreeItem;
class PlayerItem;
class Door;
class TransparencyManager;
class ItemDataManager;

/**
 * En Isomot una columna es una lista de elementos rejilla que se dibujarán a lo largo del eje Z.
 */
typedef std::list<GridItem*> Column;

/**
 * Subproceso de actualización de todos los elementos.
 * @param thisClass Un objeto mediador.
 */
void* updateThread(void* thisClass);

/**
 * Mediador entre los distintos elementos de la sala. Recoge las peticiones lanzadas por los elementos ante
 * determinados sucesos y las envía a otros elementos para que las procesen.
 */
class Mediator
{ 
public:

  /**
   * Constructor.
   * @param room Sala en la que negocia este mediador.
   */
  Mediator(Room* room);

  /**
   * Destructor.
   */
  virtual ~Mediator();

  /**
   * Actualiza el comportamiento de todos los elementos un ciclo.
   */
  void update();
  
  /**
   * Inicia la actualización de los elementos en un subproceso separado del principal.
   */
  void startUpdate();
  
  /**
   * Detiene la actualización de los elementos.
   */
  void stopUpdate();
  
  /**
   * Señala para el motor qué elementos libres deben volverse a enmascarar. Se usa cuando un elemento
   * libre cambia su imagen dado que el cambio afecta al resto de elementos cuyas imágenes se solapan con
   * la suya.
   * @param item Elemento que solicita la operación.
   */
  void markItemsForMasking(FreeItem* item);

  /**
   * Señala para el motor qué elementos libres deben volverse a enmascarar. Se usa cuando un elemento
   * rejilla cambia su posición dado que el cambio afecta al resto de elementos cuyas imágenes se
   * solapan con la suya y espacialmente quedan detrás de él.
   * @param gridItem El elemento rejilla que solicita la operación.
   */
  void markItemsForMasking(GridItem* gridItem);

  /**
   * Señala para el motor qué elementos deben sombrearse. Se usa cuando un elemento rejilla es añadido a la 
   * sala o cambia su sombra dado que el cambio afecta al resto de elementos que se encuentren debajo de él.
   * @param item Elemento rejilla que solicita la operación.
   */
  void markItemsForShady(GridItem* gridItem);

  /**
   * Señala para el motor qué elementos deben sombrearse. Se usa cuando un elemento libre es añadido a la 
   * sala o cambia su sombra dado que el cambio afecta al resto de elementos que se encuentren debajo de él.
   * @param item Elemento libre que solicita la operación.
   */
  void markItemsForShady(FreeItem* freeItem);

  /**
   * Sombrea una loseta.
   * @param floorTile La loseta que solicita la operación.
   */
  void castShadow(FloorTile* floorTile);

  /**
   * Sombrea un elemento rejilla.
   * @param gridItem El elemento rejilla que solicita la operación.
   */
  void castShadow(GridItem* gridItem);

  /**
   * Sombrea un elemento libre.
   * @param freeItem El elemento libre que solicita la operación.
   */
  void castShadow(FreeItem* freeItem);
  
  /**
   * Enmascara un elemento libre.
   * @param freeItem El elemento libre que solicita la operación.
   */
  void mask(FreeItem* freeItem);

  /**
   * Busca un elemento en la sala.
   * @param id Identificador del elemento asignado por el motor.
   * @return El elemento si se encontró ó 0 si no existe.
   */
  Item* findItem(int id);
  
  /**
   * Busca un elemento en la sala.
   * @param label Etiqueta del elemento. En el caso de existir varios elementos con la misma etiqueta 
   * devolverá el primero que encuentre.
   * @return El elemento si se encontró ó 0 si no existe.
   */
  Item* findItem(short label);
  
  /**
   * Busca un elemento en la sala.
   * @param id Comportamiento del elemento. En el caso de existir varios elementos con el mismo comportamiento
   * devolverá el primero que encuentre.
   * @return El elemento si se encontró ó 0 si no existe.
   */
  Item* findItem(const BehaviorId& id);
  
  /**
   * Busca colisiones entre un elemento y el resto de la sala. De haberlas se almacenarán en la pila.
   * @param item El elemento para el que se buscarán colisiones.
   * @return true si se encontraron colisiones o false en caso contrario.
   */
  bool findCollision(Item* item);

  /**
   * Busca la coordenada Z más alta donde situar un elemento.
   * @param item El elemento para el que se busca la coordenada.
   * @return El nuevo valor de Z o cero si hubo colisión o no se pudo hallar.
   */
  int findHighestZ(Item* item);

  /**
   * Inserta un elemento rejilla en su estructura de datos correspondiente.
   * @param item Un nuevo elemento rejilla.
   */
  void insertItem(GridItem* gridItem);

  /**
   * Inserta un elemento libre en su estructura de datos correspondiente.
   * @param item Un nuevo elemento libre.
   */
  void insertItem(FreeItem* freeItem);
  
  /**
   * Inserta un jugador en su estructura de datos correspondiente.
   * @param item Un nuevo jugador.
   */
  void insertItem(PlayerItem* playerItem);
  
  /**
   * Elimina un elemento rejilla de su lista correspondiente.
   * @param item Un elemento rejilla existente.
   */
  void removeItem(GridItem* gridItem);
  
  /**
   * Elimina un elemento rejilla de su lista correspondiente.
   * @param item Un elemento libre existente.
   */
  void removeItem(FreeItem* freeItem);
    
  /**
   * Elimina un jugador de su lista correspondiente. Además selecciona a otro jugador 
   * como jugador activo.
   * @param item Un jugador existente.
   */
  void removeItem(PlayerItem* playerItem);
  
  /**
   * Añade un nuevo elemento a la tabla de transparencias.
   * @param percent Grado de transparencia del elemento.
   */
  void addTransparency(unsigned char percent);

  /**
   * Elimina un elemento de la tabla de transparencias.
   * @param percent Grado de transparencia del elemento.
   */
  void removeTransparency(unsigned char percent);
  
  /**
   * Añade un elemento a la pila de colisiones.
   * @param id Identificador del elemento.
   */
  void pushCollision(int id);

  /**
   * Saca el primer elemento de la pila de colisiones.
   * @return Un identificador de un elemento asignado por el motor ó 0 si la pila está vacía.
   */
  int popCollision();
  
  /**
   * Vacía la pila de colisiones.
   */
  void clearCollisionStack();

  /**
   * Indica si la pila de colisiones está vacía.
   * @return true si está vacía o false en caso contrario.
   */
  bool isCollisionStackEmpty();
  
  /**
   * Número de elementos en la pila de colisiones.
   * @return Un número positivo ó 0 si la pila está vacía.
   */
  unsigned int collisionStackSize();
  
  /**
   * Indica si un elemento ha chocado con otro de un tipo determinado.
   * @param id Etiqueta del elemento.
   * @return El elemento con el que se ha producido la colisión ó 0 si no hay colisión.
   */
  Item* collisionWith(short label);
  
  /**
   * Indica si un elemento ha chocado con otro de un comportamiento determinado.
   * @param id Identificador del comportamiento.
   * @return El elemento con el que se ha producido la colisión ó 0 si no hay colisión.
   */
  Item* collisionWith(const BehaviorId& id);
  
  /**
   * Indica si un elemento ha chocado con otro capaz de quitar vida a un jugador y que pueda
   * ser detenido por la acción de un disparo.
   * @return El elemento con el que se ha producido la colisión ó 0 si no hay colisión.
   */
  Item* collisionWithBadBoy();
  
  /**
   * Selecciona al siguiente jugador presente en la sala.
   * @param itemDataManager Necesario para poder crear el jugador compuesto a partir de los simples
   * o para crear a los jugadores simples a partir del compuesto.
   * @return true si se ha podido hacer el cambio o false si el jugador activo es el único 
   * presente en la sala.
   */
  bool nextPlayer(ItemDataManager* itemDataManager);
  
  /**
   * Selecciona al jugador que queda vivo tras la pérdida de las vidas del otro jugador.
   * @param itemDataManager Necesario para poder crear a un jugador simple a partir del compuesto.
   * @return true si se ha cambiado el control al otro jugador o false si ya no hay más jugadores.
   */
  bool alivePlayer(ItemDataManager* itemDataManager);
  
  /**
   * Establece el estado del interruptor si éste está presente en la sala. Si se enciende entonces
   * los elementos volátiles dejan de serlo y los elementos mortales móviles se detienen. Si se apaga
   * entonces los mencionados elementos vuelven a su estado original.
   */
  void changeSwitchState();
  
  /**
   * Activa la ordenación de las listas de elementos rejilla.
   */
  void activateGridItemsSorting() { this->gridItemsSorting = true; }

  /**
   * Activa la ordenación de la lista de elementos libres.
   */
  void activateFreeItemsSorting() { this->freeItemsSorting = true; }
  
  /**
   * Activa el mútex de los elementos rejilla.
   */
  void lockGridItemMutex() { pthread_mutex_lock(&gridItemsMutex); }

  /**
   * Activa el mútex de los elementos libres.
   */
  void lockFreeItemMutex() { pthread_mutex_lock(&freeItemsMutex); }

  /**
   * Desactiva el mútex de los elementos rejilla.
   */
  void unlockGridItemMutex() { pthread_mutex_unlock(&gridItemsMutex); }

  /**
   * Desactiva el mútex de los elementos libres.
   */
  void unlockFreeItemMutex() { pthread_mutex_unlock(&freeItemsMutex); }
  
protected:
  
  /**
   * Señala para el motor qué elementos libres deben sombrearse. Se usa cuando un elemento es añadido a la 
   * sala o cambia su sombra dado que el cambio afecta al resto de elementos que se encuentren debajo de él.
   * @param item Elemento que solicita la operación.
   */
  void markFreeItemsForShady(Item* item);
  
private:
  
  /**
   * Predicado binario para la ordenación una lista de elementos rejilla.
   */
  static bool sortGridItemList(GridItem* g1, GridItem* g2);

  /**
   * Predicado binario para la ordenación la lista de elementos libres.
   */
  static bool sortFreeItemList(FreeItem* f1, FreeItem* f2);

private:

  friend class Room;

  /**
   * Identificador del subproceso de actualización de los elementos.
   */
  pthread_t thread;

  /**
   * Mútex para controlar el acceso a los elementos rejilla.
   */
  pthread_mutex_t gridItemsMutex;

  /**
   * Mútex para controlar el acceso a los elementos libres.
   */
  pthread_mutex_t freeItemsMutex;
  
  /**
   * Indica si el subproceso de actualización elementos está o no ejecutándose.
   */
  bool threadRunning;
  
  /**
   * Indica si las listas de elementos rejilla están ordenadas.
   */
  bool gridItemsSorting;
  
  /**
   * Indica si la lista de elementos libres está ordenada.
   */
  bool freeItemsSorting;
  
  /**
   * Estado del interruptor si existe, porque la mayoría de las salas no tienen un elemento interruptor.
   * Con el interruptor encendido (true) los elementos volátiles dejan de serlo y los elementos mortales 
   * móviles se detienen; con el interruptor apagado los mencionados elementos vuelven a su estado original.
   */
  bool switchState;
  
  /**
   * Último jugador controlado antes de hacer un cambio de jugador.
   */
  PlayerId lastControlledPlayer;
  
  /**
   * Sala en la que negocia este mediador.
   */
  Room* room;

  /**
   * Conjunto de elementos que forman la estructura de una sala. Cada columna del vector está compuesta de
   * una lista de elementos rejilla cuya coordenada Z es mayor que la coordenada del elemento precedente,
   * es decir, forman una pila, aunque dicha pila puede tener huecos.
   */
  std::vector<Column> structure;

  /**
   * Conjunto de elementos libres de una sala.
   */
  std::list<FreeItem*> freeItems;
  
  /**
   * Jugadores presentes en la sala.
   */
  std::vector<PlayerItem*> playerItems;
  
  /**
   * Lista de elementos capaces de eliminar al jugador y que pueden ser paralizados por la acción
   * de un disparo o por el cambio de estado de una palanca.
   */
  std::vector<BehaviorId> badBoys;  
  
  /**
   * Jugador controlado por el usuario.
   */
  PlayerItem* activePlayer;
  
  /**
   * Pila de colisiones de la sala. Almacena los identificadores de los elementos.
   */
  std::vector<int> collisions;

  /**
   * Gestor de transparencias de los elementos.
   */
  TransparencyManager* transparencyManager;

public: // Operaciones de consulta y actualización.

  /**
   * Indica si el subproceso de actualización de elementos está ejecutándose.
   * @return true si está en ejecución o false si está detenido.
   */
  bool isThreadRunning() { return threadRunning; }
  
  /**
   * Coordenadas de pantalla X donde está situada la coordenada origen de la sala.
   * @return Un número entero.
   */
  int getX0() const;

  /**
   * Coordenadas de pantalla Y donde está situada la coordenada origen de la sala.
   * @return Un número entero.
   */
  int getY0() const;

  /**
   * Devuelve el número de losetas de la sala en el eje X.
   * @return Una número positivo.
   */
  int getTilesX() const;

  /**
   * Devuelve el número de losetas de la sala en el eje X.
   * @return Una número positivo.
   */
  int getTilesY() const;

  /**
   * Devuelve la longitud del lado de una loseta en unidades isométricas.
   * @return Un valor múltiplo de dos.
   */
  int getTileSize() const;

  /**
   * Grado de opacidad de las sombras.
   * @return Un valor entre 0, sin sombras, hasta 256, sombras totalmente opacas.
   */
  short getShadingScale() const;
  
  /**
   * Límite de la sala.
   * @param direction Un punto cardinal indicativo del límite que se quiere obtener.
   * @return Un valor en unidades isométricas.
   */
  unsigned short getBound(const Direction& direction);
  
  /**
   * Sala en la que negocia este mediador.
   * @return Una sala.
   */
  Room* getRoom() const;

  /**
   * Establece el jugador controlado por el usuario.
   * @return playerItem Un jugador.
   */
  void setActivePlayer(PlayerItem* playerItem);
  
  /**
   * Jugador controlado por el usuario.
   * @return Un jugador ó 0 si no hay ninguno en la sala. El segundo caso puede darse durante
   * la transición entre salas.
   */
  PlayerItem* getActivePlayer();
  
  /**
   * Jugador inactivo, aquel que no está controlando el usuario.
   * @return Un jugador ó 0 si no hay más jugadores.
   */
  PlayerItem* getHidePlayer();
  
  /**
   * Acceso a las puertas de la sala.
   * @param direction Un punto cardinal que señala el muro donde se encuentra la puerta.
   * @return Una puerta ó 0 si la puerta no existe para la dirección indicada.
   */
  Door* getDoor(const Direction& direction);
};

/**
 * Objeto-función usado como predicado en la búsqueda de un elemento por su identificador.
 */
class EqualItemId : public std::binary_function<Item*, int, bool>
{
public:
  bool operator()(Item* item, int id) const;
};

/**
 * Objeto-función usado como predicado en la búsqueda de un jugador por su identificador.
 */
class EqualPlayerItemId : public std::binary_function<PlayerItem*, int, bool>
{
public:
  bool operator()(PlayerItem* playerItem, int id) const;
};

/**
 * Objeto-función usado como predicado en la búsqueda de un elemento por su etiqueta.
 */
class EqualItemLabel : public std::binary_function<Item*, short, bool>
{
public:
  bool operator()(Item* item, short label) const;
};

/**
 * Objeto-función usado como predicado en la búsqueda de un elemento por su comportamiento.
 */
class EqualItemBehavior : public std::binary_function<Item*, BehaviorId, bool>
{
public:
  bool operator()(Item* item, BehaviorId id) const;
};

}

#endif //MEDIATOR_HPP_
