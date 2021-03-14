#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include<cassert>
#include<cmath>
#include<iostream>

//------------------------------- define some vector --------------------------------------------

template<class T, int n> struct vec
{
    vec() = default;
    T& operator[](const int i) {
        assert(i>=0 && i < n);
        return data[i];
    }
    T operator[](const int i) const {
        assert(i>=0 && i < n);
        return data[i];
    }
    double norm2() const {
        return (*this) * (*this);
    }
    double norm() const {
        return std::sqrt(norm2());
    }
    T data[n] = {};
};

template<class T, int n> T operator*(const vec<T, n>& lhs, const vec<T, n>& rhs) {
    T ret = 0;
    for(int i = n; i--; ret += lhs[i]*rhs[i]);
    return ret;
}


template<class T, int n> vec<T, n> operator+(const vec<T, n>& lhs, const vec<T, n>& rhs){
    vec<T, n> ret = lhs;
    for(int i = n; i--; ret[i] += rhs[i]);
    return ret;
}

template<class T, int n> vec<T, n> operator-(const vec<T, n>& lhs, const vec<T, n>& rhs){
    vec<T, n> ret = lhs;
    for(int i = n; i--; ret[i] -= rhs[i]);
    return ret;
}

template<class T, int n> vec<T, n> operator*(const double rhs, const vec<T, n>& lhs) {
    vec<T, n> ret = lhs;
    for(int i = n; i--; ret[i] *= rhs);
    return ret;
}

template<class T, int n> vec<T, n> operator*(const vec<T, n>& lhs, const double rhs) {
    vec<T, n> ret = lhs;
    for(int i = n; i--; ret[i] *= rhs);
    return ret;
}

template<class T, int n> vec<T, n> operator/(const vec<T, n>& lhs, const double rhs) {
    vec<T, n> ret = lhs;
    for(int i = n; i--; ret[i] /= rhs);
    return ret;
}

template<class T, int n> vec<T, n> operator-(const vec<T, n> v) {
    vec<T, n> ret = v;
    for(int i =n; i--; ret[i] = -ret[i]);
    return ret;
}

template<class T, int n1, int n2> vec<T, n1> embed(const vec<T, n2>& v, T fill = 1) {
    vec<T, n1> ret;
    for(int i = n1; i--; ret[i] = (i < n2 ? v[i] : fill));
    return ret;
}

template<class T, int n1, int n2> vec<T, n1> proj(const vec<T, n2>& v) {
    vec<T, n1> ret;
    for(int i = n1; i--; ret[i] = v[i]);
    return ret;
}

template<class T> vec<T, 3> cross(const vec<T, 3>& v1, const vec<T, 3>& v2) {
    return vec<T, 3>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

template<class T, int n> std::ostream& operator<<(std::ostream& out, const vec<T, n>& v) {
    for(int i=0; i < n; i++) {
        out << v[i] << " ";
    }
    return out;
}

template<class T1, class T2, int n> vec<T2, n> cast(const vec<T1, n>& v) {
    vec<T2, n> ret;
    for(int i = 0; i < n; i++) {
        ret[i] = (T2)(v[i]);
    }
    return ret;
}

template<class T> struct vec<T, 2> 
{
    vec() = default;
    vec(T X, T Y): x(X), y(Y){}
    T& operator[](const int i) {
        assert(i >=0 && i < 2);
        return i == 0 ? x : y;
    }
    T operator[](const int i) const {
       assert(i >=0 && i < 2);
       return i == 0 ? x : y;
    }
    double norm2() const { return (*this)*(*this); }
    double norm() const {return std::sqrt(norm2()); }
    vec& normalize() {
        *this = *this / norm(); 
        return *this;
    }
    T x, y;
};

template<class T> struct vec<T, 3>
{
    vec() = default;
    vec(double X, double Y, double Z): x(X), y(Y), z(Z){}
    T& operator[](const int i){
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (i == 1) ? y : z;
    }
    T operator[](const int i) const{
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (i == 1) ? y : z;
    }
    double norm2() const { return (*this)*(*this); }
    double norm() const { return std::sqrt(norm2()); }
    vec& normalize() {
        *this = *this / norm(); 
        return *this;
    }

    vec<T, 2> to2d() {
        return vec<T, 2>(x, y);
    }

    T x, y, z;
};

template<class T> struct vec<T, 4>
{
    vec() = default;
    vec(T X, T Y, T Z, T W)
        :x(X), y(Y), z(Z), w(W){}
    T operator[](const int i) const {
        assert(i >= 0 && i < 4);
        return i == 0 ? x :
                    i == 1 ? y :
                        i == 2 ? z : w;

    }

    T& operator[](const int i) {
        assert(i >= 0 && i < 4);
        return i == 0 ? x :
                    i == 1 ? y :
                        i == 2 ? z : w;

    }

    double norm2() const { return (*this)*(*this); }
    double norm() const { return std::sqrt(norm2()); }
    vec& normalize() {
        *this = *this / norm(); 
        return *this;
    }

    T x, y, z, w;
};



typedef vec<float, 2> vec2f;
typedef vec<float, 3> vec3f;
typedef vec<float, 4> vec4f;

typedef vec<int, 2> vec2i;
typedef vec<int, 3> vec3i;
typedef vec<int, 4> vec4i;

typedef vec<double, 2> vec2d;
typedef vec<double, 3> vec3d;
typedef vec<double, 4> vec4d;


//------------------------------define matrix------------------------------------

template<class T, int n> struct dt; // 计算行列式所需要的

template<class T, int nrows, int ncols> struct mat
{
    vec<T, ncols> rows[nrows] = {{}};
    mat() = default;
    vec<T, ncols>& operator[](const int idx) {
        assert(idx >= 0 && idx < nrows);
        return rows[idx];
    }
    const vec<T, ncols>& operator[](const int idx) const {
        assert(idx >= 0 && idx < nrows);
        return rows[idx];
    }

    vec<T, nrows> col(const int idx) const {
        assert(idx >= 0 && idx < ncols);
        vec<T, nrows> ret;
        for(int i = nrows; i--; ret[i] = rows[i][idx]);
        return ret;
    }

    void set_col(const int idx, const vec<T, nrows>& v) {
        assert(idx >= 0 && idx < ncols);
        for(int i = nrows; i--; rows[i][idx]=v[i]);
    }

    static mat<T, nrows, ncols> identity() {
        mat<T, nrows, ncols> ret;
        for(int i=0; i < nrows; i++) 
            for(int j = 0; j < ncols; j++)
                if(i == j) ret[i][j] = 1;
                else ret[i][j] = 0;
        return ret;
    }

    double det() const {
        return dt<T, ncols>::det(*this);
    }

    mat<T, nrows-1,ncols-1> get_minor(const int row, const int col) const {
        mat<T, nrows-1,ncols-1> ret;
        for (int i=nrows-1; i--; )
            for (int j=ncols-1;j--; ret[i][j]=rows[i<row?i:i+1][j<col?j:j+1]);
        return ret;
    }

    double cofactor(const int row, const int col) const {
        return get_minor(row,col).det()*((row+col)%2 ? -1 : 1);
    }

    mat<T, nrows,ncols> adjugate() const {
        mat<T, nrows,ncols> ret;
        for (int i=nrows; i--; )
            for (int j=ncols; j--; ret[i][j]=cofactor(i,j));
        return ret;
    }

    mat<T, nrows,ncols> invert_transpose() const {
        mat<T, nrows,ncols> ret = adjugate();
        return ret/(ret[0]*rows[0]);
    }

    mat<T, nrows,ncols> invert() const {
        return invert_transpose().transpose();
    }

    mat<T, ncols,nrows> transpose() const {
        mat<T, ncols,nrows> ret;
        for (int i=ncols; i--; ret[i]=this->col(i));
        return ret;
    }

};

template<class T, int nrows,int ncols> vec<T, nrows> operator*(const mat<T, nrows,ncols>& lhs, const vec<T, ncols>& rhs) {
    vec<T, nrows> ret;
    for (int i=nrows; i--; ret[i]=lhs[i]*rhs);
    return ret;
}

template<class T, int R1,int C1,int C2>mat<T, R1,C2> operator*(const mat<T, R1,C1>& lhs, const mat<T, C1,C2>& rhs) {
    mat<T, R1,C2> result;
    for (int i=R1; i--; )
        for (int j=C2; j--; result[i][j]=lhs[i]*rhs.col(j));
    return result;
}

template<class T, int nrows,int ncols>mat<T, nrows,ncols> operator*(const mat<T, nrows,ncols>& lhs, const double& val) {
    mat<T, nrows,ncols> result;
    for (int i=nrows; i--; result[i] = lhs[i]*val);
    return result;
}

template<class T, int nrows,int ncols>mat<T, nrows,ncols> operator/(const mat<T, nrows,ncols>& lhs, const double& val) {
    mat<T, nrows,ncols> result;
    for (int i=nrows; i--; result[i] = lhs[i]/val);
    return result;
}

template<class T, int nrows,int ncols>mat<T, nrows, ncols> operator+(const mat<T, nrows,ncols>& lhs, const mat<T, nrows,ncols>& rhs) {
    mat<T, nrows,ncols> result;
    for (int i=nrows; i--; )
        for (int j=ncols; j--; result[i][j]=lhs[i][j]+rhs[i][j]);
    return result;
}

template<class T, int nrows,int ncols>mat<T, nrows,ncols> operator-(const mat<T, nrows,ncols>& lhs, const mat<T, nrows,ncols>& rhs) {
    mat<T, nrows,ncols> result;
    for (int i=nrows; i--; )
        for (int j=ncols; j--; result[i][j]=lhs[i][j]-rhs[i][j]);
    return result;
}

template<class T, int nrows,int ncols> std::ostream& operator<<(std::ostream& out, const mat<T, nrows,ncols>& m) {
    for (int i=0; i<nrows; i++) out << m[i] << std::endl;
    return out;
}

template<class T, int n> struct dt {
    static double det(const mat<T, n, n>& src) {
        double ret = 0;
        for (int i=n; i--; ret += src[0][i]*src.cofactor(0,i));
        return ret;
    }
};

template<class T> struct dt<T, 1> {
    static double det(const mat<T, 1,1>& src) {
        return src[0][0];
    }
};

typedef mat<double, 4, 4> mat4d;
typedef mat<float, 4, 4> mat4f;
typedef mat<int, 4, 4> mat4i;

typedef mat<double, 3, 3> mat3d;
typedef mat<float, 3, 3> mat3f;
typedef mat<int, 3, 3> mat3i;

typedef mat<double, 2, 2> mat2d;
typedef mat<float, 2, 2> mat2f;
typedef mat<int, 2, 2> mat2i;


#endif