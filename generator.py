import sys

def main():
    with open("template.cpp", "r") as f:
        content = f.read()

    # Escape the content to make it a valid C string literal
    # 1. Escape backslashes
    escaped = content.replace("\\", "\\\\")
    # 2. Escape quotes
    escaped = escaped.replace("\"", "\\\"")
    # 3. Add newlines and quotes for C-style string concatenation
    lines = escaped.split('\n')
    c_string_lines = ['"' + line + '\\n"' for line in lines]
    c_string = '\n'.join(c_string_lines)

    # Now verify the template has the placeholder
    placeholder = "%c%s%c;"
    if placeholder not in content:
        print("Error: Template missing placeholder '%c%s%c;'")
        sys.exit(1)

    # Inject the C-string into the original content (NOT the escaped content)
    # But wait, looking at quinie.cpp logic:
    # fprintf(fp, s, current_gen + 1, child_id.c_str(), my_id.c_str(), 34, s, 34);
    # The 's' variable in the code must contain the formatting characters!
    
    # We need to construct the file such that:
    # quinie.cpp = (Part 1 of template) + (variable s = c_string) + (Part 2 of template)
    
    # But 'c_string' is the escaped version of the WHOLE template.
    
    # Let's split template by placeholder
    parts = content.split(placeholder)
    if len(parts) != 2:
        print("Error: Placeholder issues")
        sys.exit(1)
        
    # We also need to fix the %d and %s in the "main" function of the seed (quinie.cpp).
    # In the seed, current_gen = 0, my_id = "SEED", parent_id = "NONE".
    # But the template has `%d`, `%s`.
    # So we need to format those for the SEED instance.
    
    final_source = parts[0] + c_string + ";" + parts[1]
    
    # Now replace the placeholders for the SEED instance
    # The first %d is current_gen
    final_source = final_source.replace("int current_gen = %d;", "int current_gen = 0;", 1)
    final_source = final_source.replace('string my_id = "%s";', 'string my_id = "SEED";', 1)
    final_source = final_source.replace('string parent_id = "%s";', 'string parent_id = "NONE";', 1)
    
    with open("quinie.cpp", "w") as f:
        f.write(final_source)
        
    print("Generated quinie.cpp successfully")

if __name__ == "__main__":
    main()
