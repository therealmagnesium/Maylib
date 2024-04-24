project("glad")
kind("StaticLib")
language("C++")
cppdialect("C++17")
systemversion("latest")

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
