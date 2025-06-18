#ifndef _CONFIG_DEFAULTS_HPP
#define _CONFIG_DEFAULTS_HPP

#include <Adafruit_TinyUSB.h>
#include <config.pb.h>

// clang-format off

const Config default_config = {
    .game_mode_configs_count = 10,
    .game_mode_configs = {
    GameModeConfig {
            .mode_id = MODE_MELEE,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 0,
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_LF4 },
        },
       GameModeConfig {
            .mode_id = MODE_PROJECT_M,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_RF4 }, // LF5 activates Up
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_LF3 },
        },
        GameModeConfig {
            .mode_id = MODE_ULTIMATE,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_RF4 }, // LF5 activates Up
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_LF2 },
        },
        GameModeConfig {
            .mode_id = MODE_PROJECT_M,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_RT1 }, // LF5 activates A
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_RT1 },
        },
        GameModeConfig {
            .mode_id = MODE_PROJECT_M,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_LF15 }, // LF5 activates C45
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_RF7 },
        },
        GameModeConfig {
            .mode_id = MODE_PROJECT_M,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 2,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_LF14 }, // LF5 activates DP*
                ButtonRemap { .physical_button = BTN_RF8, .activates = BTN_RF16 }, // D-Pad Down instead of D-Pad Up
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_RF8 },
        },
        GameModeConfig {
            .mode_id = MODE_FGC,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_RF4 }, // LF5 activates Up
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_LF5 },
        },
        GameModeConfig {
            .mode_id = MODE_RIVALS_OF_AETHER,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_RF4 }, // LF5 activates Up
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_RF1 },
        },
        GameModeConfig {
            .mode_id = MODE_RIVALS_2,
            .socd_pairs_count = 4,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_RF4, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT3, .button_dir2 = BTN_RT5, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_RT2, .button_dir2 = BTN_RT4, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 1,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_RF4 }, // LF5 activates Up
            },
            .activation_binding_count = 3,
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_RF5 },
        },
        GameModeConfig {
            .mode_id = MODE_CUSTOM,
            .socd_pairs_count = 2,
            .socd_pairs = {
                SocdPair { .button_dir1 = BTN_LF3, .button_dir2 = BTN_LF1, .socd_type = SOCD_NEUTRAL },
                SocdPair { .button_dir1 = BTN_LF2, .button_dir2 = BTN_LT1, .socd_type = SOCD_NEUTRAL },
            },
            .button_remapping_count = 2,
            .button_remapping = {
                ButtonRemap { .physical_button = BTN_RT4, .activates = BTN_LT1 },
                ButtonRemap { .physical_button = BTN_LF5, .activates = BTN_LT1 },
            },
            .activation_binding = { BTN_LT1, BTN_MB1, BTN_LF1 },
            .custom_mode_config = 1,
        },
    },
    .communication_backend_configs_count = 8,
    .communication_backend_configs = {
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_XINPUT,
            .default_mode_config = 2,
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_DINPUT,
            .default_mode_config = 2,
            .activation_binding_count = 1,
            .activation_binding = { BTN_RF3 },
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_NINTENDO_SWITCH,
            .default_mode_config = 3,
            .activation_binding_count = 1,
            .activation_binding = { BTN_RF2 },
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_GAMECUBE,
            .default_mode_config = 2,
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_N64,
            .default_mode_config = 1,
            .activation_binding = { BTN_RT3 },
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_NES,
            .default_mode_config = 1,
            .activation_binding_count = 1,
            .activation_binding = { BTN_LT1 },
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_SNES,
            .default_mode_config = 1,
            .activation_binding_count = 1,
            .activation_binding = { BTN_LT2 },
        },
        CommunicationBackendConfig {
            .backend_id = COMMS_BACKEND_CONFIGURATOR,
            .activation_binding_count = 1,
            .activation_binding = { BTN_MB1 },
        }
    },
    .custom_modes_count = 1,
    .custom_modes = {
        CustomModeConfig {
            .digital_button_mappings_count = 9,
            .digital_button_mappings = {
                { BTN_RF1 },
                { BTN_RF2 },
                { BTN_RF5 },
                { BTN_RF6 },
                { BTN_RF8 },
                { BTN_RF7 },
                { BTN_RF3 },
                { BTN_RF4 },
                { BTN_MB1 },
                { BTN_RT3 },
                { BTN_RT1 },
                { BTN_RT5 },
                { BTN_LT1 },
                { BTN_LF2 },
                { BTN_LF3 },
                { BTN_LF1 },
                { BTN_LT2 },
                { BTN_RT2 },
            },
            .analog_trigger_mappings = {
                { BTN_RF4, TRIGGER_LT, 255 },
                { BTN_RF3, TRIGGER_RT, 255 },
            },
        }
    },
    .keyboard_modes_count = 0,
    .default_backend_config = 1,
    .default_usb_backend_config = 1,
    .melee_options = {
        .crouch_walk_os = false,
        .disable_ledgedash_socd_override = true,
    },
    .project_m_options = {
        .true_z_press = true,
        .disable_ledgedash_socd_override = true,
    },
};

// clang-format on

#endif
