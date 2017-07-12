This files are generated from configuration.xsd, items.xsd, language.xsd, map.xsd, room.xsd, savegame.xsd, sounds.xsd with:


xsdcxx cxx-tree --namespace-map =cxml --cxx-regex '/(.*)\.[^.]+$/\u$1XML.cpp/' --hxx-regex '/(.*)\.[^.]+$/\u$1XML.hpp/' *.xsd
