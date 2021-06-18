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
#include "Utils/Position.hpp"
#include "Utils/ResourceManager.hpp"
#include "constants.hpp"
#include "funcs.hpp"
#include "Entity/templates/Player.hpp"
#include "Entity/templates/Background.hpp"
#include "Entity/templates/SpawnerTest.hpp"
#include "Entity/templates/HPdisplay.hpp"
#include "Entity/templates/Wall.hpp"
#include "Entity/templates/HPeffect.hpp"
#include "Entity/templates/Target.hpp"
#include "Entity/templates/GameOverText.hpp"
#include "Utils/Random.hpp"
#include <fstream>


void gameloop() {
    bool lowPerf = false;
    // if on linux limit fps on battery
#ifdef __linux
    // open file with the status of the first battery
    // we pretend that every laptop has just one
    std::ifstream batteryFile ("/sys/class/power_supply/BAT0/status");
    if (batteryFile.is_open()) {
        // If we succeded in opening the file, that means that there is battery
        // in the system (although we do not check if it is there right now)
        std::string status;
        std::getline(batteryFile, status);
        // That file will contain a string with the battery status, we only
        // care if it is Discharging
        if (status == "Discharging") {
            std::cout << "You are on battery so we will limit fps to 30!"
                << std::endl;
            // try to send a desktop notification using libnotify
            std::system("notify-send \"GrzesSFMLib\" \"Limiting fps to 30 on battery\"");
            lowPerf = true;
        }
    }
#endif
    // initialize `randomnes`
    utils::Random::init(640);

    // set up settings for OpenGL
    sf::ContextSettings settings;
    if (lowPerf) {
        // if lower performence -> set AA to 0
        settings.antialiasingLevel = 0;
    } else {
        int aa = sf::RenderTexture::getMaximumAntialiasingLevel();
        settings.antialiasingLevel = aa;
    }

    // Create window
    sf::RenderWindow window(
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "GrzesSFMLib",
        sf::Style::Default,
        settings
    );
    if (lowPerf) {
        window.setFramerateLimit(30);
        window.setVerticalSyncEnabled(false);
    } else {
        window.setVerticalSyncEnabled(true);
    }
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
    /*
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
    */
    // add player entity
    testScene.addEntity(new entity::playerEntity(
        utils::Position(),
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

    // add hp effect
    testScene.addEntity(new entity::HPeffect(
        utils::Position(),
        &testScene
        ), entity::top
    );
    testScene.addEntity(new entity::GameOverText(
        utils::Position(),
        &testScene
        ), entity::top
    );
    testScene.addEntity(new entity::Target(
                utils::Position(),
                &testScene
        ), entity::back
    );

    // get refrence to player and set it as a focused entity
    auto player = testScene.GetEntityByTag(entity::entityTags::player);
    testScene.focusedEntity = player;
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
