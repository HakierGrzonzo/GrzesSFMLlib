#include "SpawnerTest.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/sprites/Test.hpp"
#include "../../Component/templates/spawners/Test.hpp"
#include "Korwin.hpp"

namespace entity {
    SpawnerTest::SpawnerTest(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::test, scene_) {
    }

    void SpawnerTest::Initialize() {
        add_component(component::sprites::testSprite);
        //add_component(component::spawners::Generic<tests::korwintest>)
        //add_component(component::Debug);
    }
    void SpawnerTest::LateInitialize() {
        auto spawner = GetComponent<component::Spawner>();
        assertCond(spawner == nullptr, "Spawner is missing");
        spawner->startSpawning(2, 2000, -1);
        scene->audioScene.addSource(
                scene->getWeakPtr(this),
                "test.aac",
                1,
                true
            );
    }
    SpawnerTest::~SpawnerTest() {}
}
