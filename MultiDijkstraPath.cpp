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

const int nodeNum=5;
const int maxHop=100;

int graph[][nodeNum]={
    {0,1,maxHop,1,1},
    {1,0,1,maxHop,maxHop},
    {maxHop,1,0,1,1},
    {1,maxHop,1,0,maxHop},
    {1,maxHop,1,maxHop,0}
   

};

vector<int> getAdjacent(int index){
    vector<int> ajacent;
    for(int i=0;i<nodeNum;i++){
        if(graph[index][i]<maxHop&&graph[index][i]!=0){
            ajacent.push_back(i);
        }
    }
    return ajacent;
    
}
//PreTable
vector < vector<int> > MultiPathDijkstra(int index){
    
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
                
                index=i;
                
                minDist=dist[i];
            
            }
        }
        
        isChoiced[index]=true;
        
        count++;
        
        
        
    }
    
    
    return  preTbale;
}

vector<vector<string>> translatePreToPath(vector< vector<int> >pre,int index){
    vector<vector<string>> path(nodeNum);
    vector<bool> isChoiced(nodeNum,false);
    int count =0;
    
    isChoiced[index]=true;
    count++;
    
    while(count<nodeNum){
        
        for(int i=0;i<pre.size();i++){
            if(isChoiced[i])
                continue;
            int j,k=0;
            for(j=0;j<pre[i].size();j++){
                int preIndex=pre[i][j];
                stringstream stream;
                stream<<pre[i][j];
                if(isChoiced[preIndex]){
                    if(preIndex==index){
                        path[i].push_back(stream.str());
                    }else{
                        for(int k=0;k<path[preIndex].size();k++){
                            path[i].push_back(path[preIndex][k]+"   "+stream.str());
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
    
    return path;
    
}

int main(){
    vector< vector<int> > preTable=MultiPathDijkstra(0);
    for(int i=0;i<preTable.size();i++){
        for(int j=0;j<preTable[i].size();j++){
            cout<<preTable[i][j]<<" ";
        }
        cout<<endl;
    }
    
    vector< vector<string> > path=translatePreToPath(preTable, 0);
    for(int i=0;i<path.size();i++){
        for(int j=0;j<path[i].size();j++){
            cout<<path[i][j]<<",";
        }
        cout<<endl;
    }
}
