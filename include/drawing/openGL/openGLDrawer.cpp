#include "openGLDrawer.hpp"
#include "cuda_runtime_api.h"
#include "drawing/openGL/objects/Mesh.hpp"
#include "drawing/openGL/shaders/fullscreenFBO.hpp"
#include "driver_types.h"
#include "my_utils/Profiler.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <alloca.h>
#include <memory>
#include "my_utils/Profiler.hpp"
#include "objects/Mesh.hpp"
namespace openGLDrawer {

std::unique_ptr<OGLhandler> OGlhandler;

void initialize(int width, int height)
{
    OGlhandler = std::make_unique<OGLhandler>(width, height);
    OGlhandler->mainWindow->makeCurrent();
}

void draw(Genotype& populus, [[maybe_unused]] float scale)
{
    newTimer("Draw");
    Mesh drawing;
    drawing.addVao(OGlhandler->newTriangleShader, populus, GL_TRIANGLES);
    OGlhandler->mainWindow->cleanWindow();
    glUseProgram(OGlhandler->newTriangleShader->shaderProgram); // wlaczenie programu cieniowania
    OGlhandler->mainWindow->bindFramebuffer();
    glViewport(0, 0, OGlhandler->mainWindow->getWidth(), OGlhandler->mainWindow->getHeight());
    drawing.drawLastVAO();
    OGlhandler->mainWindow->swapBuffer();
}
void clean()
{
    delete OGlhandler.release();
    // leave in case of need of cleanup
}

std::vector<unsigned char> getPixels()
{
    newTimer("getPixels");
    std::vector<unsigned char> data(OGlhandler->mainWindow->getWidth() * OGlhandler->mainWindow->getHeight() * 4);
    glReadPixels(0, 0, OGlhandler->mainWindow->getWidth(), OGlhandler->mainWindow->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
        data.data());
    return data;
}
std::vector<unsigned char> getPixelsSecond()
{
    newTimer("getPixels");
    std::vector<unsigned char> data(OGlhandler->drawerWindow->getWidth() * OGlhandler->drawerWindow->getHeight() * 4);
    glReadPixels(0, 0, OGlhandler->drawerWindow->getWidth(), OGlhandler->drawerWindow->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
        data.data());
    return data;
}
void drawSecond(Genotype& populus)
{
    Mesh drawing;
    OGlhandler->drawerWindow->makeCurrent();
    drawing.addVao(OGlhandler->newTriangleShader, populus, GL_TRIANGLES);
    OGlhandler->drawerWindow->cleanWindow();
    glUseProgram(OGlhandler->newTriangleShader->shaderProgram); // wlaczenie programu cieniowania
    OGlhandler->drawerWindow->bindFramebuffer();
    glViewport(0, 0, OGlhandler->drawerWindow->getWidth(), OGlhandler->drawerWindow->getHeight());
    drawing.drawLastVAO();
    OGlhandler->drawerWindow->swapBuffer();
}
void saveToPNG(const char* filename)
{
    std::vector<unsigned char> data = getPixelsSecond();
    OGlhandler->mainWindow->makeCurrent();
    std::vector<unsigned char> flippedPixels(OGlhandler->drawerWindow->getWidth() * OGlhandler->drawerWindow->getHeight() * 4);

    for (int y = 0; y < OGlhandler->drawerWindow->getHeight(); y++) {
        memcpy(flippedPixels.data() + (y * OGlhandler->drawerWindow->getWidth() * 4),
            data.data() + ((OGlhandler->drawerWindow->getHeight() - y - 1) * OGlhandler->drawerWindow->getWidth() * 4),
            OGlhandler->drawerWindow->getWidth() * 4);
    }
    stbi_write_png(filename, OGlhandler->drawerWindow->getWidth(), OGlhandler->drawerWindow->getHeight(), 4, flippedPixels.data(),
        OGlhandler->drawerWindow->getWidth() * 4);
}

inline myData::position rotate(float x, float y, float angle)
{
    return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}
} // namespace openGLDrawer