#ifndef _INPUT_H_
#define _INPUT_H_

#include <map>
#include <queue>

#include "../events/delegates/action.h"

#include "input_type.h"
#include "key_code.h"
#include "key.h"

namespace bebone::core {
    using namespace std;

    /// Singleton Input System class. Works with Action delegates
    class Input {
        private:
            using BeboneAction = Action<>;

            map<Key, BeboneAction> key_actions;
            queue<Key> queued_keys;

            Input() = default;

            void queue_key(const KeyCode& key_code, const InputType& input_type);
            void execute_queued_actions();

        public:
            Input(const Input& obj) = delete;
            void operator=(Input const& obj) = delete;

            /// Returns singleton reference to the input system object
            /// @return Input system object reference
            static Input& get_instance();

            /*!
            * Registers the key to do specific action
            * 
            * @param key_code - key code
            * @param action - function object, which will execute when the key will be pressed/released
            * @param input_type - specifies the input type. By default it is set to InputType::PRESS
            */
            void register_key_action(const KeyCode& key_code, std::function<void()>& action, const InputType& input_type = InputType::Press);
            
            /*!
            * Removes the specific action from the key
            * 
            * @param key_code - key code
            * @param action - function object, which will execute when the key will be pressed/released
            * @param input_type - specifies the input type. By default it is set to InputType::PRESS
            */
            void remove_key_action(const KeyCode& key_code, std::function<void()>& action, const InputType& input_type = InputType::Press);

            friend class InputHandler;
            friend struct KeyListener;
            friend struct MouseListener;
    };
}

#endif