#include "modes/DefaultKeyboardMode.hpp"

#include "core/socd.hpp"
#include "core/state.hpp"

DefaultKeyboardMode::DefaultKeyboardMode() : KeyboardMode() {}

void DefaultKeyboardMode::UpdateKeys(const InputState &inputs) {
    Press(HID_KEY_SHIFT_LEFT, inputs.rt2);
    Press(HID_KEY_ARROW_LEFT, inputs.lf3);
    Press(HID_KEY_ARROW_DOWN, inputs.lf2);
    Press(HID_KEY_ARROW_RIGHT, inputs.lf1);
    Press(HID_KEY_ARROW_UP, inputs.lf5);
    Press(HID_KEY_ENTER, inputs.mb1);
    Press(HID_KEY_SPACE, inputs.lt1);
    Press(HID_KEY_X, inputs.rf1);
    Press(HID_KEY_Z, inputs.rt1);
    Press(HID_KEY_C, inputs.rf3);
}
