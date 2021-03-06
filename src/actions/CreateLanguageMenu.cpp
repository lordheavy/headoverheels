
#include "CreateLanguageMenu.hpp"
#include "Ism.hpp"
#include "GuiManager.hpp"
#include "LanguageManager.hpp"
#include "ConfigurationManager.hpp"
#include "Font.hpp"
#include "Screen.hpp"
#include "Menu.hpp"
#include "Label.hpp"
#include "Icon.hpp"
#include "SelectLanguage.hpp"

using gui::CreateLanguageMenu;
using gui::LanguageManager;
using gui::LanguageText;
using gui::SelectLanguage;

//--------------------------------------------------------------------------------------------------
CreateLanguageMenu::CreateLanguageMenu(BITMAP* destination)
: Action(),
  destination(destination)
{
  // Lee los idiomas en los que está disponible el juego.
  this->parse(isomot::sharePath() + "text/language.xml");

  // Lee el idioma establecido en la configuración.
  ConfigurationManager configurationManager(isomot::homePath() + "configuration.xml");
  configurationManager.read();
  language = configurationManager.getLanguage();
}

//--------------------------------------------------------------------------------------------------
CreateLanguageMenu::~CreateLanguageMenu()
{
  this->texts.clear();
}

//--------------------------------------------------------------------------------------------------
void CreateLanguageMenu::execute()
{
  Label* label = 0;
  Screen* screen = new Screen(0, 0, this->destination);

  // Imagen de fondo.
  screen->setBackground(GuiManager::getInstance()->findImage("background"));

  // Etiqueta fija: HEAD.
  label = new Label(200, 24, "HEAD");
  label->changeFont("big", "yellow");
  screen->addWidget(label);
  // Etiqueta fija: OVER.
  label = new Label(280, 45, "OVER", "regular", "multicolor");
  screen->addWidget(label);
  // Etiqueta fija: HEELS.
  label = new Label(360, 24, "HEELS");
  label->changeFont("big", "yellow");
  screen->addWidget(label);

  // Icono: Head.
  screen->addWidget(new Icon(66, 24, GuiManager::getInstance()->findImage("head")));
  // Icono: Heels.
  screen->addWidget(new Icon(518, 24, GuiManager::getInstance()->findImage("heels")));

  // Presenta los idiomas disponibles.
  Menu* menu = new Menu(40, 120, 300, 11);
  for(std::list<LanguageText*>::iterator i = this->texts.begin(); i != this->texts.end(); ++i)
  {
    label = new Label((*i)->getText());
    label->setAction(new SelectLanguage(this->destination, (*i)->getId()));
    if((this->language.empty() && i == this->texts.begin()) || this->language.compare((*i)->getId()) == 0)
    {
      menu->addActiveOption(label);
    }
    else
    {
      menu->addOption(label);
    }
  }
  screen->addWidget(menu);

  // Crea la cadena de responsabilidad.
  screen->setSucessor(menu);

  // Cambia la pantalla mostrada en la interfaz.
  GuiManager::getInstance()->changeScreen(screen);
}

//--------------------------------------------------------------------------------------------------
void CreateLanguageMenu::parse(const std::string& fileName)
{
  // Carga el archivo XML especificado y almacena los datos XML en la lista.
  try
  {
    std::auto_ptr<lxml::LanguageXML> languageXML(lxml::language(fileName.c_str()));

    // Almacena todos los registros del archivo en la lista.
    for(lxml::LanguageXML::text_const_iterator t = languageXML->text().begin(); t != languageXML->text().end(); ++t)
    {
      LanguageText* lang = new LanguageText((*t).id(), (*t).x(), (*t).y());

      for(lxml::text::properties_const_iterator p = (*t).properties().begin(); p != (*t).properties().end(); ++p)
      {
        for(lxml::properties::ustring_const_iterator u = (*p).ustring().begin(); u != (*p).ustring().end(); ++u)
        {
          lang->addLine(*u, std::string(), std::string());
        }
      }

      this->texts.push_back(lang);
    }
  }
  catch(const xml_schema::exception& e)
  {
    std::cerr << e << std::endl;
  }
}
