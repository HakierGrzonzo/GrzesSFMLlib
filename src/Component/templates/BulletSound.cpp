#include "BulletSound.hpp"


namespace component {
    BulletSound::BulletSound(entity::Entity* parent_) : Component(parent_) {
        isInitialized = false;
    }

    void BulletSound::Update() {
        if (!isInitialized) {
            isInitialized = true;
            parent->scene->audioScene.addSource(
                    parent->scene->getWeakPtr(parent),
                    "sfx/bulletsound.wav.aac",
                    .4,
                    true
                );
        }
    }
}
