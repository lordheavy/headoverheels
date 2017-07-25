project('headoverheels', 'cpp', 'c',
        version : '1.0.2',
	license : 'GPL2')

mycc = meson.get_compiler('c')
cppflags = ['-Wno-deprecated-declarations']
add_project_arguments(cppflags, language : 'cpp')

dep_allegro = dependency('allegro', version : '>=4.4.0')
dep_xercesc = dependency('xerces-c', version : '>=3.1.0')
dep_vorbis = dependency('vorbis')
dep_vorbisenc = dependency('vorbisenc')
dep_vorbisfile = dependency('vorbisfile')
dep_ogg = dependency('ogg')
dep_thread = dependency('threads')
mycc.has_header('xsd/cxx/config.hxx')

subdir('src')
