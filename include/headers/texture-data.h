#ifndef INFO_H
#define INFO_H

#include <iostream>

/* Amount of textures the texture atlas holds
   E.G:
   Current texture atlas has a size of 256x256 pixels
   Each texture is 16x16
   256/16 = 16, so 16 rows and columns of textures
   16*16 textures = 256 textures */
int TEX_ATLAS_WIDTH = 16;
int TEX_ATLAS_HEIGHT = 16;

float calculateOffset(int tex_index, const char* type){
   if (type == "height"){
      std::cout << ((1.0/TEX_ATLAS_HEIGHT) * tex_index) << std::endl;
      return ((1.0/TEX_ATLAS_HEIGHT) * tex_index);
   }
   else{
      std::cout << ((1.0/(TEX_ATLAS_WIDTH) * tex_index)) << std::endl;
      return ((1.0/TEX_ATLAS_WIDTH) * tex_index);
   }
}

float DIRT_TEX_POS_TOP_LEFT[2] = {0.0, 0.0};
float DIRT_TEX_POS_TOP_RIGHT[2] = {calculateOffset(1, "width"), 0.0};
float DIRT_TEX_POS_BOTTOM_LEFT[2] = {0.0, calculateOffset(1, "height")};
float DIRT_TEX_POS_BOTTOM_RIGHT[2] = {calculateOffset(1, "width"), calculateOffset(1, "height")};
// Side Grass texture Coords
float SIDE_GRASS_TEX_POS_TOP_LEFT[2] = {calculateOffset(1, "width"), 0.0};
float SIDE_GRASS_TEX_POS_TOP_RIGHT[2] = {calculateOffset(2, "width"), 0.0};
float SIDE_GRASS_TEX_POS_BOTTOM_LEFT[2] = {calculateOffset(1, "width"), calculateOffset(1, "height")};
float SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[2] = {calculateOffset(2, "width"), calculateOffset(1, "height")};
// Grass texture Coords
float GRASS_TEX_POS_TOP_LEFT[2] = {calculateOffset(2, "width"), 0.0};
float GRASS_TEX_POS_TOP_RIGHT[2] = {calculateOffset(3, "width"), 0.0};
float GRASS_TEX_POS_BOTTOM_LEFT[2] = {calculateOffset(2, "width"), calculateOffset(1, "height")};
float GRASS_TEX_POS_BOTTOM_RIGHT[2] = {calculateOffset(3, "width"), calculateOffset(1, "height")};

#endif