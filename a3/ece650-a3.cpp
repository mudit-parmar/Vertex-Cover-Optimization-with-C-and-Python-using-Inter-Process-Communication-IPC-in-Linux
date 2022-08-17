//https://git.uwaterloo.ca/ece650-f2021/cpp/-/blob/master/using_exec.cpp
//https://git.uwaterloo.ca/ece650-f2021/cpp/-/blob/master/using_pipe.cpp
#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <sys/wait.h>

int procCin(void) {

    while (!std::cin.eof()) {
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << std::endl;
    }
    return 0;
}


int main (int argc, char **argv) {
    int option,s,n,l,c;
    std::string s_string, n_string, l_string, c_string;
    while((option=getopt(argc,argv,"s:n:l:c:")) != -1){
        switch (option) {
            case 's':
                s_string=optarg;
                s = atoi(s_string.c_str());
		        if (s<2){
		            std::cerr<<"Error: Invalid Input \n";
		            exit(1);
		        }
		
                break;

            case 'n':
                n_string=optarg;
                n = atoi(n_string.c_str());
		        if (n<1){
		            std::cerr<<"Error: Invalid Input \n";
		            exit(1);
		        }

                break;
            case 'l':
                l_string=optarg;
                l = atoi(l_string.c_str());
		        if (l<5){
		            std::cerr<<"Error: Invalid Input \n";
		            exit(1);
		        }

                break;
            case 'c':
                c_string=optarg;
                c = atoi(c_string.c_str());
		        if (c<1){
		            std::cerr<<"Error: Invalid Input  \n";
		            exit(1);
		        }
                break;

        }
    }

    pid_t k1,k2,k3;

    int RgentoA1[2];
    int A1toA2[2];
    pipe(RgentoA1);
    pipe(A1toA2);
    pid_t child_pid;

    child_pid = fork();
    if(child_pid == 0)
    {
        
        dup2(RgentoA1[1], STDOUT_FILENO);
        close(RgentoA1[0]);
        close(RgentoA1[1]);

        int rgen = execv("rgen",argv);
        return rgen;
    }

    k1 = child_pid;
    
    child_pid = fork();
    if(child_pid == 0)
    {
        dup2(RgentoA1[0], STDIN_FILENO);
        close(RgentoA1[0]);
        close(RgentoA1[1]);

        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);

        char *argv1[3];

        argv1[0] = (char *)"python3";
        argv1[1] = (char *)"ece650-a1.py";
        argv1[2] = 0;

        return execvp("python3", argv1);
    }
    k2 = child_pid;

    child_pid = fork();
    if(child_pid == 0)
    {
        
        
       dup2(A1toA2[0], STDIN_FILENO);
       close(A1toA2[0]);
       close(A1toA2[1]);
  
        int a2 = execv("ece650-a2",argv);
        return a2;
    }
    k3 = child_pid;


        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[1]);
        int res = procCin();

        int status;
        kill(k1, SIGTERM);
        waitpid(k1, &status, 0);

        kill(k2, SIGTERM);
        waitpid(k2, &status, 0);

        kill(k3, SIGTERM);
        waitpid(k3, &status, 0);




return res;
    
}