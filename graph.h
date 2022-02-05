#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

//edits to this are likely not needed
template <class T>
struct Vertex {
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree; // Part 2: number of nodes pointing in
  int top_num; // Part 2: topological sorting number
  Vertex(T l) : label(l) {top_num = 0;} //Part 1
  // You may include default constructor optionally.
};

// optional, but probably helpful
template <class T>
ostream& operator<<(ostream &o, Vertex<T> v) {
  o << v.label << " : ";
  if (v.adj_list.size() != 0) {
    for (size_t i = 0; i < v.adj_list.size() - 1; ++i) {
      o << v.adj_list[i] << " ";
    }
    o << v.adj_list[v.adj_list.size() - 1];
  }
  return o;
}



// std::priority_queue may take takes three template parameters: <Type, ContainerType, Functor>
// syntax for custom compare functor
// Refer the instructions PDF last section for more information

template<class T>
class VertexCompare
{
public:
  bool operator()(Vertex<T> v1, Vertex<T> v2){
     if (v1.top_num > v2.top_num) {
       return true;
     }
     return false;
  }
};

template <class T>
class Graph {
private:
  //c++ stl hash table

  unordered_map<T, Vertex<T>> node_set;
  int vertices = 0; //number of vertices initialized to 0
  vector< Vertex<T> > map_vertices = {}; //stores vertices to be printed to displayGraph()
public:
  Graph() {};  //No modification needed to default constructor. Can be used optionally if needed.
  ~Graph() {}; //No modification needed to destructor. Can be used optionally if needed.

  // build a graph - refer the instructions PDF for more information.
  void buildGraph(istream &input) {
    string vertexLine;
    getline(input, vertexLine); //inputs the current line in the input stream

    do {
      stringstream ss(vertexLine); //turns line into stringstream

      T element;
      T label; //two created variables for input
      ss >> label; //First, the label is inserted and vertex is created
      Vertex<T> input_vertex(label);

      while (ss >> element) { //while the file can input another element, the element is pushed into the adjacency list
        input_vertex.adj_list.push_back(element);
      }
      node_set.insert(make_pair(input_vertex.label, input_vertex)); //turns the label and vertex into a pair and pushed onto map
      ++vertices; //number of vertices is incremented
      map_vertices.push_back(input_vertex); //just a vector that stores all the vertices for displayGraph()
    }
    while (getline(input, vertexLine));
  }

  // display the graph into o - refer the instructions PDF for more information.
  void displayGraph(ostream& o) {
    for (size_t i = 0; i < map_vertices.size(); ++i) { //goes through the list of vertices and prints each out
      o << map_vertices.at(i) << std::endl;
    }
  }

  //return the vertex at label, else throw any exception  - refer the instructions PDF for more information.
  Vertex<T> at(T label) {
    return node_set.at(label);
  }

  //return the graph size (number of verticies)
  int size() {
    return this->vertices; //private variable that represents the number of vertices
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  bool topological_sort() {
    queue<T> q;
    int counter = 0; //to find next top_num values

    while (!q.empty()) {
      q.pop(); //make sure it's empty first
    }

    for (auto& it: node_set) {
      if (node_set.at(it.first).indegree == 0) {
        q.push(it.first); //pushes all values with indegrees of 0
      }
    }

    while (!q.empty()) {
      T currlabel = q.front(); //next one that's being checked
      
      node_set.at(currlabel).top_num = counter + 1; //assigns top num value and increments
      ++counter;

      q.pop();

      for (auto& jt: node_set.at(currlabel).adj_list) {
        if (--(node_set.at(jt).indegree) == 0) { //decrements but also checks if it should be pushed
          q.push(jt);
        }
      }
    }

    if (counter != vertices) { //if for some reason the counter does not equal the number of vertices, something was missed
      return false;
    }

    return true;
  }; // Part 2

  // find indegree
  void compute_indegree() {
    for (auto& it: node_set) {
      it.second.indegree = 0; //set all equal to 0 for start
    }

    for (auto& it: node_set) { //go through each vertex
      for (auto& j: it.second.adj_list) { //goes through adjacency list and adds one to each because they connect from current vertex
        node_set.at(j).indegree++;
      }
    }
  }; // Part 2


  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream& o, bool addNewline=true)
  { 
    std::priority_queue<Vertex<T>, vector<Vertex<T>>, VertexCompare<T>> pq;
    for (auto& it: node_set) {
      pq.push(it.second); //pushes each vertex into priority queue
    }
    
    while (!pq.empty()) {
      o << pq.top().label << " "; //outputs the label and then pops it out of the pq
      pq.pop();
    }

    if(addNewline){o << '\n';};
  }; // Part 2
};

#endif
