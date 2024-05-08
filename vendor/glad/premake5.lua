local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("glad")
kind("StaticLib")
language("C")
cdialect("C11")
systemversion("latest")

targetdir("../../bin/" .. outputdir .. "/%{prj.name}")
objdir("../../build/" .. outputdir .. "/%{prj.name}")

files({
	"include/**.h",
	"src/**.c",
})

includedirs({
	"include",
})

libdirs({})

links({})
