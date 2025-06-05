#include "symbol_table.hpp"

void SymbolTable::push_scope() {
    auto new_scope = std::make_unique<Scope>(current_scope);
    current_scope = new_scope.get();
    all_scopes.push_back(std::move(new_scope));
}

void SymbolTable::pop_scope() {
    if (current_scope->parent != nullptr) {
        current_scope = current_scope->parent;
    }
}

bool SymbolTable::insert_symbol(const std::string& name, Symbol symbol) {
    return current_scope->symbols.try_emplace(name, std::move(symbol)).second;
}

Symbol* SymbolTable::lookup(const std::string& name) {
    Scope* search_scope = current_scope;
    while (search_scope != nullptr) {
        auto it = search_scope->symbols.find(name);
        if (it != search_scope->symbols.end()) {
            return &it->second;
        }
        search_scope = search_scope->parent;
    }
    return nullptr;
}

Symbol* SymbolTable::lookup_current_scope_only(const std::string& name) {
    auto it = current_scope->symbols.find(name);
    if (it != current_scope->symbols.end()) {
        return &it->second;
    }
    return nullptr;
}

Symbol* SymbolTable::lookup_root_scope_only(const std::string& name) {
    if (all_scopes.empty()) {
        return nullptr;
    }
    
    Scope* root_scope = all_scopes.front().get();
    auto it = root_scope->symbols.find(name);
    if (it != root_scope->symbols.end()) {
        return &it->second;
    }
    return nullptr;
}

void SymbolTable::print() const {
    print_scope(current_scope);
}

std::optional<VarType> SymbolTable::get_symbol_type(const std::string& name) {
    Symbol* symbol = lookup(name);
    if (!symbol) {
        return std::nullopt;
    }

    switch (symbol->category) {
        case SymbolCategory::PROCEDURE: return std::get<Procedure>(symbol->content).return_type;
        case SymbolCategory::VARIABLE:  return std::get<Variable>(symbol->content).type;
        case SymbolCategory::RECORD:    return VarType{PrimitiveType::NOT_PRIMITIVE, symbol->name};
        default:                        return VarType{PrimitiveType::UNDEFINED};
    }
}





// =============================== UTILS ====================================

std::string SymbolTable::symbolCategory_to_string(SymbolCategory category) const{
    switch (category) {
        case SymbolCategory::PROCEDURE: return "PROCEDURE";
        case SymbolCategory::RECORD:    return "RECORD";
        case SymbolCategory::VARIABLE:  return "VARIABLE";
        default:                        return "UNDEFINED";
    }
}

std::string SymbolTable::varType_to_string(const VarType& varType) const {
    if (varType.p_type != PrimitiveType::NOT_PRIMITIVE) {
        switch (varType.p_type) {
            case PrimitiveType::BOOL:   return "BOOL";
            case PrimitiveType::FLOAT:  return "FLOAT";
            case PrimitiveType::INT:    return "INT";
            case PrimitiveType::STRING: return "STRING";
            case PrimitiveType::VOID:   return "VOID";
            default:                    return "UNDEFINED";
        }
    }

    return varType.record_name.value_or("UNDEFINED_RECORD");
}

std::string SymbolTable::procedure_to_string(const Procedure& proc) const {
    std::string params;
    for (size_t i = 0; i < proc.params.size(); ++i) {
        params += proc.params[i].name + ": " + varType_to_string(proc.params[i].type);
        if (i < proc.params.size() - 1) {
            params += ", ";
        }
    }
    return "[ReturnType: " + varType_to_string(proc.return_type) + ", Parameters: {" + params + "}]";
}

std::string SymbolTable::record_to_string(const Record& rec) const {
    std::string fields;
    for (size_t i = 0; i < rec.fields.size(); ++i) {
        fields += rec.fields[i].name + ": " + varType_to_string(rec.fields[i].type);
        if (i < rec.fields.size() - 1) {
            fields += ", ";
        }
    }
    return "[Fields: {" + fields + "}]";
}

std::string SymbolTable::variable_to_string(const Variable& var) const {
    return "[VarType: " + varType_to_string(var.type) + "]";
}

std::string SymbolTable::symbol_to_string(const Symbol& symbol) const {
        std::string output = "[Name: " + symbol.name;
        output += ", Category: " + symbolCategory_to_string(symbol.category);
        output += ", Content: ";

        switch (symbol.category) {
            case SymbolCategory::PROCEDURE:
                output += procedure_to_string(std::get<Procedure>(symbol.content));
                break;
            case SymbolCategory::RECORD:
                output += record_to_string(std::get<Record>(symbol.content));
                break;
            case SymbolCategory::VARIABLE:
                output += variable_to_string(std::get<Variable>(symbol.content));
                break;
            default:
                output += "UNDEFINED";
                break;
        }

        output += "]";
        return output;
    }

void SymbolTable::print_scope(const Scope* scope) const {
    if (!scope) return;

    if (scope->parent) {
        print_scope(scope->parent);
        std::cout << "\u2191\n";
    }

    std::cout << "==================" << std::endl;

    if (scope->symbols.empty()) {
        std::cout << "  (Scope is empty)\n";
    } else {
        for (const auto& [name, symbol] : scope->symbols) {
            std::cout << "  \u25CF " << name << " \u2192 " << symbol_to_string(symbol) << "\n";
        }
    }
}

        // const Procedure* getSubProgram(const std::string& subprogname) {
        //     Symbol* symbol = findSymbolInGlobalScope(subprogname);
        //     if (symbol && symbol->category == SymbolCategory::PROCEDURE) {
        //         // std::get_if retorna um ponteiro para o tipo se ele estiver ativo, ou nullptr.
        //         return std::get_if<Procedure>(&symbol->content);
        //     }
        //     return nullptr;
        // }
        // const Record* getRecordType(const std::string& recordName) {
        //     Symbol* symbol = findSymbolInGlobalScope(recordName);
        //     if (symbol && symbol->category == SymbolCategory::RECORD) {
        //         return std::get_if<Record>(&symbol->content);
        //     }
        //     return nullptr;
        // }