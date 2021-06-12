#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <box2d/b2_math.h>
#include <cstdlib>
#include <ostream>
#include <stdexcept>
#include "Component/Component.hpp"
#include "Entity/Entity-System.hpp"
#include "Entity/templates/Korwin.hpp"
#include "Utils/ResourceManager.hpp"
#include "constants.hpp"
#include "funcs.hpp"
#include "Entity/templates/Player.hpp"
#include "Entity/templates/Background.hpp"
#include "Entity/templates/SpawnerTest.hpp"
#include "Entity/templates/HPdisplay.hpp"
#include "Entity/templates/Wall.hpp"
#include "Utils/Random.hpp"


void gameloop() {
    // initialize `randomness`
    utils::Random::init(640);

    // set up settings for OpenGL
    sf::ContextSettings settings;
    int aa = sf::RenderTexture::getMaximumAntialiasingLevel();
    print(aa);
    settings.antialiasingLevel = aa;

    // Create window
    sf::RenderWindow window(
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "GrzesSFMLib",
        sf::Style::Default,
        settings
    );
    window.setVerticalSyncEnabled(true);
    std::cout << "OpenGL version: " << window.getSettings().majorVersion << 
        '.' << window.getSettings().minorVersion << std::endl;

    assertCond(
        window.getSettings().majorVersion < 3,
        "You need OpenGL 3.0 or better to play this game"
    );
    
    // create scene
    entity::EntitySystem testScene = entity::EntitySystem(&window);
    // setup background
    testScene.addEntity(new entity::background(
        &testScene
    ), entity::layers::back);
    // add test dev entity
    testScene.addEntity(new entity::SpawnerTest(
        utils::Position(0, 600),
        &testScene
    ));
    // add 2x korwin
    testScene.addEntity(new entity::tests::korwintest(
        utils::Position(6, 0),
        &testScene
    ));
    testScene.addEntity(new entity::tests::korwintest(
        utils::Position(0, 0),
        &testScene
    ));
    // add player entity
    testScene.addEntity(new entity::playerEntity(
        utils::Position(1000, 1000),
        &testScene
    ));
    testScene.addEntity(new entity::HPdisplayer(
        utils::Position(),
        &testScene
    ));

    // add some walls
    testScene.addEntity(new entity::Wall(
        utils::Position(500, 500),
        &testScene
    ));

    // get refrence to player and set it as a focused entity
    auto player = testScene.GetEntityByTag(entity::entityTags::player);
    testScene.focusedEntity = player;
    auto cameraPosSmoother = utils::CameraSmoother(
            10,
            player.lock()->position.xy
        );

    /*
     * main loop
     */
    print("entering main loop!")
    while (window.isOpen()) {
        // do Update() tick;
        testScene.doTick();
    }
    utils::ResourceManager::Flush();
}
