#include "Bullet.hpp"
#include "Creature.hpp"
#include "Physics.hpp"
#include "../../Entity/templates/Explosion.hpp"
#include <box2d/b2_body.h>
#include "../../funcs.hpp"

namespace component {
    Bullet::Bullet(entity::Entity* parent) : PhysicsBody(parent) {
        deleteAfter = 5;
        isDone = false;
        damage = -10;
    };
    
    void Bullet::setDamage(int newDamage) {
        damage = newDamage;
    }

    void Bullet::Awake() {
        assertCond(world == nullptr, "b2World is not set");
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = true;
        bodyDef.position.Set(parent->position.xy.x / box2sfRatio, parent->position.xy.y / box2sfRatio);
        // add `this` as userData for Colision callbacks to work
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
        body = world->CreateBody(&bodyDef);
        shape.m_radius = .01;
        fixture.shape = &shape;
        fixture.density = .5;
        fixture.friction = .001;
        body->CreateFixture(&fixture);
    }

    void Bullet::OnCollisionEnter(PhysicsBody* other) {
        auto creature = other->getParent()->GetComponent<Creature>();
        if (creature != nullptr) {
            creature->changeHP(-damage);
            // We cant delete box2d body while physics are working
        }
        isDone = true;
    }

    void Bullet::FixedUpdate(double timeStep) {
        deleteAfter -= timeStep;
    }

    void Bullet::LateFixedUpdate() {
        parent->position.xy = box2sf(body->GetPosition());
        parent->position.rotation = body->GetAngle();
        if (isDone || deleteAfter < 0) {
            parent->scene->addEntity(
                    new entity::Explosion(
                        parent->position,
                        parent->scene
                    ));
            parent->scene->deleteEntity(parent);
        }
    }
}
