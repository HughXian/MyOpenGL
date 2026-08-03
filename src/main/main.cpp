#include <iostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void CB_FramebufferSize(GLFWwindow* window,int width, int height)
{
    if (window)
    {
        glViewport(0, 0, width, height);
        return;
    }
    std::cout << "[error]:window is nullptr" << std::endl;
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
    int windowWeight = 1600;
    int windowHeight = 800;
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


    //渲染循环
    //在我们每次循环的开始前检查一次GLFW是否被要求退出，
    // 如果是的话，该函数返回true，渲染循环将停止运行，之后我们就可以关闭应用程序。
    while (!glfwWindowShouldClose(window))
    {
        //函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
        // 并调用对应的回调函数（可以通过回调方法手动设置）
        glfwSwapBuffers(window);

        //会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
        // 它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwPollEvents();

    }

    //当渲染循环结束后我们需要正确释放 / 删除之前的分配的所有资源。
    glfwTerminate();

    return 0; 
}