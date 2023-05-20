#ifndef OPENGLDRAWER_HPP
#define OPENGLDRAWER_HPP

#include "genetic/Genotype.hpp"
#include "handler.hpp"
#include "objects/mesh.hpp"
#include "my_utils/Logger.hpp"
#include "common/DataStructures.hpp"
#include "drawing/openGL/objects/mesh.hpp"
#include "genetic/Genotype.hpp"
#include <GL/glcorearb.h>
#ifdef __clang__
#define STBIWDEF static inline
#endif
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "drawing/openGL/handler.hpp"
#include <GL/gl.h>
#include <cuda_gl_interop.h>

namespace OpenGLDrawer
{
    void Initialize(int width, int height);

    unsigned char* Draw(Genotype& populus);

    void clean();

    void SaveToPNG(const char* filename);

    void AddTriangles(Genotype& populus, float Scale = 0.2f);

    std::vector<float> prepareTriangles(Genotype& genes, float Scale);
} // namespace OpenGLDrawer

#endif // OPENGLDRAWER_HPP
