#include "modes/Rivals2.hpp"

#define ANALOG_STICK_MIN 1
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

Rivals2::Rivals2() : ControllerMode() {}

void Rivals2::UpdateDigitalOutputs(const InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.rt1;
    outputs.b = inputs.rf1;
    outputs.x = inputs.rf2;
    outputs.y = inputs.rf6;
    outputs.buttonR = inputs.rf3;
    if (inputs.nunchuk_connected) {
        // Lightshield with C button.
        if (inputs.nunchuk_c) {
            outputs.triggerLAnalog = 49;
        }
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.lf4;
    }
    outputs.triggerRDigital = inputs.rf5;
    outputs.start = inputs.mb1;
    outputs.select = inputs.mb3;
    outputs.home = inputs.mb2;
    outputs.buttonL = inputs.rf7;
    outputs.leftStickClick = inputs.rf8;
    outputs.rightStickClick = inputs.lt1 || inputs.lt2;

    // Activate D-Pad layer by holding Mod X + Mod Y.
    if (inputs.lt1 && inputs.lt2) {
        outputs.dpadUp = inputs.rt4;
        outputs.dpadDown = inputs.rt2;
        outputs.dpadLeft = inputs.rt3;
        outputs.dpadRight = inputs.rt5;
    }

    // Activate select by holding Mod X
    if ((inputs.lt1)) outputs.select = inputs.mb1;
    // Activate home by holding Mod Y
    if ((inputs.lt2)) outputs.home = inputs.mb1;
}

void Rivals2::UpdateAnalogOutputs(const InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.lf3, // Left
        inputs.lf1, // Right
        inputs.lf2, // Down
        inputs.rf4, // Up
        inputs.rt3, // C-Left
        inputs.rt5, // C-Right
        inputs.rt2, // C-Down
        inputs.rt4, // C-Up
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.lf4 || inputs.rf5;

    // Joystick accurate diagonals [joystick outputs (0.87~, 0.87~) rather than (+/- 1.2, 1.2)]
    if (directions.diagonal && !shield_button_pressed) {
        // X = 92 (0.78 in-game); [x < 0.8] allows crouch tilts/crouch turn-around tilts
        outputs.leftStickX = 128 + (directions.x * 92);
        // Y = 96 (0.83 in-game); [y > 0.8] allows fast fall
        outputs.leftStickY = 128 + (directions.y * 96);
    }

    if (directions.diagonal && shield_button_pressed) {
        // (0.77~, 0.77~) to prevent spot dodging when inputting lower 45° notch while grounded
        outputs.leftStickX = 128 + (directions.x * 92);
        outputs.leftStickY = 128 + (directions.y * 92);
    }

    if (inputs.lt1) {
        /* if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 76);
            // MX Horizontal Tilts
            if (inputs.rt1) {
                outputs.leftStickX = 128 + (directions.x * 44);
            }
        }

        if(directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 73);
        } */

        // Extra DI, Air Dodge, and Up B angles
        if (directions.diagonal) {
            if (shield_button_pressed) {
                outputs.leftStickX = 128 + (directions.x * 90);
                outputs.leftStickY = 128 + (directions.y * 42);
            }

            /* // Angled F-tilts
            if (inputs.rt1) {
                outputs.leftStickX = 128 + (directions.x * 69);
                outputs.leftStickY = 128 + (directions.y * 53);
            } */

            // Angles just for DI and Up B
            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 96);
                outputs.leftStickY = 128 + (directions.y * 28);
            }

            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 84);
                outputs.leftStickY = 128 + (directions.y * 34);
            }

            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 40);
            }

            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 86);
                outputs.leftStickY = 128 + (directions.y * 57);
            }

            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 82);
                outputs.leftStickY = 128 + (directions.y * 67);
            }
        }
    }

    if (inputs.lt2) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 41);
        }

        /* if(directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 78);
        } */

        // Extra DI, Air Dodge, and Up B angles
        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 41);
            outputs.leftStickY = 128 + (directions.y * 76);


            // Angles just for DI and Up B
            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 96);
            }

            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 34);
                outputs.leftStickY = 128 + (directions.y * 84);
            }

            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 76);
            }

            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 57);
                outputs.leftStickY = 128 + (directions.y * 86);
            }

            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 67);
                outputs.leftStickY = 128 + (directions.y * 82);
            }
        }
    }

    // Shut off C-stick when using D-Pad layer.
    if (inputs.lt1 && inputs.lt2) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;

        if (directions.horizontal) {
            // "perfect" walking speed (matches animation)
            outputs.leftStickX = 128 + (directions.x * 61);
        }
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }

    // Turns off Start when holding Mod X or Mod Y
    if ((inputs.lt1 || inputs.lt2)) {
        outputs.start = false;
    }
}
