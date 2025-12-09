#pragma once

#include "imgui.h"
#include "implot.h"
#include "Triangle.h"
#include <filesystem>
#include <fstream>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace fs = std::filesystem;

class UIManager {
public:
    UIManager();
    void DrawUI(ImGuiIO& io); // UI


    // Getters  main.cpp and Shader
    bool shouldDrawTriangle() const { 
        return drawTriangle; 
    }
    bool isQuitRequest() const { 
        return quitRequest; 
    }
    float getSize() const { 
        return size; 
    }
    float getRotationRadian() const { 
        return rorate_angle * ((float)M_PI / 180.0f); 
    }
    const float* getTriangleColor() const {
        return triangle_color; 
    }
    const float* getBackgroundColor() const { 
        return background_color; 
    }

private:
    // file menu
    bool setting_window = false;

    // view menu
    bool game_window = false;
    bool layer_window = false;
    bool audio_window = false;
    bool animatio_window = false;
    bool console_window = false;
    bool performace_window = false;

    // tools menu
    bool show_demo_window = false;
    bool control_window = false;
    bool table_window = false;
    bool terminal_window = false;

    // control triangle window
    bool drawTriangle = true;
    float size = 1.0f;
    float triangle_color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
    float background_color[4] = { 0.07f, 0.13f, 0.17f, 1.0f };
    float rorate_angle = 0.0f;


    // checkbox test
    bool check_box = false;



    // Imgui function (maybe)
    bool opt_fullscreen = true;
    bool dockspace_open = true;
    bool quitRequest = false;
    bool graphmath = true;
    bool values = true;

    int num_points = 500;
    double x_min = -10.0, x_max = 10.0; 
        
    // view menu function
    void drawGameWindow();
    void drawLayerWindow();
    void drawAudioWindow();
    void drawAnimationWindow();
    void drawConsoleWindow();
    void drawPerformaceWindow();

    void drawTerminalWindow(); // terminal
    void drawControlsWindow(ImGuiIO& io); // Controls
    void drawMenuBar(); //  Menu Bar
    void drawtablewindow();
    void drawsettingwindow();
};
