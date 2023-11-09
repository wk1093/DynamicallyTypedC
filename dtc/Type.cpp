#include "Type.h"

BasicType::BasicType(bool sign, uint64_t bytes) : sign(sign), bytes(bytes) {}

BasicType::BasicType(uint64_t bytes, bool floating) : bytes(bytes), floating(floating), sign(true) {}

StructType::StructType(std::vector<Type> types) : types(std::move(types)) {}

StructType::StructType(std::initializer_list<Type> types) : types(types) {}

Type::Type(BasicType type, uint64_t deref) : type(type), deref_count(deref) {}

Type::Type(StructType type, uint64_t deref) : type(type), deref_count(deref) {}

Type::Type(std::initializer_list<Type> types, uint64_t deref) : type(StructType(types)), deref_count(deref) {}

bool Type::operator==(const Type &other) const {
    if (deref_count != other.deref_count) return false;
    if (type.index() != other.type.index()) return false;
    if (auto b = std::get_if<BasicType>(&type)) {
        if (auto b2 = std::get_if<BasicType>(&other.type)) {
            return b->sign == b2->sign && b->bytes == b2->bytes && b->floating == b2->floating;
        }
        return false;
    } else if (auto s = std::get_if<StructType>(&type)) {
        if (auto s2 = std::get_if<StructType>(&other.type)) {
            if (s->types.size() != s2->types.size()) return false;
            for (size_t i = 0; i < s->types.size(); i++) {
                if (s->types[i] != s2->types[i]) return false;
            }
            return true;
        }
        return false;
    }
    return false;
}

bool Type::operator!=(const Type &other) const {
    return !(*this == other);
}

Type new_struct_type(std::vector<Type> types) {
    return Type(StructType(std::move(types)));
}

uint64_t t_sizeof(Type t) {
    if (t.deref_count > 0) {
        return sizeof(void*);
    } else if (auto b = std::get_if<BasicType>(&t.type)) {
        return b->bytes;
    } else if (auto s = std::get_if<StructType>(&t.type)) {
        uint64_t size = 0;
        for (auto& tp : s->types) {
            size += t_sizeof(tp);
        }
        return size;
    }
    return 0;
}
