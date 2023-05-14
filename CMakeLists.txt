cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SpaceGame")


add_executable (
	SpaceGame 
	"Source/main.cpp"
	"Source/System/SpriteSystem.cpp"
	"Source/System/PhysicsSystem.cpp"
	"Source/System/SpaceShipSystem.cpp"
)

target_include_directories (SpaceGame PRIVATE "Source/")

add_subdirectory ("External/entt")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_libraries (
		SpaceGame 
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-graphics-s-d.lib
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-network-s-d.lib 
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-audio-s-d.lib 
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-system-s-d.lib
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-window-s-d.lib
	)
else ()
	target_link_libraries (
		SpaceGame 
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-graphics-s.lib
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-network-s.lib 
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-audio-s.lib 
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-system-s.lib
		${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/sfml-window-s.lib
	)
endif ()

target_link_libraries (
	SpaceGame 
	opengl32.lib
	${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/freetype.lib
	winmm.lib
	gdi32.lib
	${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/vorbisenc.lib
	${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/vorbisfile.lib
	${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/vorbis.lib
	${CMAKE_SOURCE_DIR}/External/SFML-2.5.1/lib/ogg.lib
	ws2_32.lib
	EnTT::EnTT
)

target_include_directories (SpaceGame PRIVATE External/SFML-2.5.1/include)

target_compile_definitions (SpaceGame PRIVATE SFML_STATIC)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property (TARGET SpaceGame PROPERTY CXX_STANDARD 20)
endif()
