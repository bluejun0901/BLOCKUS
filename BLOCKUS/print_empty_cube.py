#
#  print_empty_cube.py
#  BLOCKUS
#
#  Created by 김명준 on 7/31/24.
#

b, c, d = map(int, input().split())

print('{')
for z in range(b):
    if z == 0:
        print('    {')
    else:
        print('    }, {')
    for y in range(c):
        if y == 0:
            print('        { ', end='')
        else:
            print(' },')
            print('        { ', end='')
        for x in range(d):
            if x == 0:
                print('0', end='')
            else:
                print(', 0', end='')
    print(' }')
print('    }')
print('};')
