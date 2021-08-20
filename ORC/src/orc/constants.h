#pragma once
#include "pch.h"

namespace orc::c
{
	constexpr static char game_window_title[] = "Game Window";

	constexpr static char test_window_title[] = "Test Window";

	constexpr static char test_dockspace_title[] = "Test Dockspace";
	constexpr static char test_dockspace_id[] = "__orc_dockspace_id";

	// Each chunk has 6 layers. Each layer is represented by AT MOST a single sprite batch. Therefore, a map can contain up to 512 * 512 chunks.
	constexpr static size_t sprite_batch_bank_size = 512 * 512 * 6;
}
