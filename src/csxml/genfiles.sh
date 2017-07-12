#!/bin/sh

# script to generate cpp/hpp files from .xsd files
# with xsd 4.0 (really basic but it works)

# format: filename, namespace, ouputfilename
myarray=('configuration' 'cxml' 'ConfigurationXML'
         'items' 'ixml' 'ItemsXML'
         'language' 'lxml' 'LanguageXML'
         'map' 'mxml' 'MapXML'
         'room' 'rxml' 'RoomXML'
         'savegame' 'sgxml' 'SaveGameXML'
         'sounds' 'sxml' 'SoundsXML'
         '' '' '')

index=0

while [ "${myarray[$index]}" != '' ]
do
  fname=${myarray[$index]}
  (( index += 1 ))
  nspace=${myarray[$index]}
  (( index += 1 ))
  ofname=${myarray[$index]}
  (( index += 1 ))

  xsdcxx cxx-tree --namespace-map =${nspace} --cxx-regex "/(?=.*).+/${ofname}.cpp/" --hxx-regex "/(?=.*).+/${ofname}.hpp/" --generate-serialization ${fname}.xsd
done
