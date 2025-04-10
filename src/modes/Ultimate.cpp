/* CONVERTED TO HDR MODE */
#include "modes/Ultimate.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

Ultimate::Ultimate() : ControllerMode() {}

void Ultimate::UpdateDigitalOutputs(const InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.rt1;
    outputs.b = inputs.rf1;
    outputs.x = inputs.rf2;
    outputs.y = inputs.rf6;
    outputs.buttonL = inputs.rf7;
    outputs.buttonR = inputs.rf3;
    outputs.triggerLDigital = inputs.lf4;
    outputs.triggerRDigital = inputs.rf5;
    outputs.start = inputs.mb1;
    outputs.select = inputs.mb3;
    outputs.home = inputs.mb2;

    // Turn on D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.rt4;
        outputs.dpadDown = inputs.rt2;
        outputs.dpadLeft = inputs.rt3;
        outputs.dpadRight = inputs.rt5;
    }

    // Activate select by holding Mod X
    if ((inputs.lt1)) {
        outputs.select = inputs.mb1;
    }
    // Activate home by holding Mod Y
    if ((inputs.lt2)) {
        outputs.home = inputs.mb1;
    }
    // Don't override dpad up if it's already pressed using the MX + MY dpad
    // layer.
    outputs.dpadUp = outputs.dpadUp || inputs.rf8;

    // D-Pad Neutral SOCD
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c) {
        if (inputs.rt2 && inputs.rf8) {
            outputs.dpadUp = false;
            outputs.dpadDown = false;
        }
    }
}

void Ultimate::UpdateAnalogOutputs(const InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.lf3,
        inputs.lf1,
        inputs.lf2,
        inputs.rf4,
        inputs.rt3,
        inputs.rt5,
        inputs.rt2,
        inputs.rt4,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.lf4 || inputs.rf5;

    if (directions.diagonal) {
        // down + horizontal + B outputs down special
        if (inputs.rf1 && directions.y == -1) {
            outputs.leftStickX = 128 + (directions.x * 28);
            outputs.leftStickY = 128 + (directions.y * 85);
        }
    }

    if (inputs.lt1) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 49);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 49);
        }

        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 65);
            outputs.rightStickY = 128 + (directions.y * 44);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 49);
            outputs.leftStickY = 128 + (directions.y * 28);

            // Angled tilts
            if (inputs.rt1) {
                outputs.leftStickX = 128 + (directions.x * 47);
                outputs.leftStickY = 128 + (directions.y * 43);
            }

            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 85);
                outputs.leftStickY = 128 + (directions.y * 31);
            }

            if (inputs.rf5) {
                outputs.leftStickX = 128 + (directions.x * 96);
                outputs.leftStickY = 128 + (directions.y * 28);
            }

            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 99);
                outputs.leftStickY = 128 + (directions.y * 40);
            }

            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 95);
                outputs.leftStickY = 128 + (directions.y * 50);
            }

            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 86);
                outputs.leftStickY = 128 + (directions.y * 57);
            }

            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 72);
                outputs.leftStickY = 128 + (directions.y * 61);
            }
        }
    }

    if (inputs.lt2) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 35);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 52);

            // Shield drop
            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 53);
            }
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 38);
            outputs.leftStickY = 128 + (directions.y * 49);

            // Shield drop
            if (shield_button_pressed && directions.y == -1) {
                outputs.leftStickX = 128 + (directions.x * 38);
                outputs.leftStickY = 128 + (directions.y * 53);
            }

            if (inputs.rf5) {
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 82);
            }

            if (inputs.rf1) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 96);
            }

            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 99);
            }

            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 50);
                outputs.leftStickY = 128 + (directions.y * 95);
            }

            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 57);
                outputs.leftStickY = 128 + (directions.y * 86);
            }

            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 61);
                outputs.leftStickY = 128 + (directions.y * 72);
            }
        }
    }

    /* if (inputs.lf5) {
        // Up2 Nair
        outputs.leftStickX = 128;
        outputs.leftStickY = 128;
    } */

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    // We don't apply this for c-up + c-left/c-right in case we want to implement
    // C-stick nair somehow.
    if (directions.cx != 0 && directions.cy == -1) {
        // 3000 9875
        outputs.rightStickX = 128 + (directions.cx * 35);
        outputs.rightStickY = 128 + (directions.cy * 98);
    }

    if (inputs.lf4) {
        outputs.triggerLAnalog = 140;
    }

    if (inputs.rf5) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Turns off Start when holding Mod X or Mod Y
    if ((inputs.lt1 || inputs.lt2)) {
        outputs.start = false;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}