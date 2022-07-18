#include<iostream>
#include<vector>

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
            y3=temp;
        }

        if((y1<y3&&y3<y2)||(y1<y4&&y4<y2)||(y3<y1&&y1<y4)||(y3<y2&&y2<y4)){
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
        
        int temp2 =x3;
        x3=x4;
        x4=temp2;
        
    }
    
    
    std::cout<<x1<<std::endl;
    std::cout<<x2<<std::endl;
    std::cout<<x3<<std::endl;
    std::cout<<x4<<std::endl;
    if((x1<x3&&x3<x2)||(x1<x4&&x4<x2)||(x3<x1&&x1<x4)||(x3<x2&&x2<x4)){
            //std::cout<<"Failed for same c"<<x1<<','<<y1<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<' '<<x4<<','<<y4<<' '<<std::endl;
            return -1;
    }

    return 1;

}

int isGoodForStreet(int x, int y,std::vector<std::pair<int,int>> &streetSegmentsStore){

        // for(int i=0;i<streetSegmentsStore.size();i++){
        //     if(x==streetSegmentsStore.at(i).first && y==streetSegmentsStore.at(i).second){
        //         //std::cout<<"Failed for pick good"<<streetSegmentsStore.at(i).first<<','<<streetSegmentsStore.at(i).second<<' '<<x<<','<<y<<std::endl;
        //         return -1;
        //     }
        // }

        for(int i=0;i<streetSegmentsStore.size()-1;i++){
            if(isOverlap(streetSegmentsStore.back(),std::make_pair(x,y),streetSegmentsStore.at(i),streetSegmentsStore.at(i+1))!=1)
                return -1;

            // if(i!=streetSegmentsStore.size()-2 && 
            //     isIntersect(streetSegmentsStore.back(),std::make_pair(x,y),streetSegmentsStore.at(i),streetSegmentsStore.at(i+1))!=1){
            //     return -1;
            // }    
        }

        return 1;
}

int main(){

    std::vector<std::pair<int,int>> streetsSegmentsStore;

    std::pair<int,int> p1;
    p1.first=2;
    p1.second=3;
    streetsSegmentsStore.push_back(p1);

    std::cout<<"here1"<<isGoodForStreet(3,-3,streetsSegmentsStore)<<std::endl;
    streetsSegmentsStore.push_back(std::make_pair(3,-3));

    std::cout<<"here2"<<isGoodForStreet(-1,1,streetsSegmentsStore)<<std::endl;
    streetsSegmentsStore.push_back(std::make_pair(-1,1));

    std::cout<<"here"<<isGoodForStreet(0,0,streetsSegmentsStore)<<std::endl;
    streetsSegmentsStore.push_back(std::make_pair(0,0));
    

}