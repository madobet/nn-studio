#ifndef VMATRIX_H
#define VMATRIX_H


class VMatrix
{
public:
    VMatrix();
    VMatrix(int x, int y);
    VMatrix(int x, int y, int z);
    ~VMatrix();
    int DisplayConsole();
private:
    int m, n, q;
    double** data_2;
    double*** data_3;
};

#endif // VMATRIX_H
