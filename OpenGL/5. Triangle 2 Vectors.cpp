#include <iostream>
#include <sstream>
#define GLEW_STATIC
#include "GL/glew.h" // Anadimos glew antes ya que GLFW usa algunas librerias de OpenGL que se llaman aqui
#include "GLFW/glfw3.h"


using namespace std;

const char *APP_TITTLE = "Introduccion a OpenGL";
const int gWindowWidth = 1024;
const int gWindowHeight = 720;
bool gfullscreen = false;
GLFWwindow *pWindow;

const GLchar* vertexShaderSrc =
"#version 330 core\n"
"layout (location=0) in vec3 pos;"
"layout (location=1) in vec3 color;"
"out vec3 vert_color;"
"void main()"
"{"
"	vert_color=color;"
"	gl_Position = vec4(pos.x,pos.y,pos.z,1.0);"
"}"
;

const GLchar* fragmentShaderSrc =
"#version 330 core\n"
"in vec3 vert_color;"
"out vec4 frag_color;"
"void main()"
"{"
"	frag_color = vec4(vert_color,1.0f);"
"}"
;

// Prototipos
void glfw_onKey(GLFWwindow* window,int key,int scancode,int action,int mode);
void showFPS(GLFWwindow*window);
bool inicializarOpenGL();

int main()
{
	if (!inicializarOpenGL())
	{
		cerr<< "OpenGL no pudo Inicializar" <<endl;
		return -1;
	}

	// Creamos un buffer en la GPU y le pasamos los vertices
	GLfloat vert_pos[] =
	{
		0.0f,0.5f,0.0f, // Top
		0.5f,-0.5f,0.0f, // Derecha
		-0.5f,-0.5f,0.0f // Izquierrda
	};

	GLfloat vert_color[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f
	};

	GLuint vbo,vbo2,vao;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vert_pos),vert_pos,GL_STATIC_DRAW); 

	glGenBuffers(1,&vbo2);
	glBindBuffer(GL_ARRAY_BUFFER,vbo2);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vert_color),vert_color,GL_STATIC_DRAW); 
	/*
		GL_STATIC_DRAW = crear una vez y editar varias
		GL_DINAMIC_DRAW = usar varias veces
		GL_STREAM_DRAW = crear una vez cambiarlo una vez uso de una vez
	*/

	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	// Posicion
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);

	// Color
	glBindBuffer(GL_ARRAY_BUFFER,vbo2);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(1);

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
		glDrawArrays(GL_TRIANGLES,0,3);
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
