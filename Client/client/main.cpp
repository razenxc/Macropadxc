#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Actions.h"
#include "Config.h"

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

// =====================================================
// Action names. Must match enum ActionType in Actions.h
const char* uiActionNames[] = { 
    "Anything (None)",      // 0
    "Media: Previous",      // 1
    "Media: Play/Pause",    // 2
    "Media: Next",          // 3
    "Volume: Up",           // 4
    "Volume: Down",         // 5
    "Volume: Mute",         // 6
    "Open Website (URI)",   // 7
    "Run Application"       // 8
};

int entryPoint()
{
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow(1, 1, "", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwHideWindow(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw("Unable to context to OpenGL");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiCond_Always);

        // ==== BEGIN =====
        ImGui::Begin("Ware Client");
        Config::loadConfig();
        
        if (ImGui::Button("Exit"))
        {
            break;
        }

        if (ImGui::Button("Force Config Load")) 
        {
            Config::loadConfig();
        }

        ImGui::Separator();

        const char* pages[] = { "Page 0", "Page 1", "Page 2", "Page 3", "Page 4", "Page 5", "Page 6", "Page 7", "Page 8", "Page 9" };
        static int currentPage = 0;
        ImGui::Combo("Layer / Page", &currentPage, pages, IM_ARRAYSIZE(pages));

        ImGui::Separator();

        for (int i = 1; i <= 8; i++)
        {
            std::string key = "P" + std::to_string(currentPage) + "F" + std::to_string(i);

            ImGui::PushID(key.c_str());
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Button F%d:", i);
            ImGui::SameLine();

            Action& action = Config::keyBindings[key];

            int currentType = (int)action.type;
            ImGui::SetNextItemWidth(200);
            
            if (ImGui::Combo("##type", &currentType, uiActionNames, IM_ARRAYSIZE(uiActionNames)))
            {
                action.type = (ActionType)currentType;
                Config::write({key, action});
            }

            if (action.type == CMD_OPEN_URL || action.type == CMD_RUN_APP)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(250);
                
                char buffer[256];
                strncpy_s(buffer, action.payload.c_str(), sizeof(buffer));
                buffer[sizeof(buffer)-1] = 0;

                if (ImGui::InputText("##pay", buffer, sizeof(buffer)))
                {
                    action.payload = std::string(buffer);
                    Config::write({key, action});
                }

                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(action.type == CMD_OPEN_URL ? "Example: https://youtube.com" : "Example: C:\\Windows\\notepad.exe");
            }

            ImGui::PopID();
        }

        ImGui::End();
        // ==== END =====

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}