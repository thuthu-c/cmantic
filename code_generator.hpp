#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <string>
#include <sstream>
#include <map>
#include "type_utils.hpp"

class CodeGenerator {
private:
    int temp_counter;
    int label_counter;
    int call_counter;
    std::string program_name;

    std::stringstream declarations;
    std::stringstream procedures; // Para procedures que não são a main
    std::stringstream main_code;    // Para o corpo da procedure main

    // Mapeia um ID de chamada para o seu rótulo de retorno
    std::map<int, std::string> call_map;

    std::string build_control_procedure();

public:
    CodeGenerator();

    std::string new_temp();
    std::string new_label();

    void set_program_name(const std::string& name);
    const std::string& get_program_name() const;

    void emit_declaration(const std::string& code);
    
    void emit_code_to_procedure(bool is_main, const std::string& code);

    std::string type_to_c_type(const VarType& type);
    std::string get_return_variable_name(const VarType& type);
    std::string get_final_code();
    int register_call(const std::string& return_label);
};

#endif // CODE_GENERATOR_HPP
