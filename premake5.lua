workspace("Maylib")
architecture("x64")

configurations({
	"Debug",
	"Release",
	"Dist",
})

include("Base")
include("App")
