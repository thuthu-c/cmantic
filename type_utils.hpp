#ifndef TYPEUTILS_H
#define TYPEUTILS_H

#include <string>
#include <optional>
#include <vector>
#include <variant>

enum class SymbolCategory {
    PROCEDURE,
    RECORD,
    VARIABLE,
    UNDEFINED
};

enum class PrimitiveType {
    BOOL,
    FLOAT,
    INT,
    STRING,
    VOID,
    NOT_PRIMITIVE,
    UNDEFINED
};

struct VarType {
    PrimitiveType p_type;
    std::optional<std::string> record_name;

    bool operator==(const VarType& other) const {
    if (p_type != other.p_type) {
        return false;
    }
    if (p_type == PrimitiveType::NOT_PRIMITIVE) {
        return record_name.has_value() && other.record_name.has_value() &&
               record_name.value() == other.record_name.value();
    }
    return true;
}
};

struct ParamField {
    std::string name;
    VarType type;
};

struct Procedure {
    VarType return_type;
    std::vector<ParamField> params;
};

struct Variable {
    VarType type;
};

struct Record {
    std::vector<ParamField> fields;
};

using SymbolContent = std::variant<Procedure, Record, Variable>;

struct Symbol {
    std::string name;
    SymbolCategory category;
    SymbolContent content;
};

#endif