#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h" // Anadimos glew antes ya que GLFW usa algunas librerias de OpenGL que se llaman aqui
#include "GLFW/glfw3.h"


using namespace std;

const char *APP_TITTLE = "Introduccion a OpenGL";
const int gWindowWidth = 1024;
const int gWindowHeight = 720;

int main()
{
	if(!glfwInit())
	{
		cerr<< "Inicializacion de GLFW Fallida"<<endl;
		return -1;
	}

	// Definimos la version de OpenGL que usaremos
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

	GLFWwindow *pWindow = glfwCreateWindow(gWindowWidth,gWindowHeight,APP_TITTLE,NULL,NULL);
	
	if (pWindow == NULL)
	{
		cerr<<"Error al crear ventana en GLFW"<<endl;
		return -1;
	}

	glfwMakeContextCurrent(pWindow);

	glewExperimental = GL_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		cerr<< "Inicializacion de GLEW Fallida!"<<endl;
		return -1;
	}

	while (!glfwWindowShouldClose(pWindow))
	{
		glfwPollEvents();

		glClearColor(0.25f,0.38f,0.47f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pWindow);
	}


	glfwTerminate();

	return 0;
}
