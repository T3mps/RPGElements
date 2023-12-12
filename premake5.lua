newaction {
    trigger     = "clean",
    description = "Cleans the project: removes bin and bin-int directories",
    execute     = function ()
        print("Removing build artifacts...")
        os.rmdir("./bin")
        os.rmdir("./bin-int")
        print("Clean complete.")
    end
}

workspace "RPGElements"
    architecture "x64"
    startproject "RPGElements"
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    IncludeDir = {}
    IncludeDir["RPGElements"] = "src"
    IncludeDir["entt"] = "Vendor/entt/"
    group "Dependencies"
    
    project "RPGElements"
        location "RPGElements"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. outputdir)
        objdir ("bin-int/" .. outputdir)

        files {
            "%{prj.location}/src/**.h",
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/src/**.hpp"
        }    

        includedirs {
            "%{IncludeDir.RPGElements}",
            "%{IncludeDir.entt}"
        }

        defines { "_CRT_SECURE_NO_WARNINGS" }

        filter "configurations:Debug"
            defines { "RPGELEMENTS_DEBUG" }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines { "RPGELEMENTS_RELEASE" }
            runtime "Release"
            optimize "on"