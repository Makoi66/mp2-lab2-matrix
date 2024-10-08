﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (this->sz == 0 || this->sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        this->pMem = new T[this->sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }


    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }


    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }


    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
    }


    ~TDynamicVector()
    {
        delete[] this->pMem;
    }


    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            delete[] this->pMem;
            this->sz = v.sz;
            this->pMem = new T[this->sz];
            std::copy(v.pMem, v.pMem + v.sz, this->pMem);
        }

        return *this;
    }


    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }


    size_t size() const noexcept { return sz; }


    T& operator[](size_t ind)
    {
        return pMem[ind];
    }


    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }


    T& at(size_t ind)
    {
        if (ind >= 0 && ind < this->sz) {
            return pMem[ind];
        }
        throw std::out_of_range("error index");
    }


    const T& at(size_t ind) const
    {
        if (ind >= 0 && ind < this->sz) {
            return pMem[ind];
        }
        throw std::out_of_range("error index");
    }


    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) {
            return 0;
        }
        else {
            for (int i = 0; i < sz; ++i) {
                if (pMem[i] != v.pMem[i]) {
                    return 0;
                }
            }
        }
        return 1;
    }


    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> result(sz);
        for (int i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] + val;
        }
        return result;
    }


    TDynamicVector operator-(double val)
    {
        TDynamicVector<T> result(sz);
        for (int i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] - val;
        }
        return result;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector<T> result(sz);
        for (int i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] * val;
        }
        return result;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw std::length_error("vector's sizes not equal");
        }
        TDynamicVector<T> result(sz);
        for (int i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] + v.pMem[i];
        }
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw std::length_error("vector's sizes not equal");
        }
        TDynamicVector<T> result(sz);
        for (int i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] - v.pMem[i];
        }
        return result;
    }
    T operator*(const TDynamicVector& v) /*noexcept(noexcept(T()))*/
    {
        if (sz != v.sz) throw std::length_error("wrong sizes");
        T sum = 0;
        for (int i = 0; i < sz; ++i) {
            sum += pMem[i] * v.pMem[i];
        }
        return sum;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (this->sz > MAX_MATRIX_SIZE) {
            throw std::overflow_error("over big size");
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    //(собственный дополнительный метод для получения размера матрицы)
    int get_size() {
        return sz;
    }

    //(собственный дополнительный метод получения исключения для неверных индексов)
    T& at(size_t ind1, size_t ind2)
    {
        if (ind1 >= 0 && ind2 >= 0 && ind1 < sz && ind2 < sz) {
            return this->pMem[ind1][ind2];
        }
        throw std::out_of_range("error index");
    }

    // сравнение friend
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) {
            return 0;
        }
        else {
            for (int i = 0; i < sz; ++i) {
                if (pMem[i] != m.pMem[i])
                    return 0;
            }
        }
        return 1;
    }

    ////(собственный дополнительный метод для оператора=)
    //bool operator!=(const TDynamicMatrix& m) const noexcept
    //{
    //    return !(*this == m);
    //}

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < pMem[i].sz; ++j) {
                result[i][j] = pMem[i][j] * val;
            }
        }
        return result;
    }


    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) {
            throw std::invalid_argument("Matrix and vector have not equal sizes");
        }

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            T sum = T();
            for (size_t j = 0; j < sz; ++j) {
                sum += pMem[i][j] * v[j];
            }
            result[i] = sum;
        }

        return result;
    }


    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw std::length_error("wrong sizes");
        }
        TDynamicMatrix result(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                result[i][j] = pMem[i][j] + m.pMem[i][j];
            }
        }
        return result;
    }


    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw std::length_error("wrong sizes")
;
        }
        TDynamicMatrix result(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                result[i][j] = pMem[i][j] - m.pMem[i][j];
            }
        }
        return result;
    }


    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw std::length_error("wrong sizes");
        }
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j < sz; ++j) {
                T sum = 0;
                for (size_t k = 0; k < sz; ++k) {
                    sum += pMem[i][k] * m[k][j];
                }
                result[i][j] = sum;
            }
        }

        return result;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
            istr >> v[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
            ostr << v[i] << endl;
        return ostr;
    }
};

#endif