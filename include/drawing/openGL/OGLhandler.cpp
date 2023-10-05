#include "OGLhandler.hpp"

OGLhandler* OGLhandler::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = new OGLhandler();
    }
    return instance_;
}
void OGLhandler::initGL() { }

OGLhandler::~OGLhandler() { }
