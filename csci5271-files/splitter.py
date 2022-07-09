filename = input("Please enter a filename: ")

fi = open(filename, "r")
f = filename.split(".")
fo = open((f[0] + "long.txt"), "w")

for line in fi:
    words = line.split()
    for word in words:
        fo.write(word)
        fo.write("\n")

fi.close()
fo.close()