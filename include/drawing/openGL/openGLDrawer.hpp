#ifndef OPENGLDRAWER_HPP
#define OPENGLDRAWER_HPP

#include "driver_types.h"
#include <cstddef>
#ifdef __clang__
#define STBIWDEF static inline
#endif
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "common/DataStructures.hpp"
#include "drawing/openGL/OGLhandler.hpp"
#include "drawing/openGL/objects/Mesh.hpp"
#include "drawing/openGL/shaders/Triangle2.hpp"
#include "external_utils/stb_image_write.h"
#include "genetic/Genotype.hpp"
#include <GL/glcorearb.h>
#include <cuda_gl_interop.h>

namespace openGLDrawer {
extern GLuint bufferID;
extern std::unique_ptr<OGLhandler> OGlhandler;

unsigned char* GetCUDAImgDataPointer(int width, int height);

void initialize(int width, int height);

void draw(Genotype& populus, float scale);
void drawSecond(Genotype& populus);

void clean();

std::vector<unsigned char> getPixels();

void saveToPNG(const char* filename);
} // namespace openGLDrawer

#endif // OPENGLDRAWER_HPP
