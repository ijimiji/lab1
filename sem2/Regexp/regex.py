import re
regex = r"(\D+)(\d+)(\D+)(\d+)(\D+)(\d+\D+\d+)(\d)([A-Z]+\D{5})(\d+)"
subst = r"\1 \3 \5 \7 \9"
f = open("L1_UTF8.txt")
lines = f.readlines()
f.close()
new_lines = []
for line in lines:
    # print(line)
    new_lines.append(re.sub(regex, subst, line, 0, re.MULTILINE))
f = open("L1_NEW_UTF8.txt", "w")
f.writelines(new_lines)
f.close()