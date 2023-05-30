#include "openGLDrawer.hpp"
#include "drawing/openGL/handler.hpp"
#include "drawing/openGL/objects/mesh.hpp"
#include "my_utils/Profiler.hpp"
namespace OpenGLDrawer
{
    GLuint bufferID;
    void TESTTEXTURE(int width, int height)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Specify the texture format and data type
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // Attach the texture to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    }

    unsigned char* GetCUDAImgDataPointer(int width, int height)
    {
        newTimer("cuda pass data FULL");
        cudaGraphicsResource* cudaResource;
        cudaGraphicsGLRegisterBuffer(&cudaResource, bufferID, cudaGraphicsMapFlagsNone);
        newTimer("cuda pass data");

        unsigned char* devPixels;
        size_t size;
        cudaGraphicsMapResources(1, &cudaResource, nullptr);
        cudaGraphicsResourceGetMappedPointer((void**)&devPixels, &size, cudaResource);
        return devPixels;
    }
    void Initialize(int width, int height)
    {
        OGLhandler::initEngine(width, height);

        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, bufferID);
        glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 4 * sizeof(unsigned char), nullptr, GL_STREAM_READ);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    }

    void Draw(Genotype& populus, float scale)
    {
        newTimer("new drawing");
        {
            newTimer("add triangles");
            AddTriangles(populus, scale);
        }
        OGLhandler::prepareScene();
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // if not already bound
        glViewport(0, 0, OGLhandler::width, OGLhandler::height);
        glClear(GL_DEPTH_BUFFER_BIT);
        mesh::DrawLastVAO();
        glfwSwapBuffers(OGLhandler::window);
        mesh::Clear();
    }
    void clean() { OGLhandler::cleanup(); }

    std::vector<unsigned char> getPixels()
    {
        std::vector<unsigned char> data(OGLhandler::width * OGLhandler::height * 4);
        {
            glReadPixels(0, 0, OGLhandler::width, OGLhandler::height, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
        }
        return data;
    }

    void SaveToPNG(const char* filename)
    {
        std::vector<unsigned char> data = getPixels();
        std::vector<unsigned char> flippedPixels(OGLhandler::width * OGLhandler::height * 4);
        {
            newTimer("pixelFlippin");
            for (int y = 0; y < OGLhandler::height; y++) {
                memcpy(flippedPixels.data() + (y * OGLhandler::width * 4),
                  data.data() + ((OGLhandler::height - y - 1) * OGLhandler::width * 4), OGLhandler::width * 4);
            }
        }
        {
            newTimer("fileWritin");
            stbi_write_png(filename, OGLhandler::width, OGLhandler::height, 4, data.data(), OGLhandler::width * 4);
        }
    }

    inline myData::position rotate(float x, float y, float angle)
    {
        return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }

    void AddTriangles(Genotype& genes, float Scale)
    {
        mesh::AddVao(prepareTriangles(genes, Scale), OGLhandler::shaderProgram, GL_TRIANGLES);
    }

    std::vector<float> prepareTriangles(Genotype& genes, float Scale)
    {
        std::vector<float> Verticies = std::vector<float>();
        int i = 0;
        int max = genes.genes.size();
        for (auto gene : genes.genes) {
            if (gene.type_of_shape == myData::ShapeType::triangle) {
                float color[4] = { gene.color.r, gene.color.g, gene.color.b, gene.color.a };
                float x = (gene.position.x * OGLhandler::width);
                float y = (gene.position.y * OGLhandler::height);

                float scaleX = gene.scale.x * Scale * OGLhandler::width;
                float scaleY = gene.scale.y * Scale * OGLhandler::height;
                float rotation = gene.rotation * 3.14;
                myData::position p1, p2;
                if (rotation != 0) {
                    p1 = rotate(scaleX, scaleY, rotation * 2);
                    p2 = rotate(-scaleX, scaleY, rotation * 2);
                }
                p1.move(x, y);
                p2.move(x, y);
                float distance = 1.f / max;
                x = x / (float)(OGLhandler::width)*2 - 1;
                y = y / (float)(OGLhandler::height)*2 - 1;
                p2.x = p2.x / (float)(OGLhandler::width)*2 - 1;
                p2.y = p2.y / (float)(OGLhandler::height)*2 - 1;
                p1.x = p1.x / (float)(OGLhandler::width)*2 - 1;
                p1.y = p1.y / (float)(OGLhandler::height)*2 - 1;
                Verticies.insert(Verticies.end(), { x, y, distance * i - 1.f, 1.f });
                Verticies.insert(Verticies.end(), color, color + 4);
                Verticies.insert(Verticies.end(), { p1.x, p1.y, distance * i - 1.f, 1.f });
                Verticies.insert(Verticies.end(), color, color + 4);
                Verticies.insert(Verticies.end(), { p2.x, p2.y, distance * i - 1.f, 1.f });
                Verticies.insert(Verticies.end(), color, color + 4);
            }
            i++;
        }
        return Verticies;
    }

} // namespace OpenGLDrawer