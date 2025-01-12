// System files

#include <iostream>

// GLFW and GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom Headers


// Custom Functions

void InitializeGL(){
   // Initialize GLFW (or basically openGL)
}

void Update(){

   // Update logic will go here

   std::cout << "Game updated!";
}

// Main function

int WinMain(int argc, char** argv){

   // Main logic will go here

   // while loop:
   Update();
   // end of while loop

   return 0;
}