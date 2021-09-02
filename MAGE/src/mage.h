#include "pch.h"

#include "mage/constants.h"

#include "mage/graphics/sprite.h"
#include "mage/graphics/sprite_atlas.h"
#include "mage/graphics/sprite_atlas_bank.h"
#include "mage/graphics/sprite_atlas_coords.h"
#include "mage/graphics/sprite_bank.h"

#include "mage/graphics/wrap/buffer.h"
#include "mage/graphics/wrap/camera.h"
#include "mage/graphics/wrap/framebuffer.h"
#include "mage/graphics/wrap/shader_program.h"
#include "mage/graphics/wrap/texture.h"
#include "mage/graphics/wrap/vertex_array.h"

#include "mage/world/chunk.h"
#include "mage/world/sprite_batch.h"
#include "mage/world/tile.h"

#include "mage/world/dynamic/dynamic.h"
#include "mage/world/dynamic/dynamic_batch.h"
#include "mage/world/dynamic/dynamic_batch_list.h"
#include "mage/world/dynamic/dynamic_list.h"
