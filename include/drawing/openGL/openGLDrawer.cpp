#include "openGLDrawer.hpp"
#include "common/DataStructures.hpp"
#include "drawing/openGL/objects/mesh.hpp"
#include "genetic/Genotype.hpp"
namespace OpenGLDrawer
{

    void Initialize(int width, int height) { OGLhandler::initEngine(width, height); }

    void Draw(Genotype& populus)
    {
        {

            newTimer("new drawing");
            AddTriangles(populus);
        }
        bool once = true;
        while (!glfwWindowShouldClose(OGLhandler::window)) {
            {
                newTimer("new drawing");
                OGLhandler::renderScene();
                mesh::DrawVAO();

                glBindVertexArray(0);
                glfwSwapBuffers(OGLhandler::window); // zamieniamy bufory
                glfwPollEvents(); // przetwarzanie zdarzen
            }
            if (once) {
                logger.LogDeb(profiler.getTimingsAsString().c_str());
                once = false;
            }
        }

        logger.LogDeb(profiler.getTimingsAsString().c_str());
        OGLhandler::cleanup();

        glfwDestroyWindow(OGLhandler::window); // niszczy okno i jego kontekst
        glfwTerminate();
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
                float x = (gene.position.x * 2) - 1;
                float y = (gene.position.y * -2) + 1;

                float scaleX = gene.scale.x * Scale * 2;
                float scaleY = gene.scale.y * Scale * 2;
                float rotation = gene.rotation * 3.14;
                myData::position p1, p2;
                if (rotation != 0) {
                    p1 = rotate(scaleX, scaleY, rotation * 2);
                    p2 = rotate(-scaleX, scaleY, rotation * 2);
                }
                p1.move(x, y);
                p2.move(x, y);
                float distance = 1.f / max;

                Verticies.insert(Verticies.end(), { x, y, distance * i - 0.5f, 1.f });
                Verticies.insert(Verticies.end(), color, color + 4);
                Verticies.insert(Verticies.end(), { p1.x, p1.y, distance * i - 0.5f, 1.f });
                Verticies.insert(Verticies.end(), color, color + 4);
                Verticies.insert(Verticies.end(), { p2.x, p2.y, distance * i - 0.5f, 1.f });
                Verticies.insert(Verticies.end(), color, color + 4);
            }
            i++;
        }
        return Verticies;
    }

} // namespace OpenGLDrawer