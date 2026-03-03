#include "InputManager.h"

void InputManager::update(InputManager* This)
{
    int current = This->currentState;
    This->autoRepeatState = 0;
    This->shortHoldState = 0;

    int mask = 1;
    for (int i = 0; i < 31; i++)
    {
        if (current & mask)
        {
            // Increment hold counter for this key
            This->durationCounters[i]++;

            // Logic for "Short Hold" / initial press buffer (< 8 frames)
            if (This->durationCounters[i] < 8)
                This->shortHoldState |= mask;

            // Logic for Auto-Repeat
            // If held < 26 frames, set auto-repeat bit
            if (This->durationCounters[i] < 26)
                This->autoRepeatState |= mask;
            else
                This->durationCounters[i] -= 8;
        }
        else
            This->durationCounters[i] = 0; // Key not held, reset counter
        mask <<= 1;
    }

    // Calculate Trigger (Pressed This Frame) and Release
    // Trigger = Current AND (NOT Previous)
    int changes = This->currentState ^ This->previousState;

    This->triggerState = changes & This->currentState;
    This->releaseState = changes & This->previousState; // (NOT Current AND Previous)
}