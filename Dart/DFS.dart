import 'dart:io';


List<bool> visited;
List<List<int> > graph;



void dfs(int u){
    visited[u]=true;
    for(int i=0;i<graph[u].length;++i){
       int v = graph[u][i];
      if(!visited[v]){
        dfs(v);
      }
    }
}

void main(){
  

  
  int nodes = int.parse(stdin.readLineSync());
  int edges = int.parse(stdin.readLineSync());

  visited = List.filled(nodes, false);
  
  graph = new List(nodes);
  for(int i=0;i<graph.length;++i){
    graph[i] = new List();
  }
 
 for(int i=0;i<edges;++i){
  var u = int.parse(stdin.readLineSync());
  var v = int.parse(stdin.readLineSync());
  graph[u].add(v); 
 }

  int from = int.parse(stdin.readLineSync());  
  dfs(from);
  for(int i=0;i<nodes;++i){
    print('node $i is reachable from $from');
  }
  print(visited);
}
