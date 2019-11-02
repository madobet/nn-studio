#include "vgraph.h"

VGraph::VGraph()
    :size(0), edge(0), vertex(nullptr), weight(nullptr), sparse(nullptr)
{
}

VGraph::VGraph(int g_size, double ** mat)
    : size(g_size)
{
    edge = 0;
    weight = new double*[size];
    for(int i=0;i<size;i++)
    {
        weight[i] = new double[size];
        for(int j=0;j<size;j++)
        {
            weight[i][j] = mat[i][j];
            if(weight[i][j]!=0) edge++;
        }
    }
    ConvertToSpr();
    CreateAdjFromWMat();
}
/*
VGraph::VGraph(int e_size, double* spr_mat[3])
    : edge(e_size)
{
    sparse = new double[3]*;
    for(int i = 0; i < edge; i++)
    {
        sparse[i] = new double[3];
        for(int j = 0; j < 3; j++)
        {
             sparse[i][j] = spr_mat[i][j];
        }

    }
    ConvertToMat();
    CreateAdjFromWMat();
}
*/
VGraph::VGraph(const VGraph & G)
    : size(G.size), edge(G.edge)
{
    weight = new double*[size];
    for(int i=0;i<size;i++)
    {
        weight[i] = new double[size];
        for(int j=0;j<size;j++)
        {
            weight[i][j] = G.weight[i][j];
        }
    }
    CreateAdjFromWMat();
    ConvertToSpr();
}
//------------------------------
int VGraph::VertexNum() const
{
    return size;
}

int VGraph::EdgeNum() const
{
    return edge;
}

int VGraph::ConnectNum() const
{
    int count = 0;
    for(int i = 0;i<size;i++)
        for(int j = i;j<size;j++)
            if(weight[i][j]!=0) count++;
    return count;
}

void VGraph::Topology() const
{
    for (int i = 0; i < size; i++) {
        const node* ptnode = &(vertex[i]);
        std::cout << ptnode->id;
        ptnode = ptnode->next;
        while (ptnode != nullptr)
        {
            std::cout << "->" << ptnode->id;
            ptnode = ptnode->next;
        }
        std::cout << std::endl;
    }
}

int VGraph::Alone() const
{
    int num = 0;
    for (int i = 0; i < size; i++) {
        num += ((vertex[i].next == nullptr) ? 1 : 0);
    }
    return num;
}

bool VGraph::Edge(int vs, int vt) const
{
    return (weight[vs][vt] != 0)?true:false;
}

bool VGraph::Connectivity(int vs)
{
    bool r = true;
    UnweightSLen(vs);
    for (int i = 0; i<size; i++)
    {
        if (vertex[i].dist == INFINITY)
            r = false;
        vertex[i].dist = INFINITY;	// reset the distance field to INF for next use
    }
    return r;
}

bool VGraph::Connectivity(int vs, int vt) const
{
    return (Edge(vs,vt) || Edge(vt,vs));
}

double VGraph::Weight(int vs, int vt) const
{
    return weight[vs][vt];
}
//---------------------------------


bool VGraph::AddDirEdge(int i, int j, double w) {
    node* ptnode = new node(j, vertex[i].next);
    vertex[i].next = ptnode;
    weight[i][j] = w;
    return true;
}

bool VGraph::AddEdge(int i, int j, double w) {
    AddDirEdge(i, j, w);
    AddDirEdge(j, i, w);
    return true;
}

bool VGraph::DelDirEdge(int i, int j) {
    node* prev = vertex[i].FindPrevNode(j);
    if (prev == nullptr)
        return true;
    node* now = prev->next;
    if (now == nullptr)
        return true;
    prev->next = now->next;
    delete now;//这样释放带指针的结构？
    weight[i][j] = 0;
    return true;
}

bool VGraph::DelEdge(int i, int j) {
    DelDirEdge(i, j);
    DelDirEdge(j, i);
    return true;
}

bool VGraph::UnweightSLen(int vs) {
    InitialDis();
    std::queue<int> q;
    if (vs<0)
    {
        std::cout << "illegal vertex!" << std::endl;
        return false;
    }
    vertex[vs].dist = 0;
    q.push(vs);
    while (!q.empty())
    {
        int select_vertex = q.front();
        q.pop();
        const node* ptnode = vertex[select_vertex].next;
        while (ptnode != nullptr)
        {
            int id_sub;
            id_sub = ptnode->id;
            if (vertex[id_sub].dist == INFINITY)	//attention! should not be written as "if(ptNode->distance==INFINITYTE)!"
            {
                vertex[id_sub].dist = vertex[select_vertex].dist + 1;
                q.push(id_sub);
            }
            ptnode = ptnode->next;
        }
    }
    return true;
}

bool VGraph::WeightSLen(int vs) {
    return true;
}

double VGraph::CharPathLen() {
    double path_len = 0;
    const int max = size*(size - 1) / 2;
    int side_sum = max;
    int dis = 0;

    for (int vs = 0; vs<size; vs++)
    {
        UnweightSLen(vs);
        for (int v_e = vs + 1; v_e<size; v_e++)
        {
            dis = vertex[v_e].dist;
            if (dis == INFINITY)
            {
                side_sum--;
                continue;
            }
            path_len += dis;
            vertex[v_e].dist = INFINITY;	//复原distance域
        }
    }
    if (side_sum == 0)
        return INFINITY;
    path_len = path_len / side_sum;
    return path_len;
}

double VGraph::Coefficient() {
    double c = 0;
    for (int i = 0; i<size; i++)
        c += Coefficient(i);
    c = c / size;
    return c;
}

double VGraph::Coefficient(int id) {
    std::stack<int> s;
    const node* ptnode = vertex[id].next;
    int k = 0;
    while (ptnode != nullptr)
    {
        s.push(ptnode->id);
        ptnode = ptnode->next;
        k++;
    }
    if (k == 0 || k == 1)
        return 0;

    int* knode_id = new int[k];
    for (int i = 0; i<k; i++)
    {
        knode_id[i] = s.top(); s.pop();
    }
    int edge_num = 0;
    for (int i = 0; i<k; i++)
    {
        int j;
        for (j = i + 1; j<k; j++)
        {
            if (weight[knode_id[i]][knode_id[j]] != 0)
                edge_num++;
            ptnode = vertex[knode_id[i]].next;
            while (ptnode != nullptr)
            {
                if (ptnode->id != id)	//不能经过中心点本身
                    if (weight[ptnode->id][knode_id[j]] != 0)
                        edge_num++;
                ptnode = ptnode->next;
            }
        }
    }
    delete[] knode_id;
    double c = k*(k - 1) / 2;
    c = edge_num / c;
    return c;
}

VGraph::~VGraph() {
    DelAdj();
    DelMatrix();
}

int VGraph::InitialDis() {
    int i = 0;
    for (; i < size; i++)
        vertex[i].dist = INFINITY;
    return i;
}

int VGraph::CreateAdjFromWMat() {
    if (vertex != nullptr)
        DelAdj();	//保险起见，先删除一下当前邻接表
    vertex = new node[size];
    for (int i = 0; i < size; i++)
    {
        vertex[i].id = i;
    }
    int oh = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (weight[i][j] != 0)
            {
                AddDirEdge(i, j, weight[i][j]);
                oh++;
            }
    return oh;
}

inline void VGraph::ConvertToSpr() {
    DelSprMat();
    sparse = new double*[edge];
    for(int i = 0; i < edge; i++)
        sparse[i] = new double[3];
    int k = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size;j++)
            if (weight[i][j] != 0){
                sparse[k][1] = i;
                sparse[k][2] = j;
                sparse[k][3] = weight[i][j];
                k++;
            }
}

inline void VGraph::ConvertToMat() {
    DelNorMat();
    weight = new double*[size];
    for(int i = 0; i < size; i++)
        weight[i] = new double[size];
    for(int i = 0; i < edge; i++)
        weight[int(sparse[i][1])][int(sparse[i][2])] = sparse[i][3];
}

inline void VGraph::DelNorMat() {
    if(weight == nullptr)
        return;
    for(int i = 0; i < size; i++)
        delete[] weight[i];
    delete[] weight;
    weight = nullptr;
}

inline void VGraph::DelSprMat() {
    if(sparse == nullptr)
        return;
    for (int i = 0; i < edge; i++)
        delete[] sparse[i];
    delete[] sparse;
    sparse = nullptr;
}

void VGraph::DelAdj() {
    if(vertex == nullptr)
        return;
    for (int i = 0; i < size; i++)
    {
        node* ptnode = vertex[i].next;
        while (ptnode != nullptr)
        {
            node* temp = ptnode->next;
            delete ptnode;
            ptnode = temp;
        }
    }
    delete[] vertex;
    vertex = nullptr;
}

inline void VGraph::DelMatrix() {
    DelNorMat();
    DelSprMat();
}

//------
const VGraph::node * VGraph::node::FindNode(int id) const
{
    const node* now = next;
    while (now) {
        if (now->id == id) return now;
        now = now->next;
    }
    return nullptr;
}

VGraph::node * VGraph::node::FindPrevNode(int id)
{
    node* prev = this;
    node* now = this->next;
    if (now == nullptr)
        return prev;
    while (now != nullptr) {
        if (now->id == id) return prev;
        prev = now;
        now = now->next;
    }
    return nullptr;
}
