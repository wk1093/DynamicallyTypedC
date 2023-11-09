#pragma once
#ifndef DTC_VARIABLE_H
#define DTC_VARIABLE_H

#include "Type.h"

struct Variable {
    Type type{};
    std::vector<std::byte> data{};

    Variable() = default;
    Variable(int8_t a);
    Variable(uint8_t a);
    Variable(int16_t a);
    Variable(uint16_t a);
    Variable(int32_t a);
    Variable(uint32_t a);
    Variable(int64_t a);
    Variable(uint64_t a);
    Variable(float a);
    Variable(double a);
    Variable(Variable* a);
    Variable(void* a);
    Variable(std::vector<Variable> vars);
    Variable(std::initializer_list<Variable> vars);

    Variable(const Type& t, std::vector<std::byte> data);

    ~Variable() = default;

    [[nodiscard]] bool is_basic() const;

    std::byte* getdata(size_t i=0);
    Variable getsub(size_t i=0);
};

Variable new_i8(int8_t val);
Variable new_u8(uint8_t val);
Variable new_i16(int16_t val);
Variable new_u16(uint16_t val);
Variable new_i32(int32_t val);
Variable new_u32(uint32_t val);
Variable new_i64(int64_t val);
Variable new_u64(uint64_t val);

Variable new_f32(float val);
Variable new_f64(double val);

Variable new_ptr(void* p);

Variable new_varptr(Variable* p);

Variable new_bool(bool val);

Variable new_struct(std::vector<Variable> vars);


#endif //DTC_VARIABLE_H
