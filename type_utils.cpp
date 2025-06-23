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

VarType* check_arithmetic_op(VarType* left, VarType* right, const std::string& op) {
    if (!left || !right) return new VarType{PrimitiveType::UNDEFINED};
    bool left_is_num = left->p_type == PrimitiveType::INT || left->p_type == PrimitiveType::FLOAT;
    bool right_is_num = right->p_type == PrimitiveType::INT || right->p_type == PrimitiveType::FLOAT;

    if (!left_is_num || !right_is_num) {
        std::cerr << "Operandos para '" << op << "' devem ser numéricos. Foram: " << type_to_string(*left) << " e " << type_to_string(*right) << std::endl;
        error();
        delete left; delete right;
        return new VarType{PrimitiveType::UNDEFINED};
    }
    
    PrimitiveType result_type = (left->p_type == PrimitiveType::FLOAT || right->p_type == PrimitiveType::FLOAT) ? PrimitiveType::FLOAT : PrimitiveType::INT;
    delete left; delete right;
    return new VarType{result_type};
}

VarType* check_logical_op(VarType* left, VarType* right, const std::string& op) {
    if (!left || !right || left->p_type != PrimitiveType::BOOL || right->p_type != PrimitiveType::BOOL) {
        std::cerr << "Operandos para '" << op << "' devem ser booleanos. Foram: " << type_to_string(*left) << " e " << type_to_string(*right) << std::endl;
    }
    delete left; delete right;
    return new VarType{PrimitiveType::BOOL};
}


VarType* check_relational_op(VarType* left, VarType* right, const std::string& op) {
    if (!left || !right) return new VarType{PrimitiveType::UNDEFINED};
    bool left_is_num = left->p_type == PrimitiveType::INT || left->p_type == PrimitiveType::FLOAT;
    bool right_is_num = right->p_type == PrimitiveType::INT || right->p_type == PrimitiveType::FLOAT;
    
    if ((!left_is_num || !right_is_num) && !(*left == *right)) {
        std::cerr << "Operandos para '" << op << "' são incompatíveis para comparação: " << type_to_string(*left) << " e " << type_to_string(*right) << std::endl;
        return new VarType{PrimitiveType::UNDEFINED};
    }
    delete left; delete right;
    return new VarType{PrimitiveType::BOOL};
}