workspace "Simulator"
    architecture "x86"

    configurations {
        "Debug",
        "Release"
    }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Simulator"
    architecture "x86"

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
    }

    includedirs{
        "src/SFML/SFML-2.6.1/include",
    }

    libdirs {
        "src/SFML/SFML-2.6.1/lib"
    }

    defines {
        "SFML_STATIC",
    }

    filter "configurations:Debug"
        defines {
            "_DEBUG",
            "_WINDOWS"
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

        runtime "Debug"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        defines{
            "NDEBUG"
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

        runtime "Release"
        symbols "Off"
        optimize "On"
