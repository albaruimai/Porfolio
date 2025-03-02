//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

#include "../stb/stb_image.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include "Motor3DLUM/EntityLUM.hpp" // Will drag system OpenGL headers
#include <GL/glext.h>
#include <string>
#include <vector>

struct ButImagen {
    double xini {0}, yini {0}, xfin {0}, yfin {0};
    GLuint img_texture {0};
    bool pressed { false };
};

struct MyImGui
{
    MyImGui();
    ~MyImGui();

    void InitGuiWithContext(GLFWwindow& window);
    void InitGui(GLFWwindow& window);

    void SetStyle(const std::string& style);

    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

    void NewFrame();
    void NewWindow(float xini, float yini, float xsize, float ysize, const std::string& titol, bool no);
    void EndWindow();

    void DeleteTexture(GLuint img_texture);

    GLuint CreateImage(const std::string& path);
    ButImagen CreateImageButton(const std::string& path, double x, double y);

    void CreateText(const std::string& texto);

    bool CreateCheckbox(const std::string& texto, bool activo);
    float CreateSliderFloat(const std::string& texto, float vdefecto, float vmin, float vmax);
    int CreateSliderInt(const std::string& texto, int vdefecto, int vmin, int vmax);
    int CreateCombo(const std::string& texto, int actual, const std::vector<std::string>& items);
    int CreateRadioButtons(int v, const std::vector<std::string>& items);
    bool CollapsingHeader(const std::string&);

    bool IsClicked() { return ImGui::IsItemClicked(); };

    void InSameLine(float space) { ImGui::SameLine(space); };

    void Render(GLFWwindow& window);

    private:
        const char* glsl_version { "#version 420" };
        ImGuiWindowFlags wflags { 0 };
        ImGuiWindowFlags nwflags { 0 };
        bool p_open {false};
};