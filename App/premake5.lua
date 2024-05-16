local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Application")
kind("ConsoleApp")
language("C++")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
	"source/**.h",
	"source/**.cpp",
})

includedirs({
	"../Base/source",
	"../vendor/glm",
	"../vendor/glad/include",
	"../vendor/stb_image/source",
	"../vendor/ImGui/include",
	"/mingw64/include",
})

libdirs({
	"../vendor/glad/bin",
	"../vendor/stb_image/bin",
	"../vendor/ImGui/lib/%{cfg.system}",
})

links({
	"Maylib-Base",
	"glad",
	"stb_image",
	"assimp",
	"ImGui",
	"ImGui_SDL2_GL3",
	"SDL2",
})

postbuildcommands({
	"cp -r assets/ %{cfg.buildtarget.directory}",
	"cp ../vendor/dlls/*.dll %{cfg.buildtarget.directory}",
})

filter("system:Unix")
system("linux")
cppdialect("C++17")
systemversion("latest")
defines({
	"PLATFORM_LINUX",
})

filter("system:Windows")
system("windows")
cppdialect("C++17")
systemversion("latest")
defines({
	"PLATFORM_WINDOWs",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")
