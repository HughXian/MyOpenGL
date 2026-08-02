::<这是注释格式>

::关闭命令行默认【打印命令本身】
@echo off

::chcp 65001：把控制台编码设置为 UTF-8，防止中文乱码。
::>nul：屏蔽这条命令本身的输出信息，不要打印编码切换提示。
chcp 65001 >nul

::%~dp0 = 当前 bat 脚本所在文件夹完整路径
::定义变量SOURCE_ROOT为%~dp0
set "SOURCE_ROOT=%~dp0"
:: 移除路径末尾多余反斜杠，解决引号Bug
if "%SOURCE_ROOT:~-1%"=="\" set "SOURCE_ROOT=%SOURCE_ROOT:~0,-1%"

::vs的生成目录
set "BUILD_DIR=%SOURCE_ROOT%\build"

::CMake 生成器名称
set "GENERATOR_NAME=Visual Studio 17 2022"

::生成平台为x64
set "DEFAULT_PLATFORM=x64"

echo ========================================
echo 源码目录: %SOURCE_ROOT%
echo 构建目录: %BUILD_DIR%
echo 默认平台: %DEFAULT_PLATFORM%
echo ========================================

:: 删除旧build文件夹（可选，注释掉就不会清理）
::if exist "%BUILD_DIR%" (
::    echo [清理] 删除旧构建目录 build ...
::    rmdir /s /q "%BUILD_DIR%"
::)

:: 创建build目录
mkdir "%BUILD_DIR%"

echo.
echo [CMake] 开始生成解决方案...
cmake -G "%GENERATOR_NAME%" -A %DEFAULT_PLATFORM% -B "%BUILD_DIR%" -S "%SOURCE_ROOT%"

if %errorlevel% equ 0 (
    echo.
    echo 生成成功！
    echo 解决方案：%BUILD_DIR%\MyOpenGL.sln
) else (
    echo.
    echo CMake生成失败！
)
pause
