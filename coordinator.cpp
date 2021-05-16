#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <iostream>
using namespace std;

#define MAX 10

//struct for command arguments
struct cli_struct {
    bool c, m;
    int i, j;
    char* datafile;
} args;


//function declarations
cli_struct parse_args(int argc,char* argv[]);

//main function
int main(int argc, char* argv[]) {

    args = parse_args(argc, argv);
    

    printf("args.c = %d, args.m = %d, args.i = %d, args.j = %d, args.datafile = %s\n", args.c, args.m, args.i, args.j, args.datafile);
    return 0;
}

//funciton definitions
//function to parse command line arguments
cli_struct parse_args(int argc,char* argv[]) {
    cli_struct cli_args;
    int option;
    cli_args.c = false;
    cli_args.m = false;
    cli_args.i = 0;
    cli_args.j = 20;

    while((option = getopt(argc, argv, "hc:m:")) != -1) {
        switch (option) {
        case 'h':
            printf("coordinator [-h] [-c i] [-m j] datafile\n\t-c: Indicate how many child processese should be launched in total.\n\t-m: Indicate the maximum number of children allowed to exist in the system at the same time. ");
            exit(0);
        
        case 'c':
            cli_args.c = true;
            cli_args.i = atoi(optarg);
            break;

        case 'm':
            cli_args.m = true;
            cli_args.j = atoi(optarg);
            break;

        case '?':
            printf("unknown option: %s\n", optarg);
            exit(-1);
        }
    }    

    for(; optind < argc; optind++) {
        cli_args.datafile = argv[optind];
    }

    return cli_args;
}