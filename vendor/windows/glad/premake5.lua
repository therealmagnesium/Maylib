local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

workspace("glad")
architecture("x64")

configurations({
	"Debug",
	"Release",
	"Dist",
})

project("glad")
kind("StaticLib")
language("C++")

targetdir("bin/")
objdir("build/")

files({
	"include/**.h",
	"src/**.c",
})

includedirs({
	"include",
})

libdirs({})

links({})

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
