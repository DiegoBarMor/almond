#include "event_manager.hpp"

// -----------------------------------------------------------------------------
void nd::EventManager::handle_event(const nd::Event& event) { // FUNC@handle_event
    __last_event = event;
} // END@handle_event


// -----------------------------------------------------------------------------
