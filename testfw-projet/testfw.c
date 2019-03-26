#define _GNU_SOURCE

#include "testfw.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#define INITIAL_CAPACITY 100  //capacité du tableau de tests

/* ********** STRUCTURES ********** */

struct testfw_t
{
    char *program;
    int timeout;
    char *logfile;
    char *cmd;
    bool silent;
    bool verbose;
    struct test_t** tab;//tableau de tests.
    unsigned int capacity; //capacity du tableau tab qui peut augmenter si besoin
    int size;// le nombre de tests actuellement enregistrés dans le tableau de tests
};
/*extraire une sous_chaine de caractere dans une chaine de caracteres
*src.Debut de la chaine à extraire :pos  et la taille est len.*/

char *substr(char *src,int pos,int len){
    char *dest=NULL;
    if (len>0) {
        dest = calloc(len+1, 1);
        if(NULL != dest) {
            strncat(dest,src+pos,len);
        }
    }
    return dest;
}
/* ********** FRAMEWORK ********** */

struct testfw_t *testfw_init(char *program, int timeout, char *logfile, char *cmd, bool silent, bool verbose)
{
    //allocation de la structure;
    struct testfw_t * fw=(  struct testfw_t*)malloc(sizeof( struct testfw_t));
    if (fw==NULL){
        fprintf(stderr," ERROR: ERROR:invalid pointer *fw free in the function testfw_init\n ");
        exit(EXIT_FAILURE);
    }

    else{
        //initialisation des champs de la structure
        fw->timeout = timeout;
        fw->logfile = logfile;
        //fw->logfile = access(fw->logfile,W_OK) == 0 ? strdup(logfile) : NULL;
        fw->silent = silent;
        fw->verbose = verbose;
        fw->cmd = cmd;
        //fw->cmd = cmd != NULL ? strdup(cmd) : NULL;
        fw->program = program;
        //fw->program = program != NULL ? strdup(program) : NULL;
        //allocation du tableau de test.
        fw->tab=(struct test_t**)malloc(INITIAL_CAPACITY*sizeof(struct test_t*));
        if(fw->tab==NULL){
            fprintf(stderr,"ERROR:Failure in the allocation of array tests in the function *testfw_init " );
            exit(EXIT_FAILURE);
        }
        fw->capacity = INITIAL_CAPACITY;
        fw->size = 0;
    }
    return fw;
}

void testfw_free(struct testfw_t *fw)
{
    if (fw==NULL){
        fprintf(stderr,"ERROR:invalid pointer *fw free in the function testfw_free ");
        exit(EXIT_FAILURE);
    }else{//liberer tous les champs dynamiquement alloués
        if(fw->tab!=NULL){
            for(int i=0;i<fw->size;i++){
                if(fw->tab[i]){
                    if(fw->tab[i]->name){
                        free(fw->tab[i]->name);
                    }
                    if(fw->tab[i]->suite){
                        free(fw->tab[i]->suite);
                    }
                    free(fw->tab[i]);
                }
            }
            free(fw->tab);
        }
        free(fw);
    }
}

int testfw_length(struct testfw_t *fw)
{
    if (fw==NULL){
        fprintf(stderr,"ERROR:invalid pointer *fw free in the function testfw_length");
        exit(EXIT_FAILURE);
    }
    return fw->size;
}

struct test_t *testfw_get(struct testfw_t *fw, int k)
{
    if (fw==NULL || fw->tab==NULL || fw->tab[k]==NULL || k<0 )
    {
        fprintf(stderr,"ERROR:invalid pointer or value in the function testfw_get\n ");
        exit(EXIT_FAILURE);
    }
    if (k>=fw->size)
    {
        fprintf(stderr,"ERROR:%d greater than the number of tests recorded\n ",k);
        exit(EXIT_FAILURE);
    }
    return fw->tab[k];
}

/* ********** REGISTER TEST ********** */

struct test_t *testfw_register_func(struct testfw_t *fw, char *suite, char *name, testfw_func_t func)
{
    if (fw==NULL)
    {
        fprintf(stderr," ERROR:invalid pointer fw in the function  testfw_register_func\n ");
        exit(EXIT_FAILURE);
    }
    //Reallouer  le tableau de tests  s'il n y  plus de place pour ajouter un nouveau test
    if(fw->size>=fw->capacity)
    {
        // On augmente la taille du tableau
        fw->capacity+=INITIAL_CAPACITY;
        fw->tab=(struct test_t**)realloc(fw->tab,fw->capacity*sizeof(struct test_t*));
        if(fw->tab==NULL)
        {
            fprintf(stderr, "ERROR:Failure to realloc in testfw_register_func\n");
            exit(EXIT_FAILURE);
        }
    }
    //allocation du test
    struct test_t* t=(struct test_t*)malloc(sizeof(struct test_t));
    if (t==NULL)
    {
        fprintf(stderr,"  struct test_t ");
        exit(EXIT_FAILURE);
    }
    int len_name=strlen(name);
    int len_suite=strlen(suite);
    //ici substr est utilisé pour allouer les variables name et  suite
    char*name1=substr(name,0,len_name);
    char*suite1=substr(suite,0,len_suite);
    t->suite=suite1;
    t->name=name1;
    t->func=func;
    fw->tab[fw->size]=t;
    fw->size+=1;
    return t;
}

struct test_t *testfw_register_symb(struct testfw_t *fw, char *suite, char *name)
{
    if (fw==NULL)
    {
        fprintf(stderr," ERROR:invalid pointer fw in the function  testfw_register_func\n ");
        exit(EXIT_FAILURE);
    }
    char *cmd;
    asprintf(&cmd,"%s_%s",suite,name);
    struct test_t * t;
    void *plugin = dlopen (NULL, RTLD_NOW);
    if (!plugin)
    {
        fprintf(stderr, " dlopen %s (%s)\n",dlerror(), fw->program);
        exit(EXIT_FAILURE);
    }
    testfw_func_t (func_pr);
    func_pr = dlsym(plugin,cmd);

    if(func_pr)
    {
        //enregistré le test
        t=testfw_register_func(fw, suite, name, func_pr);
    }
    else
    {
        fprintf(stderr, " dlsym %s\n",dlerror());
        dlclose(plugin);
        exit(EXIT_FAILURE);
    }
    free(cmd);
    dlclose(plugin);
    return t;
}

int testfw_register_suite(struct testfw_t *fw, char *suite)
{
    int compteur=0;//compteur du nombre de tests enregistrés
    if(fw==NULL)
    {
        fprintf(stderr," ERROR:invalid pointer fw in the function  testfw_register_suite\n");
        exit(EXIT_FAILURE);
    }
    char *cmd;
    asprintf(&cmd,"nm --defined-only %s | cut -d ' ' -f 3 | grep ^%s_ | cut -d '_' -f 2",fw->program,suite);
    FILE* file=popen(cmd,"r");
    if(file==NULL)
    {
        fprintf(stderr, "Failure to open with  **popen** in function test_register_suite \n" );
        exit(EXIT_FAILURE);
    }
    char chaine[INITIAL_CAPACITY];
    while (fgets(chaine,INITIAL_CAPACITY,file)!=NULL)   //lire chaque ligne
    {
        char *name=strtok(chaine,"\n"); //enlever le dernier caractere "\n" de la chaine lu
        struct test_t *t=testfw_register_symb(fw,suite,name);//enregistré la test
        if(t!=NULL)
            compteur+=1;
    }
    free(cmd);
    pclose(file);
    return compteur;
}

void signal_handler(int sig)
{
}

void run_test(struct testfw_t* fw,struct test_t* current_test, int argc, char* argv[], int fd)
{
    if (fw->cmd)
    {
        FILE* cmd_stream=popen(fw->cmd,"w");
        if (cmd_stream)
        {
            fd=fileno(cmd_stream);
        }
        dup2(fd,1);
        current_test->func(argc,argv);
        fclose(stdout);
        if (pclose(cmd_stream)!=0){
            exit(1);
        }
        exit(0);
    }
    dup2(fd,1);
    exit(current_test->func(argc,argv));
}

char* get_test_result(struct test_t* current_test, int return_value, int status,pid_t pid, double seconds_elasped, int* failed_tests_number)
{
    char* test_status = NULL;
    char* test_result = malloc(256*sizeof (char));
    if (return_value == -1)
    {
        kill(pid,SIGALRM);
        test_status = "TIMEOUT";
        status=124;
        (*failed_tests_number)++;
    }
    else
    {
        if (status == 0)
            test_status = "SUCCESS";
        else if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            test_status = "KILLED";
            (*failed_tests_number)++;
            snprintf(test_result,256,"[%s] run test \"%s.%s\" in %.2f ms (status \"%s\")\n",test_status,current_test->suite,current_test->name,seconds_elasped,strsignal(sig));
            return test_result;
        }
        else
        {
            test_status = "FAILURE";
            status=1;
            (*failed_tests_number)++;
        }
    }
    snprintf(test_result,256,"[%s] run test \"%s.%s\" in %.2f ms (status %d)\n",test_status,current_test->suite,current_test->name,seconds_elasped,status);
    return test_result;
}
jmp_buf buf;
void myack(int sig){
    siglongjmp(buf,sig);
}
int testfw_run_all(struct testfw_t *fw, int argc, char *argv[], enum testfw_mode_t mode)
{
    if (!fw)
    {
        exit(EXIT_FAILURE);
    }
    int failed_tests_number = 0;
    int fd=5;
    if (fw->logfile)
    {
        fd=open(fw->logfile,O_WRONLY|O_CREAT|O_TRUNC,0644);
        // dup2(fd,1); // Supprimé par A. Esnard à la demande de Nathan Lesne
        dup2(fd,2);
    }
    if (fw->silent)
    {
        close(1);
        close(2);
    }
    if (fw->timeout < 0)
    {
        fw->timeout = 0;
    }

    struct sigaction sa;
    sa.sa_handler = &signal_handler;
    sa.sa_flags = SA_RESETHAND;
    sigemptyset(&sa.sa_mask);

    switch (mode) {
    case TESTFW_FORKS:
    {
        struct timeval before,after;

        for (int i = 0; i < fw->size; i++)
        {

            struct test_t* current_test = testfw_get(fw,i);
            gettimeofday(&before, NULL);
            alarm(fw->timeout);
            pid_t pid = fork();

            if (pid == 0)
            {
                run_test(fw,current_test,argc,argv,fd);
            }
            sigaction(SIGALRM,&sa,NULL);
            int status;
            int return_value = wait(&status);
            gettimeofday(&after, NULL);
            alarm(0);
            double seconds_elasped = (after.tv_sec-before.tv_sec)*1000+(after.tv_usec-before.tv_usec)/(double)1000;
            char* test_result = get_test_result(current_test,return_value,status,pid,seconds_elasped,&failed_tests_number);
            printf("%s", test_result);
            free(test_result);
        }
        break;
    }
    case TESTFW_FORKP:
    {
        alarm(fw->timeout);
        for (int i = 0; i < fw->size; i++)
        {
            sigaction(SIGALRM,&sa,NULL);
            pid_t pid = fork();
            if (pid == 0)
            {
                struct timeval before,after;
                struct test_t* current_test = testfw_get(fw,i);
                gettimeofday(&before, NULL);
                pid_t fils = fork();

                if (fils == 0)
                {
                    run_test(fw,current_test,argc,argv,fd);
                }
                int status;
                int return_value = wait(&status);
                gettimeofday(&after, NULL);
                double seconds_elasped = (after.tv_sec-before.tv_sec)*1000+(after.tv_usec-before.tv_usec)/(double)1000;
                char* test_result = get_test_result(current_test,return_value,status,fils,seconds_elasped,&failed_tests_number);
                printf("%s", test_result);
                free(test_result);
            }
        }
        wait(NULL);
        alarm(0);
    }
    case TESTFW_NOFORK:
    {
        struct sigaction act;
        act.sa_handler = myack;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        struct timeval begin,end;
        for(int sig=0;sig<32;sig++){
            sigaction(sig,&act,NULL);
        }
        int out=dup(1);
        for(int i=0;i<fw->size;i++ ){
            dup2(fd,1);
            gettimeofday(&begin,NULL);
            char *test_result=NULL;
            alarm(fw->timeout);
            int ret=sigsetjmp(buf,1);
            if(ret==0){
                int ret_exit=fw->tab[i]->func(argc,argv);
                gettimeofday(&end,NULL);
                double seconds_elasped = (end.tv_sec-begin.tv_sec)*1000+(end.tv_usec-begin.tv_usec)/(double)1000;
                if(ret_exit==0){
                    test_result="SUCCESS";
                }else{
                    test_result="FAILURE";
                }

                dprintf(out,"[%s] run test \"%s.%s\" in %.2f ms (status %d)\n",test_result,fw->tab[i]->suite,fw->tab[i]->name,seconds_elasped,ret_exit);

            }else{
                gettimeofday(&end,NULL);
                failed_tests_number++;
                double seconds_elasped = (end.tv_sec-begin.tv_sec)*1000+(end.tv_usec-begin.tv_usec)/(double)1000;
                if(ret==14 && seconds_elasped >=fw->timeout*1000){
                    test_result="TIMEOUT";
                    dprintf(out,"[%s] run test \"%s.%s\" in %.2f ms (status %d)\n",test_result,fw->tab[i]->suite,fw->tab[i]->name,seconds_elasped,124);
                }else{
                    test_result="KILLED";
                    dprintf(out,"[%s] run test \"%s.%s\" in %.2f ms (status \"%s\")\n",test_result,fw->tab[i]->suite,fw->tab[i]->name,seconds_elasped,strsignal(ret));
                }


            }

        }
        break;
    }

    }

    return failed_tests_number;
}
