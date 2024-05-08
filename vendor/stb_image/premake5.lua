local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("stb_image")
kind("StaticLib")
language("C++")
cppdialect("C++17")
systemversion("latest")

targetdir("../../bin/" .. outputdir .. "/%{prj.name}")
objdir("../../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/**.h",
    "source/**.cpp",
})

includedirs({
    "include",
})

libdirs({})

links({})
