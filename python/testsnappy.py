#!/usr/bin/python
"""

"""

import snappy

def main():
    r = snappy.compress("ZZZZZZZZZZZZZ")
    print(r)
    
if __name__ == '__main__':
    main()
