//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// range.template.h file to make changes.

#ifndef PXR_BASE_GF_RANGE3F_H
#define PXR_BASE_GF_RANGE3F_H

/// \file gf/range3f.h
/// \ingroup group_gf_BasicGeometry

#include "pxr/pxr.h"

#include "pxr/base/gf/api.h"
#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/traits.h"

#include <boost/functional/hash.hpp>

#include <cfloat>
#include <cstddef>
#include <iosfwd>

PXR_NAMESPACE_OPEN_SCOPE

class GfRange3d;
class GfRange3f;

template <>
struct GfIsGfRange<class GfRange3f> { static const bool value = true; };

/// \class GfRange3f
/// \ingroup group_gf_BasicGeometry
///
/// Basic type: 3-dimensional floating point range.
///
/// This class represents a 3-dimensional range (or interval) All
/// operations are component-wise and conform to interval mathematics. An
/// empty range is one where max < min.
/// The default empty is [FLT_MAX,-FLT_MAX]
class GfRange3f
{
public:

    /// Helper typedef.
    typedef GfVec3f MinMaxType;

    static const size_t dimension = GfVec3f::dimension;
    typedef GfVec3f::ScalarType ScalarType;

    /// Sets the range to an empty interval
    // TODO check whether this can be deprecated.
    void inline SetEmpty() {
        _min[0] = _min[1] = _min[2] =  FLT_MAX;
        _max[0] = _max[1] = _max[2] = -FLT_MAX;
    }

    /// The default constructor creates an empty range.
    GfRange3f() {
        SetEmpty();
    }

    /// This constructor initializes the minimum and maximum points.
    GfRange3f(const GfVec3f &min, const GfVec3f &max)
        : _min(min), _max(max)
    {
    }

    /// Returns the minimum value of the range.
    const GfVec3f &GetMin() const { return _min; }

    /// Returns the maximum value of the range.
    const GfVec3f &GetMax() const { return _max; }

    /// Returns the size of the range.
    GfVec3f GetSize() const { return _max - _min; }

    /// Returns the midpoint of the range, that is, 0.5*(min+max).
    /// Note: this returns zero in the case of default-constructed ranges,
    /// or ranges set via SetEmpty().
    GfVec3f GetMidpoint() const {
        return static_cast<ScalarType>(0.5) * _min
               + static_cast<ScalarType>(0.5) * _max;
    }

    /// Sets the minimum value of the range.
    void SetMin(const GfVec3f &min) { _min = min; }

    /// Sets the maximum value of the range.
    void SetMax(const GfVec3f &max) { _max = max; }

    /// Returns whether the range is empty (max < min).
    bool IsEmpty() const {
        return _min[0] > _max[0] || _min[1] > _max[1] || _min[2] > _max[2];
    }

    /// Modifies the range if necessary to surround the given value.
    /// \deprecated Use UnionWith() instead.
    void ExtendBy(const GfVec3f &point) { UnionWith(point); }

    /// Modifies the range if necessary to surround the given range.
    /// \deprecated Use UnionWith() instead.
    void ExtendBy(const GfRange3f &range) { UnionWith(range); }

    /// Returns true if the \p point is located inside the range. As with all
    /// operations of this type, the range is assumed to include its extrema.
    bool Contains(const GfVec3f &point) const {
        return (point[0] >= _min[0] && point[0] <= _max[0]
             && point[1] >= _min[1] && point[1] <= _max[1]
             && point[2] >= _min[2] && point[2] <= _max[2]);
    }

    /// Returns true if the \p range is located entirely inside the range. As
    /// with all operations of this type, the ranges are assumed to include
    /// their extrema.
    bool Contains(const GfRange3f &range) const {
        return Contains(range._min) && Contains(range._max);
    }

    /// Returns true if the \p point is located inside the range. As with all
    /// operations of this type, the range is assumed to include its extrema.
    /// \deprecated Use Contains() instead.
    bool IsInside(const GfVec3f &point) const {
        return Contains(point);
    }

    /// Returns true if the \p range is located entirely inside the range. As
    /// with all operations of this type, the ranges are assumed to include
    /// their extrema.
    /// \deprecated Use Contains() instead.
    bool IsInside(const GfRange3f &range) const {
        return Contains(range);
    }

    /// Returns true if the \p range is located entirely outside the range. As
    /// with all operations of this type, the ranges are assumed to include
    /// their extrema.
    bool IsOutside(const GfRange3f &range) const {
        return ((range._max[0] < _min[0] || range._min[0] > _max[0])
             || (range._max[1] < _min[1] || range._min[1] > _max[1])
             || (range._max[2] < _min[2] || range._min[2] > _max[2]));
    }

    /// Returns the smallest \c GfRange3f which contains both \p a and \p b.
    static GfRange3f GetUnion(const GfRange3f &a, const GfRange3f &b) {
        GfRange3f res = a;
        _FindMin(res._min,b._min);
        _FindMax(res._max,b._max);
        return res;
    }

    /// Extend \p this to include \p b.
    const GfRange3f &UnionWith(const GfRange3f &b) {
        _FindMin(_min,b._min);
        _FindMax(_max,b._max);
        return *this;
    }

    /// Extend \p this to include \p b.
    const GfRange3f &UnionWith(const GfVec3f &b) {
        _FindMin(_min,b);
        _FindMax(_max,b);
        return *this;
    }

    /// Returns the smallest \c GfRange3f which contains both \p a and \p b
    /// \deprecated Use GetUnion() instead.
    static GfRange3f Union(const GfRange3f &a, const GfRange3f &b) {
        return GetUnion(a, b);
    }

    /// Extend \p this to include \p b.
    /// \deprecated Use UnionWith() instead.
    const GfRange3f &Union(const GfRange3f &b) {
        return UnionWith(b);
    }

    /// Extend \p this to include \p b.
    /// \deprecated Use UnionWith() instead.
    const GfRange3f &Union(const GfVec3f &b) {
        return UnionWith(b);
    }

    /// Returns a \c GfRange3f that describes the intersection of \p a and \p b.
    static GfRange3f GetIntersection(const GfRange3f &a, const GfRange3f &b) {
        GfRange3f res = a;
        _FindMax(res._min,b._min);
        _FindMin(res._max,b._max);
        return res;
    }

    /// Returns a \c GfRange3f that describes the intersection of \p a and \p b.
    /// \deprecated Use GetIntersection() instead.
    static GfRange3f Intersection(const GfRange3f &a, const GfRange3f &b) {
        return GetIntersection(a, b);
    }

    /// Modifies this range to hold its intersection with \p b and returns the
    /// result
    const GfRange3f &IntersectWith(const GfRange3f &b) {
        _FindMax(_min,b._min);
        _FindMin(_max,b._max);
        return *this;
    }

    /// Modifies this range to hold its intersection with \p b and returns the
    /// result.
    /// \deprecated Use IntersectWith() instead.
    const GfRange3f &Intersection(const GfRange3f &b) {
        return IntersectWith(b);
    }

    /// unary sum.
    GfRange3f &operator +=(const GfRange3f &b) {
        _min += b._min;
        _max += b._max;
        return *this;
    }

    /// unary difference.
    GfRange3f &operator -=(const GfRange3f &b) {
        _min -= b._max;
        _max -= b._min;
        return *this;
    }

    /// unary multiply.
    GfRange3f &operator *=(double m) {
        if (m > 0) {
            _min *= m;
            _max *= m;
        } else {
            GfVec3f tmp = _min;
            _min = _max * m;
            _max = tmp * m;
        }
        return *this;
    }

    /// unary division.
    GfRange3f &operator /=(double m) {
        return *this *= (1.0 / m);
    }

    /// binary sum.
    GfRange3f operator +(const GfRange3f &b) const {
        return GfRange3f(_min + b._min, _max + b._max);
    }


    /// binary difference.
    GfRange3f operator -(const GfRange3f &b) const {
        return GfRange3f(_min - b._max, _max - b._min);
    }

    /// scalar multiply.
    friend GfRange3f operator *(double m, const GfRange3f &r) {
        return (m > 0 ? 
            GfRange3f(r._min*m, r._max*m) : 
            GfRange3f(r._max*m, r._min*m));
    }

    /// scalar multiply.
    friend GfRange3f operator *(const GfRange3f &r, double m) {
        return (m > 0 ? 
            GfRange3f(r._min*m, r._max*m) : 
            GfRange3f(r._max*m, r._min*m));
    }

    /// scalar divide.
    friend GfRange3f operator /(const GfRange3f &r, double m) {
        return r * (1.0 / m);
    }

    /// hash.
    friend inline size_t hash_value(const GfRange3f &r) {
        size_t h = 0;
        boost::hash_combine(h, r._min);
        boost::hash_combine(h, r._max);
        return h;
    }

    /// The min and max points must match exactly for equality.
    bool operator ==(const GfRange3f &b) const {
        return (_min == b._min && _max == b._max);
    }

    bool operator !=(const GfRange3f &b) const {
        return !(*this == b);
    }

    /// Compare this range to a GfRange3d.
    ///
    /// The values must match exactly and it does exactly what you might
    /// expect when comparing float and double values.
    GF_API inline bool operator ==(const GfRange3d& other) const;
    GF_API inline bool operator !=(const GfRange3d& other) const;

    /// Compute the squared distance from a point to the range.
    GF_API
    double GetDistanceSquared(const GfVec3f &p) const;

    /// Returns the ith corner of the range, in the following order:
    /// LDB, RDB, LUB, RUB, LDF, RDF, LUF, RUF. Where L/R is left/right,
    /// D/U is down/up, and B/F is back/front.
    GF_API
    GfVec3f GetCorner(size_t i) const;

    /// Returns the ith octant of the range, in the following order:
    /// LDB, RDB, LUB, RUB, LDF, RDF, LUF, RUF. Where L/R is left/right,
    /// D/U is down/up, and B/F is back/front.
    GF_API
    GfRange3f GetOctant(size_t i) const;

    /// The unit cube.
    GF_API
    static const GfRange3f UnitCube;

  private:
    /// Minimum and maximum points.
    GfVec3f _min, _max;

    /// Extends minimum point if necessary to contain given point.
    static void _FindMin(GfVec3f &dest, const GfVec3f &point) {
        if (point[0] < dest[0]) dest[0] = point[0];
        if (point[1] < dest[1]) dest[1] = point[1];
        if (point[2] < dest[2]) dest[2] = point[2];
    }

    /// Extends maximum point if necessary to contain given point.
    static void _FindMax(GfVec3f &dest, const GfVec3f &point) {
        if (point[0] > dest[0]) dest[0] = point[0];
        if (point[1] > dest[1]) dest[1] = point[1];
        if (point[2] > dest[2]) dest[2] = point[2];
    }
};

/// Output a GfRange3f.
/// \ingroup group_gf_DebuggingOutput
GF_API std::ostream& operator<<(std::ostream &, GfRange3f const &);

PXR_NAMESPACE_CLOSE_SCOPE
#include "pxr/base/gf/range3d.h"
PXR_NAMESPACE_OPEN_SCOPE

inline bool
GfRange3f::operator ==(const GfRange3d& other) const {
    return _min == GfVec3f(other.GetMin()) &&
           _max == GfVec3f(other.GetMax());
}

inline bool
GfRange3f::operator !=(const GfRange3d& other) const {
    return !(*this == other);
}


PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_BASE_GF_RANGE3F_H
