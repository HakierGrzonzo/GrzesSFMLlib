#pragma once
#include "../Component.hpp"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/box2d.h>
#include <memory>

namespace component {
    class PhysicsBody : public Component {
            // Box2D dynamic body class
            // #TODO: try to get collider size from sprite
        public:
            PhysicsBody(entity::Entity* parent_);
            b2Body* body;
            std::shared_ptr<b2World> world;
            void Awake();
            void LateFixedUpdate();
            entity::Entity* getParent() const;
            // Called when collision begins
            virtual void OnCollisionEnter(PhysicsBody* other);
            // Called when collision ends
            virtual void OnCollisionLeave(PhysicsBody* other);
            virtual ~PhysicsBody();
        private:
            b2BodyDef bodyDef;
            b2PolygonShape shape;
            b2FixtureDef fixture;
    };

}
