#include "type_utils.hpp"
#include <iostream>

std::string type_to_string(const VarType& type) {
    switch (type.p_type) {
        case PrimitiveType::BOOL: return "bool";
        case PrimitiveType::FLOAT: return "float";
        case PrimitiveType::INT: return "int";
        case PrimitiveType::STRING: return "string";
        case PrimitiveType::VOID: return "null";
        case PrimitiveType::NOT_PRIMITIVE:
            if (type.record_name.has_value()) {
                return type.record_name.value();
            }
            return "unnamed_record";
        case PrimitiveType::REF:
            if (type.referenced_type) {
                return "ref(" + type_to_string(*type.referenced_type) + ")";
            }
            return "ref(undefined)"; // Ou "ref(invalid)"
        case PrimitiveType::UNDEFINED: return "undefined_type";
        default: return "unknown_type";
    }
}

bool are_types_compatible(const VarType& declared_type, const VarType& assigned_type) {
    if (declared_type == assigned_type) {
        return true;
    }

    if (assigned_type.p_type == PrimitiveType::VOID) {
        return true;
    }

    if (declared_type.p_type == PrimitiveType::FLOAT && 
        assigned_type.p_type == PrimitiveType::INT) {
        return true;
    }
    
    return false;
}