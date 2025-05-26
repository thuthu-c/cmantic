from bs4 import BeautifulSoup
import os

# Path to the HTML file
html_file = os.path.join(os.path.dirname(__file__), 'table.html')

# Parse the HTML file
with open(html_file, 'r', encoding='utf-8') as file:
    soup = BeautifulSoup(file, 'html.parser')

# Find the table
table = soup.find('table')

# Symbol to ID maps
terminal_to_id = {}
non_terminal_to_id = {}
symbol_to_id = {}

next_term_id = -1
next_non_term_id = 1

def get_terminal_id(symbol):
    global next_term_id
    if symbol not in terminal_to_id:
        terminal_to_id[symbol] = next_term_id
        next_term_id -= 1
    return terminal_to_id[symbol]

def get_non_terminal_id(symbol):
    global next_non_term_id
    if symbol not in non_terminal_to_id:
        non_terminal_to_id[symbol] = next_non_term_id
        next_non_term_id += 1
    return non_terminal_to_id[symbol]

get_non_terminal_id("program")
get_terminal_id("ε")

# Extract table header and rows
rows = table.find_all('tr')
terminals = [header.text.strip() for header in rows[0].find_all('th')[1:]]
terminal_ids = [get_terminal_id(t) for t in terminals]

non_terminals = []
rules_matrix = {}

for row in rows[1:]:
    cells = row.find_all('td')
    if len(cells) < 2:
        continue
    non_terminal = cells[0].text.strip()
    non_terminals.append(non_terminal)
    nt_id = get_non_terminal_id(non_terminal)

    for i, cell in enumerate(cells[1:]):
        terminal = terminals[i]
        t_id = get_terminal_id(terminal)
        content = cell.text.strip()
        if content:
            symbols = content.replace("::=", "").split()
            rule_ids = []
            for sym in symbols:
                # Determine if symbol is terminal or non-terminal
                if sym in terminal_to_id:
                    rule_ids.append(get_terminal_id(sym))
                else:
                    rule_ids.append(get_non_terminal_id(sym))
            rules_matrix[(nt_id, t_id)] = rule_ids

# Initialize matrix with empty vectors
n_rows = len(non_terminals)
n_cols = len(terminals)
cpp_code = '#include <vector>\n#include <string>\n#include <map>\n\n'
cpp_code += f'std::vector<std::vector<std::vector<int>>> table({n_rows}, std::vector<std::vector<int>>({n_cols}));\n'

# Map (nt_id, t_id) to cell content
nt_ids = list(non_terminal_to_id.values())
t_ids = list(terminal_to_id.values())

nt_id_index = {nt: i for i, nt in enumerate(nt_ids)}
t_id_index = {t: i for i, t in enumerate(t_ids)}

for (nt_id, t_id), rule_ids in rules_matrix.items():
    row = nt_id_index[nt_id]
    col = t_id_index[t_id]
    rule_str = ', '.join(map(str, rule_ids))
    cpp_code += f'table[{row}][{col}] = {{{rule_str}}};\n'

# Merge all symbol IDs into one dictionary for output
symbol_to_id = {**terminal_to_id, **non_terminal_to_id}
cpp_code += '\nstd::map<int, std::string> symbol_map = {\n'
for sym, sid in sorted(symbol_to_id.items(), key=lambda x: x[1]):
    clean_sym = sym.strip('"')
    cpp_code += f'    {{{sid}, "{clean_sym}"}},\n'
cpp_code += '};\n'

# Save to file
output_file = os.path.join(os.path.dirname(__file__), 'table_2.cpp')
with open(output_file, 'w', encoding='utf-8') as file:
    file.write(cpp_code)

# print(f"Código C++ com IDs (terminais negativos, não-terminais positivos) foi salvo em: {output_file}")
print("IDs de símbolos:", terminal_to_id)
print("Ids de não-terminais:", non_terminal_to_id)

# Gerar o arquivo enums.txt
with open("enums.txt", "w", encoding="utf-8") as f:
    for key, value in terminal_to_id.items():
        line = f"A_{key.upper()} = {value}\n"
        f.write(line)

    f.write("\n")  # Separador entre os dois blocos

    for key, value in non_terminal_to_id.items():
        line = f"P_{key.upper()} = {value}\n"
        f.write(line)