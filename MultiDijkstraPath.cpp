//
//  main.cpp
//  MultiPathDijkstra
//
//  Created by Louisia on 17/02/2017.
//  Copyright © 2017 Louisia. All rights reserved.
//
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
// the nodeNum in the graph

//the maxHop represent the two node not connect directly
const int maxHop=1000;

class MultiPathDijsktr{
private:
    int nodeNum;
    char *node;
    int **graph;
public:
    MultiPathDijsktr(const int nodeNum,char *node,int *graph);
    ~MultiPathDijsktr();
    vector<int> getAdjacent(int index);
    vector < vector<int> > MultiPathDijkstra(int index);
    vector<vector<string>> translatePreToPath(vector< vector<int> >pre,int index);
    void printMultiPath(vector< vector<string> > path);
    
   
};

MultiPathDijsktr::MultiPathDijsktr(int nodeNum,char *node,int *graph){
   
    this->nodeNum=nodeNum;
    this->node=new char[nodeNum];
    this->graph=new int*[nodeNum];
    
    for(int i=0;i<nodeNum;i++){
        this->node[i]=node[i];
    }
    for(int i=0;i<nodeNum;i++){
        this->graph[i]=new int[nodeNum];
        for(int j=0;j<nodeNum;j++){
            this->graph[i][j]=*(graph+i*nodeNum+j);
        }
    }
    
    
}
MultiPathDijsktr::~MultiPathDijsktr(){
    delete []node;
    node=NULL;
    for(int i=0;i<nodeNum;i++){
        delete []graph[i];
        graph[i]=NULL;
    }
}


//the adjacent matrix to represent the graph
/**
 function: 
    get the adjacent nodes' index of the current node
 parameters:
    index: the index of the current node
 */
vector<int> MultiPathDijsktr::getAdjacent(int index){
    vector<int> ajacent;
    for(int i=0;i<nodeNum;i++){
        if(graph[index][i]!=maxHop&&graph[index][i]!=0){
            ajacent.push_back(i);
        }
    }
    return ajacent;
    
}
/**
 function:
    get the shortest multi preNode to the currentNode of all the other nodes
 parameters:
    index: the index of the current node
 
 */
vector < vector<int> > MultiPathDijsktr::MultiPathDijkstra(int index){
    
    if(index<0){
        cout<<"index error"<<endl;
        return vector< vector<int> >();
    }
    
    vector< vector<int> >preTbale(nodeNum);
    
    vector<int>dist(nodeNum,maxHop);
    
    vector<bool> isChoiced(nodeNum,false);
    
    int count=0;
    
    dist[index]=0;
    isChoiced[index]=true;
    count++;
    
    while(count<nodeNum){
    
        vector<int> adjacent =getAdjacent(index);
        
        for(vector<int>::size_type i=0;i<adjacent.size();i++){
            
            int addIndex=adjacent[i];
           
            if(isChoiced[addIndex])
                continue;
            
            if(dist[addIndex]>dist[index]+1){
            
                dist[addIndex]=dist[index]+1;
                preTbale[addIndex].resize(1,index);
            
            }else if(dist[addIndex]==dist[index]+1){
            
                preTbale[addIndex].push_back(index);
            
            }
        }
        
        int minDist=maxHop;
        for(vector<int>::size_type i=0;i<dist.size();i++){
            
            if(isChoiced[i])
                continue;
            
            if(dist[i]<minDist){
                
                index=static_cast<int>(i);
                
                minDist=dist[i];
            
            }
        }
        
        isChoiced[index]=true;
        
        count++;
        
        
        
    }
    
    
    return  preTbale;
}

/**
 function:
    translate the multi shortest pretable to multi paths
 parameters:
    index: the index of the current node
 
 */
vector<vector<string>> MultiPathDijsktr::translatePreToPath(vector< vector<int> >pre,int index){
    vector<vector<string>> path(nodeNum);
    vector<bool> isChoiced(nodeNum,false);
    int count =0;
    
    isChoiced[index]=true;
    count++;
    
    while(count<nodeNum){
        
        for(vector<int>::size_type i=0;i<pre.size();i++){
            if(isChoiced[i])
                continue;
            vector<int>::size_type j,k=0;
            for(j=0;j<pre[i].size();j++){
                int preIndex=pre[i][j];
                char nodeName=node[preIndex];
                stringstream stream;
                stream<<nodeName;
                if(isChoiced[preIndex]){
                    if(preIndex==index){
                        path[i].push_back(stream.str());
                    }else{
                        for(int k=0;k<path[preIndex].size();k++){
                            path[i].push_back(path[preIndex][k]+"--->"+stream.str());
                        }
                    }
                    k++;
                }
            }
            if(k==j){
                isChoiced[i]=true;
                count++;
                path[i].erase(unique(path[i].begin(), path[i].end()), path[i].end());
            }
            
        }
        
    }
    
    for(vector<int>::size_type i=0;i<path.size();i++){
        for(vector<int>::size_type j=0;j<path[i].size();j++){
            stringstream sstream;
            sstream<<node[i];
            path[i][j]=path[i][j]+"--->"+sstream.str();
            
        }
    }
    
    return path;
    
}

void MultiPathDijsktr::printMultiPath(vector< vector<string> > path){
    for(int i=0;i<path.size();i++){
                if(path[i].size()==0)
                    continue;
                for(int j=0;j<path[i].size();j++){
                    if(j<path[i].size()-1)
                        cout<<path[i][j]<<",";
                    else
                        cout<<path[i][j];
                }
                cout<<endl;
            }
}

int main(){
    
    const int nodeNum=5;
  
    char node[]={'A','B','C','D','E'};
    
    
    int graph[5][5]={
        {0,1,maxHop,1,1},
        {1,0,1,maxHop,maxHop},
        {maxHop,1,0,1,1},
        {1,maxHop,1,0,maxHop},
        {1,maxHop,1,maxHop,0}
    };
    
    
    MultiPathDijsktr mp(nodeNum,node,*graph);
    
    vector< vector<int> > preTable=mp.MultiPathDijkstra(0);
    
    vector< vector<string> > path=mp.translatePreToPath(preTable, 0);
    mp.printMultiPath(path);

}
