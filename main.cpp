#include <iostream>
#include "dtc/VarMath.h"

void printType(const Type& t) {
    // if basicType
    if (auto b = std::get_if<BasicType>(&t.type)) {
        if (b->floating) {
            std::cout << std::dec <<  "f" << (b->bytes * 8);
        } else {
            std::cout << std::dec << (b->sign ? "i" : "u") << (b->bytes * 8);
        }
    } else if (auto s = std::get_if<StructType>(&t.type)) {
        std::cout << "struct {";
        for (size_t i = 0; i < s->types.size(); i++) {
            printType(s->types[i]);
            if (i != s->types.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}";
    }
    for (uint64_t i = 0; i < t.deref_count; i++) {
        std::cout << "*";
    }
}

template<typename T>
T primitive(Variable v, size_t index= 0) {
    // if template type size is not the same as the variable type size
    // err
    if (sizeof(T) != t_sizeof(v.type)) {
        printType(v.type);
        std::cout << std::endl;
        throw std::runtime_error("primitive type size mismatch");
    }
    return *(T*)(v.getdata(index));
}

void printVariable(Variable v, bool done=true) {
    if (v.type.deref_count > 0) {
        if (v.data.size() != sizeof(void*)) {
            throw std::runtime_error("pointer size mismatch");
        }
        printType(v.type);
        std::cout << "(0x" << std::hex << *(void**)v.data.data() << ")";
        if (done) {
            std::cout << std::endl;
        }
        return;
    }
    if (v.is_basic()) {
        printType(v.type);
        std::cout << "(";
        if (auto s = std::get_if<BasicType>(&v.type.type)) {
            if (s->floating) {
                if (s->bytes == 4) {
                    std::cout << std::dec << primitive<f32>(v);
                } else if (s->bytes == 8) {
                    std::cout << std::dec << primitive<f64>(v);
                }
            } else {
                if (s->sign) {
                    if (s->bytes == 1) {
                        std::cout << (int)primitive<i8>(v);
                    } else if (s->bytes == 2) {
                        std::cout << primitive<i16>(v);
                    } else if (s->bytes == 4) {
                        std::cout << primitive<i32>(v);
                    } else if (s->bytes == 8) {
                        std::cout << primitive<i64>(v);
                    }
                } else {
                    if (s->bytes == 1) {
                        std::cout << (int)primitive<u8>(v);
                    } else if (s->bytes == 2) {
                        std::cout << primitive<u16>(v);
                    } else if (s->bytes == 4) {
                        std::cout << primitive<u32>(v);
                    } else if (s->bytes == 8) {
                        std::cout << primitive<u64>(v);
                    }
                }
            }
        } else {
            throw std::runtime_error("variable is not basic type");
        }
        std::cout << ")";
    } else {
        if (auto s = std::get_if<StructType>(&v.type.type)) {
            std::cout << "struct";
            for (uint64_t i = 0; i < v.type.deref_count; i++) {
                std::cout << "*";
            }
            std::cout << " {";
            for (size_t i = 0; i < s->types.size(); i++) {
                Variable sub = v.getsub(i);
                printVariable(sub, false);
                if (i != s->types.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "}";
        } else {
            throw std::runtime_error("variable is not struct type");
        }
    }
    if (done) {
        std::cout << std::endl;
    }
}


int main() {
//    Variable v = (i8)0x12;
//    Variable v2 = (u16)0x3412;
//    printVariable(v);
//    printVariable(v2);
//
//    Type st = {t_i8, t_u16};
//    Variable s = {v, v2}; // creates the struct type {i8, u16} and creates a variable of that type
//    printVariable(s);
//
//    Variable out = var_add_i(s.getsub(0), s.getsub(1));
//    printVariable(out);
    i8 a = 0x12;
    u32 b = 0x12434;
    auto c= b - a;

    Variable va = a;
    Variable vb = b;
    Variable vc = var_sub_i(b, a);

    printVariable(vc);
    std::cout << c << std::endl;

    return 0;
}
