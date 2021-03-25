import os

os.chdir('build/')
for i in range(1, 5):
    os.system('.\Calculator.exe ../test/test' + str(i) + \
        '.txt ../test/out' + str(i) + '.txt')