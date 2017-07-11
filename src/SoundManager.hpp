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

#ifndef SOUNDMANAGER_HPP_
#define SOUNDMANAGER_HPP_

#include <list>
#include <string>
#include <ext/hash_map>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cassert>
#include <allegro.h>
#include "alogg/aloggpth.h"
#include "alogg/aloggint.h"
#include "csxml/SoundsXML.hpp"
#include "Ism.hpp"

#define BLOCK_SIZE 40960

/**
 * Definición de la función hash para poder emplear std::string en plantillas __gnu_cxx::hash_map.
 * Código de Stefan Olsson.
 */
namespace __gnu_cxx
{
  template<> struct hash<std::string>
  {
    size_t operator()(const std::string& x) const
    {
      return hash<const char*>()(x.c_str());
    }
  };
}

namespace isomot
{

// Declaraciones adelantadas.
class SampleData;
class SoundData;

/**
 * Gestor de los efectos de sonido. Almacena todos los sonidos emitidos por los
 * diferentes elementos del juego en una tabla cuyo campo principal es la etiqueta
 * que identifica al elemento. Cada elemento tiene un sonido determinado asociado
 * a una acción que normalmente coincide con alguno de sus estados.
 */ 
class SoundManager
{
private:
  
  /**
   * Constructor.
   */
	SoundManager();
	
public:
  
  /**
   * Destructor.
   */
	~SoundManager();
	
  /**
   * Único objeto de esta clase para toda la aplicación.
   * @return Un puntero al objeto único.
   */
  static SoundManager* getInstance();
  
  /**
   * Crea la lista de sonidos a partir de la información extraída por el gestor XML del archivo 
   * que almacena los sonidos.
   * @param fileName Nombre del archivo XML que contiene los datos de los sonidos.
   */
  void load(const std::string& fileName);
  
  /**
   * Reproduce un sonido.
   * @param label Identificador del elemento que emite el sonido.
   * @param state Estado del elemento.
   * @param loop Si vale true, el sonido se reproduce continuamente.
   */
  void play(short label, const StateId& stateId, bool loop = false);
  
  /**
   * Detiene la reproducción de un sonido.
   * @param label Identificador del elemento que emite el sonido.
   * @param state Estado del elemento.
   */  
  void stop(short label, const StateId& stateId);
  
  /**
   * Detiene la reproducción de todos los sonidos.
   */
  void stopAllSounds();
  
  /**
   * Reproduce un archivo OGG.
   * @param fileName Nombre del archivo.
   */
  void playOgg(const std::string& fileName);
  
  /**
   * Detiene la reproducción en curso de un archivo OGG.
   */
  void stopOgg();
  
  /**
   * Indica si un determinado archivo OGG está reproduciéndose.
   * @param fileName Nombre del archivo OGG.
   * @return true si está sonando o false en caso contrario.
   */
  bool isPlayingTheme(const std::string& fileName) { return this->oggPlaying.compare(fileName) == 0; }
  
private:

  /**
   * Busca un sonido en la tabla.
   * @param label Identificador del elemento que emite el sonido.
   * @param state Estado del elemento.
   * @return El sonido ó 0 si no se encontró.
   */
  SampleData* findSample(short label, const StateId& stateId);
  
  /**
   * Traduce el identificador de un estado empleado por Isomot a una cadena
   * de caracteres utilizada en la tabla de sonidos.
   * @param stateId Un estado usado por el motor isométrico.
   * @return Una cadena de caracteres con alguno de los estado manejados por la tabla de sonidos.
   */
  std::string translateState(const StateId& stateId);
  
private:
  
  /**
   * Único objeto de esta clase para toda la aplicación.
   */
  static SoundManager* instance;
  
  /**
   * Nombre del archivo XML que contiene los datos de los sonidos.
   */
  std::string fileName;
  
  /**
   * Subproceso encargado de la reproducción de archivos OGG.
   */
  alogg_thread* oggPlayer;
  
  /**
   * Segmento del archivo OGG que se está reproduciendo.
   */
  alogg_stream* oggStream;
  
  /**
   * Indica si se está reproduciendo algún archivo OGG.
   */
  bool isPlayingOgg;
  
  /**
   * Nombre del tema que se está reproduciendo.
   */
  std::string oggPlaying;
  
  /**
   * Volumen de los efectos sonoros.
   */
  int fxVolume;
  
  /**
   * Volumen de la música.
   */
  int musicVolume;
  
  /**
   * Tabla de sonidos.
   */
  std::list<SoundData> soundData;
  
public: // Operaciones de consulta y actualización.
  
  /**
   * Establece el volumen de los efectos sonoros.
   * @param volume Un valor comprendido entre 0 y 99.
   */
  void setFxVolume(int volume) { this->fxVolume = volume; }
  
  /**
   * Volumen de los efectos sonoros.
   * @return Un valor comprendido entre 0 y 99.
   */
  int getFxVolume() const { return this->fxVolume; }

  /**
   * Establece el volumen de la música.
   * @param volume Un valor comprendido entre 0 y 99.
   */
  void setMusicVolume(int volume);
  
  /**
   * Volumen de la música.
   * @return Un valor comprendido entre 0 y 99.
   */
  int getMusicVolume() const { return this->musicVolume; }
};

/**
 * Estructura que asocia cada muestra de sonido a un indicador de reproducción.
 */
class SampleData
{
public:
  
  /**
   * Sonido digital manejado por Allegro.
   */
  SAMPLE* sample;
  
  /**
   * Número de voz asignada a la reproducción del sonido.
   */
  int voice;
};

/**
 * Almacena los sonidos del juego. Cada sonido está ligado a un par elemento/estado.
 */
class SoundData
{
public:
 
  /**
   * Constructor.
   * @param label Etiqueta unívoca de un elemento.
   */
  SoundData(short label);
  
  /**
   * Liga un sonido a un elemento del juego.
   * @param state Descripción textual del estado.
   * @param sampleFileName Nombre del archivo de sonido.
   */
  void add(const std::string& state, const std::string& sampleFileName);
  
  /**
   * Busca un sonido.
   * @param state Estado asociado al sonido.
   * @return Sonido digital manejado por Allegro.
   */
  SampleData* find(const std::string& state);
  
public:
  
  /**
   * Etiqueta unívoca del elemento, es decir, no puede haber dos elementos de distinto tipo con la
   * misma etiqueta. Las etiquetas son constantes y no cadenas de caracteres.
   */
  short label;
  
  /**
   * Tabla hash que almacena el par estado/sonido. El estado viene definido por la cadena de 
   * caracteres que figura en el archivo XML de definición de los sonidos.
   */
  __gnu_cxx::hash_map<std::string, SampleData> table;
  
  /**
   * Ruta al archivo ejecutable. Se necesita para cargar los sonidos.
   */
  std::string path;
  
public: // Operaciones de consulta y actualización.
  
  /**
   * La etiqueta que identifica a un elemento.
   * @return Un número positivo.
   */
  short getLabel() const { return this->label; }
};

/**
 * Objeto-función usado como predicado en la búsqueda de los datos de un sonido del juego.
 */
struct EqualSoundData : public std::binary_function<SoundData, short, bool>
{
  bool operator()(const SoundData& soundData, short label) const;
};

}

#endif /*SOUNDMANAGER_HPP_*/
