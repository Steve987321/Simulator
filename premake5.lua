workspace "Simulator"
    filter "system:macosx"
        architecture "x86_64"
    filter "system:windows"
        architecture "x86"

    filter {}

    configurations {
        "Debug",
        "Release"
    }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Simulator"
    location "src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. output_dir .. "/")
    objdir ("bin-intermediate/" .. output_dir .. "/")

    files {
        "**.cpp",
        "**.h",
        "**.hpp",
        "vendor/imgui/**.cpp"
    }

    includedirs {
        "vendor",
        "vendor/SFML/SFML-2.6.1/include",
    }

    libdirs {
        "vendor/SFML/SFML-2.6.1/lib",
    }

    filter "system:macosx"
        links {
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework",
            "CoreVideo.framework",
            "sfml-system",
            "sfml-window",
            "sfml-graphics",
            "sfml-audio",
        }
    
    filter {"system:windows", "configurations:Debug"}
        defines {
            "SFML_STATIC",
            "_WINDOWS",
        }
    
        links {
            "opengl32",
            "winmm",
            "gdi32",
            "freetype",
            "flac",
            "ogg",
            "openal32",
            "vorbis",
            "vorbisenc",
            "vorbisfile",
            "sfml-system-s-d",
            "sfml-window-s-d",
            "sfml-graphics-s-d",
            "sfml-audio-s-d",
        }   

    filter {"system:windows", "configurations:Release"}
        defines {
            "SFML_STATIC",
            "_WINDOWS",
        }
    
        links {
            "opengl32",
            "winmm",
            "gdi32",
            "freetype",
            "flac",
            "ogg",
            "openal32",
            "vorbis",
            "vorbisenc",
            "vorbisfile",
            "sfml-system-s",
            "sfml-window-s",
            "sfml-graphics-s",
            "sfml-audio-s",
        }   

    filter "configurations:Debug"
        defines {
            "_DEBUG",
        }

        runtime "Debug"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        defines{
            "NDEBUG"
        }

        runtime "Release"
        symbols "Off"
        optimize "On"
