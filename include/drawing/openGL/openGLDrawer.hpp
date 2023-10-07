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
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include "objects/Mesh.hpp"
#include <GL/glcorearb.h>
#include <cuda_gl_interop.h>

namespace OpenGLDrawer {
extern GLuint bufferID;
extern OGLhandler* OGlhandler;

unsigned char* GetCUDAImgDataPointer(int width, int height);

void Initialize(int width, int height);

void Draw(Genotype& populus, float scale);

void clean();

std::vector<unsigned char> getPixels();

void SaveToPNG(const char* filename);

void AddTriangles(Genotype& populus, float Scale = 0.2f);

std::vector<float> prepareTriangles(Genotype& genes, float Scale);
std::vector<Shaders::Triangle2::VertexInput> prepareTriangles2(Genotype& genes);
} // namespace OpenGLDrawer

#endif // OPENGLDRAWER_HPP
