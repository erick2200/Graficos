#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *,int,int);
void process_input(GLFWwindow*);

const char *vertexShaderCode =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
    "}\0"
;

const char *fragmentShaderCode =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vertexColor;\n"
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
        -0.5f , 0.5f ,0.0f,     //izquierda arriba 0
        -0.5f ,-0.5f ,0.0f,     //izquierda abajo  1
         0.5f ,-0.5f ,0.0f,     //derecha abajo    2
         0.5f , 0.5f ,0.0f      //derecha arriba   3
    };

    unsigned int indices[] =
    {
        0,1,2,      //triangulo 1
        2,3,0       //triangulo 2
    };

    //buffer para pasar vertex data
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexData),VertexData,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 *sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //game loop 
    while(!glfwWindowShouldClose(window))
    {
        //entrada
        process_input(window);

        //mostrar
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        //revisar y cambiar
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
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


