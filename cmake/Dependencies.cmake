include(FetchContent)

find_package(OpenGL REQUIRED)

if(NOT glm_FOUND)
	FetchContent_Declare(
		glm
		GIT_REPOSITORY "https://github.com/g-truc/glm.git"
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
	)
	message(STATUS "Using glm via FetchContent")
	FetchContent_MakeAvailable(glm)
endif()

find_package(SDL3 CONFIG QUIET)
if(SDL3_FOUND)
    message(STATUS "Using SDL3 via find_package")
endif()
if(NOT SDL3_FOUND)
	FetchContent_Declare(
		SDL3
		GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
		GIT_TAG        "main"
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
	)
	message(STATUS "Using SDL3 via FetchContent")
	FetchContent_MakeAvailable(SDL3)
endif()

#find_package(STB QUIET)
#if(STB_FOUND)
#    message(STATUS "Using STB via find_package")
#endif()
#if(NOT STB_FOUND)
#	FetchContent_Declare(
#		STB
#		GIT_REPOSITORY "https://github.com/unrealsid/stb-cmake.git"
#		GIT_SHALLOW TRUE
#		GIT_PROGRESS TRUE
#	)
#	message(STATUS "Using STB via FetchContent")
#	FetchContent_MakeAvailable(STB)
#endif()

#find_package(TINYPLY QUIET)
#if(TINYPLY_FOUND)
#	message(STATUS "Using TinyPly via find_package")
#endif()
#if(NOT TINYPLY_FOUND)
#	FetchContent_Declare(
#			TINYPLY
#			GIT_REPOSITORY "https://github.com/unrealsid/tinyply-cmake.git"
#			GIT_SHALLOW TRUE
#			GIT_PROGRESS TRUE
#	)
#	message(STATUS "Using Tiny Ply via FetchContent")
#	FetchContent_MakeAvailable(TINYPLY)
#endif()

#imgui
#find_package(Imgui QUIET)
#if(Imgui_FOUND)
#	message(STATUS "Using ImgUI via find_package")
#endif()
#if(NOT Imgui_FOUND)
#	FetchContent_Declare(
#			Imgui
#			GIT_REPOSITORY "https://github.com/unrealsid/imgui-cmake.git"
#			GIT_SHALLOW TRUE
#			GIT_PROGRESS TRUE
#	)
#	message(STATUS "Using Imgui via FetchContent")
#	FetchContent_MakeAvailable(Imgui)
#endif()