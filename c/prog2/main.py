import os

full_path = os.path.realpath(__file__)
file_path = os.path.dirname(full_path)


def compile(name, args, input_file, output_file):
    os.system(f"cd {file_path} && gcc {name}.c {args} {name} && {name} < {input_file}.txt > {output_file}.txt")
    # os.system(f"echo Exit Code is %errorlevel%")


if __name__ == '__main__':
    NAME_C = "zadanie2_final"
    ARGS = "-Wall -o"
    OUTPUT = "zadanie2_output"
    INPUT = "zadanie2_input"

    compile(NAME_C, ARGS, INPUT, OUTPUT)
