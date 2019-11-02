#ifndef MATENG_H
#define MATENG_H

#include "engine.h"	// MATLAB headfile
#include <string>

class MatEng
{
public:
    MatEng();
    MatEng(const char* work_directory);
    MatEng(std::string& work_directory);
    ~MatEng();

    bool Exe(const char* cmd);
    bool PutVar(const char *name, const int i);
    bool PutVar(const char *name, const double d);
    bool PutVar(const char *name, const double *vector, int m);
    bool PutVar(const char *name, const double *vector, int m, int n);
    bool DelVar(const char *name);
    void ClearAll();
    int GetInt(const char *name);
    const double* GetDouble(const char *name);
private:
    static const int buff_size = 1024;
    char mat_buffer[buff_size];  // MATLAB output buffer
    Engine* ep;

    bool ExistVar(const char *name);
    inline void ClearMatBuff();
    inline void EngineInitial();
};

#endif // MATENG_H
