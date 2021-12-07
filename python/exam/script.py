with open('run.py') as f:
    lines = f.read().splitlines()

with open('run_formatted.py', 'r+') as f:
    f.truncate(0)
    for line in lines:
        f.write(line.lower().replace('_', ' ')+'\n')

