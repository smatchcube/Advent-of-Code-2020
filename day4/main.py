import string

def read_passport(line):
    key_value_list = [w.split(':') for w in line.split()]
    return {s[0]: s[1] for s in key_value_list}

with open("input") as f:
    passports = [read_passport(line) for line in f.read().split("\n\n")]

def has_needed_fields(passport):
    return {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}.issubset(passport.keys())

print("Part two:", len([passport for passport in passports if has_needed_fields(passport)]))

def is_valid(passport):
    
    if not has_needed_fields(passport):
        return False

    def valid_number(s, l, m):
        if not s.isdigit():
            return False
        y = int(s)
        return l <= y and y <= m
    
    if not valid_number(passport["byr"], 1920, 2002):
        return False
    if not valid_number(passport["iyr"], 2010, 2020):
        return False
    if not valid_number(passport["eyr"], 2020, 2030):
        return False

    hgt = passport["hgt"]
    if not hgt.endswith(("cm", "in")):
        return False
    if hgt[-2:] == "cm":
        if not valid_number(hgt[:-2], 150, 193):
            return False
    elif not valid_number(hgt[:-2], 59, 76):
        return False

    hcl = passport["hcl"]
    if len(hcl) != 7 or hcl[0] != '#'or not set(hcl[1:]).issubset(set(string.hexdigits)):
        return False

    if passport["ecl"] not in {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}:
        return False

    pid = passport["pid"]
    if not pid.isdigit() or len(pid) != 9:
        return False

    return True

print("Part one:", len([passport for passport in passports if is_valid(passport)]))
