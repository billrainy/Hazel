workspace "Hazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release", 
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
	location "Hazel"    --项目解决方案的存放目录
	kind "SharedLib"  --项目类型：静态库(StaticLib)、动态库(SharedLib)、控制台应用(ConsoleApp)、窗口应用(WindowedApp)等
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")  --分别指定输出目录(targetdir)和中间文件目录(objdir)
	objdir ("bin-int/"..outputdir.."/%{prj.name}")  

	files
	{
		"%{prj.name}/src/**.h", -- 指定需要编译的源文件，使用通配符匹配
		"%{prj.name}/src/**.cpp",  --the search of the files to be compiled startsat the same level as premake5.lua file locates 
	}

	includedirs  --expicitly specify the search paths for the header files, so that without needing a full path or relative paths from the current file to each included header in #include directives in my codebase.
	{   -- 添加需要引入的头文件的搜索路径，包括项目自定义的头文件与外部库中的头文件
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	-- 注意：spdlog库提供了两种调用策略：a.header-only version; b.compiled version;
	-- 前者所有实现都在头文件中，并不需要编译链接额外的二进制对象，故在编译项目时，只需要编译器搜索到该库的头文件即可；
	-- 后者则需要首先将库编译为二进制文件(如 .lib)，然后需要在使用该库的项目的配置中添加links命令，如links { "spdlog.lib" } -- 假设Windows下的库名为spdlog.lib位于系统的默认库搜索路径中，或者通过其他方式（如环境变量）已告知链接器
	-- 本项目选择第一种调用策略，即header-only

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"HZ_PLATFORM_WINDOWS";  -- defined macro
			"HZ_BUILD_DLL"		
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"  
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files  -- This pattern allows you to include all source files within a directory RECURSIVELY.
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp", 
	}

	--The includedirs command in a Premake Lua script is used to specify directories where header files are located.
	--These directories will be searched by the compiler when resolving #include directives.
	includedirs
	{
		"Hazel/src",
		"Hazel/vendor/spdlog/include"
	}

	links "Hazel"  -- It provides the executable of Sandbox proj with access to the output .dll files of Hazel proj.
	-- 'links' specifies the dependency between Sandbox proj on Hazel proj in terms of both statically and dynamically linking ways


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"  --该配置仅影响C/C++标准库组件的链接，而不影响对自定义库'Hazel.dll'的链接方式
		systemversion "latest"

		defines 
		{
			"HZ_PLATFORM_WINDOWS";
		}


	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"