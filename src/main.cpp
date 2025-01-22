#define STB_IMAGE_IMPLEMENTATION

// System files

#include <iostream>
#include <stdexcept>
#include <math.h>

// GLFW and GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom Headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/shader.h"
#include "headers/texture-data.h"
#include "stb_image.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "ImGUI/imgui.h"

// Classes

// Custom Variables



float vertices[] = {
   //     Vertices     //   Textures   //

   // Back face
   -0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_LEFT[0], SIDE_GRASS_TEX_POS_BOTTOM_LEFT[1],
    0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[0], SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[1],
    0.5f,  0.5f, -0.5f,    SIDE_GRASS_TEX_POS_TOP_RIGHT[0], SIDE_GRASS_TEX_POS_TOP_RIGHT[1],
    0.5f,  0.5f, -0.5f,    SIDE_GRASS_TEX_POS_TOP_RIGHT[0], SIDE_GRASS_TEX_POS_TOP_RIGHT[1],
   -0.5f,  0.5f, -0.5f,    SIDE_GRASS_TEX_POS_TOP_LEFT[0], SIDE_GRASS_TEX_POS_TOP_LEFT[1],
   -0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_LEFT[0], SIDE_GRASS_TEX_POS_BOTTOM_LEFT[1],

   // Front Face
   -0.5f, -0.5f,  0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_LEFT[0], SIDE_GRASS_TEX_POS_BOTTOM_LEFT[1],
    0.5f, -0.5f,  0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[0], SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[1],
    0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_RIGHT[0], SIDE_GRASS_TEX_POS_TOP_RIGHT[1],
    0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_RIGHT[0], SIDE_GRASS_TEX_POS_TOP_RIGHT[1],
   -0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_LEFT[0], SIDE_GRASS_TEX_POS_TOP_LEFT[1],
   -0.5f, -0.5f,  0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_LEFT[0], SIDE_GRASS_TEX_POS_BOTTOM_LEFT[1],

   // Right Face
   -0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_LEFT[0], SIDE_GRASS_TEX_POS_TOP_LEFT[1],
   -0.5f,  0.5f, -0.5f,    SIDE_GRASS_TEX_POS_TOP_RIGHT[0], SIDE_GRASS_TEX_POS_TOP_RIGHT[1],
   -0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[0], SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[1],
   -0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[0], SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[1],
   -0.5f, -0.5f,  0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_LEFT[0], SIDE_GRASS_TEX_POS_BOTTOM_LEFT[1],
   -0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_LEFT[0], SIDE_GRASS_TEX_POS_TOP_LEFT[1],

   // Left Face
    0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_LEFT[0], SIDE_GRASS_TEX_POS_TOP_LEFT[1],
    0.5f,  0.5f, -0.5f,    SIDE_GRASS_TEX_POS_TOP_RIGHT[0], SIDE_GRASS_TEX_POS_TOP_RIGHT[1],
    0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[0], SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[1],
    0.5f, -0.5f, -0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[0], SIDE_GRASS_TEX_POS_BOTTOM_RIGHT[1],
    0.5f, -0.5f,  0.5f,    SIDE_GRASS_TEX_POS_BOTTOM_LEFT[0], SIDE_GRASS_TEX_POS_BOTTOM_LEFT[1],
    0.5f,  0.5f,  0.5f,    SIDE_GRASS_TEX_POS_TOP_LEFT[0], SIDE_GRASS_TEX_POS_TOP_LEFT[1],

   // Bottom Face
   -0.5f, -0.5f, -0.5f,    DIRT_TEX_POS_BOTTOM_LEFT[0], DIRT_TEX_POS_BOTTOM_LEFT[1],
    0.5f, -0.5f, -0.5f,    DIRT_TEX_POS_BOTTOM_RIGHT[0], DIRT_TEX_POS_BOTTOM_RIGHT[1],
    0.5f, -0.5f,  0.5f,    DIRT_TEX_POS_TOP_RIGHT[0], DIRT_TEX_POS_TOP_RIGHT[1],
    0.5f, -0.5f,  0.5f,    DIRT_TEX_POS_TOP_RIGHT[0], DIRT_TEX_POS_TOP_RIGHT[1],
   -0.5f, -0.5f,  0.5f,    DIRT_TEX_POS_TOP_LEFT[0], DIRT_TEX_POS_TOP_LEFT[1],
   -0.5f, -0.5f, -0.5f,    DIRT_TEX_POS_BOTTOM_LEFT[0], DIRT_TEX_POS_BOTTOM_LEFT[1],

   // Top Face
   -0.5f,  0.5f, -0.5f,    GRASS_TEX_POS_BOTTOM_LEFT[0], GRASS_TEX_POS_BOTTOM_LEFT[1],
    0.5f,  0.5f, -0.5f,    GRASS_TEX_POS_BOTTOM_RIGHT[0], GRASS_TEX_POS_BOTTOM_RIGHT[1],
    0.5f,  0.5f,  0.5f,    GRASS_TEX_POS_TOP_RIGHT[0], GRASS_TEX_POS_TOP_RIGHT[1],
    0.5f,  0.5f,  0.5f,    GRASS_TEX_POS_TOP_RIGHT[0], GRASS_TEX_POS_TOP_RIGHT[1],
   -0.5f,  0.5f,  0.5f,    GRASS_TEX_POS_TOP_LEFT[0], GRASS_TEX_POS_TOP_LEFT[1],
   -0.5f,  0.5f, -0.5f,    GRASS_TEX_POS_BOTTOM_LEFT[0], GRASS_TEX_POS_BOTTOM_LEFT[1],
};

unsigned int indices[] = {
    0, 1, 3, // Bottom left triangle
    0, 2, 3  // Bottom right triangle
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

unsigned int VBO, VAO, EBO, shaderProgram;

double prevTime, currentTime = 0.0;
double timeDifference;
unsigned int counter = 0;

bool firstMouse = true;

float FPS, ms, deltaTime, lastFrame, pitch;
float yaw = -90.0f, fov = 45.0f;
float lastX = SCREEN_WIDTH / 2, lastY = SCREEN_HEIGHT / 2;

// **CAMERA**

// Camera Vector
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); 
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Declare Functions (this is so scope does not break)

void HandleInput(GLFWwindow *window);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

// Custom Functions

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{

   // Sets the new viewport size to the new scale of the window
   glViewport(0, 0, width, height);
}

void InitializeGL()
{
   // Initialize GLFW (or basically openGL)

   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // Hint GLFW on what major version we are on (Version 3)        3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // Hint GLFW on what minor version we are on (Minor Version 3)  3
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Hint GLFW to use the core profile
}

GLFWwindow *CreateWindow(int width, int height, const char *title)
{
   // Create a window with our parameters given (width, height and the title)
   GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

   // Check if the window exists, if not, then print out that something's gone wrong
   if (!window)
   {
      throw std::runtime_error("Failed to create a GLFW WINDOW!");
      glfwTerminate();
   }

   // Make our window the current context
   glfwMakeContextCurrent(window);

   // If the window is resized, this function will call
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // Check if GLAD has been loaded
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      throw std::runtime_error("Failed to initalize GLAD!");
   }

   glEnable(GL_DEPTH_TEST);

   return window;
}

void Update(GLFWwindow *window)
{

   // Update logic will go here

   // Handles the input from the user's keyboard and mouse
   HandleInput(window);
}

void Render(Shader *shader)
{
   glClearColor(0.1f, 0.75f, 1.0f, 1.0f); // Set the color buffer to this color
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // Clear the buffer

   glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Make a vector about where the camera is looking at
   glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // Calculate the camera's direction
   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
   glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // Make a vector that points to the right of the camera

   glm::mat4 model = glm::mat4(1.0f); // Create a model matrix
   glm::mat4 view; // Create a view matrix
   glm::mat4 proj = glm::mat4(1.0f); // Create a projection matrix
   // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate the matrix
   proj = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

   const float radius = 10.0f;
   // Calculate the X and Z coords of the view matrix
   float camX = std::sin(glfwGetTime()) * radius; 
   float camZ = std::cos(glfwGetTime()) * radius;
   view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

   glGenBuffers(1, &VBO);      // Generate the VBO buffer
   glGenBuffers(1, &EBO);      // Generate the EBO buffer
   glGenVertexArrays(1, &VAO); // Generate the vertex arrays

   glBindVertexArray(VAO); // Bind the VAO

   glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        // Bind the VBO buffer
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends the vertex data to the buffer's memory

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);                                      // Bind the EBO buffer
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Sends the element buffer data to the buffer's memory

   // Tells OpenGL how to interpret the vertex data
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
   glEnableVertexAttribArray(0);

   // Tells OpenGL how to interpret the texture data
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
   glEnableVertexAttribArray(2);

   shader->use(); // Use the shader program

   // Send the model matrix to the shader
   unsigned int modelLocation = glGetUniformLocation(shader->ID, "model");
   glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
   // Send the view matrix to the shader
   unsigned int viewLocation = glGetUniformLocation(shader->ID, "view");
   glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
   // Send the projection matrix to the shader
   unsigned int projLocation = glGetUniformLocation(shader->ID, "proj");
   glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);

   glBindVertexArray(VAO); // Bind the VAO
   glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the triangles

   // Delete all the unused stuff so we don't cause memory leaks
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);

   // Uncomment the next line to draw in WIREFRAME mode
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void initGUI(GLFWwindow *window)
{
   // ImGUI initialization
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO &io = ImGui::GetIO();
   (void)io;
   ImGui::StyleColorsDark();
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330");
}

void drawGUI()
{
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();

   ImGui::Begin("Debug");
   ImGui::Text("Frames Per Second (FPS): %.2f", FPS);
   ImGui::Text("Time to render frame (ms): %.2f", ms);
   ImGui::End();

   ImGui::Render();
   ImGui::EndFrame();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

unsigned int LoadImage(const char *imgPath)
{

   stbi_set_flip_vertically_on_load(false);

   unsigned int texture;
   glGenTextures(1, &texture); // Generate texture
   // glTextureActive could be used if you want more than 1 texture
   glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture
   // Repeat bind and textureActive to bind 2 textures

   // Texture parameters

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   int width, height, numberChannels;

   unsigned char *data = stbi_load(imgPath, &width, &height, &numberChannels, 0);

   if (data)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }

   stbi_image_free(data);

   return texture;
}

void HandleInput(GLFWwindow *window)
{
   const float cameraSpeed = 2.5f * deltaTime;
   // Misc Keys
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){ glfwSetWindowShouldClose(window, true); }
   if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){ glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
   if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){ glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
   // Camera Control Keys
   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraSpeed * cameraFront; 
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraSpeed * cameraFront; 
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; 
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; 
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos){

   if(firstMouse){ lastX = xPos; lastY = yPos; firstMouse = false; };

   float xOffset = xPos - lastX;
   float yOffset = lastY - yPos;
   lastX = xPos;
   lastY = yPos;

   const float sens = 0.1f;
   xOffset *= sens;
   yOffset *= sens;

   yaw += xOffset;
   pitch += yOffset;

   // Check if we are not facing directly up
   if(pitch > 89.0f){ pitch = 89.0f; }
   if(pitch < -89.0f){ pitch = -89.0f; }

   glm::vec3 dir;
   // Calculate the direction axes
   dir.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
   dir.y = std::sin(glm::radians(pitch));
   dir.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

   // Normalise the direction
   cameraFront = glm::normalize(dir);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset){
   fov -= (float)yOffset;
   if(fov < 1.0f) fov = 1.0f;
   if(fov > 90.0f) fov = 90.0f;
}

void calculateFps()
{
   currentTime = glfwGetTime();
   timeDifference = currentTime - prevTime;
   counter++;
   if (timeDifference >= 1.0 / 30)
   {
      FPS = ((1.0 / timeDifference) * counter); // Calculate fps
      ms = ((timeDifference / counter) * 1000); // Calculate ms
      prevTime = currentTime;
      counter = 0;
   }
}

void calculateDeltaTime(){
   float currentFrame = glfwGetTime();
   deltaTime = currentFrame - lastFrame;
   lastFrame = currentFrame;
}

void TerminateAll()
{
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glDeleteProgram(shaderProgram);
   glfwTerminate();

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
}

// Main function

int WinMain(int argc, char **argv)
{

   // Variables

   // Main logic will go here

   InitializeGL();
   GLFWwindow *window = CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft Clone");
   Shader rectangleShader("src/assets/shaders/triangle.vert", "src/assets/shaders/triangle.frag");
   LoadImage("src/assets/images/texture-atlas.png");
   initGUI(window);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetCursorPosCallback(window, mouseCallback);
   glfwSetScrollCallback(window, scrollCallback);
   // LoadImage could be used again if you want multiple images at once

   // main loop:
   while (!glfwWindowShouldClose(window))
   {

      // Render loop
      calculateFps();
      calculateDeltaTime();
      Render(&rectangleShader);
      drawGUI();

      // Other
      glfwSwapBuffers(window); // Swap the front and back buffers
      glfwPollEvents();        // Tell OpenGL to handle the main events (resizing, closing, etc.)
      Update(window);          // Run the update function
   }

   TerminateAll();
   return 0;
}