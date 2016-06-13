#ifndef PROJECTREADER_H
#define PROJECTREADER_H
#include <cstdio>

/**
 * Class that is used to read Project from file.
 */
class ProjectReader {
public:
    /**
     * Read project from source file.
     * Creates Project instance.
     */
    static void read(FILE* stream);
};

#endif // PROJECTREADER_H
