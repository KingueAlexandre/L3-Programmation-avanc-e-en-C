from ctypes import *
import timeit
from PIL import Image

def invert_color_on_image(img):
    bitmap = img.load()
    
    for i in range(512):
        for j in range(512):
            (r,g,b,a) = bitmap[i,j]
            bitmap[i,j] = (255 - r, 255 - g, 255 - b, a)

Pix_c = c_ubyte * 4
Img_c_line = Pix_c * 512
Img_c = Img_c_line * 512

def convert_bitmap_to_c(img):
    img_c = Img_c()
    bitmap = img.load()
    for i in range(512):
        for j in range(512):
            for k in range(4):
                img_c[i][j][k] = bitmap[i, j][k]
    return img_c

def rebuild_image(img_c, img):
    bitmap = img.load()
    for i in range(512):
        for j in range(512):
            bitmap[i, j] = (img_c[i][j][0], img_c[i][j][1], img_c[i][j][2], img_c[i][j][3])


def niveaux_de_gris_moy(img):
    for line in img :
        for pix in line :
            value = (pix[0]+pix[1]+pix[2])/3
            pix[0] = value
            pix[1] = value
            pix[2] = value

def niveaux_de_gris_clarte(img):
    for line in img :
        for pix in line :
            value = (max(pix) + min(pix)) /2
            pix[0] = value
            pix[1] = value
            pix[2] = value

def niveaux_de_gris_luminance(img):
    for line in img :
        for pix in line :
            value = 0.2126*pix[0]+0.7152*pix[1]+0.0722*pix[2]
            pix[0] = value
            pix[1] = value
            pix[2] = value  

def seuillage_noir_blanc(img):
    niveaux_de_gris_luminance(img)
    for line in img:
        for pix in line:
            if pix[0] > 0.5:
                pix[0] = 1
                pix[1] = 1
                pix[2] = 1
            else:
                pix[0] = 0
                pix[1] = 0
                pix[2] = 0

def plus_rouge(img):
    for line in img:
        for pix in line:
            pix[0] = (1+pix[0])/2

def tres_vert(img):
    for line in img:
        for pix in line:
            pix[1] = (3 + pix[1])/4

def moyenne(img1, img2) :
    img =  [[[0,0,0] for _ in range(len(img1[0]))] for _ in range(len(img1))]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(3) :
                img[i][j][k] = (img1[i][j][k] + img2[i][j][k])/2
    return img

def degrade_rouge_bleu_img(img):
    for i, line in enumerate(img):
        for j, pix in enumerate(line):
            coef = (i+j) / (1024.0)
            pix[0] = (1 - coef)*pix[0]
            pix[1] = 0
            pix[2] = coef*pix[2]

def lumiere_milieu(img):
    for i, line in enumerate(img):
        for j, pix in enumerate(line):
            coef = (1 - ((256 - i)**2 + (256 - j)**2) / (2.0*(256**2)))**10
            pix[0] = coef*pix[0]
            pix[1] = coef*pix[1]
            pix[2] = coef*pix[2]

def remplacer_zone(img, x, y, couleur):
    c = img[x][y]
    
    def aux(i,j) :
        if img[i][j] == c :
            img[i][j] = couleur
            if i > 0 :
                aux(i-1, j)
            if j > 0 :
                aux(i, j-1)
            if i < len(img) - 1 :
                aux(i+1, j)
            if j < len(img[0]) - 1 :
                aux(i, j+1)
    
    if not (c == couleur) :
        aux(x,y)

def distance(c1, c2) :
    return math.sqrt(abs(c1[0] - c2[0])**2 + abs(c1[1] - c2[1])**2 + abs(c1[2] - c2[2])**2)

def remplacer_similaires(img, x, y):
    c = img[x][y]
    tab = [[True for _ in range(len(img[0]))] for _ in range(len(img))]
    l = [(x,y)]
    k = 0 
    
    while k < len(l) :
        i,j = l[k][0],l[k][1]
        if tab[i][j] :
            tab[i][j] = False
            if distance(img[i][j],c) < 0.25 :
                l.append((i,j))
                if i > 0 and tab[i-1][j]:
                    l.append((i-1,j))
                if j > 0 and tab[i][j-1]:
                    l.append((i,j-1))
                if i < len(img) - 1 and tab[i+1][j]:
                    l.append((i+1,j))
                if j < len(img[0]) - 1 and tab[i][j+1]:
                    l.append((i,j+1))
        k += 1
    
    for i,j in l :
        img[i][j][0] = c[0]
        img[i][j][1] = c[1]
        img[i][j][2] = c[2]

def segmentation(img):
    t = [[True for _ in range(len(img[0]))] for _ in range(len(img))]
    x,y = 0,0
    while x < len(img) :
        y = 0
        while y < len(img[0]) :
            if t[x][y] :
                tab = [[True for _ in range(len(img[0]))] for _ in range(len(img))]
                c = img[x][y]
                l = [(x,y)]
                k = 0 
                while k < len(l) :
                    i,j = l[k][0],l[k][1]
                    if tab[i][j] and t[i][j]:
                        if distance(img[i][j],c) < 0.15 :
                            l.append((i,j))
                            t[i][j] = False
                            if i > 0 and tab[i-1][j]:
                                l.append((i-1,j))
                            if j > 0 and tab[i][j-1]:
                                l.append((i,j-1))
                            if i < len(img) - 1 and tab[i+1][j]:
                                l.append((i+1,j))
                            if j < len(img[0]) - 1 and tab[i][j+1]:
                                l.append((i,j+1))
                    k += 1
            
                for i,j in l :
                    t[i][j] = False
                    img[i][j][0] = c[0]
                    img[i][j][1] = c[1]
                    img[i][j][2] = c[2]            
            
            y += 1
        x += 1

def codage(img1, img2) :
    img =  [[[0,0,0] for _ in range(len(img1[0]))] for _ in range(len(img1))]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(3) :
                n = img1[i][j][k]
                n = (int(n*1000))/1000
                n = n + img2[i][j][k] / 1000
                img[i][j][k] = n
                
    return img

def decodage(img) :
    result =  [[[0,0,0] for _ in range(len(img[0]))] for _ in range(len(img))]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(3) :
                n = img[i][j][k]
                n = n*1000 - int(n*1000)
                result[i][j][k] = n
                
    return result

def agrandissement_entier(img, facteur) :
    result =  [[[0,0,0] for _ in range(len(img[0])*facteur)] for _ in range(len(img)*facteur)]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(facteur) :
                for l in range(facteur) :
                    result[i*facteur+k][j*facteur+l] = img[i][j] 
                
    return result

def agrandissement(img, facteur) :
    n = int(len(img)*facteur)
    m = int(len(img[0])*facteur)
    result =  [[[0,0,0] for _ in range(m)] for _ in range(n)]
    for i in range(n) :
        for j in range(m) :
            x = i//facteur
            y = j//facteur
            if i/facteur - x > 0.5 and x < len(img)-1:
                x += 1
            if j/facteur - y > 0.5 and y < len(img[0])-1:
                y += 1            
            result[i][j] = img[x][y]   
                
    return result

def reduction(img, diviseur) :
    n = len(img)//diviseur
    m = len(img[0])//diviseur
    result =  [[[0,0,0] for _ in range(m)] for _ in range(n)]
    for i in range(n) :
        for j in range(m) :
            coul_moy = [0,0,0]
            for k in range(diviseur) :
                for l in range(diviseur) :
                    coul_moy[0] += img[i*diviseur+k][j*diviseur+l][0]
                    coul_moy[1] += img[i*diviseur+k][j*diviseur+l][1]
                    coul_moy[2] += img[i*diviseur+k][j*diviseur+l][2]
            coul_moy[0] = coul_moy[0] / (diviseur ** 2)
            coul_moy[1] = coul_moy[1] / (diviseur ** 2)
            coul_moy[2] = coul_moy[2] / (diviseur ** 2)
            
            result[i][j] = coul_moy
                
    return result