#include "mateng.h"

MatEng::MatEng()
{
    ClearMatBuff();
    EngineInitial();
}

MatEng::MatEng(const char* work_directory)
{
    std::string dir = "cd \'";
    dir = dir + work_directory;
    dir = dir + "\'";
    ClearMatBuff();
    EngineInitial();
    engEvalString(ep, dir.c_str());
}

MatEng::MatEng(std::string& work_directory)
{
    std::string dir = "cd \'";
    dir = dir + work_directory;
    dir = dir + "\'";
    ClearMatBuff();
    EngineInitial();
    engEvalString(ep, dir.c_str());
}

MatEng::~MatEng()
{
    ClearMatBuff();
    engClose(ep);
}

bool MatEng::Exe(const char *cmd)
{
    return engEvalString(ep, cmd)?false:true;
}

bool MatEng::PutVar(const char *name, const int i)
{
    mxArray *mx =mxCreateDoubleMatrix(1,1,mxREAL);
    double* real =
    engPutVariable(ep,name,);
}

inline void MatEng::ClearMatBuff()
// clear MATLAB output buffer
{
    for(int i = 0;i< buff_size; i++)
        mat_buffer[i] = 0;
}

void MatEng::EngineIintial()
// MATLAB engine initialization
{
    if(ep = engOpen(NULL))
        engOutputBuffer(ep, mat_buffer, buff_size);
    else
        ep = nullptr;
    // open engine
    engSetVisible(ep,false);
    // hide engine
}
