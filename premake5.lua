workspace "DRMS"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

outputDir = "$(Configuration)-$(Platform)"
solutionDir = "$(SolutionDir)"
configurationMacro = "$(Configuration)"
platformMacro = "$(Platform)"
projectNameMacro = "$(ProjectName)"

---------- DRMS project description ----------
project "DRMS"
	location "DRMS"
	kind "ConsoleApp"
	language "C++"

	targetdir ("$(SolutionDir)bin/" .. outputDir .. "/DRMS")
	objdir ("$(SolutionDir)intDir/" .. outputDir .. "/$(ProjectName)")

	pchheader "drmsafx.h"
	pchsource "DRMS/src/drmsafx.cpp"

	files {
		"DRMS/**.txt",
		"DRMS/**.h",
		"DRMS/**.cpp",
		"DRMS/src/**.h",
		"DRMS/src/**.cpp",
		"DRMS/src/**.txt",
	}

	includedirs {
		"$(SolutionDir)DRMS/src",
	}

	libdirs {
	}

	links { 

	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DRMS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DRMS_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "DRMS_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "DRMS_DISTRIBUTION"
		optimize "On"