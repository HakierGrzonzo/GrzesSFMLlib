project('GrzesSFMLlib', 'cpp',
  version : '0.1',
  license: 'MIT',
  default_options : ['warning_level=2', 'cpp_std=c++20'])


#add_global_arguments('-g', language : 'cpp')
#add_global_arguments('-O0', language : 'cpp')
#warning('Turning off optimization in debug mode')


sfml = dependency('sfml-all')
box2d = dependency('box2d')
openal = dependency('openal')
libavcodec = dependency('libavcodec')
libavutil = dependency('libavutil')
libavformat = dependency('libavformat')
libswresample = dependency('libswresample')
boxerInc = include_directories('../Boxer/include')

windows = get_option('windows')
if windows
  boxer = declare_dependency()
  gtk = declare_dependency()
else
  boxer = declare_dependency(link_args: '/lib64/libBoxer.a', include_directories: boxerInc)
  gtk = dependency('gtk+-3.0')
  add_global_arguments('-DBOXER=1', language: 'cpp')
endif


executable('GrzesSFMLlib',
          './src/Audio/AudioMacros.cpp',
          './src/Audio/AudioScene.cpp',
          './src/Audio/Player.cpp',
          './src/Component/Component.cpp',
          './src/Component/templates/BigExplosion.cpp',
          './src/Component/templates/Bullet.cpp',
          './src/Component/templates/BulletSound.cpp',
          './src/Component/templates/Creature.cpp',
          './src/Component/templates/Debug.cpp',
          './src/Component/templates/Enemy.cpp',
          './src/Component/templates/EnemyController.cpp',
          './src/Component/templates/EnemyTarget.cpp',
          './src/Component/templates/Explosion.cpp',
          './src/Component/templates/GameOverText.cpp',
          './src/Component/templates/Gun.cpp',
          './src/Component/templates/HPdisplayer.cpp',
          './src/Component/templates/Korwin.cpp',
          './src/Component/templates/Physics.cpp',
          './src/Component/templates/Player.cpp',
          './src/Component/templates/Renderable.cpp',
          './src/Component/templates/ShadedSprite.cpp',
          './src/Component/templates/Spawner.cpp',
          './src/Component/templates/Sprite.cpp',
          './src/Component/templates/StaticPhysics.cpp',
          './src/Component/templates/guns/Pistol.cpp',
          './src/Component/templates/playerControler.cpp',
          './src/Component/templates/sprites/Background.cpp',
          './src/Component/templates/sprites/Bullet.cpp',
          './src/Component/templates/sprites/Explosion.cpp',
          './src/Component/templates/sprites/HPeffect.cpp',
          './src/Component/templates/sprites/Player.cpp',
          './src/Component/templates/sprites/Test.cpp',
          './src/Component/templates/sprites/Wall.cpp',
          './src/Entity/ChunkCoord.cpp',
          './src/Entity/Entity-System.cpp',
          './src/Entity/Entity.cpp',
          './src/Entity/Inputs.cpp',
          './src/Entity/templates/Background.cpp',
          './src/Entity/templates/BigExplosion.cpp',
          './src/Entity/templates/Bullet.cpp',
          './src/Entity/templates/Explosion.cpp',
          './src/Entity/templates/GameOverText.cpp',
          './src/Entity/templates/HPdisplay.cpp',
          './src/Entity/templates/HPeffect.cpp',
          './src/Entity/templates/Korwin.cpp',
          './src/Entity/templates/Player.cpp',
          './src/Entity/templates/SpawnerTest.cpp',
          './src/Entity/templates/Target.cpp',
          './src/Entity/templates/Test.cpp',
          './src/Entity/templates/Wall.cpp',
          './src/Utils/CameraSmoother.cpp',
          './src/Utils/ContactListener.cpp',
          './src/Utils/Position.cpp',
          './src/Utils/Random.cpp',
          './src/Utils/ResourceManager.cpp',
          './src/gameloop.cpp',
          './src/main.cpp',
           dependencies: [
             box2d, 
             sfml, 
             boxer, 
             gtk, 
             openal,
             libavcodec,
             libavutil,
             libavformat,
             libswresample
             ])
