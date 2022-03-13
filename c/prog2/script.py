import os

full_path = os.path.realpath(__file__)
file_path = os.path.dirname(full_path)


def compile(name, args):
    # os.system(f"cd {file_path} && gcc ./{name}.c {args} {name}.exe && ./{name}.exe < ./test_cases/z2/input.txt > ./test_cases/z2/output.txt")
    os.system(f"cd {file_path} && gcc ./{name}.c {args} {name}.exe && valgrind --log-file=\"./test_cases/z2/valgrind_log.txt\" ./{name}.exe < ./test_cases/z2/input.txt > ./test_cases/z2/output.txt")
    # os.system(f"echo Exit Code is %errorlevel%")


if __name__ == '__main__':
    NAME_C = "zadanie2"
    ARGS = "-Wall -o"

    compile(NAME_C, ARGS)
