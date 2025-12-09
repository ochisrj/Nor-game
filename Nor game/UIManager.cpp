#include "UIManager.h"
#include "imgui.h"
#include "implot.h"
// Constructor 
UIManager::UIManager() {
    
}

void UIManager::DrawUI(ImGuiIO& io) {
    // 1. Menu Bar
    drawMenuBar();

    // view menu
    drawGameWindow();
    drawLayerWindow();
    drawAudioWindow();
    drawAnimationWindow();
    drawConsoleWindow();
    drawPerformaceWindow();

    // tool menu
    drawControlsWindow(io);
    drawtablewindow();
    drawTerminalWindow();
    drawsettingwindow();
    

    // Demo Window 
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }


}

void UIManager::drawMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("file")) {
            
            if (ImGui::MenuItem("Quit", "	ctrl + q"))
            {
                quitRequest = true;
            }
            ImGui::MenuItem("setting",nullptr,&setting_window);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("view")) {
            ImGui::MenuItem("game", nullptr, &game_window);
            ImGui::MenuItem("layer", nullptr, &layer_window);
            ImGui::MenuItem("audio", nullptr, &audio_window);
            ImGui::MenuItem("animation", nullptr, &animatio_window);
            ImGui::MenuItem("console", nullptr, &console_window);
            ImGui::MenuItem("performace", nullptr, &performace_window);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("tools")) {
            ImGui::MenuItem("ImGui Demo", nullptr, &show_demo_window);
            ImGui::MenuItem("triangle setting", nullptr, &control_window);
            ImGui::MenuItem("table", nullptr, &table_window);
            ImGui::MenuItem("Terminal", nullptr, &terminal_window);
            ImGui::EndMenu();
        }

        
        ImGui::EndMainMenuBar();
    }
}

void UIManager::drawGameWindow() {
    if (game_window) {
        if (ImGui::Begin("Game", &game_window)) {
           

        }
        ImGui::End();
    }
}

void UIManager::drawLayerWindow() {
    if (layer_window) {
        if (ImGui::Begin("Layer", &layer_window)) {
            ImGui::Text("settingdad test");
        }
        ImGui::End();
    }
}

void UIManager::drawAudioWindow() {
    if (audio_window) {
        if (ImGui::Begin("Audio", &audio_window)) {
            ImGui::Text("settdading test");
        }
        ImGui::End();
    }
}

void UIManager::drawAnimationWindow() {
    if (animatio_window) {
        if (ImGui::Begin("Animtion", &animatio_window)) {
            ImGui::Text("setting tdaest");
        }
        ImGui::End();
    }
}

void UIManager::drawConsoleWindow() {
    if (console_window) {
        if (ImGui::Begin("Console", &console_window)) {
            ImGui::Text("setdadting test");
        }
        ImGui::End();
    }
}

void UIManager::drawPerformaceWindow() {
    if (performace_window) {
        if (ImGui::Begin("Performace(FPS)", &performace_window)) {
            ImGui::Text("CPU");
        }

        float sample[100];
        for (int n = 0; n < 100; n++)
            sample[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
        ImGui::PlotLines("ms", sample, 100);
     
        float Gpugra[150];
        for (int n = 0; n < 150; n++)
            Gpugra[n] = sinf(n * 0.5f + ImGui::GetTime() * 1.5f);
        ImGui::PlotLines("cs", Gpugra, 150);
        ImGui::End();
    }
}



void UIManager::drawControlsWindow(ImGuiIO& io) {
                              
    if (control_window) {
        ImGui::SetNextWindowSize(ImVec2(350, 280), ImGuiCond_FirstUseEver);
        ImVec2 windowSize = ImGui::GetWindowSize();
        const float PADDING = 10.0f;
        const float MENU_BAR_HEIGHT = ImGui::GetFrameHeight();
        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x - windowSize.x - PADDING, MENU_BAR_HEIGHT + PADDING),
            ImGuiCond_Appearing
        );
        if (ImGui::Begin("Triangle Setting", &control_window)) {
            ImGui::Text("Triangle Properties:");
            ImGui::Text("Hello World i love GUNTRUM");
            ImGui::Checkbox("Draw Triangle", &drawTriangle);
            ImGui::SliderFloat("Triangle Size", &size, 0.0f, 10.0f);
            ImGui::ColorEdit4("Triangle Color", triangle_color);
            ImGui::SliderFloat("Rotation (Degree)", &rorate_angle, 0.0f, 360.0f, "%.1f deg");
            ImGui::Separator();
            ImGui::Text("Background Properties:");
            ImGui::ColorEdit4("Background Color", background_color);
        }
        ImGui::End();
    }
}

void UIManager::drawtablewindow() {
    if (table_window) {
        if (ImGui::Begin("table content", &table_window)) {
            if (ImGui::BeginTable("My Table", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Value");
                ImGui::TableSetupColumn("Status");

                ImGui::TableHeadersRow();

                for (int i = 0; i < 5; ++i) {
                    ImGui::TableNextRow();
                    
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("Item %d");


                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("Active");
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();
    }
}

void UIManager::drawTerminalWindow() {
    if (terminal_window) {
        ImGui::SetNextWindowSize(ImVec2(800, 500), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Terminal/File Explorer", &terminal_window)) {

            // ใช้ Columns เพื่อแบ่งพื้นที่เหมือนในภาพ
            // คอลัมน์ที่ 1: รายการไฟล์ (File Tree)
            // คอลัมน์ที่ 2: เนื้อหา/รายละเอียด (Content)

            ImGui::Columns(2, "TerminalColumns", true); // 2 คอลัมน์, ปรับขนาดได้

            // --- คอลัมน์ที่ 1: File Tree ---
            ImGui::Text("home/fredrik/imgui");
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "docs/");

            // จำลอง Tree Node
            if (ImGui::TreeNodeEx("examples/", ImGuiTreeNodeFlags_DefaultOpen)) {
                // ใช้ Selectable เพื่อให้ดูเหมือนรายการที่คลิกได้
                if (ImGui::Selectable("misc/", false)) {}
                if (ImGui::Selectable("imgui_demo.cpp", false)) {}
                if (ImGui::Selectable("imgui_internal.h", false)) {}
                ImGui::TreePop();
            }

            ImGui::NextColumn(); // ย้ายไปคอลัมน์ถัดไป

            // --- คอลัมน์ที่ 2: Content View ---
            ImGui::Text("We carry the information to identify a \"texture\" in the ImTextureID type.");
            ImGui::Separator();

            // ใช้ Child Window เพื่อจำลองพื้นที่โค้ดที่มี Scrollbar
            if (ImGui::BeginChild("CodeView", ImVec2(0, 0), true)) {

                ImGui::TextDisabled("DirectX9:");
                ImGui::Text("0 - ImTextureID = LPDIRECT3DTEXTURE9");
                ImGui::Text("1 - See ImGui_ImplDX9_RenderData() function in imgui_impl_dx9.cpp");
                ImGui::Text("");
                ImGui::TextDisabled("DirectX11:");
                ImGui::Text("10 - ImTextureID = ID3D11ShaderResourceView*");
                ImGui::Text("11 - See ImGui_ImplDX11_RenderData() function in imgui_impl_dx11.cpp");

                // ถ้าคุณต้องการให้โค้ดมีสีสวยงามเหมือนในภาพ ต้องใช้ไลบรารี Syntax Highlighting ภายนอก 
                // หรือใช้ ImGui::TextColored สำหรับโค้ดที่ต้องการเน้น
            }
            ImGui::EndChild();

            ImGui::Columns(1); // กลับไปที่ 1 คอลัมน์
        }
        ImGui::End();
    }
}

void UIManager::drawsettingwindow() {
    if (setting_window) {
        if (ImGui::Begin("setting", &setting_window)) {
            ImGui::Text("setting test");
        }
        ImGui::End();
    }
}