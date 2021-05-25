project('GrzesSFMLlib', 'cpp',
  version : '0.1',
  license: 'MIT',
  default_options : ['warning_level=3', 'cpp_std=c++20'])


    add_global_arguments('-g', language : 'cpp')
    add_global_arguments('-O0', language : 'cpp')
    warning('Turning off optimization in debug mode')

sfml = dependency('sfml-all')
box2d = dependency('box2d')
gtk = dependency('gtk+-3.0')
boxerInc = include_directories('../Boxer/include')
boxer = declare_dependency(link_args: '/lib64/libBoxer.a', include_directories: boxerInc)

executable('GrzesSFMLlib',
          './src/Entity/templates/Background.cpp',
'./src/Entity/templates/Korwin.cpp',
'./src/Entity/templates/Player.cpp',
'./src/Entity/templates/Test.cpp',
'./src/Entity/templates/HPdisplay.cpp',
'./src/Entity/Entity.cpp',
'./src/Entity/Entity-System.cpp',
'./src/main.cpp',
'./src/Component/templates/sprites/Background.cpp',
'./src/Component/templates/sprites/Player.cpp',
'./src/Component/templates/sprites/Test.cpp',
'./src/Component/templates/Korwin.cpp',
'./src/Component/templates/Physics.cpp',
'./src/Component/templates/Renderable.cpp',
'./src/Component/templates/ShadedSprite.cpp',
'./src/Component/templates/Sprite.cpp',
'./src/Component/templates/Creature.cpp',
'./src/Component/templates/HPdisplayer.cpp',
'./src/Component/Component.cpp',
'./src/Utils/Position.cpp',
'./src/Utils/ResourceManager.cpp',
'./src/gameloop.cpp',
           dependencies: [box2d, sfml, boxer, gtk])
