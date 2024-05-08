project("stb_image")
kind("StaticLib")
language("C++")
cppdialect("C++17")
systemversion("latest")

targetdir("bin/")
objdir("build/")

files({
	"source/**.h",
	"source/**.cpp",
})

includedirs({
	"include",
})

libdirs({})

links({})
