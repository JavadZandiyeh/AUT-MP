from PIL import Image


alphabet = "abcdefghijklmnopqrstuvwxyz0123456789"

N = 7
M = 5

f = open("chars.txt", "w")
for filename in alphabet:
    im = Image.open(f'./characters/{filename}.png', 'r')
    pixels = list(im.getdata())

    print(pixels)


    for i in range(N):
        for j in range(M):
            f.write("#" if pixels[i*M+j][0] > 128 else ".")
        f.write("\n")

    f.write("\n")

f.close()
