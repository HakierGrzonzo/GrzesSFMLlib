#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace entity {
    struct callBackContainer {
        void* arg;
        void (*callback)(void*);
    };
    class InputDirector {
        public:
            InputDirector();
            // register a callback consistin of a void function taking a void* parameter
            // it is not pretty but it does not work
            std::shared_ptr<callBackContainer> subscribe(sf::Keyboard::Key key, void (*callback)(void*), void* arg);
            void doTick();
        private:
            std::weak_ptr<callBackContainer> subscriberMap[sf::Keyboard::KeyCount];
    };
    void nullCallback(void* arg);
}
