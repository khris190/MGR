#include "openGLDrawer.hpp"
#include "drawing/openGL/objects/Mesh.hpp"
#include "my_utils/Profiler.hpp"
#include <GL/gl.h>
// #include <GL/glext.h>
// #include <alloca.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include "my_utils/Profiler.hpp"
#include "objects/Mesh.hpp"
namespace openGLDrawer
{

    std::unique_ptr<OGLhandler> OGlhandler;

    void initialize(int width, int height)
    {
        OGlhandler = std::make_unique<OGLhandler>(width, height);
        OGlhandler->mainWindow->makeCurrent();
    }

    void draw(Genotype &populus, [[maybe_unused]] float scale)
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
    }

    std::vector<unsigned char> getPixels()
    {
        newTimer("getPixels");
        std::vector<unsigned char> data(OGlhandler->mainWindow->getWidth() * OGlhandler->mainWindow->getHeight() * 4);
        glReadPixels(0, 0, OGlhandler->mainWindow->getWidth(), OGlhandler->mainWindow->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
                     data.data());
        return data;
    }

    void drawSecond(Genotype &populus)
    {
        newTimer("drawSecond");
        OGlhandler->drawerVBO->bind();
        Mesh drawing;
        drawing.addVao(OGlhandler->newTriangleShader, populus, GL_TRIANGLES);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                       // Set the clear color to a light blue
        glClear(GL_COLOR_BUFFER_BIT);                               // czyszczenie bufora koloru
        glUseProgram(OGlhandler->newTriangleShader->shaderProgram); // wlaczenie programu cieniowania
        glViewport(0, 0, OGlhandler->drawerVBO->getWidth(), OGlhandler->drawerVBO->getHeight());
        drawing.drawLastVAO();
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind framebuffer
    }
    std::vector<unsigned char> getPixelsSecond()
    {
        newTimer("getPixels");
        OGlhandler->drawerVBO->bind();
        std::vector<unsigned char>
            data(OGlhandler->drawerVBO->getWidth() * OGlhandler->drawerVBO->getHeight() * 4);
        glReadPixels(0, 0, OGlhandler->drawerVBO->getWidth(), OGlhandler->drawerVBO->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
                     data.data());
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind framebuffer
        return data;
    }
    void saveToPNG(const char *filename)
    {
        newTimer("saveToPNG");
        std::vector<unsigned char> data = OGlhandler->drawerVBO->getPixels();
        OGlhandler->mainWindow->makeCurrent();
        if (INT32_MAX < OGlhandler->drawerVBO->getWidth() * OGlhandler->drawerVBO->getHeight() * 4)
        {
            std::cerr << "IMG INT OVERFLOWW BY: " << OGlhandler->drawerVBO->getWidth() * OGlhandler->drawerVBO->getHeight() * 4 - INT32_MAX << "BYTES" << std::endl;
            exit(10);
        }
        std::vector<unsigned char> flippedPixels(OGlhandler->drawerVBO->getWidth() * OGlhandler->drawerVBO->getHeight() * 4);

        for (int y = 0; y < OGlhandler->drawerVBO->getHeight(); y++)
        {
            memcpy(flippedPixels.data() + (y * OGlhandler->drawerVBO->getWidth() * 4),
                   data.data() + ((OGlhandler->drawerVBO->getHeight() - y - 1) * OGlhandler->drawerVBO->getWidth() * 4),
                   OGlhandler->drawerVBO->getWidth() * 4);
        }
        newTimer("file savin");
        stbi_write_png(filename, OGlhandler->drawerVBO->getWidth(), OGlhandler->drawerVBO->getHeight(), 4, flippedPixels.data(),
                       OGlhandler->drawerVBO->getWidth() * 4);
    }

    inline myData::position rotate(float x, float y, float angle)
    {
        return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }
} // namespace openGLDrawer