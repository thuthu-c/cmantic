#ifndef TYPEUTILS_H
#define TYPEUTILS_H

#include <string>
#include <optional>
#include <vector>
#include <variant>
#include <memory>
#include <utility>

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
    REF,
    UNDEFINED
};

struct VarType {
    PrimitiveType p_type;
    std::optional<std::string> record_name;
    std::unique_ptr<VarType> referenced_type;

    VarType() : p_type(PrimitiveType::UNDEFINED) {}

    VarType(PrimitiveType primitive) : p_type(primitive) {
        if (p_type == PrimitiveType::NOT_PRIMITIVE || p_type == PrimitiveType::REF) {
            p_type = PrimitiveType::UNDEFINED;
        }
    }

    VarType(PrimitiveType primitive, std::string name)
        : p_type(primitive), record_name(std::move(name)) {
        if (p_type != PrimitiveType::NOT_PRIMITIVE) {
            p_type = PrimitiveType::UNDEFINED;
            record_name.reset();
        }
    }

    VarType(PrimitiveType primitive, std::unique_ptr<VarType> reference)
        : p_type(primitive), referenced_type(std::move(reference)) {
        if (p_type != PrimitiveType::REF) {
            p_type = PrimitiveType::UNDEFINED;
            referenced_type.reset();
        }
        if (!referenced_type && p_type == PrimitiveType::REF) {
            // TODO : Checar se faz referência a um tipo válido
        }
    }

    VarType(const VarType& other)
        : p_type(other.p_type), record_name(other.record_name) {
        if (other.referenced_type) {
            referenced_type = std::make_unique<VarType>(*other.referenced_type);
        }
    }

    VarType& operator=(const VarType& other) {
        if (this == &other) {
            return *this;
        }
        p_type = other.p_type;
        record_name = other.record_name;
        if (other.referenced_type) {
            referenced_type = std::make_unique<VarType>(*other.referenced_type);
        } else {
            referenced_type.reset();
        }
        return *this;
    }

    bool operator==(const VarType& other) const {
        if (p_type != other.p_type) {
            return false;
        }

        switch (p_type) {
            case PrimitiveType::NOT_PRIMITIVE:
                return record_name == other.record_name;

            case PrimitiveType::REF:
                if (referenced_type && other.referenced_type) {
                    return *referenced_type == *other.referenced_type;
                }
                return !referenced_type && !other.referenced_type;

            default:
                return true;
        }
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

std::string type_to_string(const VarType& type);
bool are_types_compatible(const VarType& declared_type, const VarType& assigned_type);

#endif