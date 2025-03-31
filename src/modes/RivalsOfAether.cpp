#include "modes/RivalsOfAether.hpp"

#define ANALOG_STICK_MIN 1
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

RivalsOfAether::RivalsOfAether(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up,      socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };
}

void RivalsOfAether::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a;
    outputs.b = inputs.b;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    outputs.buttonL = inputs.lightshield;
    outputs.buttonR = inputs.z;
    outputs.triggerLDigital = inputs.l;
    outputs.triggerRDigital = inputs.r;
    outputs.start = inputs.start;
    outputs.select = inputs.select;
    outputs.home = inputs.home;
    outputs.leftStickClick = inputs.up2;

    // Activate D-Pad layer by holding Mod X + Mod Y.
    if (inputs.mod_x && inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    // Activate select by holding Mod X
    if ((inputs.mod_x)) outputs.select = inputs.start;

    // Activate home by holding Mod Y
    if ((inputs.mod_y)) outputs.home = inputs.start;

    // Don't override dpad up if it's already pressed using the MX + MY dpad
    // layer.
    outputs.dpadUp = outputs.dpadUp || inputs.midshield;
}

void RivalsOfAether::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.l || inputs.r;

    if (inputs.mod_x) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 76);
            // MX Horizontal Tilts
            if (inputs.a) {
                outputs.leftStickX = 128 + (directions.x * 44);
            }
        }

        if(directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 73);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 70);
            outputs.leftStickY = 128 + (directions.y * 34);

            // Angled F-tilts
            if (inputs.a) {
                outputs.leftStickX = 128 + (directions.x * 69);
                outputs.leftStickY = 128 + (directions.y * 53);
            }

            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 96);
                outputs.leftStickY = 128 + (directions.y * 28);
            }
            
            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 84);
                outputs.leftStickY = 128 + (directions.y * 34);
            }

            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 76);
                outputs.leftStickY = 128 + (directions.y * 40);
            }
            
            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 86);
                outputs.leftStickY = 128 + (directions.y * 57);
            }

            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 82);
                outputs.leftStickY = 128 + (directions.y * 67);
            }

            /* Shortest UpB when holding Z*/
            if (inputs.z) { 
                // (x, y), (53, 68), (~0.31, ~0.188) [coords, code_values, in-game values] 
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 42);

                /* 60% Magnitude UpB when holding B and Z*/
                if (inputs.b) {
                    // (x, y), (68, 42), (~0.49, ~0.188) [coords, code_values, in-game values]
                    outputs.leftStickX = 128 + (directions.x * 68);
                    outputs.leftStickY = 128 + (directions.y * 42);
                    // (x, y), (71, 47), (~0.52, ~0.24) [coords, code_values, in-game values]
                    if (inputs.c_down) {
                        outputs.leftStickX = 128 + (directions.x * 71);
                        outputs.leftStickY = 128 + (directions.y * 47);
                    }
                    // (x, y), (71, 51), (~0.52, 0.29~) [coords, code_values, in-game values]
                    if (inputs.c_left) {
                        outputs.leftStickX = 128 + (directions.x * 71);
                        outputs.leftStickY = 128 + (directions.y * 51);
                    }
                    // (x, y), (69, 55), (~0.51, ~0.34) [coords, code_values, in-game values]
                    if (inputs.c_up) {
                        outputs.leftStickX = 128 + (directions.x * 69);
                        outputs.leftStickY = 128 + (directions.y * 55);
                    }
                    // (x, y), (64, 60), (, ~0.38) [coords, code_values, in-game values]
                    if (inputs.c_right) {
                        outputs.leftStickX = 128 + (directions.x * 64);
                        outputs.leftStickY = 128 + (directions.y * 60);
                    }
                }
            }
        }
    }

    if (inputs.mod_y) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 41);
        }

        if(directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 78);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 41);
            outputs.leftStickY = 128 + (directions.y * 76);

            if (inputs.b) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 96);
            }

            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 34);
                outputs.leftStickY = 128 + (directions.y * 84);
            }

            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 76);
            }

            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 57);
                outputs.leftStickY = 128 + (directions.y * 86);
            }

            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 67);
                outputs.leftStickY = 128 + (directions.y * 82);
            }
            
            /* Shortest UpB when holding Z*/
            if (inputs.z) {
                // (x, y), (42, 53), (~0.188, ~0.31) [coords, code_values, in-game values] 
                outputs.leftStickX = 128 + (directions.x * 42);
                outputs.leftStickY = 128 + (directions.y * 53);

                /* 60% Magnitude UpB when holding B and Z*/
                if (inputs.b) {
                    // (x, y), (42, 68), (~0.188, ~0.49) [coords, code_values, in-game values] 
                    outputs.leftStickX = 128 + (directions.x * 42);
                    outputs.leftStickY = 128 + (directions.y * 68);
                    // (x, y), (47, 71), (~0.24, ~0.52) [coords, code_values, in-game values]
                    if (inputs.c_down) {
                        outputs.leftStickX = 128 + (directions.x * 47);
                        outputs.leftStickY = 128 + (directions.y * 71);
                    }
                    // (x, y), (51, 71), (~0.29, ~0.52) [coords, code_values, in-game values]
                    if (inputs.c_left) {
                        outputs.leftStickX = 128 + (directions.x * 51);
                        outputs.leftStickY = 128 + (directions.y * 71);
                    }
                    // (x, y), (55, 69), (~0.34, ~0.51) [coords, code_values, in-game values]
                    if (inputs.c_up) {
                        outputs.leftStickX = 128 + (directions.x * 55);
                        outputs.leftStickY = 128 + (directions.y * 69);
                    }
                    // (x, y), (60, 64), (~0.38, ~0.) [coords, code_values, in-game values]
                    if (inputs.c_right) {
                        outputs.leftStickX = 128 + (directions.x * 60);
                        outputs.leftStickY = 128 + (directions.y * 64);
                    }
                }
            }
        }
    }

    // Shut off C-stick when using D-Pad layer.
    if (inputs.mod_x && inputs.mod_y) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;

        if (directions.horizontal) {
            // "perfect" walking speed (matches animation)
            outputs.leftStickX = 128 + (directions.x * 61);
        }
    }

    // Turns off Start when holding Mod X or Mod Y
    if ((inputs.mod_x || inputs.mod_y)) {
        outputs.start = false;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
