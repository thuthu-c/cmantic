#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory>
#include <optional>
#include <iostream>
#include "type_utils.hpp"

class SymbolTable {
    private:
        struct Scope {
            std::unordered_map<std::string, Symbol> symbols;
            Scope* parent;

            Scope() : parent(nullptr) {}
            Scope(Scope* p) : parent(p) {}
        };

        Scope* current_scope;
        std::vector<std::unique_ptr<Scope>> all_scopes;

        std::string symbolCategory_to_string(SymbolCategory category) const;
        std::string varType_to_string(const VarType& varType) const;
        std::string procedure_to_string(const Procedure& proc) const;
        std::string record_to_string(const Record& rec) const;
        std::string variable_to_string(const Variable& var) const;
        std::string symbol_to_string(const Symbol& symbol) const;
        void print_scope(const Scope* scope) const;

    public:
        SymbolTable() {
            auto root_scope = std::make_unique<Scope>();
            current_scope = root_scope.get();
            all_scopes.push_back(std::move(root_scope));
        }

        void push_scope();
        void pop_scope();

        bool insert_symbol(const std::string& name, Symbol symbol);
        Symbol* lookup(const std::string& name);
        Symbol* lookup_current_scope_only(const std::string& name);
        Symbol* lookup_root_scope_only(const std::string& name);

        void print() const;

        std::optional<VarType> get_symbol_type(const std::string& name);
};

#endif