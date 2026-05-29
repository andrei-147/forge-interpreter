workspace "forge"
architecture "x86_64"
configurations { "debug", "release", "prod" }
platforms { "linux", "windows", "macos" }

project "forge-interpreter"
kind "ConsoleApp"
language "C++"
cppdialect "C++23"

targetdir "bin/%{cfg.buildcfg}-%{cfg.platform}"
objdir "bin/obj/%{cfg.buildcfg}-%{cfg.platform}"

files {
    "src/**.cpp",
    "include/**.h",
    "include/**.hpp",
}

includedirs {
    "include"
}

buildoptions { "-Wall", "-Wpedantic" }

filter "configurations:debug"
defines { "DEBUG" }
symbols "On"
optimize "Off"

filter "configurations:release"
defines { "NDEBUG", "RELEASE" }
symbols "Off"
optimize "On"

filter "configurations:prod"
defines { "NDEBUG", "PROD" }
symbols "Off"
optimize "Full"
linktimeoptimization "On"

filter "platforms:windows"
system "windows"
defines { "FORGE_PLATFORM_WINDOWS" }

filter "platforms:linux"
system "linux"
defines { "FORGE_PLATFORM_LINUX" }

filter "platforms:macos"
system "macosx"
defines { "FORGE_PLATFORM_MACOS" }

filter {}
