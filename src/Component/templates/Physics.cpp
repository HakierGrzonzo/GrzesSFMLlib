#include "Physics.hpp"
#include <box2d/b2_body.h>
#include <box2d/box2d.h>
#include "../../funcs.hpp"
#include "../../constants.hpp"
#include "Creature.hpp"

namespace component {
    PhysicsBody::PhysicsBody(entity::Entity* parent_) : component::Component(parent_) {
        world = nullptr;
        body = nullptr;
    }
    PhysicsBody::~PhysicsBody() {
        // Destroy box2d body
        world->DestroyBody(body);
    }
    void PhysicsBody::Awake() {
        assertCond(world == nullptr, "b2World is not set!");
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = true;
        bodyDef.position.Set(parent->position.xy.x / box2sfRatio, parent->position.xy.y / box2sfRatio);
        // add `this` as userData for Colision callbacks to work
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
        body = world->CreateBody(&bodyDef);
        shape.SetAsBox(.1, .1);
        fixture.shape = &shape;
        fixture.density = 1;
        fixture.friction = .3;
        body->CreateFixture(&fixture);
    }
    void PhysicsBody::LateFixedUpdate() {
       parent->position.xy = box2sf(body->GetPosition());
       parent->position.rotation = body->GetAngle();
    };
    entity::Entity* PhysicsBody::getParent() const{
        return parent;
    }
    void PhysicsBody::OnCollisionEnter(PhysicsBody* other) {
        if (other->getParent()->tag == entity::player) {
            other->getParent()->GetComponent<Creature>()->changeHP(-10);
        }
    }

    void PhysicsBody::OnCollisionLeave(PhysicsBody* other) {}
}
