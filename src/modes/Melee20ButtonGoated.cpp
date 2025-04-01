#include "modes/Melee20ButtonGoated.hpp"

#define ANALOG_STICK_MIN 48
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 208

Melee20ButtonGoated::Melee20ButtonGoated(socd::SocdType socd_type, Melee20ButtonGoatedOptions options) {
    _socd_pair_count = 5;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up,      socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up2,     socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };

    _options = options;
    _horizontal_socd = false;
}

void Melee20ButtonGoated::HandleSocd(InputState &inputs) {
    _horizontal_socd = inputs.left && inputs.right;
    InputMode::HandleSocd(inputs);
}

void Melee20ButtonGoated::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a;
    outputs.b = inputs.b;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.z;
    if (inputs.nunchuk_connected) {
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.l;
    }
    outputs.triggerRDigital = inputs.r;
    outputs.start = inputs.start;

    // Activate D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    if (inputs.select)
        outputs.dpadLeft = true;
    if (inputs.home)
        outputs.dpadRight = true;
}

void Melee20ButtonGoated::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up || inputs.up2,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.l || inputs.r || inputs.lightshield || inputs.midshield;
    
    if (directions.diagonal) {
        // q1/2 = 7000 7000
        outputs.leftStickX = 128 + (directions.x * 56);
        outputs.leftStickY = 128 + (directions.y * 56);
        // L, R, LS, and MS + q3/4 = 7000 6875 (For vanilla shield drop. Gives 44.5
        // degree wavedash). Also used as default q3/4 diagonal if crouch walk option select is
        // enabled.
        if (directions.y == -1) {
            outputs.leftStickX = 128 + (directions.x * 80);
            outputs.leftStickY = 128 + (directions.y * 60);

            if (shield_button_pressed || _options.crouch_walk_os) {
                outputs.leftStickX = 128 + (directions.x * 56);
                outputs.leftStickY = 128 + (directions.y * 55);
            }     
        }
    }

    if (inputs.mod_x) {
        // MX + Horizontal (even if shield is held) = 6625 = 53
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 53);
        }
        // MX + Vertical (even if shield is held) = 5375 = 43
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 43);

            // shine on platform without falling through
            if (inputs.b) {
                outputs.leftStickY = 128 + (directions.y * 45);
            }
        }
        if (directions.diagonal && shield_button_pressed) {
            // 9500 2875 = 76 23
            outputs.leftStickX = 128 + (directions.x * 76);
            outputs.leftStickY = 128 + (directions.y * 23);
        }

        if (directions.diagonal && !shield_button_pressed) {
            // 22.9638 - 7375 3125 = 59 25
            outputs.leftStickX = 128 + (directions.x * 59);
            outputs.leftStickY = 128 + (directions.y * 25);

            /* Up B Angles */
            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 23);
            }
            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 75);
                outputs.leftStickY = 128 + (directions.y * 31);
            }
            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 73);
                outputs.leftStickY = 128 + (directions.y * 39);
            }
            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 69);
                outputs.leftStickY = 128 + (directions.y * 46);
            }
            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 50);
                outputs.leftStickY = 128 + (directions.y * 41);
            }
            
        }

        // Angled fsmash
        if (directions.cx != 0) {
            // 8500 5250 = 68 42
            outputs.rightStickX = 128 + (directions.cx * 68);
            outputs.rightStickY = 128 + (directions.y * 42);
        }
    }

    if (inputs.mod_y) {
        // MY + Horizontal (even if shield is held) = 3375 = 27
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 27);
        }
        // MY + Vertical = 7375 = 59
        if (directions.vertical) {
            if (directions.y == 1) {
                outputs.leftStickY = 128 + (directions.y * 52);
            }
            if (directions.y == -1) {
                outputs.leftStickY = 128 + (directions.y * 59);
            }

            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 55);
            }
            
            // Pikachu/Pichu double up-special
            if (inputs.up && inputs.up2 && inputs.b) {
                outputs.leftStickY = 128 - (directions.y * 40);
            }

        }
        if (directions.diagonal && shield_button_pressed) {
            // MY + L, R, LS, and MS + q1/2 = 4750 8750 = 38 70
            outputs.leftStickX = 128 + (directions.x * 38);
            outputs.leftStickY = 128 + (directions.y * 70);
            // MY + L, R, LS, and MS + q3/4 = 5000 8500 = 40 68
            // Parasol dash
            if (directions.y == 1 && (inputs.x || inputs.y)) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 68);
            }
            // steepest wavedash
            if (directions.y == -1) {
                // 2875 9500 = 23 76
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 76);
            }
        }


        if (directions.diagonal && !shield_button_pressed) {
            // buffered turnaround vertical tilts
            if (directions.y == -1) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 53);
            }

            if (directions.y == 1) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 52);
            }

            /* Up B Angles */
            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 23);
                outputs.leftStickY = 128 + (directions.y * 76);
            }
            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 31);
                outputs.leftStickY = 128 + (directions.y * 75);
            }
            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 39);
                outputs.leftStickY = 128 + (directions.y * 75);
            }
            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 46);
                outputs.leftStickY = 128 + (directions.y * 69);
            }
            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 41);
                outputs.leftStickY = 128 + (directions.y * 50);
            }
        }

        // Slight angled fsmash
        if (directions.cx != 0) {
            // 9500 2875 = 76 23
            outputs.rightStickX = 128 + (directions.cx * 76);
            outputs.rightStickY = 128 + (directions.y * 23);
        }
    }

    /* if (inputs.up2) {
        // Up2 Nair
        outputs.leftStickX = 128;
        outputs.leftStickY = 128;
    } */

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        // 2875 9500 = 23 76
        outputs.rightStickX = 128 + (directions.cx * 23);
        outputs.rightStickY = 128 + (directions.cy * 76);
    }

    // Horizontal SOCD overrides X-axis modifiers (for ledgedash maximum jump
    // trajectory).
    if (_horizontal_socd && !directions.vertical) {
        outputs.leftStickX = 128 + (directions.x * 80);
    }

    if (inputs.lightshield) {
        outputs.triggerRAnalog = 43;
    }
    if (inputs.midshield) {
        outputs.triggerRAnalog = 94;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }
    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;

        // slight angled ftilts
        if (inputs.a && directions.diagonal) {
            // 9500 2875 = 76 23
            outputs.leftStickX = 128 + (directions.x * 76);
            outputs.leftStickY = 128 + (directions.y * 23);
        }
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
