
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "IShader.hpp"

namespace Shaders
{
    class Triangle : public IShader
    {
    public:
        GLuint vertexLoc; // lokalizacja atrybutu wierzcholka - wspolrzedne
        GLuint colorLoc; // lokalizacja atrybutu wierzcholka - kolor

        Triangle(const std::string& vertexShaderPath = "shaders/triangle/shader.vert",
          const std::string& fragmentShaderPath = "shaders/triangle/shader.frag");
        Triangle(Triangle&&) = default;
        Triangle(const Triangle&) = default;
        Triangle& operator=(Triangle&&) = default;
        Triangle& operator=(const Triangle&) = default;
        ~Triangle();
    };

} // namespace Shaders

#endif // TRIANGLE_HPP
