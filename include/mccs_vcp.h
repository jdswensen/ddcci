#ifndef _MCCS_VCP_H_
#define _MCCS_VCP_H_

#include <stdio.h>
#include <stdint.h>

// ================================================================================================
// General
// ================================================================================================
#define MCCS_VCP_NEW_CONTROL_VALUE 0x02

// ================================================================================================
// Preset Operations
// ================================================================================================
#define MCCS_VCP_RESTORE_FACTORY_DEFAULTS 0x04
#define MCCS_VCP_RESTORE_FACTORY_LUMINANCE_CONTRAST_DEFAULTS 0x05
#define MCCS_VCP_RESTORE_FACTORY_GEOMETRY_DEFAULTS 0x06
#define MCCS_VCP_RESTORE_FACTORY_COLOR_DEFAULT 0x08
#define MCCS_VCP_RESTORE_FACTORY_TV_DEFAULTS 0x0A
#define MCCS_VCP_SETTINGS 0xB0

// ================================================================================================
// Image Adjustments
// ================================================================================================
#define MCCS_VCP_LUMINANCE_BRIGHTNESS 0x10
#define MCCS_VCP_CONTRAST 0x12


// ================================================================================================
// Display Control
// ================================================================================================
#define MCCS_VCP_DISPLAY_CONTROLLER_ID 0xC8
#define MCCS_VCP_DISPLAY_FIRMWARE_VERSION 0xC9
#define MCCS_VCP_DISPLAY_VCP_VERSION 0xDF

// ================================================================================================
// Miscellaneous Functions
// ================================================================================================
#define MCCS_VCP_ASSET_TAG 0xD2

// ================================================================================================
// Manufacturer Specific
// ================================================================================================
#define MCCS_VCP_MANUFACTURER_0 0xE0
#define MCCS_VCP_MANUFACTURER_1 0xE1
#define MCCS_VCP_MANUFACTURER_2 0xE2
#define MCCS_VCP_MANUFACTURER_3 0xE3
#define MCCS_VCP_MANUFACTURER_4 0xE4
#define MCCS_VCP_MANUFACTURER_4 0xE5
#define MCCS_VCP_MANUFACTURER_5 0xE6
#define MCCS_VCP_MANUFACTURER_7 0xE7

#endif