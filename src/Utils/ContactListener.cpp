#include "ContactListener.hpp"
#include "../Component/templates/Physics.hpp"

namespace utils {
    void ContactListener::BeginContact(b2Contact* contact) {
        auto bodyAuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        auto bodyBuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        if (bodyAuserdata != nullptr && bodyBuserdata != nullptr) {
            bodyAuserdata->OnCollisionEnter(bodyBuserdata);
            bodyBuserdata->OnCollisionEnter(bodyAuserdata);
        }
    }
    void ContactListener::EndContact(b2Contact* contact) {
        auto bodyAuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        auto bodyBuserdata = reinterpret_cast<component::PhysicsBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        if (bodyAuserdata != nullptr && bodyBuserdata != nullptr) {
            bodyAuserdata->OnCollisionLeave(bodyBuserdata);
            bodyBuserdata->OnCollisionLeave(bodyAuserdata);
        }
    }
}
