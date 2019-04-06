#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *,int,int);
void process_input(GLFWwindow*);

const char *vertexShaderCode =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0"
;

const char *fragmentShaderCode =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(ourColor,1.0f);\n"
    "}\n\0"
;


int main()
{
    //creando contexto
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //creacion de pantalla
    GLFWwindow *window = glfwCreateWindow(800,600,"Graficos",NULL,NULL);
    if(window==NULL)
    {
        std::cerr << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //cargando glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error in initcializar GLAD" << std::endl;
        return -1;
    }

    //para comprobar si compilo
    int sucess;
    char infoLog[512];

    //creando y compilando vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderCode,NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&sucess);
    if(!sucess)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cerr << "ERROR IN COMPILED VERTEX SHADER\n" << infoLog << std::endl;
    }
    
    //creando y compilando fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderCode,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&sucess);
    if(!sucess)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cerr << "ERROR IN COMPILED FRAGMENT SHADER:\n" << infoLog <<std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&sucess);
    if(!sucess)
    {
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cerr << "ERROR IN LINKING SHADERS\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //cordenadas del triangulo
    float VertexData[] =
    {
        //Position              //Color
        -0.5f ,-0.5f ,0.0f,    1.0f,0.0f,0.0f,
         0.5f ,-0.5f ,0.0f,    0.0f,1.0f,0.0f,
         0.0f , 0.5f ,0.0f,    0.0f,0.0f,1.0f
    };



    //buffer para pasar vertex data
    unsigned int VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexData),VertexData,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 *sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);    


    //game loop 
    while(!glfwWindowShouldClose(window))
    {
        //entrada
        process_input(window);

        //mostrar
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        //revisar y cambiar
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glfwTerminate();


}

//accion a realizar si se pulsa escape
void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}
//funcion para cambiar tamanio de pantalla
void framebuffer_size_callback(GLFWwindow *window,int widht,int height)
{
    glViewport(0,0,widht,height);
}


