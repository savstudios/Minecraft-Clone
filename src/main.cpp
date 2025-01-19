#define STB_IMAGE_IMPLEMENTATION

// System files

#include <iostream>
#include <stdexcept>
#include <math.h>

// GLFW and GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom Headers

#include "headers/shader.h"
#include "stb_image.h"

// Custom Variables

float vertices[] = {
   //     Vertices     //     Colors     //      Textures       // 
   -0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // Top left
   -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f - (1.0f/16),  // Bottom left
    0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f + (1.0f/16), 1.0f,  // Top Right
    0.5f, -0.5f,  0.0f,  1.0f, 1.0f, 1.0f,  0.0f + (1.0f/16), 1.0f - (1.0f/16), // Bottom Right
};

unsigned int indices[] = {
   0, 1, 3, // Bottom left triangle
   0, 2, 3  // Bottom right triangle
};

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 600;

unsigned int VBO, VAO, EBO, shaderProgram;

// Declare Functions (this is so scope does not break)

void HandleInput(GLFWwindow* window);

// Custom Functions

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

   // Sets the new viewport size to the new scale of the window
   glViewport(0, 0, width, height);
}

void InitializeGL(){
   // Initialize GLFW (or basically openGL)

   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Hint GLFW on what major version we are on (Version 3)        3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Hint GLFW on what minor version we are on (Minor Version 3)  3
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Hint GLFW to use the core profile

}

GLFWwindow* CreateWindow(int width, int height, const char* title){
   // Create a window with our parameters given (width, height and the title)
   GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

   // Check if the window exists, if not, then print out that something's gone wrong
   if (!window){throw std::runtime_error("Failed to create a GLFW WINDOW!"); glfwTerminate(); }

   // Make our window the current context
   glfwMakeContextCurrent(window);

   // If the window is resized, this function will call
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // Check if GLAD has been loaded
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){throw std::runtime_error("Failed to initalize GLAD!"); }

   return window;
}

void Update(GLFWwindow* window){

   // Update logic will go here

   // Handles the input from the user's keyboard and mouse
   HandleInput(window);
}

void Render(Shader* shader){
   glClearColor(0.1f, 0.75f, 1.0f, 1.0f); // Set the color buffer to this color
   glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer

   glGenBuffers(1, &VBO); // Generate the VBO buffer
   glGenBuffers(1, &EBO); // Generate the EBO buffer
   glGenVertexArrays(1, &VAO); // Generate the vertex arrays

   glBindVertexArray(VAO); // Bind the VAO

   glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO buffer
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends the vertex data to the buffer's memory

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the EBO buffer
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Sends the element buffer data to the buffer's memory

   // Tells OpenGL how to interpret the vertex data
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // Tells OpenGL how to interpret the color data
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); 
   glEnableVertexAttribArray(1);

   // Tells OpenGL how to interpret the texture data
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); 
   glEnableVertexAttribArray(2);

   shader -> use(); // Use the shader program
   glBindVertexArray(VAO); // Bind the VAO
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw the triangles

   // Delete all the unused stuff so we don't cause memory leaks
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);

   // Uncomment the next line to draw in WIREFRAME mode
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

unsigned int LoadImage(const char* imgPath){

   stbi_set_flip_vertically_on_load(true);

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

   unsigned char* data = stbi_load(imgPath, &width, &height, &numberChannels, 0);

   if(data){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }

   stbi_image_free(data);

   return texture;
}

void HandleInput(GLFWwindow* window){
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){ glfwSetWindowShouldClose(window, true); }
   if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){ glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
   if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){ glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
}

void TerminateAll(){
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glDeleteProgram(shaderProgram);
   glfwTerminate();
}

// Main function

int WinMain(int argc, char** argv){

   // Main logic will go here

   InitializeGL();
   GLFWwindow* window = CreateWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "Minecraft Clone");
   Shader rectangleShader("src/assets/shaders/triangle.vert", "src/assets/shaders/triangle.frag");
   LoadImage("src/assets/images/texture-atlas.png");
   // LoadImage could be used again if you want multiple images at once

   // main loop:
   while (!glfwWindowShouldClose(window)){

      // Render loop

      Render(&rectangleShader);

      // Other
      glfwSwapBuffers(window); // Swap the front and back buffers
      glfwPollEvents(); // Tell OpenGL to handle the main events (resizing, closing, etc.)
      Update(window); // Run the update function
   }

   TerminateAll();
   return 0;
}