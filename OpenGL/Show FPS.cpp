#include<iostream>

#define GLEW_STATIC
#include <gl/glew.h>
#include <sstream>
#include <GLFW/glfw3.h>

const GLint ANCHO = 1280 , ALTO = 720;

void glfw_OnKey(GLFWwindow* ventana,int key,int scancode,int action,int mode)
{
	if (key == GLFW_KEY_ESCAPE && action==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(ventana,GL_TRUE);
	}
}

void mostrarFPS(GLFWwindow * ventana)
{
	static double segundosPrevios = 0.0;
	static int conteoFrames = 0;
	double segundosTranscurridos;
	double segundoActual = glfwGetTime();
	segundosTranscurridos = segundoActual - segundosPrevios;

	if(segundosTranscurridos>0.25)
	{
		segundosPrevios=segundoActual;
		double fps = (double)conteoFrames/segundosTranscurridos;
		double msPerFrame = 1000.0 / fps;
		std::ostringstream salida;
		salida.precision(3);
		salida << std::fixed<<"FPS: "<< fps <<" - Frame Time: "<<msPerFrame << "(ms)";
		glfwSetWindowTitle(ventana,salida.str().c_str());

		conteoFrames= 0;
	}
	conteoFrames++;
}

int main()
{
	 glfwInit();
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	 glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	 glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

	GLFWwindow* Ventana = glfwCreateWindow(ANCHO,ALTO,"Hello World!",nullptr,nullptr);
	int ScreenWidth,ScreenHeight;
	glfwGetFramebufferSize(Ventana,&ScreenWidth,&ScreenHeight);

	if (Ventana == nullptr)
	{
		std::cout<<"Error Creando la Ventana"<<std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(Ventana);

	glfwSetKeyCallback(Ventana,glfw_OnKey);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout<<"Error al Iniciar GLEW"<<std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0,0,ScreenWidth,ScreenHeight);

	// Ciclo Principal
	while(!glfwWindowShouldClose(Ventana))
	{
		
		mostrarFPS(Ventana);

		glfwPollEvents();

		glClearColor(0.2f,0.3f,0.3f,1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(Ventana);
	}
	 glfwTerminate();
	 return EXIT_SUCCESS;
}
