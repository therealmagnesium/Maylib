#!/bin/bash

config="$1"
appName="Application"

if [[ $config = "run" ]]
then
    mode="$2"
    system="$3"

    if [[ $mode = "debug" ]]
    then
        cd "bin/Debug-$system/$appName"
        ./$appName
    elif [[ $mode = "release" ]]
    then
        cd "bin/Release-$system/$appName"
        ./$appName
    elif [[ $mode = "dist" ]]
    then
        cd "bin/Dist-$system/$appName"
        ./$appName
    fi
elif [[ $config = "assets" ]]
then
    mode="$2"
    system="$3"
    if [[ $mode = "debug" ]]
    then
        cp -r "App/assets/" "bin/Debug-$system/Application/"
    elif [[ $mode = "release" ]]
    then
        cp -r "App/assets/" "bin/Release-$system/Application/"
    elif [[ $mode = "dist" ]]
    then
        cp -r "App/assets/" "bin/Dist-$system/Application/"
    fi

elif [[ $config = "clean" ]]
then
    rm -rf bin build
	rm -rf vendor/glad/bin vendor/glad/build
	rm -rf vendor/stb_image/bin vendor/stb_image/build
    rm Makefile
    rm Base/Makefile
    rm App/Makefile
	rm vendor/glad/Makefile
	rm vendor/stb_image/Makefile
else
    system="$2"
    "./vendor/premake/$system/premake5" export-compile-commands
    "./vendor/premake/$system/premake5" gmake
    make all config=$config -j7
    cp "compile_commands/$config.json" "compile_commands.json"
fi
