#include "handler.hpp"
#include <stdexcept>
namespace OGLhandler
{

    /* #region private */
    void initGLFW(int width = 768, int height = 681, const char* title = "window")
    {
        glfwSetErrorCallback(errorCallback); // rejestracja funkcji zwrotnej do obslugi bledow

        if (!glfwInit()) // inicjacja biblioteki GLFW
            exit(EXIT_FAILURE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // inicjacja wersji kontekstu
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // incicjacja profilu rdzennego
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

        glfwWindowHint(GLFW_SAMPLES, 4);

        glfwWindowHint(GLFW_RED_BITS, 8); // 8 bits for red channel
        glfwWindowHint(GLFW_GREEN_BITS, 8); // 8 bits for green channel
        glfwWindowHint(GLFW_BLUE_BITS, 8); // 8 bits for blue channel
        glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits for alpha channel
        glfwWindowHint(GLFW_DEPTH_BITS, 24); // 24 bits for depth buffer
        glfwWindowHint(GLFW_STENCIL_BITS, 8); // 8 bits for stencil buffer
        glEnable(GL_MULTISAMPLE);
        window = glfwCreateWindow(width, height, title, NULL, NULL); // utworzenie okna i zwiazanego z nim kontekstu
        if (!window) {
            glfwTerminate(); // konczy dzialanie biblioteki GLFW
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(window, keyCallback); // rejestracja funkcji zwrotnej do oblsugi klawiatury

        glfwMakeContextCurrent(window);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            // GLEW initialization failed
            glfwTerminate();
            return;
        }
    }

    void initGLEW()
    {
        // inicjacja GLEW
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Blad: " << glewGetErrorString(err) << std::endl;
            exit(1);
        }

        if (!GLEW_VERSION_3_3) {
            std::cerr << "Brak obslugi OpenGL 3.3\n";
            exit(2);
        }

        glfwSwapInterval(0); // v-sync on
    }

    void initFramebuffer()
    {
        glGenFramebuffers(1, &fboID);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            throw std::runtime_error("chuj");
        }
    }

    /* #endregion */

    //******************************************************************************************
    GLuint shaderProgram; // identyfikator programu cieniowania

    GLuint vertexLoc; // lokalizacja atrybutu wierzcholka - wspolrzedne
    GLuint colorLoc; // lokalizacja atrybutu wierzcholka - kolor

    std::array<GLuint, 2> vao; // identyfikatory obiektow VAO
    std::array<GLuint, 3> buffers; // identyfikatory obiektow VBO
    int width;
    int height;
    GLFWwindow* window;
    GLuint fboID;
    GLuint textureID;
    GLuint depthrenderbuffer;
    GLenum DrawBuffers[1];
    //******************************************************************************************

    void initEngine(int width, int height)
    {
        OGLhandler::height = height;
        OGLhandler::width = width;
        initGLFW(width, height);
        initGLEW();
        initGL();
        // initFramebuffer();
    }

    void draw()
    {

        // glowna petla programu
        while (!glfwWindowShouldClose(window)) {
            prepareScene();

            glfwSwapBuffers(window); // zamieniamy bufory
            glfwPollEvents(); // przetwarzanie zdarzen
        }
    }

    void drawVAO(GLenum mode, GLuint Vao, size_t arraySize)
    {
        glBindVertexArray(Vao);
        glDrawArrays(mode, 0, arraySize);
    }

    /*------------------------------------------------------------------------------------------
    ** funkcja zwrotna do obslugi bledow biblioteki GLFW
    ** error - kod bledu
    ** description - opis bledu
    **------------------------------------------------------------------------------------------*/
    void errorCallback(int error, const char* description) { std::cerr << "Error: " << description << std::endl; }

    /*------------------------------------------------------------------------------------------
    ** funkcja zwrotna do obslugi klawiatury
    ** window - okno, kt�re otrzymalo zdarzenie
    ** key - klawisz jaki zostal nacisniety lub zwolniony
    ** scancode - scancode klawisza specyficzny dla systemu
    ** action - zachowanie klawisza (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
    ** mods - pole bitowe zawierajace informacje o nacisnietych modyfikatorach (GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
    *GLFW_MOD_ALT, GLFW_MOD_SUPER)
    **------------------------------------------------------------------------------------------*/
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    /*------------------------------------------------------------------------------------------
    ** funkcja wykonywana przed zamknieciem programu
    **------------------------------------------------------------------------------------------*/
    void cleanup()
    {
        glDeleteTextures(1, &textureID);
        glDeleteFramebuffers(1, &fboID);
        glDeleteBuffers((GLsizei)buffers.size(), buffers.data()); // usuniecie VBO
        glDeleteVertexArrays((GLsizei)vao.size(), vao.data()); // usuiecie VAO
        glDeleteProgram(shaderProgram); // usuniecie programu cieniowania

        glfwDestroyWindow(OGLhandler::window); // niszczy okno i jego kontekst
        glfwTerminate();
    }

    /*------------------------------------------------------------------------------------------
    ** funkcja inicjujaca ustawienia OpenGL
    **------------------------------------------------------------------------------------------*/
    void initGL()
    {
        std::cout << "GLEW = " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "GL_VENDOR = " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "GL_RENDERER = " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "GL_VERSION = " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL = " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // kolor (RGBA) uzywany do czyszczenia bufora koloru

        setupShaders();
    }

    /*------------------------------------------------------------------------------------------
    ** funkcja tworzaca program cieniowania skladajacy sie z shadera wierzcholkow i fragmentow
    **------------------------------------------------------------------------------------------*/
    void setupShaders()
    {
        if (!shaders::setupShaders("shaders/triangle.vert", "shaders/triangle.frag", shaderProgram))
            exit(3);

        vertexLoc = glGetAttribLocation(shaderProgram, "vPosition");
        colorLoc = glGetAttribLocation(shaderProgram, "vColor");
        glUseProgram(shaderProgram);
        // GLint glViewport = glGetUniformLocation(shaderProgram, "glViewport");
        // glUniform2f(glViewport, options::WIN_WIDTH, options::WIN_HEIGHT);
    }

    /*------------------------------------------------------------------------------------------
    ** funkcja rysujaca scene
    **------------------------------------------------------------------------------------------*/
    void prepareScene()
    {

        glClear(GL_COLOR_BUFFER_BIT); // czyszczenie bufora koloru

        glUseProgram(shaderProgram); // wlaczenie programu cieniowania

        // wyrysowanie pierwszego VAO (trojkat)
        // drawVAO(GL_TRIANGLES, vao[0], 3);

        // wyrysowanie dugiego VAO (kwadrat)
        // drawVAO(GL_TRIANGLE_STRIP, vao[1], 4);
    }

} // namespace OGLhandler