#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int entryPoint();

#ifdef _WIN32
    #include <windows.h>

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        return entryPoint();
    }
#else
    int main()
    {
        return entryPoint();
    }
#endif

GLFWwindow* window;

int entryPoint()
{
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    window = glfwCreateWindow(800, 600, "", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();


    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

        // ImGui::Begin("My First Tool", nullptr, ImGuiWindowFlags_MenuBar);
        // if (ImGui::BeginMenuBar())
        // {
        //     if (ImGui::BeginMenu("File"))
        //     {
        //         if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
        //         if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
        //         if (ImGui::MenuItem("Close", "Ctrl+W"))  {  }
        //         ImGui::EndMenu();
        //     }
        //     ImGui::EndMenuBar();
        // }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}