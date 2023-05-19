#include "handler.hpp"
namespace OGLhandler
{

    /* #region private */
    void initGLFW(int width = 768, int height = 681, const char* title = "window")
    {
        glfwSetErrorCallback(errorCallback); // rejestracja funkcji zwrotnej do obslugi bledow

        if (!glfwInit()) // inicjacja biblioteki GLFW
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // inicjacja wersji kontekstu
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // incicjacja profilu rdzennego
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        window = glfwCreateWindow(width, height, title, NULL, NULL); // utworzenie okna i zwiazanego z nim kontekstu
        if (!window) {
            glfwTerminate(); // konczy dzialanie biblioteki GLFW
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(window, keyCallback); // rejestracja funkcji zwrotnej do oblsugi klawiatury

        glfwMakeContextCurrent(window);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
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

    /* #endregion */

    //******************************************************************************************
    GLuint shaderProgram; // identyfikator programu cieniowania

    GLuint vertexLoc; // lokalizacja atrybutu wierzcholka - wspolrzedne
    GLuint colorLoc; // lokalizacja atrybutu wierzcholka - kolor

    std::array<GLuint, 2> vao; // identyfikatory obiektow VAO
    std::array<GLuint, 3> buffers; // identyfikatory obiektow VBO

    GLFWwindow* window;
    //******************************************************************************************

    void initEngine(int width, int height)
    {
        initGLFW();
        initGLEW();
        initGL();
    }

    void draw()
    {

        // glowna petla programu
        while (!glfwWindowShouldClose(window)) {
            renderScene();

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
        glDeleteBuffers((GLsizei)buffers.size(), buffers.data()); // usuniecie VBO
        glDeleteVertexArrays((GLsizei)vao.size(), vao.data()); // usuiecie VAO
        glDeleteProgram(shaderProgram); // usuniecie programu cieniowania
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

        setupBuffers();
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
    ** funkcja inicjujaca VAO oraz zawarte w nim VBO z danymi o modelu
    **------------------------------------------------------------------------------------------*/
    void setupBuffers()
    {
        glGenVertexArrays((GLsizei)vao.size(), vao.data()); // generowanie identyfikatora VAO
        glGenBuffers((GLsizei)buffers.size(), buffers.data()); // generowanie identyfikatorow VBO

#pragma region trojkat
        // wspolrzedne wierzcholkow trojkata
        float positions[] = { 0.1f, 0.0f, 0.0f, 1.0f, 0.9f, -0.5f, 0.0f, 1.0f, 0.9f, 0.5f, 0.0f, 1.0f };

        // kolory wierzchokow trojkata*
        std::vector<float> colors { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };

        glBindVertexArray(vao[0]); // dowiazanie pierwszego VAO

        // VBO dla wspolrzednych wierzcholkow
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(vertexLoc); // wlaczenie tablicy atrybutu wierzcholka - wspolrzedne
        glVertexAttribPointer(
          vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, 0); // zdefiniowanie danych tablicy atrybutu wierzchoka - wspolrzedne

        // VBO dla kolorow
        glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
        glBufferData(
          GL_ARRAY_BUFFER, colors.size() * sizeof(float), reinterpret_cast<const void*>(colors.data()), GL_STATIC_DRAW);
        glEnableVertexAttribArray(colorLoc); // wlaczenie tablicy atrybutu wierzcholka - kolory
        glVertexAttribPointer(
          colorLoc, 4, GL_FLOAT, GL_FALSE, 0, 0); // zdefiniowanie danych tablicy atrybutu wierzcholka - kolory

#pragma endregion

#pragma region kwadrat
        // wspolrzedne i kolory kwadratu (x, y, z, w, r, g, b, a)

        float positionsAndColors[]
          = { -0.9f, 0.4f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.9f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, -0.1f,
                0.4f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, -0.1f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };

        glBindVertexArray(vao[1]);
        // VBO dla wspolrzednych i kolorow
        glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positionsAndColors), positionsAndColors, GL_STATIC_DRAW);

        int stride = 8 * sizeof(float); // 8 = 4 wspolrzedne wierzchoka + 4 kanaly koloru
        glEnableVertexAttribArray(vertexLoc);
        glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, stride, 0); // wspolrzedne wierzcholkow
        glEnableVertexAttribArray(colorLoc);
        glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, stride,
          reinterpret_cast<const void*>(4 * sizeof(float))); // kolory wierzcholkow

#pragma endregion

        glBindVertexArray(0);
    }

    /*------------------------------------------------------------------------------------------
    ** funkcja rysujaca scene
    **------------------------------------------------------------------------------------------*/
    void renderScene()
    {

        glClear(GL_COLOR_BUFFER_BIT); // czyszczenie bufora koloru

        glUseProgram(shaderProgram); // wlaczenie programu cieniowania

        // wyrysowanie pierwszego VAO (trojkat)
        // drawVAO(GL_TRIANGLES, vao[0], 3);

        // wyrysowanie dugiego VAO (kwadrat)
        // drawVAO(GL_TRIANGLE_STRIP, vao[1], 4);
    }

} // namespace OGLhandler