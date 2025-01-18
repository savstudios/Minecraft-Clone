#ifndef SHADER_H
#define SHADER_H

// System files

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Custom headers

#include <glad/glad.h>

// Shader Class

class Shader{
   public:
      unsigned int ID; // The id of the shader program

      Shader(const char* vertexShaderPath, const char* fragmentShaderPath){ // Creates a constructor that takes in the file location of the shaders
         // Make some variables to hold the code and the file path
         std::string vertexCode;
         std::string fragmentCode;
         std::ifstream vShaderFile;
         std::ifstream fShaderFile;

         // Make sure ifstream objects can throw exceptions
         vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
         fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

         try{

            // Open the shader path
            vShaderFile.open(vertexShaderPath);
            fShaderFile.open(fragmentShaderPath);

            // Create streams for both shaders
            std::stringstream vShaderStream, fShaderStream;

            // Read the buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Close both shader files
            vShaderFile.close();
            fShaderFile.close();

            // Convert both shader streams into strings
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
         }
         catch(std::ifstream::failure){
            std::cout << "ERROR::SHADER::FILE_NOT_SUCESSFULLY_READ" << std::endl;
         }

         // Create readable strings to the compiler
         const char* vShaderCode = vertexCode.c_str();
         const char* fShaderCode = fragmentCode.c_str();

         // Compile both shaders
         unsigned int vertex, fragment;

         vertex = compileShader(vShaderCode, 0); // Compile vertex shader
         fragment = compileShader(fShaderCode, 1); // Compile fragment shader

         ID = glCreateProgram(); // Create a shader program

         // Attach the vertex & fragment shader
         glAttachShader(ID, vertex);
         glAttachShader(ID, fragment);
         
         // Link the shader program
         glLinkProgram(ID);

         // Delete shaders as no longer needed
         glDeleteShader(vertex);
         glDeleteShader(fragment);
      }; 

      void use(){
         glUseProgram(ID); // Use the shader program
      }; 
      
      void setBool(const std::string &name, bool value) const{
         glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); // Change a bool value
      }; 
      void setInt(const std::string &name, int value) const{
         glUniform1i(glGetUniformLocation(ID, name.c_str()), value); // Change an int value
      }; 
      void setFloat(const std::string &name, float value) const{
         glUniform1f(glGetUniformLocation(ID, name.c_str()), value); // Change a float value
      }; 

   private:
      int compileShader(const char* code, unsigned int type){
         unsigned int shader;

         if(type == 0){ shader = glCreateShader(GL_VERTEX_SHADER); } // Set to 0 if a vertex shader
         else{ shader = glCreateShader(GL_FRAGMENT_SHADER); } // Set to 1 if a fragment shader
         glShaderSource(shader, 1, &code, NULL);
         glCompileShader(shader);   

         return shader;   
      }
};

#endif