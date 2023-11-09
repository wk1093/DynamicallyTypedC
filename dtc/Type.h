#pragma once
#ifndef _TYPE_H
#define _TYPE_H

#include <utility>
#include <vector>
#include <cstdint>
#include <variant>
#include <stdexcept>
#include <iostream>

struct BasicType {
    bool sign=true; // true if signed, false if unsigned
    bool floating=false;
    uint64_t bytes=0;

    BasicType() = default;
    BasicType(bool sign, uint64_t bytes);
    BasicType(uint64_t bytes, bool floating);
    ~BasicType() = default;
}; // basically just an integer of variable size
struct Type;
struct StructType {
    std::vector<Type> types{}; // a struct is basically just a bunch of types together

    StructType() = default;
    explicit StructType(std::vector<Type> types);
    StructType(std::initializer_list<Type> types);
    ~StructType() = default;
};
struct Type {
    uint64_t deref_count = 0;
    std::variant<BasicType, StructType> type{};

    Type() = default;
    explicit Type(BasicType type, uint64_t deref=0);
    explicit Type(StructType type, uint64_t deref=0);
    Type(std::initializer_list<Type> types, uint64_t deref=0);

    ~Type() = default;

    bool operator==(const Type& other) const;

    bool operator!=(const Type& other) const;
};

const auto t_i8 = Type(BasicType(true, 1));
const auto t_u8 = Type(BasicType(false, 1));
const auto t_i16 = Type(BasicType(true, 2));
const auto t_u16 = Type(BasicType(false, 2));
const auto t_i32 = Type(BasicType(true, 4));
const auto t_u32 = Type(BasicType(false, 4));
const auto t_i64 = Type(BasicType(true, 8));
const auto t_u64 = Type(BasicType(false, 8));
const auto t_f32 = Type(BasicType(4, true));
const auto t_f64 = Type(BasicType(8, true));
const auto t_bool = Type(BasicType(false, 1));
const auto t_voidptr = Type(BasicType(false, 0), 1);
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

Type new_struct_type(std::vector<Type> types);

uint64_t t_sizeof(Type t);
#endif //_TYPE_H
