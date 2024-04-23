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
    "../vendor/%{cfg.system}/glad/include",
})

libdirs({
    "../vendor/%{cfg.system}/glad/bin",
})

links({
    "Maylib-Base",
    "glad",
    "SDL2",
})

postbuildcommands({
    "cp -r assets/ %{cfg.buildtarget.directory}",
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
postbuildcommands({
    "cp ../vendor/windows/SDL2/SDL2.dll " .. "%{cfg.buildtarget.directory}",
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
