#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h> 
#include<vector>


int main(int argc,char** argv){
    std::vector<pid_t> kids;

    int rgenToA1[2];
    int A1ToA2[2];

    if(pipe(rgenToA1)==-1){
        std::cerr<<"Error: in opening the pipe for rgenToA1"<<std::endl;
        return 1;
    }

    if(pipe(A1ToA2)==-1){
        std::cerr<<"Error: in opening the pipe for A1ToA2"<<std::endl;
        return 1;
    }

    //creating child to run rgen
    pid_t child1 = fork();
    if(child1==-1){
        std::cerr<<"Error: in creating child1 for rgen"<<std::endl;
        return 1;
    }

    if(child1==0){
        //making stdout of rgen point to write end of pipe rgentoA1
        dup2(rgenToA1[1],STDOUT_FILENO);
        close(rgenToA1[1]);
        close(rgenToA1[0]);
        close(A1ToA2[0]);
        close(A1ToA2[1]);

        execv("rgen",argv);
        std::cerr<<"Error: in executing rgen from driver program"<<std::endl;
        return 1;

    }
    kids.push_back(child1);


    //creating child to run A1
    pid_t child2 = fork();
    if(child2==-1){
        std::cerr<<"Error: in creating child2 for A1"<<std::endl;
        return 1;
    }

    if(child2==0){
        //take input from regen to a1
        dup2(rgenToA1[0],STDIN_FILENO);
        close(rgenToA1[0]);
        close(rgenToA1[1]);
        //send output from a1 to a2
        dup2(A1ToA2[1],STDOUT_FILENO);
        close(A1ToA2[0]);
        close(A1ToA2[1]);
        char* arg2[3];
        arg2[0]=(char*)"python3";
        arg2[1]=(char*)"ece650-a1.py";
        arg2[2]=nullptr;

        execvp("python3",arg2);
        std::cerr<<"Error: in executing A1 from driver program"<<std::endl;
        return 1;
    }
    kids.push_back(child2);

    //creating child to run A2
    pid_t child3 = fork();
    if(child3==-1){
        std::cerr<<"Error: in creating child3 for A2"<<std::endl;
        return 1;
    }

    if(child3==0){
        //take input from a1
        dup2(A1ToA2[0],STDIN_FILENO);
        close(A1ToA2[0]);
        close(A1ToA2[1]);
        close(rgenToA1[0]);
        close(rgenToA1[1]);

        char* arg3[2];
        arg3[0]=(char*)"ece650-a2";
        arg3[1]=nullptr;

        execv("ece650-a2",arg3);
        std::cerr<<"Error: in executing A2 from driver program"<<std::endl;
        return 1;
    }
    kids.push_back(child3);

    pid_t child4 = fork();
    if(child4==-1){
        std::cerr<<"Error: in creating child4 for reading user input"<<std::endl;
        return 1;

    }
    if(child4==0){

        dup2(A1ToA2[1],STDOUT_FILENO);
        close(A1ToA2[0]);
        close(A1ToA2[1]);
        close(rgenToA1[0]);
        close(rgenToA1[1]);

        while(!std::cin.eof()) {
            // read a line of input until EOL and store in a string
            std::string line;
            std::getline(std::cin, line);
            if (line.size() > 0)
            std::cout << line << std::endl;
        }
        return 0;

    }
    kids.push_back(child4);

    close(A1ToA2[0]);
    close(A1ToA2[1]);
    close(rgenToA1[0]);
    close(rgenToA1[1]);

    //wait for any one child to finish. ideally it should be either regen or child4 which takes input
    int flagWait;
    wait(&flagWait);    

    for(pid_t kid: kids){
        int status;
        kill(kid,SIGTERM);
        waitpid(kid,&status,0);
    }

}
