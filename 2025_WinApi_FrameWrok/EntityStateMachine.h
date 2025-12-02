#pragma once
#include <unordered_map>
#include <string>
#include <cassert>
#include "EntityState.h"

class EntityStateMachine {
public:
    EntityStateMachine() 
        : _currentState(nullptr) {}

    void AddState(const std::string& name, EntityState* state) {
        _states[name] = state;
    }

    void ChangeState(const std::string& newStateName, bool forced = false) {
        auto it = _states.find(newStateName);

        EntityState* newState = it->second;

        if (!forced && _currentState == newState)
            return;

        if (_currentState)
            _currentState->Exit();

        _currentState = newState;
        _currentState->Enter();
    }

    void UpdateStateMachine() {
        if (_currentState)
            _currentState->Update();
    }

private:
    EntityState* _currentState;
    std::unordered_map<std::string, EntityState*> _states;
};
