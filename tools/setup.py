#!/usr/bin/env python3
"""
项目设置脚本 - 跨平台版本
初始化 vcpkg 子模块，引导 vcpkg，并创建构建目录
"""

import os
import sys
import subprocess
import platform
from pathlib import Path

def run_command(command, cwd=None, shell=False):
    """运行命令并处理错误"""
    try:
        print(f"执行命令: {' '.join(command) if isinstance(command, list) else command}")
        result = subprocess.run(
            command, 
            cwd=cwd, 
            shell=shell, 
            check=True, 
            capture_output=True, 
            text=True
        )
        if result.stdout:
            print(result.stdout)
        return True
    except subprocess.CalledProcessError as e:
        print(f"命令执行失败: {e}")
        if e.stdout:
            print(f"标准输出: {e.stdout}")
        if e.stderr:
            print(f"错误输出: {e.stderr}")
        return False

def main():
    # 获取项目根目录
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    
    print("=" * 60)
    print("MyLargeProject 项目设置脚本")
    print("=" * 60)
    print(f"项目根目录: {project_root}")
    print(f"操作系统: {platform.system()}")
    print()
    
    # 切换到项目根目录
    os.chdir(project_root)
    
    # 步骤 1: 初始化子模块
    print("步骤 1: 初始化 git 子模块...")
    if not run_command(["git", "submodule", "update", "--init", "--recursive"]):
        print("❌ 子模块初始化失败")
        return False
    print("✅ 子模块初始化完成")
    print()
    
    # 步骤 2: 引导 vcpkg
    print("步骤 2: 引导 vcpkg...")
    vcpkg_dir = project_root / "vcpkg"
    
    if platform.system() == "Windows":
        bootstrap_script = vcpkg_dir / "bootstrap-vcpkg.bat"
        if not run_command([str(bootstrap_script)], cwd=vcpkg_dir, shell=True):
            print("❌ vcpkg 引导失败")
            return False
    else:
        bootstrap_script = vcpkg_dir / "bootstrap-vcpkg.sh"
        # 确保脚本可执行
        os.chmod(bootstrap_script, 0o755)
        if not run_command([str(bootstrap_script)], cwd=vcpkg_dir):
            print("❌ vcpkg 引导失败")
            return False
    
    print("✅ vcpkg 引导完成")
    print()
    
    # 步骤 3: 创建构建目录
    print("步骤 3: 创建构建目录...")
    build_dir = project_root / "build"
    
    if build_dir.exists():
        print(f"构建目录已存在: {build_dir}")
    else:
        build_dir.mkdir(parents=True, exist_ok=True)
        print(f"✅ 构建目录已创建: {build_dir}")
    print()
    
    # 步骤 4: 验证 vcpkg 可执行文件
    print("步骤 4: 验证 vcpkg 安装...")
    vcpkg_executable = vcpkg_dir / ("vcpkg.exe" if platform.system() == "Windows" else "vcpkg")
    
    if vcpkg_executable.exists():
        print(f"✅ vcpkg 可执行文件已找到: {vcpkg_executable}")
        
        # 显示 vcpkg 版本
        if run_command([str(vcpkg_executable), "version"], cwd=vcpkg_dir):
            pass
    else:
        print(f"❌ vcpkg 可执行文件未找到: {vcpkg_executable}")
        return False
    print()
    
    # 步骤 4.1: 安装 vcpkg 依赖
    print("步骤 4.1: 安装 vcpkg 依赖包...请耐心等待，执行时间较久")
    if not run_command([str(vcpkg_executable), "install"], cwd=vcpkg_dir):
        print("❌ vcpkg 依赖安装失败")
        return False
    print("✅ vcpkg 依赖安装完成")
    print()

    # 步骤 5: 显示下一步操作
    print("=" * 60)
    print("🎉 项目设置完成！")
    print("=" * 60)
    print("下一步操作:")
    print()
    
    if platform.system() == "Windows":
        print("1. 配置项目 (使用 Visual Studio):")
        print("   cmake --preset windows")
        print()
        print("2. 构建项目:")
        print("   cmake --build build --config Debug")
        print("   # 或者")
        print("   cmake --build build --config Release")
    else:
        print("1. 配置项目:")
        print("   cmake --preset linux")
        print()
        print("2. 构建项目:")
        print("   cmake --build build")
    
    print()
    print("3. 运行应用程序:")
    if platform.system() == "Windows":
        print("   .\\build\\Debug\\my_app.exe")
        print("   # 或者")
        print("   .\\build\\Release\\my_app.exe")
    else:
        print("   ./build/my_app")
    
    print()
    print("4. 运行测试:")
    if platform.system() == "Windows":
        print("   .\\build\\Debug\\my_app.exe --tests")
    else:
        print("   ./build/my_app --tests")
    
    return True

if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)
