cmake_minimum_required(VERSION 2.8)
project(atris)

set (CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=2 -Wno-override-init")

set_source_files_properties(tags PROPERTIES GENERATED true)

add_custom_target(tags
        COMMAND ctags -R .
	        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories (${CMAKE_SOURCE_DIR}/inc)
include_directories (${CMAKE_SOURCE_DIR}/.protos)

include (GNUInstallDirs)

include (CheckFunctionExists)

CHECK_FUNCTION_EXISTS(vprintf HAVE_VPRINTF)
CHECK_FUNCTION_EXISTS(select HAVE_SELECT)
CHECK_FUNCTION_EXISTS(strftime HAVE_STRFTIME)

include (CheckIncludeFiles)

CHECK_INCLUDE_FILES(dirent.h HAVE_DIRENT_H)
CHECK_INCLUDE_FILES(ndir.h HAVE_NDIR_H)
CHECK_INCLUDE_FILES(netdb.h HAVE_NETDB_H)
CHECK_INCLUDE_FILES(netinet/in.h HAVE_NETINET_IN_H)
CHECK_INCLUDE_FILES(winsock.h HAVE_WINSOCK_H)
CHECK_INCLUDE_FILES(sys/dir.h HAVE_SYS_DIR_H)
CHECK_INCLUDE_FILES(sys/ndir.h HAVE_SYS_NDIR_H)
CHECK_INCLUDE_FILES(sys/select.h HAVE_SYS_SELECT_H)
CHECK_INCLUDE_FILES(sys/socket.h HAVE_SYS_SOCKET_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)

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

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

target_link_libraries(atris ${SDL_LIBRARY} ${SDL_image_LIBRARY} ${SDL_TTF_LIBRARIES})

install(TARGETS atris
	RUNTIME DESTINATION bin
	)

install(DIRECTORY graphics styles
	DESTINATION share/atris
	)
