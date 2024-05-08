workspace("Maylib")
architecture("x64")

configurations({
    "Debug",
    "Release",
    "Dist",
})

include("vendor/stb_image")
include("vendor/glad")
include("Base")
include("App")
