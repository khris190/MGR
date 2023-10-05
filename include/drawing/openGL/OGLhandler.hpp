#include "objects/window.hpp"
class OGLhandler
{
public:
    static OGLhandler* getInstance();
    /**
     * Singletons should not be cloneable.
     */
    OGLhandler(OGLhandler& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const OGLhandler&) = delete;
    void initGL();
    ~OGLhandler();

protected:
    Window mainWindow;
    static OGLhandler* instance_;
    OGLhandler() {};
};