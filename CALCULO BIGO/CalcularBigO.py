def parse_function(lines):
    """Parse a function from the text file and return its details"""
    function_info = {
        'name': '',
        'body': [],
        'complexity': 'O(1)'  
    }
    
    for line in lines:
        if line.startswith('FUNCTION_NAME:'):
            function_info['name'] = line.split(':')[1].strip()
        elif line.startswith('FUNCTION_BODY:'):
            continue
        elif line.startswith('END_FUNCTION'):
            break
        else:
            function_info['body'].append(line.strip())
    
    return function_info

def calculate_big_o(function_body):
    """Calculate Big O notation based on code patterns"""
    complexity = 'O(1)'  # Base complexity
    
    # Convert list of lines to a single string for pattern matching
    code = ' '.join(function_body)
    
    # Check for recursive calls
    if code.count(function_body[0].split('(')[0]) > 1:
        complexity = 'O(n)'  # Basic recursive complexity
    
    # Check for nested loops
    loop_keywords = ['for', 'while']
    nested_level = 0
    max_nested = 0
    
    for line in function_body:
        for keyword in loop_keywords:
            if keyword in line:
                nested_level += 1
                max_nested = max(max_nested, nested_level)
        if '}' in line:
            nested_level = max(0, nested_level - 1)
    
    if max_nested > 0:
        complexity = f'O(n^{max_nested})'
    
    return complexity

def generate_matlab_file(functions):
    """Generate MATLAB file for visualization"""
    with open('complexity_analysis.m', 'w') as f:
        f.write("% Complexity Analysis Visualization\n\n")
        f.write("figure;\n")
        f.write("hold on;\n")
        f.write("n = 1:100;\n\n")
        
        for i, func in enumerate(functions):
            complexity = func['complexity']
            if complexity == 'O(1)':
                f.write(f"y{i} = ones(size(n));\n")
            elif complexity == 'O(n)':
                f.write(f"y{i} = n;\n")
            elif complexity == 'O(n^2)':
                f.write(f"y{i} = n.^2;\n")
            elif complexity == 'O(log n)':
                f.write(f"y{i} = log(n);\n")
            
            f.write(f"plot(n, y{i}, 'DisplayName', '{func['name']} - {complexity}');\n")
        
        f.write("\ntitle('Complexity Analysis');\n")
        f.write("xlabel('Input Size (n)');\n")
        f.write("ylabel('Operations');\n")
        f.write("legend('show');\n")
        f.write("grid on;\n")
        f.write("hold off;\n")

def main():
    functions = []
    
    try:
        with open('funciones.txt', 'r') as file:
            lines = file.readlines()
            
            # Process file content
            i = 0
            while i < len(lines):
                if lines[i].startswith('FUNCTION_NAME:'):
                    # Collect all lines until END_FUNCTION
                    function_lines = []
                    while i < len(lines) and not lines[i].startswith('END_FUNCTION'):
                        function_lines.append(lines[i])
                        i += 1
                    function_lines.append(lines[i])  # Include END_FUNCTION
                    
                    # Parse and analyze function
                    function_info = parse_function(function_lines)
                    function_info['complexity'] = calculate_big_o(function_info['body'])
                    functions.append(function_info)
                i += 1
        
        # Generate MATLAB visualization file
        generate_matlab_file(functions)
        
        # Print analysis results
        print("\nComplexity Analysis Results:")
        print("-" * 40)
        for func in functions:
            print(f"Function: {func['name']}")
            print(f"Complexity: {func['complexity']}")
            print("-" * 40)
            
    except FileNotFoundError:
        print("Error: funciones.txt not found")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

if __name__ == "__main__":
    main()
