// Copyright (C) 2005-2007 Code Synthesis Tools CC
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

#include "SoundsXML.hpp"

namespace sxml
{
  // SoundsXML
  // 

  const SoundsXML::item_sequence& SoundsXML::
  item () const
  {
    return this->item_;
  }

  SoundsXML::item_sequence& SoundsXML::
  item ()
  {
    return this->item_;
  }

  void SoundsXML::
  item (const item_sequence& item)
  {
    this->item_ = item;
  }


  // item
  // 

  const item::state_sequence& item::
  state () const
  {
    return this->state_;
  }

  item::state_sequence& item::
  state ()
  {
    return this->state_;
  }

  void item::
  state (const state_sequence& state)
  {
    this->state_ = state;
  }

  const item::label_type& item::
  label () const
  {
    return this->label_.get ();
  }

  item::label_type& item::
  label ()
  {
    return this->label_.get ();
  }

  void item::
  label (const label_type& label)
  {
    this->label_.set (label);
  }


  // state
  // 

  const state::file_type& state::
  file () const
  {
    return this->file_.get ();
  }

  state::file_type& state::
  file ()
  {
    return this->file_.get ();
  }

  void state::
  file (const file_type& file)
  {
    this->file_.set (file);
  }

  void state::
  file (::std::auto_ptr< file_type > file)
  {
    this->file_.set (file);
  }

  const state::id_type& state::
  id () const
  {
    return this->id_.get ();
  }

  state::id_type& state::
  id ()
  {
    return this->id_.get ();
  }

  void state::
  id (const id_type& id)
  {
    this->id_.set (id);
  }

  void state::
  id (::std::auto_ptr< id_type > id)
  {
    this->id_.set (id);
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace sxml
{
  // SoundsXML
  //

  SoundsXML::
  SoundsXML ()
  : ::xml_schema::type (),
    item_ (::xml_schema::flags (), this)
  {
  }

  SoundsXML::
  SoundsXML (const SoundsXML& x,
             ::xml_schema::flags f,
             ::xml_schema::type* c)
  : ::xml_schema::type (x, f, c),
    item_ (x.item_, f, this)
  {
  }

  SoundsXML::
  SoundsXML (const ::xercesc::DOMElement& e,
             ::xml_schema::flags f,
             ::xml_schema::type* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    item_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e);
      this->parse (p, f);
    }
  }

  void SoundsXML::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // item
      //
      if (n.name () == "item" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< item_type > r (
          item_traits::create (i, f, this));

        this->item ().push_back (r);
        continue;
      }

      break;
    }
  }

  SoundsXML* SoundsXML::
  _clone (::xml_schema::flags f,
          ::xml_schema::type* c) const
  {
    return new SoundsXML (*this, f, c);
  }

  // item
  //

  item::
  item (const label_type& label)
  : ::xml_schema::type (),
    state_ (::xml_schema::flags (), this),
    label_ (label, ::xml_schema::flags (), this)
  {
  }

  item::
  item (const item& x,
        ::xml_schema::flags f,
        ::xml_schema::type* c)
  : ::xml_schema::type (x, f, c),
    state_ (x.state_, f, this),
    label_ (x.label_, f, this)
  {
  }

  item::
  item (const ::xercesc::DOMElement& e,
        ::xml_schema::flags f,
        ::xml_schema::type* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    state_ (f, this),
    label_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e);
      this->parse (p, f);
    }
  }

  void item::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // state
      //
      if (n.name () == "state" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< state_type > r (
          state_traits::create (i, f, this));

        this->state ().push_back (r);
        continue;
      }

      break;
    }

    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "label" && n.namespace_ ().empty ())
      {
        this->label (label_traits::create (i, f, this));
        continue;
      }
    }

    if (!label_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "label",
        "");
    }
  }

  item* item::
  _clone (::xml_schema::flags f,
          ::xml_schema::type* c) const
  {
    return new item (*this, f, c);
  }

  // state
  //

  state::
  state (const file_type& file,
         const id_type& id)
  : ::xml_schema::type (),
    file_ (file, ::xml_schema::flags (), this),
    id_ (id, ::xml_schema::flags (), this)
  {
  }

  state::
  state (const state& x,
         ::xml_schema::flags f,
         ::xml_schema::type* c)
  : ::xml_schema::type (x, f, c),
    file_ (x.file_, f, this),
    id_ (x.id_, f, this)
  {
  }

  state::
  state (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f,
         ::xml_schema::type* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    file_ (f, this),
    id_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e);
      this->parse (p, f);
    }
  }

  void state::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // file
      //
      if (n.name () == "file" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< file_type > r (
          file_traits::create (i, f, this));

        if (!file_.present ())
        {
          this->file (r);
          continue;
        }
      }

      break;
    }

    if (!file_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "file",
        "");
    }

    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "id" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< id_type > r (
          id_traits::create (i, f, this));

        this->id (r);
        continue;
      }
    }

    if (!id_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "id",
        "");
    }
  }

  state* state::
  _clone (::xml_schema::flags f,
          ::xml_schema::type* c) const
  {
    return new state (*this, f, c);
  }
}

#include <istream>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace sxml
{
  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::std::string& u,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::sxml::SoundsXML > r (
      ::sxml::sounds (
        d.get (), f | ::xml_schema::flags::own_dom, p));

    if (f & ::xml_schema::flags::keep_dom)
      d.release ();

    return r;
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::std::string& u,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (u, h, p, f));

    if (!d)
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::sxml::SoundsXML > r (
      ::sxml::sounds (
        d.get (), f | ::xml_schema::flags::own_dom, p));

    if (f & ::xml_schema::flags::keep_dom)
      d.release ();

    return r;
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::std::string& u,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (u, h, p, f));

    if (!d)
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::sxml::SoundsXML > r (
      ::sxml::sounds (
        d.get (), f | ::xml_schema::flags::own_dom, p));

    if (f & ::xml_schema::flags::keep_dom)
      d.release ();

    return r;
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::std::istream& is,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    ::xercesc::Wrapper4InputSource wrap (&isrc, false);
    return ::sxml::sounds (wrap, f, p);
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::std::istream& is,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    ::xercesc::Wrapper4InputSource wrap (&isrc, false);
    return ::sxml::sounds (wrap, h, f, p);
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::std::istream& is,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    ::xercesc::Wrapper4InputSource wrap (&isrc, false);
    return ::sxml::sounds (wrap, h, f, p);
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::std::istream& is,
          const ::std::string& sid,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    ::xercesc::Wrapper4InputSource wrap (&isrc, false);
    return ::sxml::sounds (wrap, f, p);
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::std::istream& is,
          const ::std::string& sid,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    ::xercesc::Wrapper4InputSource wrap (&isrc, false);
    return ::sxml::sounds (wrap, h, f, p);
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::std::istream& is,
          const ::std::string& sid,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    ::xercesc::Wrapper4InputSource wrap (&isrc, false);
    return ::sxml::sounds (wrap, h, f, p);
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::xercesc::DOMInputSource& i,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::sxml::SoundsXML > r (
      ::sxml::sounds (
        d.get (), f | ::xml_schema::flags::own_dom, p));

    if (f & ::xml_schema::flags::keep_dom)
      d.release ();

    return r;
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::xercesc::DOMInputSource& i,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (i, h, p, f));

    if (!d)
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::sxml::SoundsXML > r (
      ::sxml::sounds (
        d.get (), f | ::xml_schema::flags::own_dom, p));

    if (f & ::xml_schema::flags::keep_dom)
      d.release ();

    return r;
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::xercesc::DOMInputSource& i,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (i, h, p, f));

    if (!d)
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::sxml::SoundsXML > r (
      ::sxml::sounds (
        d.get (), f | ::xml_schema::flags::own_dom, p));

    if (f & ::xml_schema::flags::keep_dom)
      d.release ();

    return r;
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (const ::xercesc::DOMDocument& d,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    if (f & ::xml_schema::flags::keep_dom)
    {
      ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > c (
        static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

      ::std::auto_ptr< ::sxml::SoundsXML > r (
        ::sxml::sounds (
          c.get (), f | ::xml_schema::flags::own_dom, p));

      c.release ();
      return r;
    }

    const ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "sounds" &&
        n.namespace_ () == "")
    {
      ::std::auto_ptr< ::sxml::SoundsXML > r (
        ::xsd::cxx::tree::traits< ::sxml::SoundsXML, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "sounds",
      "");
  }

  ::std::auto_ptr< ::sxml::SoundsXML >
  sounds (::xercesc::DOMDocument* d,
          ::xml_schema::flags f,
          const ::xml_schema::properties&)
  {
    ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument > c (
      ((f & ::xml_schema::flags::keep_dom) &&
       !(f & ::xml_schema::flags::own_dom))
      ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
      : 0);

    const ::xercesc::DOMElement& e (
      c.get ()
      ? *c->getDocumentElement ()
      : *d->getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "sounds" &&
        n.namespace_ () == "")
    {
      ::std::auto_ptr< ::sxml::SoundsXML > r (
        ::xsd::cxx::tree::traits< ::sxml::SoundsXML, char >::create (
          e, f, 0));
      c.release ();
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "sounds",
      "");
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

