#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "testfw.h"

 volatile int length=0;

/* ********** STRUCTURES ********** */

struct testfw_t
{
  char *program;
  int timeout1;
  char *logfile;
  char *cmd;
   bool silent;
   bool verbose;
};

/* ********** FRAMEWORK ********** */

struct testfw_t *testfw_init(char *program, int timeout, char *logfile, char *cmd, bool silent, bool verbose)
{
  struct testfw_t * fw=(  struct testfw_t*)malloc(sizeof( struct testfw_t));
  if (fw==NULL){
    fprintf(stderr,"  struct testfw_t ");
    exit(EXIT_FAILURE);
  }else{
    fw->timeout1=timeout;
    fw->logfile=logfile;
    fw->silent=silent;
    fw->verbose=verbose;
    fw->cmd=cmd;
    fw->program=program;

  }
  return fw;
}

void testfw_free(struct testfw_t *fw)
{
  if(fw!=NULL){
    free(fw);
  }
}

int testfw_length(struct testfw_t *fw){
    return length;
}

struct test_t *testfw_get(struct testfw_t *fw, int k)
{
    return NULL;
}

/* ********** REGISTER TEST ********** */

struct test_t *testfw_register_func(struct testfw_t *fw, char *suite, char *name, testfw_func_t func)
{
  length+=1;
    return NULL;
}

struct test_t *testfw_register_symb(struct testfw_t *fw, char *suite, char *name)
{
    return NULL;
}

int testfw_register_suite(struct testfw_t *fw, char *suite)
{
    return 0;
}

/* ********** RUN TEST ********** */

int testfw_run_all(struct testfw_t *fw, int argc, char *argv[], enum testfw_mode_t mode)
{
    return 0;
}
