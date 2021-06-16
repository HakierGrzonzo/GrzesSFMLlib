#include "StaticPhysics.hpp"
#include "Physics.hpp"
#include "../../funcs.hpp"
#include "Sprite.hpp"
#include <box2d/b2_body.h>

namespace component {
    StaticBody::StaticBody(entity::Entity* parent_) : 
        PhysicsBody(parent_) {
            isFullyInit = false;
        }

    void StaticBody::Awake() {
        assertNotNull(world);
    }

    void StaticBody::Update() {
        // Be a 'late awake()'
        if (!isFullyInit) {
            isFullyInit = true;
            bodyDef.type = b2_staticBody;
            bodyDef.fixedRotation = true;
            bodyDef.position.Set(explode(sf2box(parent->position.xy)));
            bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
            body = world->CreateBody(&bodyDef);

            auto spriteRef = parent->GetComponent<component::SpriteRenderer>();
            assertNotNull(spriteRef);
            auto spriteBounds = spriteRef->getSpriteSize();
            spriteBounds /= float(2);
            shape.SetAsBox(explode(sf2box(spriteBounds)));
            fixture.shape = &shape;
            fixture.friction = .3;
            fixture.restitution = 1;
            body->CreateFixture(&fixture);
        }

    }
}
