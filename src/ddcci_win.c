#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strsafe.h>
#include <winuser.h>
#include <wchar.h>
#include <HighLevelMonitorConfigurationAPI.h>
#include <LowLevelMonitorConfigurationAPI.h>
#include <physicalmonitorenumerationapi.h>
#pragma comment(lib, "Dxva2.lib")

#include "mccs_vcp.h"

LPRECT monitor_rect[2];
HMONITOR monitor_handles[2];
UINT8 index = 0;

#define CAP_STR_LEN (3 * 1024)

const uint8_t mccs_vcp_basic_cmds[] = {
    MCCS_VCP_NEW_CONTROL_VALUE,
    MCCS_VCP_LUMINANCE_BRIGHTNESS,
    MCCS_VCP_CONTRAST,
    MCCS_VCP_DISPLAY_CONTROLLER_ID,
    MCCS_VCP_DISPLAY_FIRMWARE_VERSION,
    MCCS_VCP_DISPLAY_VCP_VERSION
};

void last_error_to_string ( WCHAR *buffer, DWORD size )
{
    WCHAR error_msg[1024];
    DWORD last_error = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        last_error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        error_msg,
        size,
        NULL
    );

    snprintf(buffer, size, "0x%08x: ", last_error);
    strncat(buffer, error_msg, size);
}

void test_vcp_code ( HANDLE hmonitor, BYTE vcp_code )
{
    BOOL success = FALSE;
    MC_VCP_CODE_TYPE code_type = MC_SET_PARAMETER;
    DWORD current_value = 0;
    DWORD max_value = 0;

    success = GetVCPFeatureAndVCPFeatureReply(hmonitor, vcp_code, &code_type, &current_value, &max_value);
    if (success)
    {
        printf("success: vcp_code: 0x%02x, code_type: 0x%02x, current_value: 0x%04x, max_value: 0x%04x\n", vcp_code, code_type, current_value, max_value);
    }
    else
    {
        WCHAR error_string[1024];
        last_error_to_string(error_string, 1024);
        printf("failure: vcp_code: 0x%02x, error: %s", vcp_code, error_string);
    }

    return;
}

BOOL CALLBACK enum_monitor(HMONITOR handle, HDC hdc, LPRECT lprc_monitor, LPARAM dw_data)
{
    DWORD physical_monitor_count = 0;
    BOOL success = FALSE;
    LPPHYSICAL_MONITOR physical_monitors = NULL;
    DWORD caps_str_len = 0;

    printf("monitor callback\n");

    if (handle != NULL)
    {
        // Get the number of physical monitors
        success = GetNumberOfPhysicalMonitorsFromHMONITOR(handle, &physical_monitor_count);
        if (success)
        {
            // Allocate array for PHYSICAL_MONITOR structs
            physical_monitors = (LPPHYSICAL_MONITOR)malloc(physical_monitor_count * sizeof(PHYSICAL_MONITOR));
            if (physical_monitors != NULL)
            {
                success = GetPhysicalMonitorsFromHMONITOR(handle, physical_monitor_count, physical_monitors);
                if (success)
                {

                    Sleep(100);
                    success = GetCapabilitiesStringLength((physical_monitors->hPhysicalMonitor), &caps_str_len);
                    if (success)
                    {
                        printf("success: GetCapabilitiesStringLength: %d\n", caps_str_len);
                        LPSTR caps_str = (LPSTR)malloc(caps_str_len);
                        if (caps_str != NULL)
                        {
                            success = CapabilitiesRequestAndCapabilitiesReply(physical_monitors->hPhysicalMonitor, caps_str, caps_str_len);
                            printf("success: CapabilitiesRequestAndCapabilitiesReply: %s\n", caps_str);;
                        }
                    }
                    else
                    {
                        WCHAR error_string[1024];
                        last_error_to_string(error_string, 1024);
                        printf("failure: GetCapabilitiesStringLength, error: %s", error_string);
                    }

                    // Look for VCP codes even if caps string length fails
                    for (UINT8 index = 0; index < sizeof(mccs_vcp_basic_cmds)/sizeof(mccs_vcp_basic_cmds[0]); index++)
                    {
                        Sleep(100);
                        test_vcp_code(physical_monitors->hPhysicalMonitor, mccs_vcp_basic_cmds[index]);
                    }

                    DestroyPhysicalMonitors(physical_monitor_count, physical_monitors);
                }

                free(physical_monitors);
            }
        }
    }

    printf("\n");
    return TRUE;
}

void main ( void )
{
    printf("enum-monitors\n");
    EnumDisplayMonitors(NULL, NULL, &enum_monitor, 0);
}