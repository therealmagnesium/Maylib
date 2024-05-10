local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Maylib-Base")
kind("StaticLib")
language("C++")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
	"source/**.h",
	"source/**.cpp",
})

includedirs({
	"source",
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
	"glad",
	"stb_image",
	"assimp",
	"SDL2",
	"ImGui",
	"ImGui_SDL2_GL3",
})

filter("system:linux")
system("linux")
cppdialect("C++17")
systemversion("latest")
defines({
	"PLATFORM_LINUX",
})

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
