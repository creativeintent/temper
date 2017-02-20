#!/usr/bin/env python

import hashlib
import random
import string

NUM_KEYS=1000

def gen_key(size=12):
    charset = string.ascii_uppercase + string.digits
    return ''.join(random.choice(charset) for _ in range(size))

def hash_key(key):
    return hashlib.sha256(key).hexdigest()

if __name__ == '__main__':
    pairs = dict()
    for _ in range(NUM_KEYS):
        size = random.randint(12, 16)
        key = gen_key(size)
        digest = hash_key(key)
        pairs[key] = digest

    with open('private.keys', 'w') as private:
        for key in pairs.keys():
            private.write(key + '\n')

    with open('public.keys', 'w') as public:
        for digest in pairs.values():
            public.write(digest + '\n')

