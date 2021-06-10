#include "Inputs.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include "../funcs.hpp"

namespace entity {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789__________();,.\"/\\~=- __\t______+-*/lrud0123456789";

    callBackContainer::callBackContainer() {
        arg = nullptr;
        callback = &nullCallback;
    }

    callBackContainer::callBackContainer(void* arg_, void (*callback_)(void*)) {
        arg = arg_;
        callback = callback_;
        if (callback == nullptr) {throw std::runtime_error("null callback");}
    }

    InputDirector::InputDirector() {
        // this pointer will expire and all weak_ptr's in subscriberMap wil be .expired()
        auto ptrToExpire = std::make_shared<callBackContainer>(callBackContainer());
        for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
            subscriberMap[i] = std::weak_ptr<callBackContainer>(ptrToExpire);
        }
    }
    
    std::shared_ptr<callBackContainer> 
    InputDirector::subscribe(
            sf::Keyboard::Key key, 
            void (*callback)(void*), 
            void* arg,
            bool force) {
        if (subscriberMap[key].expired() || force) {
            // key is not bound to anything or we force assingment
            assertCond(callback == nullptr, "callback is null!");
            auto callbackElement = std::make_shared<callBackContainer>(callBackContainer(arg, callback));
            subscriberMap[key] = std::weak_ptr<callBackContainer>(callbackElement);
            std::string registeredFor;
            try {
                registeredFor = alphabet[key];
            } catch (...) {
                registeredFor = std::to_string(key);
            }
            print("registered callback for: " + registeredFor);
            return callbackElement;
        }
        throw std::runtime_error("Key is bound!");
    }

    void InputDirector::doTick() {
        for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
            if (!subscriberMap[i].expired()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i))) {
                    auto ptr = subscriberMap[i].lock();
                    std::cout.flush();
                    ptr->callback(ptr->arg);
                }
            }
        }
    }

    void nullCallback(void* arg) {}
}
