#include "VarMath.h"

// if a.type.type is not BasicType, throw error
// if b.type.type is not BasicType, throw error
// allows adding vars of different size
// allows adding vars of different sign
// if either are signed then the result is signed
// if either are floating then err
// largest type size is final size UNLESS that type is unsigned and the other is signed in which case the result is unsigned
// ex i8 + u16 = u16
// ex i8 + i16 = i16
// ex u8 + i32 = i32
// ex u8 + u32 = u32
// ...

Variable var_add_i(Variable a, Variable b) {
    if (a.is_basic() && b.is_basic()) {
        auto a2 = std::get<BasicType>(a.type.type);
        auto b2 = std::get<BasicType>(b.type.type);

        if (a2.floating || b2.floating) {
            throw std::runtime_error("Cannot add floating types");
        }

        uint64_t size = std::max(a2.bytes, b2.bytes);
        bool sign = a2.sign || b2.sign;
        if (sign && a2.sign != b2.sign) {
            if ((!a2.sign && a2.bytes == size) || (!b2.sign && b2.bytes == size)) {
                sign = false;
            }
        }
        Variable res = Variable{Type(BasicType(sign, size)), std::vector<std::byte>(size)};
        uint64_t carry = 0;
        for (size_t i = 0; i < size; i++) {
            uint64_t a_byte = i < a.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(a.data[i])) : 0;
            uint64_t b_byte = i < b.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(b.data[i])) : 0;
            uint64_t sum = a_byte + b_byte + carry;
            carry = sum >> 8;
            res.data[i] = std::byte(sum);
        }
        return res;
    } else {
        throw std::runtime_error("Cannot add non-int types");
    }
}

Variable var_sub_i(Variable a, Variable b) {
    if (a.is_basic() && b.is_basic()) {
        auto a2 = std::get<BasicType>(a.type.type);
        auto b2 = std::get<BasicType>(b.type.type);

        if (a2.floating || b2.floating) {
            throw std::runtime_error("Cannot subtract floating types");
        }

        uint64_t size = std::max(a2.bytes, b2.bytes);
        bool sign = a2.sign || b2.sign;
        if (sign && a2.sign != b2.sign) {
            if ((!a2.sign && a2.bytes == size) || (!b2.sign && b2.bytes == size)) {
                sign = false;
            }
        }
        Variable res = Variable{Type(BasicType(sign, size)), std::vector<std::byte>(size)};
        uint64_t carry = 0;
        for (size_t i = 0; i < size; i++) {
            uint64_t a_byte = i < a.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(a.data[i])) : 0;
            uint64_t b_byte = i < b.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(b.data[i])) : 0;
            uint64_t diff = a_byte - b_byte - carry;
            carry = diff >> 8;
            res.data[i] = std::byte(diff);
        }
        return res;
    } else {
        throw std::runtime_error("Cannot subtract non-int types");
    }
}

Variable var_mul_i(Variable a, Variable b) {
    if (a.is_basic() && b.is_basic()) {
        auto a2 = std::get<BasicType>(a.type.type);
        auto b2 = std::get<BasicType>(b.type.type);

        if (a2.floating || b2.floating) {
            throw std::runtime_error("Cannot multiply floating types");
        }

        uint64_t size = std::max(a2.bytes, b2.bytes);
        bool sign = a2.sign || b2.sign;
        if (sign && a2.sign != b2.sign) {
            if ((!a2.sign && a2.bytes == size) || (!b2.sign && b2.bytes == size)) {
                sign = false;
            }
        }
        Variable res = Variable{Type(BasicType(sign, size)), std::vector<std::byte>(size)};
        uint64_t carry = 0;
        for (size_t i = 0; i < size; i++) {
            uint64_t a_byte = i < a.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(a.data[i])) : 0;
            uint64_t b_byte = i < b.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(b.data[i])) : 0;
            uint64_t prod = a_byte * b_byte + carry;
            carry = prod >> 8;
            res.data[i] = std::byte(prod);
        }
        return res;
    } else {
        throw std::runtime_error("Cannot multiply non-int types");
    }
}

Variable var_div_i(Variable a, Variable b) {
    if (a.is_basic() && b.is_basic()) {
        auto a2 = std::get<BasicType>(a.type.type);
        auto b2 = std::get<BasicType>(b.type.type);

        if (a2.floating || b2.floating) {
            throw std::runtime_error("Cannot divide floating types");
        }

        uint64_t size = std::max(a2.bytes, b2.bytes);
        bool sign = a2.sign || b2.sign;
        if (sign && a2.sign != b2.sign) {
            if ((!a2.sign && a2.bytes == size) || (!b2.sign && b2.bytes == size)) {
                sign = false;
            }
        }
        Variable res = Variable{Type(BasicType(sign, size)), std::vector<std::byte>(size)};
        uint64_t carry = 0;
        for (size_t i = 0; i < size; i++) {
            uint64_t a_byte = i < a.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(a.data[i])) : 0;
            uint64_t b_byte = i < b.data.size() ? static_cast<uint64_t>(std::to_integer<uint8_t>(b.data[i])) : 0;
            uint64_t quot = a_byte / b_byte + carry;
            carry = quot >> 8;
            res.data[i] = std::byte(quot);
        }
        return res;
    } else {
        throw std::runtime_error("Cannot divide non-int types");
    }
}