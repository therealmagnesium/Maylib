workspace("Maylib")
architecture("x64")

configurations({
	"Debug",
	"Release",
	"Dist",
})

include("vendor/glad")
include("vendor/stb_image")
include("Base")
include("App")
