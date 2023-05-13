//
// Created by xOx on 2023/3/27.
//

#ifndef TESTME_CLASSUTILS_H
#define TESTME_CLASSUTILS_H

/// @brief Internal helper class that prevent copy constructor for class
///
/// @detail When using this class simply inherit it privately
class Nocopy {
private:
    Nocopy(const Nocopy&);
    Nocopy& operator=(const Nocopy&);
};


/// @brief Internal helper class that makes all default constructors private.
///
/// @detail This prevents initializing class making it static unless an explicit constructor is declared.
/// When using this class simply inherit it privately
class StaticClass {
private:
    StaticClass(void);
    StaticClass(const StaticClass&);
    StaticClass& operator=(const StaticClass&);
};






#endif //TESTME_CLASSUTILS_H
