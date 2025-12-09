#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "imgui_internal.h" 

#include "Shader.h" 
// #include "Triangle.h"
#include "UIManager.h" 
#include "font.h"

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ** ต้องคงโค้ด GLSL ไว้ใน main.cpp เพื่อส่งให้ Constructor ของ Shader **
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"uniform float rotation;\n"
"void main()\n"
"{\n"
"    float cos_a = cos(rotation);\n"
"    float sin_a = sin(rotation);\n"
"    \n"
"    float newX = aPos.x * cos_a - aPos.y * sin_a;\n"
"    float newY = aPos.x * sin_a + aPos.y * cos_a;\n"
"    \n"
"    gl_Position = vec4(size * newX, size * newY, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"    FragColor = color;\n"
"}\n\0";



int main()
{
	// Initialize GLFW/GLAD (โค้ดเดิม)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1680, 1050, "ImGui + GLFW", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	int window_width, window_height;
	glfwGetFramebufferSize(window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);

	// Initialize ImGUI (โค้ดเดิม)
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImFontConfig font_cfg;
	font_cfg.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF(
		cascadiacode,
		cascadiacodesize,
		17.0f,
		&font_cfg,
		io.Fonts->GetGlyphRangesThai()
	);

	// ** 3. สร้าง Objects **
	Shader myShader(vertexShaderSource, fragmentShaderSource);
	// Triangle myTriangle;
	UIManager ui;


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		const float* bgColor = ui.getBackgroundColor();
		glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ui.isQuitRequest())
		{
			glfwSetWindowShouldClose(window, true);
		}

		ui.DrawUI(io);

		myShader.use();

		myShader.setFloat("size", ui.getSize());
		myShader.setFloat("rotation", ui.getRotationRadian());
		const float* tColor = ui.getTriangleColor();
		myShader.setVec4("color", tColor[0], tColor[1], tColor[2], tColor[3]);

		/*if (ui.shouldDrawTriangle())
			myTriangle.draw();
		*/

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 5. Cleanup (แก้ไขส่วนนี้)
	// ** ต้องเรียกใช้ ImGui_ImplGlfw_Shutdown(window) **
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown(); // ไม่ต้องใส่ 'window' ถ้าใช้ InitForOpenGL(window, true)
	ImGui::DestroyContext();
	ImPlot::DestroyContext();

	// GLFW Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
