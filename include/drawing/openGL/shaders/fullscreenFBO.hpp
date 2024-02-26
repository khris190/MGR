
#ifndef FULLSCREENFBO_HPP
#define FULLSCREENFBO_HPP

#include "AbstractShader.hpp"

namespace shaders {
class FullscreenFBO : public AbstractShader {
public:
    explicit FullscreenFBO(GLuint fboID);
    FullscreenFBO(FullscreenFBO&&) = default;
    FullscreenFBO(const FullscreenFBO&) = default;
    FullscreenFBO& operator=(FullscreenFBO&&) = default;
    FullscreenFBO& operator=(const FullscreenFBO&) = default;
    ~FullscreenFBO() override;
    int bindDataToBuffer(Genotype& genes) override;

protected:
    void setShaderAttributes() override;
};

} // namespace shaders

#endif // FULLSCREENFBO_HPP
