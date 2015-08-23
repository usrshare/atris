cmake_minimum_required(VERSION 2.8)
project(atris)

set (CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=2 -Wno-override-init")

set_source_files_properties(tags PROPERTIES GENERATED true)

add_custom_target(tags
        COMMAND ctags -R .
	        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories (${CMAKE_SOURCE_DIR}/inc)
include_directories (${CMAKE_SOURCE_DIR}/.protos)

include (CheckFunctionExists)

CHECK_FUNCTION_EXISTS(vprintf HAVE_VPRINTF)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)


add_executable (atris
		ai.c
		atris.c
		button.c
		display.c
		event.c
		fastrand.c
		gamemenu.c
		grid.c
		highscore.c
		identity.c
		menu.c
		network.c
		piece.c
		sound.c
		xflame.c
	       )

#find_package(PkgConfig)
#pkg_check_modules(NCURSESW "ncursesw" REQUIRED)

include_directories(${NCURSESW_INCLUDE_DIRS})

#target_link_libraries(ltest ncursesw menu m)

install(TARGETS atris
	RUNTIME DESTINATION bin
	)

install(DIRECTORY graphics styles
	DESTINATION share/atris
	)
