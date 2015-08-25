// vim: cin:sts=4:sw=4 
/*
 *                               Tetromix
 *
 * The filesystem handling file (locating the home directory).
 *
 * Copyright 2000, Kiri Wagstaff & Westley Weimer
 * Copyright 2015, usr_share
 */
#include "config.h"
#include "filesystem.h"

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* home_dir = NULL;

char* get_home_dir() {

#ifdef HAVE_SYS_STAT_H
        char* testhome = getenv("HOME"); //should work on both Linux and Windows IIRC.
	
	if (!testhome) return ""; //empty, but not null, string.

	char tetrodir[1024];
	int r = snprintf(tetrodir,1024,"%s/.tetromix/",testhome); //the tetromix subdirectory inside $HOME
	if (r+1 > 1024) { fprintf(stderr,"The home directory's location is so long, the tetromix subdir path takes more than 1024 bytes. Sorry. Also sorry for using fixed limits in 2015.\n"); exit(1);}

	r = mkdir(tetrodir,0755); //create the directory.
	if ((r != 0) && (errno != EEXIST)) {perror("Can't create ~/.tetromix/ :"); return "";} //can't create this directory.

	char* resdir = strdup(tetrodir); //this function will only be called once. so no worries about memory leaks.
	printf("Data dir identified as %s\n",resdir);
	return resdir;
#else
	return ""; //if we can't mkdir(), don't.
#endif
}

int home_filename(const char* filename, char* o_path, unsigned int o_path_sz) {

	if (!home_dir) home_dir = get_home_dir();

	int r = snprintf(o_path, o_path_sz, "%s%s", home_dir, filename); //if home_dir is empty, we'll use the current directory.
	if ((r<0) || ((unsigned int)r+1 > o_path_sz)) return 1; //if the resulting path is too long.
	return 0;
}
