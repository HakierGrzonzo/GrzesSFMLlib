#include "physicsBody.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include <box2d/b2_body.h>
#include <box2d/box2d.h>
#include "funcs.hpp"
#include "constants.hpp"

namespace component {
    PhysicsBody::PhysicsBody(entity::Entity* parent_) : component::Component(parent_) {
        world = nullptr;
        body = nullptr;
    }
    PhysicsBody::~PhysicsBody() {
        world->DestroyBody(body);
    }
    void PhysicsBody::Awake() {
        assertCond(world == nullptr, "b2World is not set!");
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(parent->position.xy.x / box2sfRatio, parent->position.xy.y / box2sfRatio);
        body = world->CreateBody(&bodyDef);
        shape.SetAsBox(.1, .1);
        fixture.shape = &shape;
        fixture.density = 1;
        fixture.friction = .3;
        body->CreateFixture(&fixture);
    }
    void PhysicsBody::FixedUpdate(double timeDelta) {
       parent->position.xy = box2sf(body->GetPosition());
    };
}
