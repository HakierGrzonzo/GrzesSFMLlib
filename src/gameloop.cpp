#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <box2d/b2_math.h>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
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
#include "Component/templates/sprites/Background.hpp"
#include "Component/templates/Physics.hpp"
#include "Utils/CameraSmoother.hpp"
#include "Utils/Random.hpp"
#include "Audio/AudioScene.hpp"


void gameloop() {
    utils::Random::init(420);
    // ========================== GAME WINDOW ========================== 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml plswrk");
    sf::View view;
    float currentZoom = 2.;
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.zoom(currentZoom);
    view.setCenter(100.f, 100.f);
    window.setVerticalSyncEnabled(true);
    
    // create scene
    entity::EntitySystem testScene = entity::EntitySystem(&window, &currentZoom);
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

    // get refrence to player
    auto player = testScene.GetEntityByTag(entity::entityTags::player);
    auto cameraPosSmoother = utils::CameraSmoother(
            10,
            player.lock()->position.xy
        );

    // Setup clock for measuring frametimes
    auto lastTime = std::chrono::steady_clock::now();

    /*
     * main loop
     */
    print("entering main loop!")
    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if (event.type == sf::Event::EventType::Resized) {
                // handle changed window size
                auto windowSize = window.getSize();
                view.setSize((float) windowSize.x, (float) windowSize.y);
                view.zoom(currentZoom);
                print("Window size changed!");
                printVec2(windowSize);
            }
        }
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> timeSinceLastFrame = now - lastTime;
        lastTime = now;
        // print fps and other stats
        std::cout << "fps: " <<
            1.0 / timeSinceLastFrame.count() <<
            "\tframetime: " <<
            timeSinceLastFrame.count() <<
            "\tentities: " <<
            testScene.background.size() +
                testScene.normal.size() +
                testScene.top.size() <<
            "\r"; 
        std::cout.flush();

        // not-so-simple movement mechanics
        b2Vec2 playerForce {0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        utils::Position preUpdatePos;
        if (!player.expired()) {
            preUpdatePos = player.lock()->position;
        }
        // do Update() tick;
        testScene.doUpdateTick();
        testScene.doFixedUpdateTick(timeSinceLastFrame.count());

        // Refresh view
        if (!player.expired()) {
            auto playerPhys = player.lock()->GetComponent<component::PhysicsBody>();
            auto postUpdatePos = player.lock()->position;
            auto newViewPos = cameraPosSmoother.calculatePosition(
                    box2sf(playerPhys->body->GetLinearVelocity()),
                    window.getView().getSize(), 
                    postUpdatePos.xy, 
                    timeSinceLastFrame.count()
                );
            view.setCenter(newViewPos);
            testScene.audioScene.Update(newViewPos);
            window.setView(view);
        }

        // DRAWING SECTION
        window.clear();
        for (long unsigned int i = 0; i < testScene.background.size(); i++) {
            auto toRender = testScene.background[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assertCond(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.normal.size(); i++) {
            auto toRender = testScene.normal[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assertCond(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        for (long unsigned int i = 0; i < testScene.top.size(); i++) {
            auto toRender = testScene.top[i]->GetComponent<component::Renderable>();
            if (toRender != nullptr) {
                auto renderStruct = toRender->Render();
                assertCond(renderStruct.drawable == nullptr, "Nullptr in background render");
                if (renderStruct.shader == nullptr) window.draw(*(renderStruct.drawable));
                else window.draw(*(renderStruct.drawable), renderStruct.shader);
            }
        }
        window.display();
    }
    utils::ResourceManager::Flush();
}
