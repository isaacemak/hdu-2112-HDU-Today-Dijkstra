//
//  main.cpp
//  hdu2112
//
//  Created by isaac on 16/6/30.
//  Copyright © 2016年 isaac. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace std;
using namespace boost;

typedef std::pair<int, int> Edge;
typedef adjacency_list < listS, vecS, directedS, no_property, property < edge_weight_t, int > > graph_t;
typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;

void printString(string s){
    cout<<"->"<<s;
}

int main(int argc, const char * argv[]) {
    
    int n;
    while (scanf("%d", &n)!=EOF)
    {
        if (n==-1)
            break;
        
        map<string,int> stations;
        
        vector<int> weights;
        vector<Edge> edges;
        vector<string> int2station;
        
        int stationCounter= 0;
        
        
        //read the names of the stations and put them into a Map
        string start, end;
        cin>>start>>end;
        
        if (stations.find(start)==stations.end()){
            int2station.push_back(start);
            stations[start]=stationCounter++;
        }
        if (stations.find(end)==stations.end()){
            int2station.push_back(end);
            stations[end]=stationCounter++;
        }
     
        
        for (int i=0; i<n; i++){
            string s, e;
            int t;
            cin>> s>>e>>t;
            
            if (stations.find(s)==stations.end()){
                int2station.push_back(s);
                stations[s]=stationCounter++;
            }
            if (stations.find(e)==stations.end()){
                int2station.push_back(e);
                stations[e]=stationCounter++;
            }
            
            int int_s= stations[s];
            int int_e= stations[e];
            
            edges.push_back(Edge(int_s,int_e));
            weights.push_back(t);
          
        }
        
        //construct the graph as the BOOST demo
        const int num_nodes = stationCounter;
        
        graph_t g(edges.begin(), edges.end(), weights.begin(), num_nodes);
              std::vector<vertex_descriptor> p(num_vertices(g));
        std::vector<int> d(num_vertices(g));
        vertex_descriptor s = vertex(stations[start], g);
        
        //call dijkstra in BOOST
        dijkstra_shortest_paths(g, s,
                                predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                                distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));
        

        //record the shortest path by looking back upon the destination point
        int current_p= stations[end];
        vector<string> str_paths;
        while(current_p){
            str_paths.push_back(int2station[current_p]);
            current_p=p[current_p];
        }
        
        //output the result
        cout<<start;
        for_each(str_paths.rbegin(), str_paths.rend(), printString);//please noted the way to traverse a container in reverse order
        cout<<endl;

        
    }
    return 0;
}
