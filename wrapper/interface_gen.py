import re
import argparse

CLI=argparse.ArgumentParser()
CLI.add_argument(
  "--file",
  type=str,
  default=None,
)
CLI.add_argument(
  "--out",
  nargs="*",
  type=str,
  default=[],
  help="output file"
)

def isSignature(line):
    symbols = [
        '#', '//', '+', '-', '/', '[', ']', '.', '=', '==',
        '\"', '\'', 'auto', ';', '}', '@', 'main(', 'else',
        'if (', 'for ', 'while ', 'throw ',
        # 'namespace', 'switch', 'case', 'default:'
        ]

    if (line.startswith('*')): 
        return False

    if (line == ''):
        return False

    if (line == '{'): 
        return False

    for symbol in symbols:
        if symbol in line: 
            return False

    if (not len(line) == 0 and line[-1] == '{'):
        print(f'### WARNING: \'{line}\' contains bracket as the last line, move it to a new line')
        return False

    return True

def getSignatures(filename):
    if (not filename.endswith('.cpp')):
        print(f'{filename} is not a valid type')
        return

    signatures = []
    with open(f'{filename}', 'r') as f:
        lines = f.readlines()
        for line in lines:
            line = line.strip()

            if (isSignature(line)): 
                signatures.append(line)

    return signatures

def writeInterface(signatures):
    filepath = args.out[0] + '/' + 'eCP.i'

    with open(filepath, 'w+') as f:
        f.write(
            r'%module eCP_wrapper' + '\n' +
            r'%{' + '\n' +
            r'  #include "combined.hpp"' + '\n' +
            r'%}' + '\n' +
            r'%include "std_vector.i"' + '\n' +
            r'%include "std_pair.i"' + '\n' +
            r'namespace std {' + '\n' +
            r'   %template(UIntVector) std::vector<unsigned int>;' + '\n' +
            r'   %template(FloatVector) std::vector<float>;' + '\n' +
            r'   %template(FloatFloatVector) std::vector<std::vector<float>>;' + '\n' +
            r'   %template(PairVector) std::pair<std::vector<unsigned int>, std::vector<float>>;' + '\n' +
            r'   %template(FloatPointerVector) std::vector<float*>;' + '\n' +
            r'}' + '\n'
            )

        for sig in signatures:
            f.write(sig +';\n')

args = CLI.parse_args()
signatures = getSignatures(args.file)

writeInterface(signatures)