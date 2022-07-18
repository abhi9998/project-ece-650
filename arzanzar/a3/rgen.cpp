#include<iostream>
#include<unistd.h>
#include<fstream>
#include<vector>
#include <math.h>

int flagCommon=0;
std::pair<int,int> commonPair;

int generateRandom(int min, int max){

    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr<<"Error: from /dev/urandom"<<std::endl;
        exit(1);
    }

    unsigned int num = 42;
    urandom.read((char *)&num, sizeof(int));
    urandom.close();

    return min + (num%(max-min+1));

}

void generateStreetNames(std::vector<std::string> &streetNames,int totalStreets){
        std::string global = "abcdefghijklmnopqrstuvwxyz"; 

        for(int i=1;i<=totalStreets;i++){
            std::string str = "";
            int val = i;
            while(val!=0){
                int temp = val%10;
                val=val/10;
                str+=global.at(temp);
            }
            streetNames.push_back(str); 
        }
        return;

}

int isOverlap(std::pair<int,int> p1,std::pair<int,int> p2,std::pair<int,int> p3,std::pair<int,int> p4){
    int x1 = p1.first;
    int y1 = p1.second;
    int x2 = p2.first;
    int y2 = p2.second;
    int x3 = p3.first;
    int y3 = p3.second;
    int x4 = p4.first;
    int y4 = p4.second;

    int deno = (y4-y3)*(x2-x1) - (y2-y1)*(x4-x3);

    if(deno!=0)
       return 1;

    //vertical line
    if(x1==x2 && x2==x3 && x3==x4&& x1==x4){
        if(y2<y1){
            int temp =y1;
            y1=y2;
            y2=temp;
        }
        if(y4<y3){
            int temp =y3;
            y3=y4;
            y4=temp;
        }

        if((y1<=y3&&y3<=y2)||(y1<=y4&&y4<=y2)||(y3<=y1&&y1<=y4)||(y3<=y2&&y2<=y4)){
            //std::cout<<"Failed for in vertical"<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
            return -1;
        }
    }
    if(x1==x2||x3==x4)
    return 1;

    double c1 = (y1*(x2-x1)-x1*(y2-y1))/(x2-x1);
    double c2 = (y3*(x4-x3)-x3*(y4-y3))/(x4-x3);

    if(c1!=c2){
        return 1;
    }

    if(x2<x1){
        int temp =x1;
        x1=x2;
        x2=temp;
    }
    if(x4<x3){
        int temp =x3;
        x3=x4;
        x4=temp;
    }

    if((x1<=x3&&x3<=x2)||(x1<=x4&&x4<=x2)||(x3<=x1&&x1<=x4)||(x3<=x2&&x2<=x4)){
            //std::cout<<"Failed for same c"<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
            return -1;
    }

    return 1;

}

int isIntersect(std::pair<int,int> p1,std::pair<int,int> p2,std::pair<int,int> p3,std::pair<int,int> p4){
    int x1 = p1.first;
    int y1 = p1.second;
    int x2 = p2.first;
    int y2 = p2.second;
    int x3 = p3.first;
    int y3 = p3.second;
    int x4 = p4.first;
    int y4 = p4.second;

    double xnum = (x4-x3)*(x2*y1-x1*y2) - (x2-x1)*(x4*y3-x3*y4);

    double ynum = (y4-y3)*(x2*y1-x1*y2) - (y2-y1)*(x4*y3-x3*y4);

    int deno = (y4-y3)*(x2-x1) - (y2-y1)*(x4-x3);

    if(deno!=0){

        double xIntersect = xnum/deno;
        double yIntersect = ynum/deno;
        //std::cout<<"Intersect point"<<xIntersect<<","<<yIntersect<<std::endl;
        // std::cout<<std::min(x1,x2)<<std::endl;
        // std::cout<<std::max(x1,x2)<<std::endl;
        // std::cout<<std::min(y1,y2)<<std::endl;
        // std::cout<<std::max(y1,y2)<<std::endl;
        // std::cout<<std::min(x3,x4)<<std::endl; 
        // std::cout<<std::max(x3,x4)<<std::endl; 
        // std::cout<<std::min(y3,y4)<<std::endl; 
        // std::cout<<std::max(y3,y4)<<std::endl;   

        if(std::min(x1,x2)<= xIntersect && xIntersect <= std::max(x1,x2) && std::min(y1,y2) <= yIntersect && yIntersect <= std::max(y1,y2)){ 
            if(std::min(x3,x4) <= xIntersect && xIntersect <= std::max(x3,x4) && std::min(y3,y4)<= yIntersect && yIntersect <= std::max(y3,y4)){
                // std::cout<<"Failed for interset"<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
                // std::cout<<"Intersect point"<<xIntersect<<","<<yIntersect<<std::endl;
                return -1;
            }else{
               // std::cout<<"Passed for interset 1  "<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
                return 1;
            }
        }else{
           // std::cout<<"Passed for interset 2  "<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
            return 1;
        }

    }

   // std::cout<<"Passed for interset 3  "<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
    return 1;
        
}

int isGoodForStreet(int x, int y,std::vector<std::pair<int,int>> &streetSegmentsStore){

        for(int i=0;i<streetSegmentsStore.size();i++){
            if(x==streetSegmentsStore.at(i).first && y==streetSegmentsStore.at(i).second){
                //std::cout<<"Failed for pick good"<<streetSegmentsStore.at(i).first<<','<<streetSegmentsStore.at(i).second<<' '<<x<<','<<y<<std::endl;
                return -1;
            }
        }

        for(int i=0;i<streetSegmentsStore.size()-1;i++){
            if(isOverlap(streetSegmentsStore.back(),std::make_pair(x,y),streetSegmentsStore.at(i),streetSegmentsStore.at(i+1))!=1)
                return -1;

            if(i!=streetSegmentsStore.size()-2 && 
                isIntersect(streetSegmentsStore.back(),std::make_pair(x,y),streetSegmentsStore.at(i),streetSegmentsStore.at(i+1))!=1){
                return -1;
            }    
        }

        return 1;
}

int isGoodForAllStreet(std::pair<int,int> p1,std::pair<int,int> p2, std::vector<std::vector<std::pair<int,int>>> &allStreets){

    for(int i=0;i<allStreets.size();i++){
        std::vector<std::pair<int,int>> temp =allStreets.at(i);

        for(int j=0;j<temp.size()-1;j++){
            
            if(isOverlap(p1,p2,temp.at(j),temp.at(j+1))!=1)
                return -1;
        }
    }
    //std::cout<<"returing from isgoo all"<<std::endl;
    return 1;
}

int generateStreets(int coordinate,int totalSegments,std::vector<std::pair<int,int>> &streetSegmentsStore,
                    std::vector<std::vector<std::pair<int,int>>> &allStreets){
        int tried=0;
        //std::cout<<"Total segments for street: "<<totalSegments<<std::endl;

        for(int i=0;i<totalSegments+1;i++){
            int x = generateRandom(-1*coordinate,coordinate);
            int y = generateRandom(-1*coordinate,coordinate);
            //std::cout<<x<<','<<y<<std::endl;

            //this will add the starting point of first street as starting point of street 2
            if(flagCommon==2){
                streetSegmentsStore.push_back(std::make_pair(commonPair.first,commonPair.second));
                flagCommon=3;
                continue;
            }

            if(streetSegmentsStore.size()==0){
                  streetSegmentsStore.push_back(std::make_pair(x,y));

                  //this will store the very first street first cooridnate in commonPair.  
                  if(flagCommon==0){
                      commonPair.first=x;
                      commonPair.second=y;
                      flagCommon=1;
                  }
                  continue;  
            }

            if(isGoodForStreet(x,y,streetSegmentsStore)==1 && 
                isGoodForAllStreet(streetSegmentsStore.back(),std::make_pair(x,y),allStreets)==1){
                    tried=0;
                    streetSegmentsStore.push_back(std::make_pair(x,y));
            }else{
                //std::cout<<tried<<"::here"<<std::endl;
                tried++;
                i--;
            }

            if(tried>50){
                return -1;
            }

        }

        //this logic is written so that one point is common in two different streets
        if(flagCommon==1){
            flagCommon=2;
        }
        
        return 0;
}

int main(int argc, char **argv){

    int street = 10;
    int segment = 5;
    int waitTime = 5;
    int coordinate= 20;
    char ch;
    opterr=0;


    while((ch = getopt(argc,argv,"s:n:l:c:"))!=-1){
        //std::cout<<"OPTIND is:"<<optind<<std::endl;
        
        switch(ch){

            case 's':
                //std::cout<<"IN S"<<std::endl;
                street = std::atoi(optarg);
                if(street<2){
                    std::cerr<<"Error: the value of flag S is less than 2"<<std::endl;
                    return 1;
                }
                //std::cout<<"Value of S is "<<street<<std::endl;
                break;

            case 'n':
                //std::cout<<"IN N"<<std::endl;
                segment = std::atoi(optarg);
                if(segment<1){
                    std::cerr<<"Error: the value of flag N is less than 1"<<std::endl;
                    return 1;
                }
                //std::cout<<"Value of N is "<<segment<<std::endl;
                break;

            case 'l':
                //std::cout<<"IN L"<<std::endl;
                waitTime = std::atoi(optarg);
                if(waitTime<5){
                    std::cerr<<"Error: the value of flag L is less than 5"<<std::endl;
                    return 1;
                }
                //std::cout<<"Value of L is "<<waitTime<<std::endl;
                break;

            case 'c':
                //std::cout<<"IN C"<<std::endl;
                coordinate = std::atoi(optarg);
                if(coordinate<1){
                    std::cerr<<"Error: the value of flag C is less than 1"<<std::endl;
                    return 1;
                }
                //std::cout<<"Value of C is "<<coordinate<<std::endl;
                break;

            case '?':
                std::cerr<<"Error: problem occured in providing arguments. Check the args"<<std::endl;
                return 1;

            default:
                std::cerr<<"Error: returning from default"<<std::endl;
                return 1;                
                  
        }
    }

    std::vector<std::vector<std::pair<int,int>>> allStreets;
    std::vector<std::string> streetNames;


    while(true){

        int totalStreets = generateRandom(2,street);
        //std::cout<<"Total streets:  "<<totalStreets<<std::endl;
        generateStreetNames(streetNames,totalStreets);    

        // for(int i=0;i<streetNames.size();i++){
        //     std::cout<<streetNames.at(i)<<std::endl;
        // }

        for(int i=0;i<totalStreets;i++){
            std::vector<std::pair<int,int>> streetSegmentsStore;
            int totalSegments = generateRandom(1,segment);

            int returnCode = generateStreets(coordinate,totalSegments,streetSegmentsStore,allStreets);
            
            if(returnCode==-1){
                std::cerr<<"Error: failed to generate valid input after 50 tries"<<std::endl;
                return 1;
            }

            allStreets.push_back(streetSegmentsStore);

        }

        int j=0;
        for (const auto &row : allStreets){ 
            std::string input="";
            input+="add \"";
            //std::cout<<streetNames.at(j)<<std::endl;
            input+=streetNames.at(j);
            input+="\"";

            j++;
            for ( const auto &s : row ) 
                input+=" ("+std::to_string(s.first)+ "," + std::to_string(s.second)+")";
                //std::cout << '('<<s.first << ','<<s.second<<')'<<std::endl;
            std::cout <<input<< std::endl;
        }
        std::cout<<"gg"<<std::endl;

        int waitingTime = generateRandom(5,waitTime);

        sleep(waitingTime);

        allStreets.clear();
        for(int i=0;i<streetNames.size();i++){
            std::cout<<"rm \""<<streetNames.at(i)<<"\""<<std::endl;
        }

        streetNames.clear();
        flagCommon=0;

        
    }


}