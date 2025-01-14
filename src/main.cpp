// System files

#include <iostream>
#include <stdexcept>

// GLFW and GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom Headers


// Custom Variables

float vertices[] = {
   //     Vertices     //
   -0.5f,  0.5f,  0.0f,  // Top left
   -0.5f, -0.5f,  0.0f,  // Bottom left
    0.5f,  0.5f,  0.0f,  // Top Right
    0.5f, -0.5f,  0.0f,  // Bottom Right
};

unsigned int indices[] = {
   0, 1, 3, // Bottom left triangle
   0, 2, 3  // Bottom right triangle
};

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main(){\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 vertexColor;\n"
"void main()\n"
"{\n"
"FragColor = vertexColor;\n"
"}\n";

unsigned int VBO, VAO, EBO, shaderProgram;

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

   unsigned int vertexShader, fragmentShader; 
   vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create the vertex shader
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach the shader source code to the shader object
   glCompileShader(vertexShader); // Compile the shader into bits (00010101)

   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create the fragment shader
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach the shader source code to the shader object
   glCompileShader(fragmentShader); // Compile the shader into bits (00001001)

   shaderProgram = glCreateProgram(); // Create a shader program

   glAttachShader(shaderProgram, vertexShader); // Attach the vertex shader to the program
   glAttachShader(shaderProgram, fragmentShader); // Attach the fragment shader to the program
   glLinkProgram(shaderProgram); // Link the shader program

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Tells OpenGL how to interpret the vertex data
   glEnableVertexAttribArray(0);

   glDeleteShader(vertexShader); // Delete the vertex and fragment shader
   glDeleteShader(fragmentShader);

   glUseProgram(shaderProgram); // Use the shader program
   glBindVertexArray(VAO); // Bind the VAO
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw the triangles

   // Uncomment the next line to draw in WIREFRAME mode
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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