#include "code_generator.hpp"
#include <algorithm>
#include <sstream> 

std::string indent_block(const std::string& text, const std::string& indent = "    ") {
    std::stringstream input(text);
    std::stringstream output;
    std::string line;
    while (std::getline(input, line)) {
        // Não indenta linhas vazias
        if (!line.empty()) {
            output << indent << line << "\n";
        } else {
            output << "\n";
        }
    }
    return output.str();
}

CodeGenerator::CodeGenerator() 
    : temp_counter(0), label_counter(0), call_counter(0), program_name("output") {}

std::string CodeGenerator::new_temp() {
    return "t" + std::to_string(temp_counter++);
}

std::string CodeGenerator::new_label() {
    return "L" + std::to_string(label_counter++);
}

void CodeGenerator::set_program_name(const std::string& name) {
    program_name = name;
}

const std::string& CodeGenerator::get_program_name() const {
    return program_name;
}

void CodeGenerator::emit_declaration(const std::string& code) {
    declarations << code;
}

void CodeGenerator::emit_code_to_procedure(bool is_main, const std::string& code) {
    if (is_main) {
        main_code << code;
    } else {
        procedures << code;
    }
}

std::string CodeGenerator::type_to_c_type(const VarType& type) {
    switch (type.p_type) {
        case PrimitiveType::INT:    return "int";
        case PrimitiveType::FLOAT:  return "float";
        case PrimitiveType::BOOL:   return "int";
        case PrimitiveType::STRING: return "char*";
        case PrimitiveType::VOID:   return "void";
        case PrimitiveType::NOT_PRIMITIVE:
            return type.record_name.value_or("undefined_struct");
        case PrimitiveType::REF:
        case PrimitiveType::DEREF:
            if (type.referenced_type) {
                return type_to_c_type(*type.referenced_type) + "*";
            }
            return "void*";
        default: return "/* undefined_type */";
    }
}

std::string CodeGenerator::get_return_variable_name(const VarType& type) {
    switch (type.p_type) {
        case PrimitiveType::INT:
        case PrimitiveType::BOOL:   return "return_value_int";
        case PrimitiveType::FLOAT:  return "return_value_float";
        case PrimitiveType::STRING: return "return_value_string";
        case PrimitiveType::NOT_PRIMITIVE:
        case PrimitiveType::REF:
        case PrimitiveType::DEREF:
            return "return_value_ptr";
        default: return "/* invalid_return_type */";
    }
}

std::string CodeGenerator::build_control_procedure() {
    if (call_map.empty()) return "";

    std::stringstream control;
    control << "control_procedure:\n";
    control << "switch (stack_pointer < 0 ? -1 : activation_stack[stack_pointer--]) {\n";
    for (const auto& pair : call_map) {
        control << "    case " << pair.first << ": goto " << pair.second << ";\n";
    }
    control << "    default: goto end_program;\n";
    control << "}\n";
    return control.str();
}

std::string CodeGenerator::get_final_code() {
    std::stringstream final_code;
    final_code << "#include <stdio.h>\n";
    final_code << "#include <stdbool.h>\n";
    final_code << "#include <string.h>\n";
    final_code << "#include <math.h>\n\n";

    final_code << "void main() {\n";
    
    final_code << indent_block(declarations.str());
    
    final_code << "    int activation_stack[1024];\n"; 
    final_code << "    int stack_pointer = -1;\n";
    final_code << "    int return_value_int;\n";
    final_code << "    float return_value_float;\n";
    final_code << "    char* return_value_string;\n";
    final_code << "    void* return_value_ptr;\n\n";

    final_code << "    goto start_main_logic;\n\n";

    final_code << indent_block(procedures.str());

    final_code << "    start_main_logic:\n";
    final_code << indent_block(main_code.str());
    final_code << "        goto end_program;\n\n";

    final_code << indent_block(build_control_procedure());

    final_code << "    end_program:\n";
    final_code << "        return;\n";
    final_code << "}\n";

    return final_code.str();
}

int CodeGenerator::register_call(const std::string& return_label) {
    call_map[++call_counter] = return_label;
    return call_counter;
}
