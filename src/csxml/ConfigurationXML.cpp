// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "ConfigurationXML.hpp"

namespace cxml
{
  // ConfigurationXML
  // 

  const ConfigurationXML::language_type& ConfigurationXML::
  language () const
  {
    return this->language_.get ();
  }

  ConfigurationXML::language_type& ConfigurationXML::
  language ()
  {
    return this->language_.get ();
  }

  void ConfigurationXML::
  language (const language_type& x)
  {
    this->language_.set (x);
  }

  void ConfigurationXML::
  language (::std::auto_ptr< language_type > x)
  {
    this->language_.set (x);
  }

  const ConfigurationXML::keyboard_type& ConfigurationXML::
  keyboard () const
  {
    return this->keyboard_.get ();
  }

  ConfigurationXML::keyboard_type& ConfigurationXML::
  keyboard ()
  {
    return this->keyboard_.get ();
  }

  void ConfigurationXML::
  keyboard (const keyboard_type& x)
  {
    this->keyboard_.set (x);
  }

  void ConfigurationXML::
  keyboard (::std::auto_ptr< keyboard_type > x)
  {
    this->keyboard_.set (x);
  }

  const ConfigurationXML::volume_type& ConfigurationXML::
  volume () const
  {
    return this->volume_.get ();
  }

  ConfigurationXML::volume_type& ConfigurationXML::
  volume ()
  {
    return this->volume_.get ();
  }

  void ConfigurationXML::
  volume (const volume_type& x)
  {
    this->volume_.set (x);
  }

  void ConfigurationXML::
  volume (::std::auto_ptr< volume_type > x)
  {
    this->volume_.set (x);
  }


  // keyboard
  // 

  const keyboard::left_type& keyboard::
  left () const
  {
    return this->left_.get ();
  }

  keyboard::left_type& keyboard::
  left ()
  {
    return this->left_.get ();
  }

  void keyboard::
  left (const left_type& x)
  {
    this->left_.set (x);
  }

  const keyboard::right_type& keyboard::
  right () const
  {
    return this->right_.get ();
  }

  keyboard::right_type& keyboard::
  right ()
  {
    return this->right_.get ();
  }

  void keyboard::
  right (const right_type& x)
  {
    this->right_.set (x);
  }

  const keyboard::up_type& keyboard::
  up () const
  {
    return this->up_.get ();
  }

  keyboard::up_type& keyboard::
  up ()
  {
    return this->up_.get ();
  }

  void keyboard::
  up (const up_type& x)
  {
    this->up_.set (x);
  }

  const keyboard::down_type& keyboard::
  down () const
  {
    return this->down_.get ();
  }

  keyboard::down_type& keyboard::
  down ()
  {
    return this->down_.get ();
  }

  void keyboard::
  down (const down_type& x)
  {
    this->down_.set (x);
  }

  const keyboard::take_type& keyboard::
  take () const
  {
    return this->take_.get ();
  }

  keyboard::take_type& keyboard::
  take ()
  {
    return this->take_.get ();
  }

  void keyboard::
  take (const take_type& x)
  {
    this->take_.set (x);
  }

  const keyboard::jump_type& keyboard::
  jump () const
  {
    return this->jump_.get ();
  }

  keyboard::jump_type& keyboard::
  jump ()
  {
    return this->jump_.get ();
  }

  void keyboard::
  jump (const jump_type& x)
  {
    this->jump_.set (x);
  }

  const keyboard::shoot_type& keyboard::
  shoot () const
  {
    return this->shoot_.get ();
  }

  keyboard::shoot_type& keyboard::
  shoot ()
  {
    return this->shoot_.get ();
  }

  void keyboard::
  shoot (const shoot_type& x)
  {
    this->shoot_.set (x);
  }

  const keyboard::takeandjump_type& keyboard::
  takeandjump () const
  {
    return this->takeandjump_.get ();
  }

  keyboard::takeandjump_type& keyboard::
  takeandjump ()
  {
    return this->takeandjump_.get ();
  }

  void keyboard::
  takeandjump (const takeandjump_type& x)
  {
    this->takeandjump_.set (x);
  }

  const keyboard::swap_type& keyboard::
  swap () const
  {
    return this->swap_.get ();
  }

  keyboard::swap_type& keyboard::
  swap ()
  {
    return this->swap_.get ();
  }

  void keyboard::
  swap (const swap_type& x)
  {
    this->swap_.set (x);
  }

  const keyboard::halt_type& keyboard::
  halt () const
  {
    return this->halt_.get ();
  }

  keyboard::halt_type& keyboard::
  halt ()
  {
    return this->halt_.get ();
  }

  void keyboard::
  halt (const halt_type& x)
  {
    this->halt_.set (x);
  }


  // volume
  // 

  const volume::fx_type& volume::
  fx () const
  {
    return this->fx_.get ();
  }

  volume::fx_type& volume::
  fx ()
  {
    return this->fx_.get ();
  }

  void volume::
  fx (const fx_type& x)
  {
    this->fx_.set (x);
  }

  const volume::music_type& volume::
  music () const
  {
    return this->music_.get ();
  }

  volume::music_type& volume::
  music ()
  {
    return this->music_.get ();
  }

  void volume::
  music (const music_type& x)
  {
    this->music_.set (x);
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace cxml
{
  // ConfigurationXML
  //

  ConfigurationXML::
  ConfigurationXML (const language_type& language,
                    const keyboard_type& keyboard,
                    const volume_type& volume)
  : ::xml_schema::type (),
    language_ (language, this),
    keyboard_ (keyboard, this),
    volume_ (volume, this)
  {
  }

  ConfigurationXML::
  ConfigurationXML (const language_type& language,
                    ::std::auto_ptr< keyboard_type > keyboard,
                    ::std::auto_ptr< volume_type > volume)
  : ::xml_schema::type (),
    language_ (language, this),
    keyboard_ (keyboard, this),
    volume_ (volume, this)
  {
  }

  ConfigurationXML::
  ConfigurationXML (const ConfigurationXML& x,
                    ::xml_schema::flags f,
                    ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    language_ (x.language_, f, this),
    keyboard_ (x.keyboard_, f, this),
    volume_ (x.volume_, f, this)
  {
  }

  ConfigurationXML::
  ConfigurationXML (const ::xercesc::DOMElement& e,
                    ::xml_schema::flags f,
                    ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    language_ (this),
    keyboard_ (this),
    volume_ (this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
      this->parse (p, f);
    }
  }

  void ConfigurationXML::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_content (); p.next_content (false))
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // language
      //
      if (n.name () == "language" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< language_type > r (
          language_traits::create (i, f, this));

        if (!language_.present ())
        {
          this->language_.set (r);
          continue;
        }
      }

      // keyboard
      //
      if (n.name () == "keyboard" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< keyboard_type > r (
          keyboard_traits::create (i, f, this));

        if (!keyboard_.present ())
        {
          this->keyboard_.set (r);
          continue;
        }
      }

      // volume
      //
      if (n.name () == "volume" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< volume_type > r (
          volume_traits::create (i, f, this));

        if (!volume_.present ())
        {
          this->volume_.set (r);
          continue;
        }
      }

      break;
    }

    if (!language_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "language",
        "");
    }

    if (!keyboard_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "keyboard",
        "");
    }

    if (!volume_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "volume",
        "");
    }
  }

  ConfigurationXML* ConfigurationXML::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class ConfigurationXML (*this, f, c);
  }

  ConfigurationXML& ConfigurationXML::
  operator= (const ConfigurationXML& x)
  {
    if (this != &x)
    {
      static_cast< ::xml_schema::type& > (*this) = x;
      this->language_ = x.language_;
      this->keyboard_ = x.keyboard_;
      this->volume_ = x.volume_;
    }

    return *this;
  }

  ConfigurationXML::
  ~ConfigurationXML ()
  {
  }

  // keyboard
  //

  keyboard::
  keyboard (const left_type& left,
            const right_type& right,
            const up_type& up,
            const down_type& down,
            const take_type& take,
            const jump_type& jump,
            const shoot_type& shoot,
            const takeandjump_type& takeandjump,
            const swap_type& swap,
            const halt_type& halt)
  : ::xml_schema::type (),
    left_ (left, this),
    right_ (right, this),
    up_ (up, this),
    down_ (down, this),
    take_ (take, this),
    jump_ (jump, this),
    shoot_ (shoot, this),
    takeandjump_ (takeandjump, this),
    swap_ (swap, this),
    halt_ (halt, this)
  {
  }

  keyboard::
  keyboard (const keyboard& x,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    left_ (x.left_, f, this),
    right_ (x.right_, f, this),
    up_ (x.up_, f, this),
    down_ (x.down_, f, this),
    take_ (x.take_, f, this),
    jump_ (x.jump_, f, this),
    shoot_ (x.shoot_, f, this),
    takeandjump_ (x.takeandjump_, f, this),
    swap_ (x.swap_, f, this),
    halt_ (x.halt_, f, this)
  {
  }

  keyboard::
  keyboard (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    left_ (this),
    right_ (this),
    up_ (this),
    down_ (this),
    take_ (this),
    jump_ (this),
    shoot_ (this),
    takeandjump_ (this),
    swap_ (this),
    halt_ (this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
      this->parse (p, f);
    }
  }

  void keyboard::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_content (); p.next_content (false))
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // left
      //
      if (n.name () == "left" && n.namespace_ ().empty ())
      {
        if (!left_.present ())
        {
          this->left_.set (left_traits::create (i, f, this));
          continue;
        }
      }

      // right
      //
      if (n.name () == "right" && n.namespace_ ().empty ())
      {
        if (!right_.present ())
        {
          this->right_.set (right_traits::create (i, f, this));
          continue;
        }
      }

      // up
      //
      if (n.name () == "up" && n.namespace_ ().empty ())
      {
        if (!up_.present ())
        {
          this->up_.set (up_traits::create (i, f, this));
          continue;
        }
      }

      // down
      //
      if (n.name () == "down" && n.namespace_ ().empty ())
      {
        if (!down_.present ())
        {
          this->down_.set (down_traits::create (i, f, this));
          continue;
        }
      }

      // take
      //
      if (n.name () == "take" && n.namespace_ ().empty ())
      {
        if (!take_.present ())
        {
          this->take_.set (take_traits::create (i, f, this));
          continue;
        }
      }

      // jump
      //
      if (n.name () == "jump" && n.namespace_ ().empty ())
      {
        if (!jump_.present ())
        {
          this->jump_.set (jump_traits::create (i, f, this));
          continue;
        }
      }

      // shoot
      //
      if (n.name () == "shoot" && n.namespace_ ().empty ())
      {
        if (!shoot_.present ())
        {
          this->shoot_.set (shoot_traits::create (i, f, this));
          continue;
        }
      }

      // takeandjump
      //
      if (n.name () == "takeandjump" && n.namespace_ ().empty ())
      {
        if (!takeandjump_.present ())
        {
          this->takeandjump_.set (takeandjump_traits::create (i, f, this));
          continue;
        }
      }

      // swap
      //
      if (n.name () == "swap" && n.namespace_ ().empty ())
      {
        if (!swap_.present ())
        {
          this->swap_.set (swap_traits::create (i, f, this));
          continue;
        }
      }

      // halt
      //
      if (n.name () == "halt" && n.namespace_ ().empty ())
      {
        if (!halt_.present ())
        {
          this->halt_.set (halt_traits::create (i, f, this));
          continue;
        }
      }

      break;
    }

    if (!left_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "left",
        "");
    }

    if (!right_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "right",
        "");
    }

    if (!up_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "up",
        "");
    }

    if (!down_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "down",
        "");
    }

    if (!take_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "take",
        "");
    }

    if (!jump_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "jump",
        "");
    }

    if (!shoot_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "shoot",
        "");
    }

    if (!takeandjump_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "takeandjump",
        "");
    }

    if (!swap_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "swap",
        "");
    }

    if (!halt_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "halt",
        "");
    }
  }

  keyboard* keyboard::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class keyboard (*this, f, c);
  }

  keyboard& keyboard::
  operator= (const keyboard& x)
  {
    if (this != &x)
    {
      static_cast< ::xml_schema::type& > (*this) = x;
      this->left_ = x.left_;
      this->right_ = x.right_;
      this->up_ = x.up_;
      this->down_ = x.down_;
      this->take_ = x.take_;
      this->jump_ = x.jump_;
      this->shoot_ = x.shoot_;
      this->takeandjump_ = x.takeandjump_;
      this->swap_ = x.swap_;
      this->halt_ = x.halt_;
    }

    return *this;
  }

  keyboard::
  ~keyboard ()
  {
  }

  // volume
  //

  volume::
  volume (const fx_type& fx,
          const music_type& music)
  : ::xml_schema::type (),
    fx_ (fx, this),
    music_ (music, this)
  {
  }

  volume::
  volume (const volume& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    fx_ (x.fx_, f, this),
    music_ (x.music_, f, this)
  {
  }

  volume::
  volume (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    fx_ (this),
    music_ (this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
      this->parse (p, f);
    }
  }

  void volume::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_content (); p.next_content (false))
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // fx
      //
      if (n.name () == "fx" && n.namespace_ ().empty ())
      {
        if (!fx_.present ())
        {
          this->fx_.set (fx_traits::create (i, f, this));
          continue;
        }
      }

      // music
      //
      if (n.name () == "music" && n.namespace_ ().empty ())
      {
        if (!music_.present ())
        {
          this->music_.set (music_traits::create (i, f, this));
          continue;
        }
      }

      break;
    }

    if (!fx_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "fx",
        "");
    }

    if (!music_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "music",
        "");
    }
  }

  volume* volume::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class volume (*this, f, c);
  }

  volume& volume::
  operator= (const volume& x)
  {
    if (this != &x)
    {
      static_cast< ::xml_schema::type& > (*this) = x;
      this->fx_ = x.fx_;
      this->music_ = x.music_;
    }

    return *this;
  }

  volume::
  ~volume ()
  {
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace cxml
{
  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::std::string& u,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    return ::std::auto_ptr< ::cxml::ConfigurationXML > (
      ::cxml::configuration (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::std::string& u,
                 ::xml_schema::error_handler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::auto_ptr< ::cxml::ConfigurationXML > (
      ::cxml::configuration (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::std::string& u,
                 ::xercesc::DOMErrorHandler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::auto_ptr< ::cxml::ConfigurationXML > (
      ::cxml::configuration (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::cxml::configuration (isrc, f, p);
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 ::xml_schema::error_handler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::cxml::configuration (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 ::xercesc::DOMErrorHandler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::cxml::configuration (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 const ::std::string& sid,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::cxml::configuration (isrc, f, p);
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 const ::std::string& sid,
                 ::xml_schema::error_handler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::cxml::configuration (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 const ::std::string& sid,
                 ::xercesc::DOMErrorHandler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::cxml::configuration (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::xercesc::InputSource& i,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    return ::std::auto_ptr< ::cxml::ConfigurationXML > (
      ::cxml::configuration (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::xercesc::InputSource& i,
                 ::xml_schema::error_handler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::auto_ptr< ::cxml::ConfigurationXML > (
      ::cxml::configuration (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::xercesc::InputSource& i,
                 ::xercesc::DOMErrorHandler& h,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::auto_ptr< ::cxml::ConfigurationXML > (
      ::cxml::configuration (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::xercesc::DOMDocument& doc,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties& p)
  {
    if (f & ::xml_schema::flags::keep_dom)
    {
      ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
        static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

      return ::std::auto_ptr< ::cxml::ConfigurationXML > (
        ::cxml::configuration (
          d, f | ::xml_schema::flags::own_dom, p));
    }

    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "configuration" &&
        n.namespace_ () == "")
    {
      ::std::auto_ptr< ::cxml::ConfigurationXML > r (
        ::xsd::cxx::tree::traits< ::cxml::ConfigurationXML, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "configuration",
      "");
  }

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d,
                 ::xml_schema::flags f,
                 const ::xml_schema::properties&)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      ((f & ::xml_schema::flags::keep_dom) &&
       !(f & ::xml_schema::flags::own_dom))
      ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
      : 0);

    ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (f & ::xml_schema::flags::keep_dom)
      doc.setUserData (::xml_schema::dom::tree_node_key,
                       (c.get () ? &c : &d),
                       0);

    if (n.name () == "configuration" &&
        n.namespace_ () == "")
    {
      ::std::auto_ptr< ::cxml::ConfigurationXML > r (
        ::xsd::cxx::tree::traits< ::cxml::ConfigurationXML, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "configuration",
      "");
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace cxml
{
  void
  configuration (::std::ostream& o,
                 const ::cxml::ConfigurationXML& s,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e,
                 ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cxml::configuration (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  configuration (::std::ostream& o,
                 const ::cxml::ConfigurationXML& s,
                 ::xml_schema::error_handler& h,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e,
                 ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cxml::configuration (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  configuration (::std::ostream& o,
                 const ::cxml::ConfigurationXML& s,
                 ::xercesc::DOMErrorHandler& h,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e,
                 ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cxml::configuration (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  configuration (::xercesc::XMLFormatTarget& t,
                 const ::cxml::ConfigurationXML& s,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e,
                 ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cxml::configuration (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  configuration (::xercesc::XMLFormatTarget& t,
                 const ::cxml::ConfigurationXML& s,
                 ::xml_schema::error_handler& h,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e,
                 ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cxml::configuration (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  configuration (::xercesc::XMLFormatTarget& t,
                 const ::cxml::ConfigurationXML& s,
                 ::xercesc::DOMErrorHandler& h,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e,
                 ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cxml::configuration (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  configuration (::xercesc::DOMDocument& d,
                 const ::cxml::ConfigurationXML& s,
                 ::xml_schema::flags)
  {
    ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "configuration" &&
        n.namespace_ () == "")
    {
      e << s;
    }
    else
    {
      throw ::xsd::cxx::tree::unexpected_element < char > (
        n.name (),
        n.namespace_ (),
        "configuration",
        "");
    }
  }

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
  configuration (const ::cxml::ConfigurationXML& s,
                 const ::xml_schema::namespace_infomap& m,
                 ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::serialize< char > (
        "configuration",
        "",
        m, f));

    ::cxml::configuration (*d, s, f);
    return d;
  }

  void
  operator<< (::xercesc::DOMElement& e, const ConfigurationXML& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // language
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "language",
          e));

      s << i.language ();
    }

    // keyboard
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "keyboard",
          e));

      s << i.keyboard ();
    }

    // volume
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "volume",
          e));

      s << i.volume ();
    }
  }

  void
  operator<< (::xercesc::DOMElement& e, const keyboard& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // left
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "left",
          e));

      s << i.left ();
    }

    // right
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "right",
          e));

      s << i.right ();
    }

    // up
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "up",
          e));

      s << i.up ();
    }

    // down
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "down",
          e));

      s << i.down ();
    }

    // take
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "take",
          e));

      s << i.take ();
    }

    // jump
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "jump",
          e));

      s << i.jump ();
    }

    // shoot
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "shoot",
          e));

      s << i.shoot ();
    }

    // takeandjump
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "takeandjump",
          e));

      s << i.takeandjump ();
    }

    // swap
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "swap",
          e));

      s << i.swap ();
    }

    // halt
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "halt",
          e));

      s << i.halt ();
    }
  }

  void
  operator<< (::xercesc::DOMElement& e, const volume& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // fx
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "fx",
          e));

      s << i.fx ();
    }

    // music
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "music",
          e));

      s << i.music ();
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

