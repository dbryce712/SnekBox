#ifndef _CONFIG_MODE_SELECTION_HPP
#define _CONFIG_MODE_SELECTION_HPP

#include "core/state.hpp"
#include "modes/DefaultKeyboardMode.hpp"
#include "modes/FgcMode.hpp"
#include "modes/Melee20Button.hpp"
#include "modes/Melee20ButtonGoated.hpp"
#include "modes/ProjectM.hpp"
#include "modes/ProjectMBidou.hpp"
#include "modes/ProjectNair.hpp"
#include "modes/RivalsOfAether.hpp"
#include "modes/Ultimate.hpp"
#include "modes/HDR.hpp"
#include "modes/RushdownRevolt.hpp"

extern KeyboardMode *current_kb_mode;

void set_mode(CommunicationBackend *backend, ControllerMode *mode) {
    // Delete keyboard mode in case one is set, so we don't end up getting both controller and
    // keyboard inputs.
    delete current_kb_mode;
    current_kb_mode = nullptr;

    // Set new controller mode.
    backend->SetGameMode(mode);
}

void set_mode(CommunicationBackend *backend, KeyboardMode *mode) {
    // Delete and reassign current keyboard mode.
    delete current_kb_mode;
    current_kb_mode = mode;

    // Unset the current controller mode so backend only gives neutral inputs.
    backend->SetGameMode(nullptr);
}

void select_mode(CommunicationBackend *backend) {
    InputState &inputs = backend->GetInputs();
    if (inputs.mod_x && !inputs.mod_y && inputs.start) {
        if (inputs.l) {
            set_mode(
                backend,
                new Melee20Button(socd::SOCD_NEUTRAL, { .crouch_walk_os = false })
            );
        } else if (inputs.left) {
            set_mode(
                backend,
                new ProjectM(
                    socd::SOCD_NEUTRAL,
                    { .true_z_press = true, .ledgedash_max_jump_traj = false }
                )
            );
        } else if (inputs.up2) {
            set_mode(
                backend,
                new Melee20ButtonGoated(socd::SOCD_NEUTRAL, { .crouch_walk_os = false })
            );
        } else if (inputs.down) {
            set_mode(backend, new Ultimate(socd::SOCD_NEUTRAL));
        } else if (inputs.right) {
            set_mode(backend, new FgcMode(socd::SOCD_NEUTRAL, socd::SOCD_NEUTRAL));
        } else if (inputs.b) {
            set_mode(backend, new RivalsOfAether(socd::SOCD_NEUTRAL));
        } else if (inputs.x) {
            set_mode(backend, new HDR(socd::SOCD_NEUTRAL));
        } else if (inputs.y) {
            set_mode(backend, new RushdownRevolt(socd::SOCD_NEUTRAL));
        } else if (inputs.z) {
            set_mode(
                backend,
                new ProjectM(
                    socd::SOCD_NEUTRAL,
                    { .true_z_press = false, .ledgedash_max_jump_traj = false }
                )
            );
        } else if (inputs.a) {
            set_mode(
                backend,
                new ProjectMBidou(
                    socd::SOCD_NEUTRAL,
                    { .true_z_press = true, .ledgedash_max_jump_traj = false }
                )
            );
        } else if (inputs.lightshield) {
            set_mode(
                backend,
                new ProjectNair(
                    socd::SOCD_NEUTRAL,
                    { .true_z_press = true, .ledgedash_max_jump_traj = false }
                )
            );
        } else if (inputs.midshield) {
            set_mode(
                backend,
                new ProjectNair(
                    socd::SOCD_NEUTRAL,
                    { .true_z_press = false, .ledgedash_max_jump_traj = false }
                )
            );
        }
    } /* else if (inputs.mod_y && !inputs.mod_x && inputs.start) {
        if (inputs.l) {
            set_mode(backend, new DefaultKeyboardMode(socd::SOCD_2IP_NO_REAC));
        }
    } */
}

#endif
