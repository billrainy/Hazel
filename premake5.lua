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
	location "Hazel"    --��Ŀ��������Ĵ��Ŀ¼
	kind "SharedLib"  --��Ŀ���ͣ���̬��(StaticLib)����̬��(SharedLib)������̨Ӧ��(ConsoleApp)������Ӧ��(WindowedApp)��
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")  --�ֱ�ָ�����Ŀ¼(targetdir)���м��ļ�Ŀ¼(objdir)
	objdir ("bin-int/"..outputdir.."/%{prj.name}")  

	files
	{
		"%{prj.name}/src/**.h", -- ָ����Ҫ�����Դ�ļ���ʹ��ͨ���ƥ��
		"%{prj.name}/src/**.cpp",  --the search of the files to be compiled startsat the same level as premake5.lua file locates 
	}

	includedirs  --expicitly specify the search paths for the header files, so that without needing a full path or relative paths from the current file to each included header in #include directives in my codebase.
	{   -- �����Ҫ�����ͷ�ļ�������·����������Ŀ�Զ����ͷ�ļ����ⲿ���е�ͷ�ļ�
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	-- ע�⣺spdlog���ṩ�����ֵ��ò��ԣ�a.header-only version; b.compiled version;
	-- ǰ������ʵ�ֶ���ͷ�ļ��У�������Ҫ�������Ӷ���Ķ����ƶ��󣬹��ڱ�����Ŀʱ��ֻ��Ҫ�������������ÿ��ͷ�ļ����ɣ�
	-- ��������Ҫ���Ƚ������Ϊ�������ļ�(�� .lib)��Ȼ����Ҫ��ʹ�øÿ����Ŀ�����������links�����links { "spdlog.lib" } -- ����Windows�µĿ���Ϊspdlog.libλ��ϵͳ��Ĭ�Ͽ�����·���У�����ͨ��������ʽ���绷���������Ѹ�֪������
	-- ����Ŀѡ���һ�ֵ��ò��ԣ���header-only

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
		staticruntime "On"  --�����ý�Ӱ��C/C++��׼����������ӣ�����Ӱ����Զ����'Hazel.dll'�����ӷ�ʽ
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