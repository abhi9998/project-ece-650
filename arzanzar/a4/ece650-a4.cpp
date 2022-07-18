// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <set>
#include <queue>
#include <algorithm>
// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

bool expectVCommand = true;
bool expectECommand = false;
//bool expectSCommand = false;
int vertexes = 0;


void callVertexCoverCheck(std::set<std::pair<int,int>>& edgeinput,int vertex){
            // -- allocate on the heap so that we can reset later if needed

            if(edgeinput.size()==0){
                std::cout<<std::endl;
                return;
            }

//            std::cout<<"here"<<std::endl;
            std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
            int minimum=0;
            Minisat::vec<Minisat::Lit> variables;


            for(int currk=1;currk<=vertex;currk++){
                
                int totalVar = currk*vertex;
                

                //preparingall the variables according to currk size
                for(int i=0;i<totalVar;i++){
                    Minisat::Lit l;
                    l = Minisat::mkLit(solver->newVar());
                    variables.push(l);
                }


                //this is for adding cnf with each k having at least one  vertex associated
                for(int i=0;i<currk;i++){
                    Minisat::vec<Minisat::Lit> clause1;
                    for(int k=0;k<vertex;k++){
                         clause1.push(variables[k*currk+i]);   
                    }
                    solver->addClause(clause1);
                }   

                
                //no one vertex should have two covers association    
                for(int i=0;i<vertex;i++){
                    for(int q=0;q<currk;q++){
                        for(int p=0;p<q;p++){
                           Minisat::vec<Minisat::Lit> clause2;
                           clause2.push(~variables[currk*i+p]);
                           clause2.push(~variables[currk*i+q]);
                           solver->addClause(clause2);     
                        }
                    }
                }

                //no one cover should be taken by two vertices
                for(int i=0;i<currk;i++){
                    for(int q=0;q<vertex;q++){
                        for(int p=0;p<q;p++){
                           Minisat::vec<Minisat::Lit> clause3;
                           clause3.push(~variables[currk*p+i]);
                           clause3.push(~variables[currk*q+i]);
                           solver->addClause(clause3);     
                        }
                    }
                }

                for (auto elem : edgeinput)
                {
                    int x = elem.first;
                    int y = elem.second;
                   
                    Minisat::vec<Minisat::Lit> clause4;
                    for(int i=0;i<currk;i++){
                        clause4.push(variables[(x-1)*currk+i]);
                        clause4.push(variables[(y-1)*currk+i]);
                    }
                    solver->addClause(clause4);  

                }    
                // auto val = solver->solve();
                // std::cout<<"Value of for "<<currk <<"is "<<val<<std::endl;
                if(solver->solve()){
                    minimum=currk;
                    break;
                }else{
                    solver.reset (new Minisat::Solver());
                    variables.clear();
                    minimum=0;
                }    

            }
           // std::cout<<"here2"<<minimum<<std::endl;
            std::vector<int> listofCovers;
            for(int i=0;i<vertex;i++){
                for(int j=0;j<minimum;j++){
                    if(solver->modelValue(variables[i*minimum+j])==Minisat::l_True){
                        listofCovers.push_back(i+1);
                    }
                }
            }
            std::sort(listofCovers.begin(), listofCovers.end());    

            for(int i=0;i<listofCovers.size()-1;i++){
                std::cout<<listofCovers.at(i)<<" ";
            }

            std::cout<<listofCovers.at(listofCovers.size()-1)<<std::endl;

}

void parseVCommand(std::string &cmdLine){

        //if(expectSCommand==true)
        // if(expectECommand==true)
        //     delete graph;

        expectECommand =false;
        //expectSCommand = false;

        std::string vCommandArg = cmdLine.substr(1,cmdLine.size()-1);
    
        //trim forward whitespace and ending space
        vCommandArg = std::regex_replace(vCommandArg, std::regex("^ +"), "");
        vCommandArg = std::regex_replace(vCommandArg, std::regex(" +$"), "");

        for(int i=0;i<vCommandArg.size();i++){
            if(vCommandArg.at(i)<'0'||vCommandArg.at(i)>'9')
                throw "not valid char in input";
        }


        try{
              int value = std::stoi(vCommandArg);  
              //std::cout<<value<<std::endl;

              if(value<=0)
                throw "argument is less than 1 in v command";

              vertexes  = value;
              expectECommand =true;
              //expectSCommand = false;
                
        }catch(...){
            throw "argument of V command not proper";
        }

}

void parseECommand(std::string &cmdLine){

        // if(expectSCommand==true)
        // delete graph;

        if(expectECommand==false){
            expectVCommand=true;
            expectECommand=false;
          //  expectSCommand=false;
            throw "V command is expected first";
        
        }


        std::string eCommandArg = cmdLine.substr(1,cmdLine.size()-1);

        //trim forward and ending whitespace
        eCommandArg = std::regex_replace(eCommandArg, std::regex("^ +"), "");
        eCommandArg = std::regex_replace(eCommandArg, std::regex(" +$"), "");

        for(int i=0;i<eCommandArg.size();i++){
            if(eCommandArg.at(i)=='<'|| eCommandArg.at(i)=='>'|| eCommandArg.at(i)=='{'||eCommandArg.at(i)=='}'||
            eCommandArg.at(i)==','||(eCommandArg.at(i)>='0'&& eCommandArg.at(i)<='9')||eCommandArg.at(i)==' ')
                continue;
            else
                throw "not proper characters in arguments of E";    
        }

        if(eCommandArg.find('{')==std::string::npos)
            throw "open curly not found";

        if(eCommandArg.find('}')==std::string::npos)    
            throw "close curly not found";

        int start = eCommandArg.find('{');
        int end = eCommandArg.find('}');
        
        if(start>end ||start!=0 ||end!=eCommandArg.size()-1)
            throw "curly bracket not properly inputted";

        
        std::set<std::pair<int,int>> edgeInput;

        bool openBracket=false;
        bool edgeSeparation=true;
        std::string contentInBracket= "";

        for(int i=start+1;i<end;i++){

            char c =eCommandArg.at(i);

            if(c=='<'){

                if(openBracket!=false ||edgeSeparation!=true)
                    throw "issue in open bracket input for E command";

                openBracket=true;    

            }else if(c=='>'){

                if(openBracket!=true)
                    throw "issue in close bracket input for E command";

                std::regex reg(",");

                std::sregex_token_iterator iter(contentInBracket.begin(), contentInBracket.end(), reg, -1);
                std::sregex_token_iterator end;

                std::vector<std::string> edgePoints(iter, end);

                //std::cout<<edgePoints.size()<<std::endl;   
                
                if(edgePoints.size()!=2)
                    throw "more than two points in edge input";

                edgePoints[0] = std::regex_replace(edgePoints[0], std::regex("^ +"), "");
                edgePoints[0] = std::regex_replace(edgePoints[0], std::regex(" +$"), "");

                edgePoints[1] = std::regex_replace(edgePoints[1], std::regex("^ +"), "");
                edgePoints[1] = std::regex_replace(edgePoints[1], std::regex(" +$"), "");

                for(int i=0;i<edgePoints[0].size();i++){
                    if(edgePoints[0].at(i)<'0'||edgePoints[0].at(i)>'9')
                        throw "Vertex in e command not given proper";
                }

                for(int i=0;i<edgePoints[1].size();i++){
                    if(edgePoints[1].at(i)<'0'||edgePoints[1].at(i)>'9')
                        throw "Vertex in e command not given proper";
                }    
                
                int x=0;
                int y=0;    

                try{
                 x = std::stoi(edgePoints[0]);
                 y = std::stoi(edgePoints[1]);
                }catch(...){
                    throw "parsing error in vertex in edge input";
                }

                if(x<1||x>vertexes||y<1||y>vertexes||x==y)
                    throw "value of V in E command is wrong";

                if(edgeInput.count(std::make_pair(x,y))||edgeInput.count(std::make_pair(y,x))){
                    throw "repetative edges in argument of E command";
                }

                edgeInput.insert(std::make_pair(x,y));    

                openBracket=false;
                edgeSeparation=false;
                contentInBracket="";

            }else if(c==','&& edgeSeparation==false){
                edgeSeparation=true;

            }else if(openBracket==true){
                   contentInBracket+=c; 

            }else if(c==' '&& openBracket==false){
                    continue;

            }else
                throw "improper content formatting in E argument";        
        }

        // graph = new Graph(vertexes);
        // graph->setEdges(edgeInput);
                
        expectECommand=false;
        //expectSCommand=true;
        
        callVertexCoverCheck(edgeInput,vertexes);

}

//void parseSCommand(std::string &cmdLine){
//    graph->printShortDistance(source,destination);        
//}

char parseCommandLine(std::string &cmdLine){

    if(cmdLine.find("V ")==0)
        return 'V';
    else if(cmdLine.find("E ")==0)
        return 'E';
    else if(cmdLine.find("s ")==0)
        return 's';
    else
        throw "input command not proper";    
}

int main(int argc, char** argv) {
 
    while (!std::cin.eof()) {
      
        
        try{
            std::string cmdLine;
            std::getline(std::cin, cmdLine);
            

            if(std::cin.fail()==1)
                break;

            //trim forward whitespace and ending space
            cmdLine = std::regex_replace(cmdLine, std::regex("^ +"), "");
            cmdLine = std::regex_replace(cmdLine, std::regex(" +$"), "");

            char order=parseCommandLine(cmdLine);

            if(order=='V')
                parseVCommand(cmdLine);
            else if(order=='E'){    
                parseECommand(cmdLine);
                
            }
            


        }catch(const char * exception){
            std::cout<<"Error: "<<exception<<std::endl;
        }
    

    }


}
