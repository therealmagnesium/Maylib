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
	"../vendor/%{cfg.system}/glad/include",
})

libdirs({
	"../vendor/%{cfg.system}/glad/bin",
})

links({
	"glad",
	"SDL2",
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
