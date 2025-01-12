// System files

#include <iostream>
#include <stdexcept>

// GLFW and GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom Headers


// Custom Variables

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 600;

// Custom Functions (this is so scope does not break)

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

void Render(){
   glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Set the color buffer to this color
   glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer
}

void HandleInput(GLFWwindow* window){
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){ glfwSetWindowShouldClose(window, true); }
}

void TerminateAll(){
   glfwTerminate();
}

// Main function

int WinMain(int argc, char** argv){

   // Main logic will go here

   InitializeGL();
   GLFWwindow* window = CreateWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "Minecraft Clone");

   // main loop:
   while (!glfwWindowShouldClose(window)){

      // Render loop

      Render();

      // Other
      glfwSwapBuffers(window); // Swap the front and back buffers
      glfwPollEvents(); // Tell OpenGL to handle the main events (resizing, closing, etc.)
      Update(window); // Run the update function
   }

   TerminateAll();
   return 0;
}