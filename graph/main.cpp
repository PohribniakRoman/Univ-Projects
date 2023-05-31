#include <iostream>
#include<vector>

using namespace std;

struct Vertex{
    vector<Vertex*> arcList;
    int vertexIndex;
};

class Graph{
private:
    vector<Vertex> vertexList;
    bool isVertexExist(int vertexIndex){
        for (auto &i : this->vertexList) {
            if(i.vertexIndex == vertexIndex){
                return true;
            }
        }
        cout<<"Vertex with index - " <<vertexIndex<<"does not exist!\n";
        return false;
    }
    Vertex& findVertex(int vertexIndex){
        for (auto &i : this->vertexList) {
            if(i.vertexIndex == vertexIndex){
                return i;
            }
        }
    }

    bool isArcExist(int vertexIndex,int vertexIndexToFind){
        for(auto &i: this->findVertex(vertexIndex).arcList){
            if(i->vertexIndex == vertexIndexToFind){
                cout<<"Arc is already exists!\n";
                return true;
            }
        }
        return false;
    }
public:
    explicit Graph(vector<vector<bool>> matrix);
    bool createVertex(int n);
    bool addArc(int vertexIndex,int vertexToAdd);
    bool deleteArc(int vertexIndex,int vertexToRemove);
    vector<Vertex*> findNeighbor(int vertexIndex);
    void printVortex(int vortexIndex);
};

Graph::Graph(vector<vector<bool>> matrix) {
    for (int i = 0;i < matrix.size();i++) {
        this->createVertex(i);
    }
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if(matrix[i][j]){
                addArc(i,j);
            }
        }
    }
}

void Graph::printVortex(int vortexIndex) {
    auto currentVortex = findVertex(vortexIndex);
    cout<<"Current vortex index is - "<<currentVortex.vertexIndex<<"\n";
    for(auto &i:currentVortex.arcList){
        cout<<"|\tNeighbor index - " << i->vertexIndex<<"\t|\n";
    }
}

vector<Vertex*> Graph::findNeighbor(int vertexIndex) {
    if(!isVertexExist(vertexIndex)){
        cout<<"Failed to find neighbor!\n";
        vector<Vertex*> nullVector;
        return nullVector;
    };
    return findVertex(vertexIndex).arcList;
};

bool Graph::addArc(int vertexIndex, int vertexToAdd) {
    if(!isVertexExist(vertexIndex) || !isVertexExist(vertexToAdd)){
        cout<<"Failed to add arc\n";
        return false;
    };
    if(isArcExist(vertexIndex,vertexToAdd))return true;
    findVertex(vertexIndex).arcList.push_back(&findVertex(vertexToAdd));
    return true;
};

bool Graph::createVertex(int n) {
    Vertex newVertex;
    newVertex.vertexIndex = n;
    this->vertexList.push_back(newVertex);
    return true;
};

bool Graph::deleteArc(int vertexIndex, int vertexToRemove) {
    if(!isVertexExist(vertexIndex) || !isVertexExist(vertexToRemove)){
        cout<<"Failed to remove arc\n";
        return false;
    };
    if(!isArcExist(vertexIndex,vertexToRemove))return true;
    auto &currentVertex = findVertex(vertexIndex);
    vector<Vertex*> newArcList;
    for (auto &i: currentVertex.arcList) {
        if(i->vertexIndex != vertexToRemove){
            newArcList.push_back(i);
        }
    }
    currentVertex.arcList = newArcList;
    return true;
}


int main(){
    vector<vector<bool>> matrix = {{true,false, true},{false,true, false},{true, false,true}};
    Graph newGraph(matrix);

    newGraph.printVortex(2);
    newGraph.deleteArc(2,2);
    newGraph.printVortex(2);
    newGraph.addArc(2,2);
    newGraph.printVortex(2);
    return 0;
}