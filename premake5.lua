workspace "RAMRider"
    architecture "x64"
    configurations { "Debug", "Release", "Production" }
    platforms { "x64" }
    startproject "Crust"
    location "build"
    warnings "High"

    outputdir = "ramrider_%{cfg.buildcfg}_%{cfg.architecture}"

	flags { "MultiProcessorCompile", "ShadowedVariables" }
    
    fatalwarnings { "All" }
    ignoredefaultlibraries { "LIBCMTD", "LIBCMT" }

    filter "configurations:Debug"
        defines { "__DEBUG__" }
        symbols "On"

    filter "configurations:Production"
        defines { "__PROD__" }
        inlining "Auto"
        runtime "Release"
        floatingpoint "Fast"
        optimize "Speed"
        linktimeoptimization "On"

    filter "configurations:Release"
        floatingpoint "Fast"
        optimize "Speed"
        linktimeoptimization "On"

group "RAMRider"
    project "ramrider-cli"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"

        targetdir ("build/bin/" .. outputdir)
        objdir ("build/bin-int/" .. outputdir)

        files { "Sources/CLI/**.h", "Sources/CLI/**.hpp", "Sources/CLI/**.c", "Sources/CLI/**.cpp" }
        includedirs { "Sources/CLI", "Sources/RAMRider" }

        links { "ramrider" }

    project "ramrider"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"

        targetdir ("build/bin/" .. outputdir)
        objdir ("build/bin-int/" .. outputdir)

        files { "Sources/RAMRider/**.h", "Sources/RAMRider/**.hpp", "Sources/RAMRider/**.c", "Sources/RAMRider/**.cpp" }
        includedirs { "Sources/RAMRider" }

group "Dependencies"
    project "gtest"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        warnings "Off" -- not my problem lol

        targetdir ("build/bin/" .. outputdir)
        objdir ("build/bin-int/" .. outputdir)

        files { "Dependencies/googletest/googletest/src/**.cc", "Dependencies/googletest/googletest/include/**.h" }
        includedirs { "Dependencies/googletest/googletest/include", "Dependencies/googletest/googletest/"  }

        filter "configurations:Debug"
            symbols "On"

        filter "configurations:Release"
            optimize "On"