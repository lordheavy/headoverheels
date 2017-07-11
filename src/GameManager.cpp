#include "GameManager.hpp"
#include "Exception.hpp"
#include "Isomot.hpp"
#include "GameFileManager.hpp"
#include "MapManager.hpp"
#include "Room.hpp"
#include "Mediator.hpp"
#include "PlayerItem.hpp"
#include "GuiManager.hpp"
#include "LanguageManager.hpp"
#include "Label.hpp"
#include "InputManager.hpp"
#include "BonusManager.hpp"
#include "SoundManager.hpp"
#include "InputManager.hpp"

namespace isomot
{

GameManager* GameManager::instance = 0;

//--------------------------------------------------------------------------------------------------
GameManager::GameManager()
: infiniteLives(false),
  isomot(new Isomot()),
  gameFileManager(new GameFileManager(this, isomot)),
  headLives(8),
  heelsLives(8),
  highSpeed(0),
  highJumps(0),
  headShield(0),
  heelsShield(0),
  horn(false),
  handbag(false),
  donuts(0),
  itemTaken(0),
  visitedRooms(0),
  freePlanets(std::vector<bool>(5, false)),
  takenCrown(false),
  eatenFish(false),
  gameOver(false),
  freedom(false),
  emperator(false)
{

}

//--------------------------------------------------------------------------------------------------
GameManager::~GameManager()
{
  delete isomot;
}

//--------------------------------------------------------------------------------------------------
GameManager* GameManager::getInstance()
{
  if(instance == 0)
  {
    instance = new GameManager();
  }

  return instance;
}

//--------------------------------------------------------------------------------------------------
StopCode GameManager::start()
{
  this->headLives = 8;
  this->heelsLives = 8;
  this->highSpeed = 0;
  this->highJumps = 0;
  this->headShield = 0;
  this->heelsShield = 0;
  this->horn = false;
  this->handbag = false;
  this->donuts = 0;
  this->itemTaken = 0;
  this->visitedRooms = 0;
  this->freePlanets.clear();
  this->freePlanets = std::vector<bool>(5, false);

  Assert<ENullPointer>(this->isomot);
  this->isomot->start();
  return this->update();
}

//--------------------------------------------------------------------------------------------------
StopCode GameManager::restart()
{
  this->isomot->restart();
  return this->update();
}

//--------------------------------------------------------------------------------------------------
void GameManager::drawGameStatus(BITMAP* destination)
{
  BITMAP* bitmap = 0;
  std::stringstream ss;

  // Escenario de la sala.
  std::string scenery = this->isomot->getMapManager()->getActiveRoom()->getScenery();
  // Si no hay escenario definido, no se pinta ningún indicador: es la pantalla final del juego.
  if(!scenery.empty())
  {
    // Marco. Varía en función del escenario.
    draw_sprite(destination, gui::GuiManager::getInstance()->findImage(scenery + "-frame"), 0, 0);

    // Jugador seleccionado.
    PlayerId playerId = static_cast<PlayerId>(this->isomot->getMapManager()->getActiveRoom()->getMediator()->getActivePlayer()->getLabel());
    std::string headIcon = playerId == Head || playerId == HeadAndHeels ? "head" : "grey-head";
    std::string heelsIcon = playerId == Heels || playerId == HeadAndHeels ? "heels" : "grey-heels";
    draw_sprite(destination, gui::GuiManager::getInstance()->findImage(headIcon), 161, 425);
    draw_sprite(destination, gui::GuiManager::getInstance()->findImage(heelsIcon), 431, 425);

    // La bocina.
    bitmap = gui::GuiManager::getInstance()->findImage(this->horn ? "horn" : "grey-horn");
    draw_sprite(destination, bitmap, 33, 425);

    // El bolso.
    bitmap = gui::GuiManager::getInstance()->findImage(this->handbag ? "handbag" : "grey-handbag");
    draw_sprite(destination, bitmap, 559, 425);

    // Vidas de Head.
    ss.str(std::string());
    ss << int(this->headLives);
    gui::Label headLivesLabel(this->headLives > 9 ? 214 : 221, 424, ss.str(), "big", "white", -2);
    headLivesLabel.draw(destination);

    // Vidas de Heels.
    ss.str(std::string());
    ss << int(this->heelsLives);
    gui::Label heelsLivesLabel(this->heelsLives > 9 ? 398 : 405, 424, ss.str(), "big", "white", -2);
    heelsLivesLabel.draw(destination);

    // Número de rosquillas.
    bitmap = gui::GuiManager::getInstance()->findImage(this->donuts != 0 ? "donuts" : "grey-donuts");
    draw_sprite(destination, bitmap, 33, 361);
    if(this->donuts > 0)
    {
      ss.str(std::string());
      ss << this->donuts;
      gui::Label donutsLabel(this->donuts > 9 ? 42 : 49, 372, ss.str(), "regular", "white", -2);
      donutsLabel.draw(destination);
    }

    // Grandes saltos.
    draw_sprite(destination, gui::GuiManager::getInstance()->findImage("high-jumps"), 505, 392);
    if(this->highJumps > 0)
    {
      ss.str(std::string());
      ss << int(this->highJumps);
      gui::Label highJumpsLabel(this->highJumps > 9 ? 505 : 512, 393, ss.str(), "regular", "white", -2);
      highJumpsLabel.draw(destination);
    }

    // Gran velocidad.
    draw_sprite(destination, gui::GuiManager::getInstance()->findImage("high-speed"), 107, 392);
    if(this->highSpeed > 0)
    {
      ss.str(std::string());
      ss << int(this->highSpeed);
      gui::Label highSpeedLabel(this->highSpeed > 9 ? 107 : 114, 393, ss.str(), "regular", "white", -2);
      highSpeedLabel.draw(destination);
    }

    // Escudo de Head.
    bitmap = gui::GuiManager::getInstance()->findImage("shield");
    draw_sprite(destination, bitmap, 107, 436);
    if(this->headShield > 0)
    {
      int headShieldValue = int(this->headShield * 99.0 / 25.0);

      ss.str(std::string());
      ss << headShieldValue;
      gui::Label headShieldLabel(headShieldValue > 9 ? 107 : 114, 437, ss.str(), "regular", "white", -2);
      headShieldLabel.draw(destination);
    }

    // Escudo de Heels.
    draw_sprite(destination, bitmap, 505, 436);
    if(this->heelsShield > 0)
    {
      int heelsShieldValue = int(this->heelsShield * 99.0 / 25.0);

      ss.str(std::string());
      ss << heelsShieldValue;
      gui::Label heelsShieldLabel(heelsShieldValue > 9 ? 505 : 512, 437, ss.str(), "regular", "white", -2);
      heelsShieldLabel.draw(destination);
    }

    // Elemento que hay dentro del bolso.
    if(this->itemTaken != 0)
    {
      draw_sprite(destination, this->itemTaken, 559, 361);
    }
  }
  else
  {
    // En la pantalla final del juego se dibuja FREEDOM en la esquina inferior izquierda.
    gui::Label freedomLabel(84, 362, "FREEDOM", "big", "multicolor");
    freedomLabel.draw(destination);
  }

  // Muestra todo en pantalla.
  acquire_screen();
  blit(destination, screen, 0, 0, 0, 0, destination->w, destination->h);
  release_screen();
}

//--------------------------------------------------------------------------------------------------
void GameManager::loadGame(const std::string& fileName)
{
  this->gameFileManager->loadGame(fileName);
}

//--------------------------------------------------------------------------------------------------
void GameManager::saveGame(const std::string& fileName)
{
  this->gameFileManager->saveGame(fileName);
}

//--------------------------------------------------------------------------------------------------
void GameManager::addLives(const PlayerId& player, unsigned char lives)
{
  switch(player)
  {
    case Head:
      if(this->headLives < 100)
      {
        this->headLives += lives;
      }
      break;

    case Heels:
      if(this->heelsLives < 100)
      {
        this->heelsLives += lives;
      }
      break;

    case HeadAndHeels:
      if(this->headLives < 100)
      {
        this->headLives += lives;
      }

      if(this->heelsLives < 100)
      {
        this->heelsLives += lives;
      }
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::loseLife(const PlayerId& player)
{
  switch(player)
  {
    case Head:
      if(this->headLives > 0)
      {
        this->headLives--;
      }
      break;

    case Heels:
      if(this->heelsLives > 0)
      {
        this->heelsLives--;
      }
      break;

    case HeadAndHeels:
      if(this->headLives > 0)
      {
        this->headLives--;
      }

      if(this->heelsLives > 0)
      {
        this->heelsLives--;
      }
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::takeTool(const MagicItem& label)
{
  switch(label)
  {
    case Horn:
      this->horn = true;
      break;

    case Handbag:
      this->handbag = true;
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::addHighSpeed(const PlayerId& player, unsigned int highSpeed)
{
  switch(player)
  {
    case Head:
    case HeadAndHeels:
      this->highSpeed += highSpeed;
      if(this->highSpeed > 99)
      {
        this->highSpeed = 99;
      }
      break;

    case Heels:
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::decreaseHighSpeed(const PlayerId& player)
{
  switch(player)
  {
    case Head:
    case HeadAndHeels:
      if(this->highSpeed > 0)
      {
        this->highSpeed--;
      }
      break;

    case Heels:
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::addHighJumps(const PlayerId& player, unsigned int highJumps)
{
  switch(player)
  {
    case Head:
      break;

    case Heels:
    case HeadAndHeels:
      this->highJumps += highJumps;
      if(this->highJumps > 99)
      {
        this->highJumps = 99;
      }
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::decreaseHighJumps(const PlayerId& player)
{
  switch(player)
  {
    case Head:
      break;

    case Heels:
    case HeadAndHeels:
      if(this->highJumps > 0)
      {
        this->highJumps--;
      }
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::addShield(const PlayerId& player, double shield)
{
  switch(player)
  {
    case Head:
      this->headShield += shield;
      if(this->headShield > 25.000)
      {
        this->headShield = 25.000;
      }
      break;

    case Heels:
      this->heelsShield += shield;
      if(this->heelsShield > 25.000)
      {
        this->heelsShield = 25.000;
      }
      break;

    case HeadAndHeels:
      this->headShield += shield;
      if(this->headShield > 25.000)
      {
        this->headShield = 25.000;
      }

      this->heelsShield += shield;
      if(this->heelsShield > 25.000)
      {
        this->heelsShield = 25.000;
      }
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::decreaseShield(const PlayerId& player, double shield)
{
  switch(player)
  {
    case Head:
      this->headShield = shield;
      if(this->headShield < 0)
      {
        this->headShield = 0;
      }
      break;

    case Heels:
      this->heelsShield = shield;
      if(this->heelsShield < 0)
      {
        this->heelsShield = 0;
      }
      break;

    case HeadAndHeels:
      this->headShield = shield;
      if(this->headShield < 0)
      {
        this->headShield = 0;
      }

      this->heelsShield = shield;
      if(this->heelsShield < 0)
      {
        this->heelsShield = 0;
      }
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::emptyHandbag(const PlayerId& player)
{
  switch(player)
  {
    case Heels:
    case HeadAndHeels:
      this->itemTaken = 0;
      break;

    default:
      ;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::resetFreePlanets()
{
  for(int i = Blacktooth; i < Safari; ++i)
  {
    this->freePlanets[i] = false;
  }
}

//--------------------------------------------------------------------------------------------------
void GameManager::liberatePlanet(const PlanetId& planet, bool now)
{
  if(planet >= Blacktooth && planet <= Safari)
  {
    this->freePlanets[planet] = true;
    this->takenCrown = now;
  }
}

//--------------------------------------------------------------------------------------------------
bool GameManager::isFreePlanet(const PlanetId& planet) const
{
  bool isFree = false;

  if(planet >= Blacktooth && planet <= Safari)
  {
    isFree = this->freePlanets[planet];
  }

  return isFree;
}

//--------------------------------------------------------------------------------------------------
unsigned short GameManager::freePlanetsCount() const
{
  unsigned short number = 0;

  for(size_t i = 0; i < freePlanets.size(); ++i)
  {
    number += freePlanets[i] ? 1 : 0;
  }

  return number;
}

//--------------------------------------------------------------------------------------------------
void GameManager::eatFish(const std::string& roomId, short label, int x, int y, int z, const Direction& direction)
{
  this->eatenFish = true;
  this->gameFileManager->assignFishData(roomId, label, x, y, z, direction);
}

//--------------------------------------------------------------------------------------------------
StopCode GameManager::update()
{
  StopCode stopCode = NoStopCode;

  // Mientras el usuario no pulse la tecla de abandono y lo confirme con Escape,
  // el juego se actualiza periódicamente.
  while(stopCode == NoStopCode)
  {
    if(!key[InputManager::getInstance()->readUserKey(KeyHalt)] && !this->takenCrown && !this->eatenFish && !this->gameOver)
    {
      // Actualiza la vista isométrica.
      BITMAP* view = this->isomot->update();
      // Se ha podido actualizar
      if(view != 0)
      {
        // Dibuja el marco y el estado del juego.
        this->drawGameStatus(view);
        // Se dibuja cada 10 milisegundos.
        sleep(10);
      }
      // La partida ha terminado.
      else
      {
        this->gameOver = true;
      }
    }
    else
    {
      // Detiene el juego.
      stopCode = this->stop();
    }
  }

  return stopCode;
}

//--------------------------------------------------------------------------------------------------
StopCode GameManager::stop()
{
  bool exit = false;
  bool confirm = false;
  StopCode stopCode = NoStopCode;

  // Detiene el motor isométrico.
  this->isomot->stop();

  // Da tiempo a que el usuario vea la parada.
  clear_keybuf();

  // El usuario acaba de liberar un planeta, se muestra la pantalla de los planetas.
  if(this->takenCrown)
  {
    stopCode = FreePlanet;
    this->takenCrown = false;
  }
  // El usuario acaba de comer un pez, se le da la opción de grabar la partida.
  else if(this->eatenFish)
  {
    this->eatenFish = false;
    isomot::InputManager* inputManager = InputManager::getInstance();

    // Presenta las intrucciones en pantalla.
    gui::LanguageText* text = 0;
    gui::LanguageManager* language = gui::GuiManager::getInstance()->getLanguageManager();

    text = language->findLanguageString("save-game");
    int deltaY = text->getY();
    for(size_t i = 0; i < text->getLinesCount(); i++)
    {
      gui::LanguageLine* line = text->getLine(i);
      gui::Label label(0, 0, line->text, line->font, line->color);
      label.changePosition((640 - label.getWidth()) >> 1, deltaY);
      deltaY += label.getHeight() * 3 / 4;
      acquire_screen();
      label.draw(screen);
      release_screen();
    }

    text = language->findLanguageString("confirm-resume");
    deltaY = text->getY();
    for(size_t i = 0; i < text->getLinesCount(); i++)
    {
      gui::LanguageLine* line = text->getLine(i);
      gui::Label label(0, 0, line->text, line->font, line->color);
      label.changePosition((640 - label.getWidth()) >> 1, deltaY);
      deltaY += label.getHeight() * 3 / 4;
      acquire_screen();
      label.draw(screen);
      release_screen();
    }

    clear_keybuf();

    // Mientras el usuario no elija una de las dos opciones no se hará nada.
    while(!confirm && !exit)
    {
      if(keypressed())
      {
        int key = readkey() >> 8;

        // Si se pulsa F2 se mostrará la interfaz para la grabación de la partida.
        if(key == KEY_F2)
        {
          exit = true;
          stopCode = SaveGame;
        }
        // Si se pulsa cualquier otra tecla, excepto una tecla de movimiento o salto,
        // prosigue la partida en curso.
        else if(key != inputManager->readUserKey(KeyNorth) &&
                key != inputManager->readUserKey(KeySouth) &&
                key != inputManager->readUserKey(KeyEast) &&
                key != inputManager->readUserKey(KeyWest) &&
                key != inputManager->readUserKey(KeyJump) &&
                key != KEY_ESC)
        {
          confirm = true;
          this->isomot->restart();
        }
      }

      // Sondea la decisión del usuario cada 10 milisegundos.
      sleep(10);
    }
  }
  // El usuario ha acabado con las vidas de todos los jugadores.
  else if(this->gameOver)
  {
    this->gameOver = false;
    stopCode = UserAction;
    this->visitedRooms = this->isomot->getMapManager()->countVisitedRooms();
    this->isomot->reset();
  }
  // El usuario ha llegado a Freedom pero le faltaron coronas.
  else if(this->freedom)
  {
    this->freedom = false;
    stopCode = Freedom;
    this->visitedRooms = this->isomot->getMapManager()->countVisitedRooms();
    this->isomot->reset();
  }
  // El usuario ha acabado el juego.
  else if(this->emperator)
  {
    this->emperator = false;
    stopCode = Sucess;
    this->visitedRooms = this->isomot->getMapManager()->countVisitedRooms();
    this->isomot->reset();
  }
  // El usuario ha pulsado la tecla de pausa.
  else
  {
    // Detiene todos los sonidos.
    SoundManager::getInstance()->stopAllSounds();

    // Presenta las intrucciones en pantalla.
    gui::LanguageText* text = 0;
    gui::LanguageManager* language = gui::GuiManager::getInstance()->getLanguageManager();

    text = language->findLanguageString("confirm-quit");
    int deltaY = text->getY();
    for(size_t i = 0; i < text->getLinesCount(); i++)
    {
      gui::LanguageLine* line = text->getLine(i);
      gui::Label label(0, 0, line->text, line->font, line->color);
      label.changePosition((640 - label.getWidth()) >> 1, deltaY);
      deltaY += label.getHeight() * 3 / 4;
      acquire_screen();
      label.draw(screen);
      release_screen();
    }

    text = language->findLanguageString("confirm-resume");
    deltaY = text->getY();
    for(size_t i = 0; i < text->getLinesCount(); i++)
    {
      gui::LanguageLine* line = text->getLine(i);
      gui::Label label(0, 0, line->text, line->font, line->color);
      label.changePosition((640 - label.getWidth()) >> 1, deltaY);
      deltaY += label.getHeight() * 3 / 4;
      acquire_screen();
      label.draw(screen);
      release_screen();
    }

    // Mientras el usuario no elija una de las dos opciones no se hará nada.
    while(!confirm && !exit)
    {
      if(keypressed())
      {
        // Si ha pulsado Escape se suspende la partida en curso.
        if(readkey() >> 8 == KEY_ESC)
        {
          exit = true;
          stopCode = UserAction;
          this->visitedRooms = this->isomot->getMapManager()->countVisitedRooms();
          this->isomot->reset();
        }
        // Si se pulsa cualquier otra tecla, prosigue la partida en curso.
        else
        {
          confirm = true;
          this->isomot->restart();
        }
      }

      // Sondea la decisión del usuario cada 10 milisegundos.
      sleep(10);
    }
  }

  return stopCode;
}

//--------------------------------------------------------------------------------------------------
unsigned char GameManager::getLives(const PlayerId& player) const
{
  unsigned char lives = 0;

  switch(player)
  {
    case Head:
      lives = this->headLives;
      break;

    case Heels:
      lives = this->heelsLives;
      break;

    case HeadAndHeels:
      lives = std::min(this->headLives, this->heelsLives);
      break;

    default:
      ;
  }

  return lives;
}

//--------------------------------------------------------------------------------------------------
double GameManager::getShield(const PlayerId& player) const
{
  double time = 0.0;

  switch(player)
  {
    case Head:
      time = this->headShield;
      break;

    case Heels:
      time = this->heelsShield;
      break;

    case HeadAndHeels:
      time = std::max(this->headShield, this->heelsShield);
      break;

    default:
      ;
  }

  return time;
}

//--------------------------------------------------------------------------------------------------
std::vector<short> GameManager::hasTool(const PlayerId& player) const
{
  std::vector<short> tools;

  switch(player)
  {
    case Head:
      if(this->horn)
      {
        tools.push_back(Horn);
      }
      break;

    case Heels:
      if(this->handbag)
      {
        tools.push_back(Handbag);
      }
      break;

    case HeadAndHeels:
      if(this->horn)
      {
        tools.push_back(Horn);
      }
      if(this->handbag)
      {
        tools.push_back(Handbag);
      }
      break;

    default:
      ;
  }

  return tools;
}

//--------------------------------------------------------------------------------------------------
unsigned short GameManager::getDonuts(const PlayerId& player) const
{
  return (player == Head || player == HeadAndHeels ? this->donuts : 0);
}

//--------------------------------------------------------------------------------------------------
size_t GameManager::getNumberFreePlanets() const
{
   return std::count(this->freePlanets.begin(), this->freePlanets.end(), true);
}

}
