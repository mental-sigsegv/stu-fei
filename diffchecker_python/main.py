import os

def compile(name, args, input_file, output_file):
    full_path = os.path.realpath(__file__)
    file_path = os.path.dirname(full_path)
    os.system(f"cd {file_path} && gcc {name}.c {args} {name} && {name} < {input_file}.txt > {output_file}.txt")

if __name__ == '__main__':
    NAME_C = "main"
    ARGS = "-Wall -o"
    OUTPUT = ''  # '> output.txt'

    

    for i in range(2):
        compile(NAME_C, ARGS, f"input{i}", f"output{i}")

