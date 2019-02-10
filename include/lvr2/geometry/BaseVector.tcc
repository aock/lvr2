/**
 * Copyright (c) 2018, University Osnabrück
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University Osnabrück nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL University Osnabrück BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * BaseVector.tcc
 *
 *  @date 02.06.2017
 *  @author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 */

#include <cmath>
#include <lvr2/util/Panic.hpp>

namespace lvr2
{

// ========================================================================
// === Named operations
// ========================================================================

template <typename CoordT>
CoordT BaseVector<CoordT>::length() const
{
    return sqrt(x * x + y * y + z * z);
}

template <typename CoordT>
CoordT BaseVector<CoordT>::length2() const
{
    return x * x + y * y + z * z;
}

template <typename CoordT>
CoordT BaseVector<CoordT>::distance(const BaseVector &other) const
{
    return (*this - other).length();
}

template <typename CoordT>
CoordT BaseVector<CoordT>::distance2(const BaseVector &other) const
{
    return (*this - other).length2();
}

template <typename CoordT>
BaseVector<CoordT> BaseVector<CoordT>::cross(const BaseVector &other) const
{
    auto tx = y * other.z - z * other.y;
    auto ty = z * other.x - x * other.z;
    auto tz = x * other.y - y * other.x;

    return BaseVector<CoordT>(tx, ty, tz);
}

template <typename CoordT>
CoordT BaseVector<CoordT>::dot(const BaseVector &other) const
{
    return x * other.x + y * other.y + z * other.z;
}


// ========================================================================
// === Operator overloads
// ========================================================================

template <typename CoordT>
BaseVector<CoordT> BaseVector<CoordT>::operator*(const CoordT &scale) const
{
    return BaseVector(*this) *= scale;
}

template <typename CoordT>
BaseVector<CoordT> BaseVector<CoordT>::operator/(const CoordT &scale) const
{
    return BaseVector(*this) /= scale;
}

template <typename CoordT>
BaseVector<CoordT>& BaseVector<CoordT>::operator*=(const CoordT &scale)
{
    x *= scale;
    y *= scale;
    z *= scale;

    return *this;
}

template <typename CoordT>
BaseVector<CoordT>& BaseVector<CoordT>::operator/=(const CoordT &scale)
{
    x /= scale;
    y /= scale;
    z /= scale;

    return *this;
}

template <typename CoordT>
BaseVector<CoordT> BaseVector<CoordT>::operator+(const BaseVector &other) const
{
    return BaseVector(*this) += other;
}

template <typename CoordT>
BaseVector<CoordT> BaseVector<CoordT>::operator-(const BaseVector &other) const
{
    return BaseVector(*this) -= other;
}

template <typename CoordT>
BaseVector<CoordT>& BaseVector<CoordT>::operator+=(const BaseVector<CoordT> &other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

template <typename CoordT>
BaseVector<CoordT>& BaseVector<CoordT>::operator-=(const BaseVector<CoordT> &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

template <typename CoordT>
bool BaseVector<CoordT>::operator==(const BaseVector &other) const
{
    return x == other.x
        && y == other.y
        && z == other.z;
}
template <typename CoordT>
bool BaseVector<CoordT>::operator!=(const BaseVector &other) const
{
    return !((*this) == other);
}

template<typename CoordT>
CoordT BaseVector<CoordT>::operator*(const BaseVector<CoordType> &other) const
{
    return dot(other);
}

template<typename CoordT>
CoordT BaseVector<CoordT>::operator[](const unsigned& index) const
{
    switch (index)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            panic("Access index out of range.");
            return x; // return statement to suppress clang warning
    }
}

template<typename CoordT>
CoordT& BaseVector<CoordT>::operator[](const unsigned& index)
{
    switch (index)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            panic("Access index out of range.");
            return x; // return statement to suppress clang warning
    }
}

} // namespace lvr2

namespace std
{
    /**
     * @class hash
     * Hash specialisation for vector class
     */
template<typename CoordT>
class hash<lvr2::BaseVector<CoordT>>
{
public:
    size_t operator()(const lvr2::BaseVector<CoordT>& s) const
    {
        size_t h1 = std::hash<CoordT>()(s.x);
        size_t h2 = std::hash<CoordT>()(s.y);
        size_t h3 = std::hash<CoordT>()(s.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
}
