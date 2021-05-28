#include "Inputs.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include "../funcs.hpp"

namespace entity {
    InputDirector::InputDirector() {
        // this pointer will expire and all weak_ptr's in subscriberMap wil be .expired()
        auto ptrToExpire = std::make_shared<callBackContainer>(new callBackContainer {nullptr, nullCallback});
        for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
            subscriberMap[i] = std::weak_ptr<callBackContainer>(ptrToExpire);
        }
    }
    
    std::shared_ptr<callBackContainer> InputDirector::subscribe(sf::Keyboard::Key key, void (*callback)(void*), void* arg) {
        if (subscriberMap[key].expired()) {
            // key is not bound to anything
            auto callbackElement = std::make_shared<callBackContainer>(new callBackContainer {arg, callback});
            subscriberMap[key] = std::weak_ptr<callBackContainer>(callbackElement);
            print("registered callback for: " + std::to_string(key));
            return callbackElement;
        }
        throw std::runtime_error("Key is bound!");
    }

    void InputDirector::doTick() {
        for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
            if (!subscriberMap[i].expired()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i))) {
                    subscriberMap[i].lock()->callback(subscriberMap[i].lock()->arg);
                }
            }
        }
    }

    void nullCallback(void* arg) {}
}
