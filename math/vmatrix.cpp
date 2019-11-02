#include "vmatrix.h"

VMatrix::VMatrix()
    :m(0),n(0),q(0),data_2(nullptr),data_3(nullptr)
{
}

VMatrix::VMatrix(int x, int y)
    :m(x),n(y),q(0),data_3(nullptr)
{
    data_2 = new double*[m];	//if "new" fails? 需要添加错误处理
    for (int i = 0; i < m; i++)
        data_2[i] = new double[n];
}

VMatrix::VMatrix(int x, int y, int z)
    :m(x),n(y),q(z),data_2(nullptr)
{
    data_3 = new double**[q];
    for (int i = 0; i < q; i++)
    {
        data_3[i] = new double*[m];
        for (int j = 0; j < m; j++)
            data_3[i][j] = new double[n];
    }//程序中的3维的建设顺序：第3维+行数+列数；习惯上的三维顺序行数+列数+第3维，注意区分
}

VMatrix::~VMatrix(){
    if (data_2){
        for (int i = 0; i < m; i++)
            delete[] data_2[i];
        delete[] data_2;
    }
    if (data_3){
        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < m; j++)
                delete[] data_3[i][j];
            delete[] data_3[i];
        }
        delete[] data_3;
    }
}
