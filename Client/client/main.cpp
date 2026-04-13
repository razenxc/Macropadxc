#include <chrono>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "actions.h"
#include "config.h"
#include "cl_utils.h"

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
    "Run Application",       // 8
    "Press Keys (Combo)"    // 9
};

int entryPoint()
{
    if (!glfwInit()) return -1;

    #ifdef _WIN32
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    #else
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    #endif

    window = glfwCreateWindow(800, 600, "Macropadxc", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw("Unable to context to OpenGL");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    #ifdef _WIN32
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    #endif

    io.ConfigViewportsNoAutoMerge = true;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    Config::loadConfig();

    auto lastCheckTime = std::chrono::steady_clock::now();
    bool isServiceRunning = true;
    std::string serviceExeName = "WareService.exe"; 

    #ifndef _WIN32
        serviceExeName = "WareService";
    #endif

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastCheckTime).count() >= 1)
        {
            isServiceRunning = isProcessRunning(serviceExeName);
            lastCheckTime = now;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiCond_Always);

        // ==== BEGIN =====
        bool isOpen = true;

        ImGui::Begin("Ware Client", &isOpen);

        if (!isOpen)
        {
            break;
        }

        if (ImGui::Button("Force Config Load")) 
        {
            Config::loadConfig();
        }

        ImGui::Separator();

        if (!isServiceRunning)
        {
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "Background service (%s) is not running!", serviceExeName.c_str());
            ImGui::TextDisabled("Key bindings are disabled. Please start the service to apply changes.");
            ImGui::Separator();
        }
        else
        {
            for (int i = 1; i <= 9; i++)
            {
                std::string key = "F" + std::to_string(i);

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

                if (action.type == CMD_OPEN_URL || action.type == CMD_RUN_APP || action.type == CMD_PRESS_KEYS)
                {
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(250);
                    
                    char buffer[256];
                    strncpy(buffer, action.payload.c_str(), sizeof(buffer));
                    buffer[sizeof(buffer)-1] = 0;

                    if (ImGui::InputText("##pay", buffer, sizeof(buffer)))
                    {
                        action.payload = std::string(buffer);
                        Config::write({key, action});
                    }

                    if (ImGui::IsItemHovered())
                    {
                        if (action.type == CMD_OPEN_URL) ImGui::SetTooltip("Example: https://youtube.com");
                        else if (action.type == CMD_RUN_APP) ImGui::SetTooltip("Example: notepad.exe");
                        else if (action.type == CMD_PRESS_KEYS) ImGui::SetTooltip("Example: CTRL+C or WIN+D");
                    }
                }
                ImGui::PopID();
            }
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