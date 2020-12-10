import functools

with open("input") as f:
    arr = [0] + [ int(x) for x in f.read().split() ]

arr.sort()

last_index = len(arr) - 1
    
@functools.lru_cache(None)
def gold(i):
    if i + 2 == last_index:
        if arr[-1] - arr[i] <= 3:
            return 2
        return 1
    if i + 1 == last_index:
        return 1
    if i == last_index:
        return 1
    r = gold(i + 1)
    if arr[i + 2] - arr[i] <= 3:
        r += gold(i+2)
        if arr[i + 3] - arr[i] <= 3:
            r += gold(i+3)
    return r

print("Part two:", gold(0))
