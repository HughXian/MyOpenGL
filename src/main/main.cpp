#include <iostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cmath>

void CB_FramebufferSize(GLFWwindow* window,int width, int height)
{
    if (window)
    {
        glViewport(0, 0, width, height);
        return;
    }
    std::cout << "[error]:window is nullptr" << std::endl;
}

void ProcessInput(GLFWwindow* window)
{
    //检查用户是否按下了 esc
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    std::cout << "test" << std::endl;

    //glfwInit 来初始化GLFW
    glfwInit();

    //version_major 叫做 主版本
    //version minor 叫做 次版本
    // 拿下面的来看就是 OpenGL 的 3.3版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //告诉GLFW使用的核心模式（Core-profile）
    //意味着 只能使用OpenGL功能的一个子集
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建一个窗口对象，存放了所有和窗口相关的数据，并且被GLFW的其他函数频繁地用到
    int windowWeight = 800;
    int windowHeight = 600;
    //std::string titleName = "这是OpenGL的窗口";
    std::string titleName = "中文";
    GLFWwindow* window = glfwCreateWindow(windowWeight, windowHeight, titleName.c_str(), nullptr, nullptr);
    if (!window)
    {
        std::cout << "[error]:failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //glad用来管理OpenGL的函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initalize glad" << std::endl;
        return -1;
    }

    //视口
    //视口是渲染窗口
    // 前两个参数控制左下角的位置
    glViewport(0, 0, windowWeight, windowHeight);

    glfwSetFramebufferSizeCallback(window, CB_FramebufferSize);

    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    float alpha = 0.0f;
    float time = 0.0f;
    //渲染循环
    //在我们每次循环的开始前检查一次GLFW是否被要求退出，
    // 如果是的话，该函数返回true，渲染循环将停止运行，之后我们就可以关闭应用程序。
    while (!glfwWindowShouldClose(window))
    {
        //检测用户输入
        ProcessInput(window);

        time = fmodf(time, 6.28319f);
        time += 0.02f;
        red = 0.5f * sinf(time) + 0.5f;
        green = 0.5f * sinf(time * 2.0f) + 0.5f;
        blue = 0.5f * sinf(time * 3.0f) + 0.5f;
        //渲染指令
        // 设置清空屏幕所用的颜色，当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被
        // 填充为 glClearColor里所设置的颜色
        glClearColor(red, green, blue, 1.0f);
        //glClear函数来清空 屏幕的颜色缓冲，接受一个缓冲位（Buffer Bit）来指定要清空的缓冲
        //可以有 颜色缓冲 GL_COLOR_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);

        //函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
        // 并调用对应的回调函数（可以通过回调方法手动设置）
        glfwSwapBuffers(window);

        //会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
        // 它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwPollEvents();

    }

    //当渲染循环结束后我们需要正确释放 / 删除之前的分配的所有资源。
    glfwTerminate();

    float vertices[] = 
    {
           -0.5f,    -0.5f,   0.0f,
            0.5f,    -0.5f,   0.0f,
            0.0f,     0.5f,   0.0f
    };

    //顶点缓冲对象是我们在OpenGL教程中第一个出现的OpenGL对象
    // 就像OpenGL中的其他对象一样，这个缓冲有一个独一无二的ID
    // 所以我们可以使用 glGenBuffers 函数生成一个带有缓冲ID的VBO对象
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // OpenGL有很多 缓冲对象类型，顶点缓冲对象的缓冲类型是 GL_ARRAY_BUFFER
    // OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型
    //　我们可以使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上：
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。
    // 然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
    // 它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
    // 第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
    // 第三个参数是我们希望发送的实际数据。
        //第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
        //• GL_STATIC_DRAW ：数据不会或几乎不会改变。
         //• GL_DYNAMIC_DRAW：数据会被改变很多。
        //• GL_STREAM_DRAW ：数据每次绘制时都会改变。
        //三角形的位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW。如果，比如说一个缓冲中的数据将频繁被改变，那么使用的类型就是GL_DYNAMIC_DRAW或GL_STREAM_DRAW，这样就能确保显卡把数据放在能够高速写入的内存部分。
        //现在我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理。下面我们会创建一个顶点着色器和片段着色器来真正处理这些数据


    // 暂时将顶点着色器的源代码硬编码在代码文件顶部的C风格字符串中
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // 为了能够让OpenGL使用它，我们必须在运行时动态编译它的源代码。

    //我们首先要做的是创建一个着色器对象，注意还是用ID来引用的。
    // 所以我们储存这个顶点着色器为unsigned int，然后用glCreateShader创建这个着色器

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 我们把需要创建的着色器类型以参数形式提供给glCreateShader。
    // 由于我们正在创建一个顶点着色器，传递的参数是GL_VERTEX_SHADER

    // 下一步我们把这个着色器源码附加到着色器对象上，然后编译它

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // glShaderSource函数把要编译的着色器对象作为第一个参数。
    // 第二参数指定了传递的源码字符串数量，这里只有一个。
    // 第三个参数是顶点着色器真正的源码，
    // 第四个参数我们先设置为NULL

    //你可能会希望检测在调用glCompileShader后编译是否成功了，
    // 如果没成功的话，你还会希望知道错误是什么，这样你才能修复它们。
    // 检测编译时错误可以通过以下代码来实现：

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //首先我们定义一个整型变量来表示是否成功编译，还定义了一个储存错误消息（如果有的话）的容器。
    // 然后我们用glGetShaderiv检查是否编译成功。
    // 如果编译失败，我们会用glGetShaderInfoLog获取错误消息，然后打印它

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //片段着色器
    //片段着色器(Fragment Shader)是第二个也是最后一个我们打算创建的用于渲染三角形的着色器。
    // 片段着色器所做的是计算像素最后的颜色输出

    return 0; 
}
