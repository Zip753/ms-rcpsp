#ifndef MS_RCPSP_PROJECTREADER_H
#define MS_RCPSP_PROJECTREADER_H

#include <cstdio>

/**
 * I/O reader of Project.
 */
class ProjectReader {
 public:
  /** Reads project from source file. Initializes Project singleton. */
  static void read(FILE *stream);
};

#endif  // MS_RCPSP_PROJECTREADER_H
