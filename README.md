# MultiPathDijkstra
编程环境：Linux C++

实现： Dijkstra 多路径  1 代表两个节点之间直接相连，maxHop代表节点之间不直接相连

测试用例：

nodeNum =5 

nodes={A,B,C,D,E}

graph={A->B,A->D,A->E,B->C,D->C,E->C}=====>{

        {0,1,maxHop,1,1},
        
        {1,0,1,maxHop,maxHop},
        
        {maxHop,1,0,1,1},
        
        {1,maxHop,1,0,maxHop},
        
        {1,maxHop,1,maxHop,0}

}

结果输出：

A--->B

A--->B--->C,A--->D--->C,A--->E--->C

A--->D

A--->E

