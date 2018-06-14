#include<iostream>

#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

const GLint ANCHO = 800, ALTO = 600;

int main()
{
	 glfwInit();
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	 glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	 glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

	GLFWwindow *Ventana = glfwCreateWindow(ANCHO,ALTO,"Hello World!",nullptr,nullptr);
	int ScreenWidth,ScreenHeight;
	glfwGetFramebufferSize(Ventana,&ScreenWidth,&ScreenHeight);

	if (Ventana == nullptr)
	{
		std::cout<<"Error Creando la Ventana"<<std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(Ventana);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout<<"Error al Iniciar GLEW"<<std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0,0,ScreenWidth,ScreenHeight);

	while(!glfwWindowShouldClose(Ventana))
	{
		glfwPollEvents();

		glClearColor(0.2f,0.3f,0.3f,1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(Ventana);
	}
	 glfwTerminate();
	 return EXIT_SUCCESS;
}
