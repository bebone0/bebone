#ifndef _BEBONE_CORE_EVENTS_LISTENERS_EVENT_H_
#define _BEBONE_CORE_EVENTS_LISTENERS_EVENT_H_

#include "../../types.h"

namespace bebone::core {
    template<class EventCategoryType, EventCategoryType eventType>
    class Event {
        private:
            bool handled = false;

        public:
            virtual ~Event() = default;

            void set_handled(const bool& value) {
                handled = value;
            }

            const bool& is_handled() const {
                return handled;
            }

            static constexpr const EventCategoryType type = eventType;
    };
}

#endif