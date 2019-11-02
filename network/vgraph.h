#ifndef VGRAPH_H
#define VGRAPH_H
#include<iostream>
#include<queue>
#include<stack>
#define INVALIDNODE -9

#ifndef INFINITY
#define INFINITY 0x7FFF
#endif

class VGraph
{
    struct node;
public:
    VGraph();
    VGraph(int g_size, double** mat);
    //VGraph(int e_size, double* spr_mat[3]);    // sparse matrix should with edge nums
    VGraph(const VGraph& G);
    // create a graph

    int VertexNum() const;          // 节点数量
    int EdgeNum() const;            // 有向边的数量
    int ConnectNum() const;         // 无向边的数量
    void Topology() const;          // 打印邻接表
    int Alone() const;              // 孤立节点数
    bool Edge(int vs, int vt) const;        // if there is an edge from vs to vt
    bool Connectivity(int vs = 0);    // vs节点出发检查连通性
    bool Connectivity(int vs, int vt) const;    // if there is a connection between vs and vt
    double Weight(int vs, int vt) const;        // the weight from vertex vs to vt
    // 检查项目

    inline bool AddDirEdge(int i, int j, double w = 1); // add i指向j，权值为weight的有向连接（仅添加一条边）
    bool AddEdge(int i, int j, double w = 1);			 // add ij间双向连接
    inline bool DelDirEdge(int i, int j);                    // delete i到j单向连接（删除所有边，所有多条重复的边）
    bool DelEdge(int i, int j);                              // delete ij间双向连接
    // 调整结构

    bool UnweightSLen(int vs);
    // the unweighted shortest path length from vertex vs to the other vertexs
    // return?
    // results were stored in every vertexs' "distance" field
    // 调用开始会将distance域置为INF
    // 计算完后需手动将邻接表的distance域重新置INFINITYTE
    bool WeightSLen(int vs);
    // 节点vs与其他各点间加权最短距离
    // return?
    // 计算后的结果保存在各节点的distance域中（调用开始会将distance域置为INF）
    double CharPathLen();           //网络的特征路径长度 这是无权的，需修改一个有权版本
    double Coefficient();			//网络的聚集系数
    double Coefficient(int id);	//某一点的聚集系数
    // 静态特性

    virtual ~VGraph();

private:
    struct node {
        int id;
        int dist;
        node* next;
        node() :id(INVALIDNODE), dist(INFINITY), next(nullptr) {}
        node(int i, node* n) :id(i), dist(INFINITY), next(n) {}
        const node* FindNode(int id) const;
        node* FindPrevNode(int id);
    };
    int size;				// total number of vertex
    int edge;               // 边数
    node* vertex;			// 图的邻接表 注意这个数组的每个元素的id域使用的都是默认值NOTANODE
    double** weight;		// 权值矩阵
    double** sparse;		// 稀疏矩阵

    int InitialDis();       //初始化distance域，返回初始化了的节点数
    int CreateAdjFromWMat();//从权值矩阵中生成邻接表（认为权值为0的连接为无连接），返回添加的边数。
                            // 两种矩阵必须被同时创建，同时删除，保持一致，故不对外提供接口
    inline void ConvertToSpr();	// convert weight matrix from normal form to sparse form
    inline void ConvertToMat();	// convert weight matrix from sparse form to normal form
    inline void DelNorMat();    // delete normal form weight matrix
    inline void DelSprMat();    // delete sparse form weight matrix
    inline void DelAdj();       // delete adj
    inline void DelMatrix();    // delete weight matrix
};

#endif // VGRAPH_H
