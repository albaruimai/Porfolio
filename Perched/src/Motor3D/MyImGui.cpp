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

#include "MyImGui.hpp"

MyImGui::MyImGui() {
    wflags |= ImGuiWindowFlags_NoTitleBar;
    wflags |= ImGuiWindowFlags_NoBackground;
    wflags |= ImGuiWindowFlags_NoScrollbar;
    wflags |= ImGuiWindowFlags_NoMove;
    wflags |= ImGuiWindowFlags_NoResize;
    wflags |= ImGuiWindowFlags_NoCollapse;
    wflags |= ImGuiWindowFlags_NoScrollWithMouse;

    nwflags = wflags;
    nwflags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

MyImGui::~MyImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MyImGui::InitGuiWithContext(GLFWwindow& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io { ImGui::GetIO() }; (void)io;

    ImGui_ImplGlfw_InitForOpenGL(&window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void MyImGui::InitGui(GLFWwindow& window) {
    IMGUI_CHECKVERSION();
    
    ImGuiIO& io { ImGui::GetIO() }; (void)io;
}


void MyImGui::SetStyle(const std::string& style) {
    if (style == "Dark") {
        ImGui::StyleColorsDark();
    } else if (style == "Classic") {
        ImGui::StyleColorsClassic();
    } else if (style == "Light") { 
        ImGui::StyleColorsLight();
    }
}

bool MyImGui::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width { 0 };
    int image_height { 0 };
    unsigned char* image_data { stbi_load(filename, &image_width, &image_height, NULL, 4) };
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
    #if defined(GL_UNPACK_ROW_LENGTH) && !defined(EMSCRIPTEN)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    #endif
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

void MyImGui::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MyImGui::NewWindow(float xini, float yini, float xsize, float ysize, const std::string& titol, bool no) {
    const ImGuiViewport* mainview { ImGui::GetMainViewport() };

    ImGui::SetNextWindowPos(ImVec2(mainview->WorkPos.x + xini, mainview->WorkPos.y + yini));
    ImGui::SetNextWindowSize(ImVec2(xsize,ysize));

    if (no) {      
        ImGui::Begin(titol.c_str(), &p_open, nwflags);
    } else {
        ImGui::Begin(titol.c_str(), &p_open, wflags);
    }
}

bool MyImGui::CollapsingHeader(const std::string &tittle){
    return ImGui::CollapsingHeader(tittle.c_str());
}

void MyImGui::EndWindow() {
    ImGui::End();
}

void MyImGui::DeleteTexture(GLuint img_texture) {
    glDeleteTextures(1, &img_texture);
}

GLuint MyImGui::CreateImage(const std::string& path) {
    int img_w { 0 };
    int img_h { 0 };           

    GLuint img_texture { 0 };
    bool rt { LoadTextureFromFile(path.c_str(), &img_texture, &img_w, &img_h) };

    ImGui::Image((void*)(intptr_t)img_texture, ImVec2(img_w, img_h));      

    return img_texture;    
}

ButImagen MyImGui::CreateImageButton(const std::string& path, double x, double y) {
    const ImGuiViewport* mainview { ImGui::GetMainViewport() };

    int img_w { 0 };
    int img_h { 0 };
    GLuint img_texture { 0 };
    LoadTextureFromFile(path.c_str(), &img_texture, &img_w, &img_h);
    bool pulsado { ImGui::ImageButton((void*)(intptr_t)img_texture, ImVec2(img_w, img_h)) };

    return {mainview->WorkPos.x + x, mainview->WorkPos.y + y, mainview->WorkPos.x + x + img_w, mainview->WorkPos.y + y + img_h, img_texture, pulsado};
}

void MyImGui::CreateText(const std::string& texto) {
    ImGui::Text(texto.c_str());
    ImGui::SetWindowFontScale(2.0);
}

bool MyImGui::CreateCheckbox(const std::string& texto, bool activo) {
    ImGui::Checkbox(texto.c_str(), &activo);

    return activo;
}

float MyImGui::CreateSliderFloat(const std::string& texto, float vdefecto, float vmin, float vmax) {
    ImGui::SliderFloat(texto.c_str(), &vdefecto, vmin, vmax);

    return vdefecto;
}

int MyImGui::CreateSliderInt(const std::string& texto, int vdefecto, int vmin, int vmax) {
    ImGui::SliderInt(texto.c_str(), &vdefecto, vmin, vmax);

    return vdefecto;
}

int MyImGui::CreateRadioButtons(int v, const std::vector<std::string>& items) {
    for (size_t i {0}; i < static_cast<size_t>(items.size()); ++i) {
        ImGui::RadioButton(items.at(i).c_str(), &v, i);
    }
    
    return v;
}

int MyImGui::CreateCombo(const std::string& texto, int actual, const std::vector<std::string>& items) {
    const char* citems[items.size()];

    for (size_t i {0}; i < static_cast<size_t>(items.size()); ++i) {
        citems[i] = items.at(i).c_str();
    }

    ImGui::Combo(texto.c_str(), &actual, citems, IM_ARRAYSIZE(citems));

    return actual;
}

void MyImGui::Render(GLFWwindow& window) {
    ImVec4 clear_color {0.45f, 0.55f, 0.60f, 1.00f};

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(&window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(&window);
}