// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <set>
#include <queue>

bool expectVCommand = true;
bool expectECommand = false;
bool expectSCommand = false;
int vertexes = 0;

class Graph{

    private:
        std::vector<std::vector<int>> edge;
        int vertices;
      
    public:

        Graph(int vertices){
            this->vertices=vertices;
            edge = std::vector<std::vector<int>>(vertices+1);
        }

        void setEdges(std::set<std::pair<int,int>>& edgeinput){
            
            for(int i=1;i<edge.size();i++){
                edge[i] = std::vector<int>();
            }
            

            for (auto elem : edgeinput)
            {
                int x = elem.first;
                int y = elem.second;
                edge[x].push_back(y);
                edge[y].push_back(x);
            }

        }

        void printShortDistance(int source,int destination){

            if(source==destination){
                std::cout<<source<<std::endl;
                return;
            }

            std::vector<int> visited = std::vector<int>(vertices+1);            
            std::vector<int> parent = std::vector<int>(vertices+1);

            for(int i=0;i<vertices+1;i++){
                visited[i]=0;
                parent[i]=-1;
            }

            std::queue<int> que = std::queue<int>();
            visited[source]=1;
            que.push(source);

            while(!que.empty()){

                 int v = que.front();   
                 for(int i=0;i<edge[v].size();i++){
                     int adj = edge[v][i];
                     if(visited[adj]==0){
                         parent[adj]=v;
                         visited[adj]=1;
                         que.push(adj);
                     }
                 }
                 que.pop();
            }

            
            std::vector<int> path;
            int posi = destination;
            while(posi!=source){
                int par = parent[posi];
                if(par==-1 && posi!=source)
                    throw "No path exists between given points";

                path.push_back(posi);
                posi=par;    
            }

            path.push_back(source);

            for(int i=path.size()-1;i>=0;i--){
                std::cout<<path.at(i);
                if(i!=0)
                std::cout<<"-";
            }
            std::cout<<std::endl;
            
        }   

}; 

Graph *graph;

void parseVCommand(std::string &cmdLine){

        if(expectSCommand==true)
            delete graph;

        expectECommand =false;
        expectSCommand = false;

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
              expectSCommand = false;
                
        }catch(...){
            throw "argument of V command not proper";
        }

}

void parseECommand(std::string &cmdLine){

        if(expectSCommand==true)
        delete graph;

        if(expectECommand==false){
            expectVCommand=true;
            expectECommand=false;
            expectSCommand=false;
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

        graph = new Graph(vertexes);
        graph->setEdges(edgeInput);
                
        expectECommand=false;
        expectSCommand=true;

}

void parseSCommand(std::string &cmdLine){

    if(expectSCommand==false){
        expectVCommand=true;
        expectECommand=false;
        expectSCommand=false;
        throw "s command is not expeccted";
    
    }

    std::string sCommandArg = cmdLine.substr(1,cmdLine.size()-1);

    //trim forward and ending whitespace
    sCommandArg = std::regex_replace(sCommandArg, std::regex("^ +"), "");
    sCommandArg = std::regex_replace(sCommandArg, std::regex(" +$"), "");

    std::string param1;
    std::string param2;
    bool checkParam1=true;
    bool checkParam2=false;
    for(int i=0;i<sCommandArg.size();i++){

        if((sCommandArg.at(i)<'0'|| sCommandArg.at(i)>'9') && sCommandArg.at(i)!=' ')
                throw "Arguments of s command not proper";

        if(sCommandArg.at(i)==' '){
            
            if(checkParam2==true)
                throw "more arugments in s command";

            checkParam1=false;
                
        }
            
        else if(checkParam1==true)
            param1+=sCommandArg.at(i);
        else{
            param2+=sCommandArg.at(i);    
            checkParam2=true;
        }

    }
    int source=0;
    int destination=0;
    try{
        source = std::stoi(param1);
        destination = std::stoi(param2);
    }catch(...){
        throw "Error in parsing the arguments of s command";
    }

    if(source<1||source>vertexes||destination<1||destination>vertexes)
        throw "problem in size of arg of s command";


    graph->printShortDistance(source,destination);        

}

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

            if(order=='V'){
                parseVCommand(cmdLine);
                std::cout<<cmdLine<<std::endl;
            }
            else if(order=='E'){    
                parseECommand(cmdLine);
                std::cout<<cmdLine<<std::endl;
            }
            else
                parseSCommand(cmdLine);


        }catch(const char * exception){
            std::cerr<<"Error: "<<exception<<std::endl;
        }
    

    }


}
