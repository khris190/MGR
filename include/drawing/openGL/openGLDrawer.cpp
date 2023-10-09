#include "openGLDrawer.hpp"
#include "cuda_runtime_api.h"
#include "drawing/openGL/objects/Mesh.hpp"
#include "drawing/openGL/shaders/fullscreenFBO.hpp"
#include "driver_types.h"
#include "my_utils/Profiler.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <alloca.h>
#include <cstddef>
#include <cstdlib>
#include <memory>
namespace openGLDrawer {

std::unique_ptr<OGLhandler> OGlhandler;

void initialize(int width, int height)
{
    OGlhandler = std::make_unique<OGLhandler>(width, height);
}

void draw(Genotype& populus, [[maybe_unused]] float scale)
{
    newTimer("Draw");
    Mesh drawing;
    drawing.AddVao(OGlhandler->newTriangleShader, populus, GL_TRIANGLES);
    OGlhandler->mainWindow->cleanWindow();
    glUseProgram(OGlhandler->newTriangleShader->shaderProgram); // wlaczenie programu cieniowania
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, OGlhandler->mainWindow->width, OGlhandler->mainWindow->height);
    glClear(GL_DEPTH_BUFFER_BIT);
    drawing.DrawLastVAO();
    OGlhandler->mainWindow->swapBuffer();
    drawing.Clear();
}
void clean()
{
    // leave in case of need of cleanup
}

std::vector<unsigned char> getPixels()
{
    std::vector<unsigned char> data(OGlhandler->mainWindow->width * OGlhandler->mainWindow->height * 4);
    {
        glReadPixels(0, 0, OGlhandler->mainWindow->width, OGlhandler->mainWindow->height, GL_RGBA, GL_UNSIGNED_BYTE,
            data.data());
    }
    return data;
}

void saveToPNG(const char* filename)
{
    std::vector<unsigned char> data = getPixels();
    std::vector<unsigned char> flippedPixels(OGlhandler->mainWindow->width * OGlhandler->mainWindow->height * 4);
    {
        newTimer("pixelFlippin");
        for (int y = 0; y < OGlhandler->mainWindow->height; y++) {
            memcpy(flippedPixels.data() + (y * OGlhandler->mainWindow->width * 4),
                data.data() + ((OGlhandler->mainWindow->height - y - 1) * OGlhandler->mainWindow->width * 4),
                OGlhandler->mainWindow->width * 4);
        }
    }
    {
        newTimer("fileWritin");
        stbi_write_png(filename, OGlhandler->mainWindow->width, OGlhandler->mainWindow->height, 4, flippedPixels.data(),
            OGlhandler->mainWindow->width * 4);
    }
}

inline myData::position rotate(float x, float y, float angle)
{
    return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}
} // namespace openGLDrawer