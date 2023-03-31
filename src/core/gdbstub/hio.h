// Copyright 2022 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <string>

#include "common/common_types.h"

namespace GDBStub {

/**
 * Based on the Rosalina implementation:
 * https://github.com/LumaTeam/Luma3DS/blob/master/sysmodules/rosalina/include/gdb.h#L46C27-L62
 */
struct PackedGdbHioRequest {
    char magic[4]; // "GDB\x00"
    u32 version;

    // Request
    char function_name[16 + 1];
    char param_format[8 + 1];

    u64 parameters[8];
    u32 string_lengths[8];

    // Return
    s64 retval;
    s32 gdb_errno;
    bool ctrl_c;
};

void SetHioRequest(const VAddr address);

bool HandleHioReply(const u8* const command_buffer, const u32 command_length);

bool HasPendingHioRequest();

bool WaitingForHioReply();

std::string BuildHioRequestPacket();

} // namespace GDBStub
