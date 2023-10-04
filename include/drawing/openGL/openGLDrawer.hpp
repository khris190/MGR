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
#include "external_utils/stb_image_write.h"
#include "drawing/openGL/handler.hpp"
// #include <GL/gl.h>
#include <cuda_gl_interop.h>

namespace OpenGLDrawer
{
    extern GLuint bufferID;
    unsigned char* GetCUDAImgDataPointer(int width, int height);

    void Initialize(int width, int height);

    void Draw(Genotype& populus, float scale);

    void clean();

    std::vector<unsigned char> getPixels();

    void SaveToPNG(const char* filename);

    void AddTriangles(Genotype& populus, float Scale = 0.2f);

    std::vector<float> prepareTriangles(Genotype& genes, float Scale);
} // namespace OpenGLDrawer

#endif // OPENGLDRAWER_HPP
