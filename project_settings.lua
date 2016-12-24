#!lua
proj_name = "Project"
project_dir = "./" .. proj_name .. "/"

-- A solution contains projects, and defines the available configurations
solution (proj_name)
   configurations { "Debug", "Release" }
   platforms { "native", "x64", "x32" }
   --startproject "iDK2_Test" -- Set this project as startup project
   location ( "./" ) -- Location of the solutions
         
    -- Project to test the library
    project (proj_name)
      kind "ConsoleApp"
      language "C++"
      location (project_dir)
      targetdir (project_dir .. "/bin/")
      
      includedirs { 
        project_dir .. "include", 
        project_dir .. "dependencies",
        project_dir .. "/dependencies/SFML/include"
      }
      
      libdirs {
        project_dir .. "/dependencies/SFML/lib", 
        project_dir .. "/dependencies/SFML/bin"
      }
      
      files{ group = "include", project_dir .. "/include/**.h" } -- include filter and get the files
      files{ group = "src", project_dir .. "/src/**.cc", "./Project/src/**.cpp" } -- src filter and get the files
      

      configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols", "ExtraWarnings"}
        links {
          "sfml-system-d",
          "sfml-window-d",
          "sfml-graphics-d",
          "sfml-audio-d",
          "sfml-network-d",
        }

      configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize", "ExtraWarnings" }
        links {
          "sfml-system",
          "sfml-window",
          "sfml-graphics",
          "sfml-audio",
          "sfml-network",
        }