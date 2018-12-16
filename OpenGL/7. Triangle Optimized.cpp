#include <iostream>
#include <sstream>
#define GLEW_STATIC
#include "GL/glew.h" // Anadimos glew antes ya que GLFW usa algunas librerias de OpenGL que se llaman aqui
#include "GLFW/glfw3.h"


using namespace std;

const char *APP_TITTLE = "Introduccion a OpenGL";
const int gWindowWidth = 1366;
const int gWindowHeight = 1024;
bool gfullscreen = false;
GLFWwindow *pWindow;

const GLchar* vertexShaderSrc =
"#version 330 core\n"
"layout (location=0) in vec3 pos;"
"void main()"
"{"
"	gl_Position = vec4(pos.x,pos.y,pos.z,1.0);"
"}"
;

const GLchar* fragmentShaderSrc =
"#version 330 core\n"
"out vec4 frag_color;"
"void main()"
"{"
"	frag_color = vec4(0.1f,0.9f,0.2f,1.0f);"
"}"
;

// Prototipos
void glfw_onKey(GLFWwindow* window,int key,int scancode,int action,int mode);
void showFPS(GLFWwindow*window);
bool inicializarOpenGL();
bool gWireFrame = false;

int main()
{
	if (!inicializarOpenGL())
	{
		cerr<< "OpenGL no pudo Inicializar" <<endl;
		return -1;
	}

	// Creamos un buffer en la GPU y le pasamos los vertices
	GLfloat vertices[] =
	{
		// Triangulo 1
		-0.5f,0.5f,0.0f, 
		 0.5f,0.5f,0.0f, 
		 0.5f,-0.5f,0.0f,
		 -0.5f,-0.5f,0.0f
	};

	GLuint indices[]={
		0,1,2,
		0,2,3
	};


	GLuint vbo,vao,ibo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); 

	
	/*
		GL_STATIC_DRAW = crear una vez y editar varias
		GL_DINAMIC_DRAW = usar varias veces
		GL_STREAM_DRAW = crear una vez cambiarlo una vez uso de una vez
	*/

	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	// Posicion
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1,&ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs,1,&vertexShaderSrc,NULL);
	glCompileShader(vs);

	GLint result;
	GLchar infoLog[512];
	glGetShaderiv(vs,GL_COMPILE_STATUS,&result);

	if (!result)
	{
		glGetShaderInfoLog(vs,sizeof(infoLog),NULL,infoLog);
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs,1,&fragmentShaderSrc,NULL);
	glCompileShader(fs);
	glGetShaderiv(fs,GL_COMPILE_STATUS,&result);

	if (!result)
	{
		glGetShaderInfoLog(fs,sizeof(infoLog),NULL,infoLog);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vs);
	glAttachShader(shaderProgram,fs);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&result);
	if (!result)
	{
		glGetShaderInfoLog(shaderProgram,sizeof(infoLog),NULL,infoLog);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	// Main Loop
	while (!glfwWindowShouldClose(pWindow))
	{
		showFPS(pWindow);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0); // 6 vertices
		glBindVertexArray(0);

		glfwSwapBuffers(pWindow);
	}

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vbo);


	glfwTerminate();

	return 0;
}

bool inicializarOpenGL()
{
	if(!glfwInit())
	{
		cerr<< "Inicializacion de GLFW Fallida"<<endl;
		return false;
	}

	// Definimos la version de OpenGL que usaremos
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

	 pWindow = NULL;

	if (gfullscreen)
	{
		GLFWmonitor *Monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode*pVmode = glfwGetVideoMode(Monitor);
		if (pVmode != NULL)
		{
			pWindow = glfwCreateWindow(pVmode->width,pVmode->height,APP_TITTLE,Monitor,NULL);
		}
	}
	else
	{
		pWindow = glfwCreateWindow(gWindowWidth,gWindowHeight,APP_TITTLE,NULL,NULL);
	}



	if (pWindow == NULL)
	{
		cerr<<"Error al crear ventana en GLFW"<<endl;
		return false;
	}

	glfwMakeContextCurrent(pWindow);

	glfwSetKeyCallback(pWindow,glfw_onKey);

	glewExperimental = GL_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		cerr<< "Inicializacion de GLEW Fallida!"<<endl;
		return false;
	}
	glClearColor(0.25f,0.38f,0.47f,1.0f);
	return true;

}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_SPACE && action==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,GL_TRUE);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		gWireFrame = !gWireFrame;
		if (gWireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
	}
}

void showFPS(GLFWwindow*window)
{
	static double tiempoPrevio = 0.0;
	static int conteoFrames = 0;
	double delta ;
	double tiempoActual = glfwGetTime();
	delta = tiempoActual - tiempoPrevio;
	if (delta > 0.25)
	{
		tiempoPrevio = tiempoActual;
		double fps = double(conteoFrames)/delta;
		double msPerFrame = 1000.0 / fps;

		ostringstream outs;
		outs.precision(2);
		outs<<fixed<<APP_TITTLE<<" FPS:"<<fps<<" Frame Time:"<<msPerFrame<<"(ms)";
		glfwSetWindowTitle(window,outs.str().c_str());
		conteoFrames=0;
	}
	conteoFrames++;
}
