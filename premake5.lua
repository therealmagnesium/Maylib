workspace("Maylib")
architecture("x64")

configurations({
	"Debug",
	"Release",
	"Dist",
})

include("vendor/glad")
include("Base")
include("App")
