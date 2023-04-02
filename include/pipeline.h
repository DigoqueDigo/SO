#ifndef PIPELINE_H
#define PIPELINE_H

#include <utils.h>
#include <parser.h>
#include <package/package.h>


int execute_pipeline(char *line, int fifo[]);

#endif