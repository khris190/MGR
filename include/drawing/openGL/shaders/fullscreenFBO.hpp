
#ifndef FULLSCREENFBO_HPP
#define FULLSCREENFBO_HPP

#include "AbstractShader.hpp"

namespace Shaders {
class fullscreenFBO : public AbstractShader {
public:
    fullscreenFBO(GLuint fboID);
    fullscreenFBO(fullscreenFBO&&) = default;
    fullscreenFBO(const fullscreenFBO&) = default;
    fullscreenFBO& operator=(fullscreenFBO&&) = default;
    fullscreenFBO& operator=(const fullscreenFBO&) = default;
    ~fullscreenFBO();
    void setShaderAttributes() override;
    int bindDataToBuffer(Genotype& genes) override;
};

} // namespace Shaders

#endif // FULLSCREENFBO_HPP
