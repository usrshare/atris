// vim: cin:sts=4:sw=4 
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/*
 *                               Tetromix
 *
 * The filesystem handling header file.
 *
 * Copyright 2000, Kiri Wagstaff & Westley Weimer
 * Copyright 2015, usr_share
 */

// the documentation on the C Prepocessor, and the copy I found at
// http://tigcc.ticalc.org/doc/cpp.html#SEC14
// in particular, says that defines starting with two underscores
// are reserved for the compiler / C library by the C standard.
// 
// Yet the developers of atris decided to name their header macros
// with these double underscores.

int home_filename(const char* filename, char* o_path, unsigned int o_path_sz);

#endif
