#ifdef __unix__
// Copyright 2024 AQ author, All Rights Reserved.
// This program is licensed under the AQ License. You can find the AQ license in
// the root directory.

#include "aqvm/base/process/file_lock/unix/file_lock.h"

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include "aqvm/base/file/file.h"

int AqvmBaseProcessFileLockUnix_LockFile(struct AqvmBaseFile_File* file) {
  if (AqvmBaseFile_CheckStream(file) != 0) {
    // TODO
    return -1;
  }
  if (file->file == stdin || file->file == stdout || file->file == stderr) {
    // TODO
    return -2;
  }

  int file_descriptor = fileno(file->file);
  if (file_descriptor == -1) {
    return -3;
  }

  struct flock file_lock = {0};
  file_lock.l_type = F_WRLCK;
  file_lock.l_whence = SEEK_SET;

  

  if (fcntl(file_descriptor, F_SETLK, &file_lock) == -1) {
    printf("%i",errno);
    return -4;
  }
  return 0;
}

int AqvmBaseProcessFileLockUnix_UnlockFile(struct AqvmBaseFile_File* file) {
  if (AqvmBaseFile_CheckStream(file) != 0) {
    // TODO
    return -1;
  }
  if (file->file == stdin || file->file == stdout || file->file == stderr) {
    // TODO
    return -2;
  }

  int file_descriptor = fileno(file->file);
  if (file_descriptor == -1) {
    return -3;
  }

  struct flock file_lock = {0};
  file_lock.l_type = F_UNLCK;

  if (fcntl(file_descriptor, F_SETLK, &file_lock) == -1) {
    // TODO
    return -4;
  }
  return 0;
}

#endif