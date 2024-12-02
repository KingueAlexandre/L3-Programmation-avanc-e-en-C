import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import math

## Default

img=mpimg.imread('Lenna.png')
plt.imshow(img)
plt.show()

## Tests

img_test = [ [[0,0,0] for j in range(512)] for i in range(512)]
fig = plt.figure()
fig.suptitle("")
plt.imshow(img_test)
plt.show()

## Niveaux de gris

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

fig = plt.figure()
fig.suptitle("Niveaux de gris")

fig.add_subplot(131)
img=mpimg.imread('Lenna.png')
niveaux_de_gris_moy(img)
plt.imshow(img)
plt.axis("off")

fig.add_subplot(132)
img=mpimg.imread('Lenna.png')
niveaux_de_gris_clarte(img)
plt.imshow(img)
plt.axis("off")

fig.add_subplot(133)
img=mpimg.imread('Lenna.png')
niveaux_de_gris_luminance(img)
plt.imshow(img)
plt.axis("off")
plt.show()


## Noir et blanc

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

fig = plt.figure()
fig.suptitle("Seuillage")
img=mpimg.imread('Lenna.png')
seuillage_noir_blanc(img)
plt.imshow(img)
plt.show()

## 

def plus_rouge(img):
    for line in img:
        for pix in line:
            pix[0] = (1+pix[0])/2


fig = plt.figure()
fig.suptitle("plus rouge")
img=mpimg.imread('Lenna.png')
plus_rouge(img)
plt.imshow(img)
plt.show()

##

def tres_vert(img):
    for line in img:
        for pix in line:
            pix[1] = (3 + pix[1])/4

fig = plt.figure()
fig.suptitle("encore plus vert")
img=mpimg.imread('Lenna.png')
tres_vert(img)
plt.imshow(img)
plt.show()

##

img_test = [ [ [1-(i+j)/1024, (i+j)/1024, 0] for j in range(512)] for i in range(512)]
fig = plt.figure()
fig.suptitle("dégradé")
plt.imshow(img_test)
plt.show()


## Moyenne de deux images

def moyenne(img1, img2) :
    img =  [[[0,0,0] for _ in range(len(img1[0]))] for _ in range(len(img1))]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(3) :
                img[i][j][k] = (img1[i][j][k] + img2[i][j][k])/2
    return img

fig = plt.figure()
fig.suptitle("moyenne de deux images")
img=mpimg.imread('Lenna.png')
img_test = [ [ [1-(i+j)/1024, (i+j)/1024, 0] for j in range(512)] for i in range(512)]
plt.imshow(moyenne(img, img_test))
plt.show()

##

def degrade_rouge_bleu_img(img):
    for i, line in enumerate(img):
        for j, pix in enumerate(line):
            coef = (i+j) / (1024.0)
            pix[0] = (1 - coef)*pix[0]
            pix[1] = 0
            pix[2] = coef*pix[2]

fig = plt.figure()
fig.suptitle("dégradé lenna")
img=mpimg.imread('Lenna.png')
degrade_rouge_bleu_img(img)
plt.imshow(img)
plt.show()

##

def lumiere_milieu(img):
    for i, line in enumerate(img):
        for j, pix in enumerate(line):
            coef = (1 - ((256 - i)**2 + (256 - j)**2) / (2.0*(256**2)))**10
            pix[0] = coef*pix[0]
            pix[1] = coef*pix[1]
            pix[2] = coef*pix[2]

fig = plt.figure()
fig.suptitle("illumination")
img=mpimg.imread('Lenna.png')
lumiere_milieu(img)
plt.imshow(img)
plt.show()

## Zone contingüe

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

fig = plt.figure()
fig.suptitle("Remplacement d'une couleur par une autre")
img_test = [ [ [1-(i+j)/1024, (i+j)/1024, 0] for j in range(512)] for i in range(512)]
remplacer_zone(img_test, 10, 10, [0,0,0])
plt.imshow(img_test)
plt.show()

## Distance

img_test = [ [ [1-(i+j)/1024, (i+j)/1024, 0] for j in range(512)] for i in range(512)]

def distance(c1, c2) :
    return math.sqrt(abs(c1[0] - c2[0])**2 + abs(c1[1] - c2[1])**2 + abs(c1[2] - c2[2])**2)
    
print(distance(img_test[10][10], [0,1,1]))

## Zone couleurs proches

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
        
fig = plt.figure()
fig.suptitle("Zones de couleurs proches")
img=mpimg.imread('Lenna.png')
remplacer_similaires(img, 100, 100)
plt.imshow(img)
plt.show()

## test segmentation

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

fig = plt.figure()
fig.suptitle("Segmentation")
img=mpimg.imread('Lenna.png')
# img= [ [ [1-(i+j)/1024, (i+j)/1024, 0] for j in range(512)] for i in range(512)]
segmentation(img)
plt.imshow(img)
plt.show()

## Stéganographie

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
    
fig = plt.figure()
fig.suptitle("Codage")
img2 = mpimg.imread('Lenna.png')
img1 = mpimg.imread('signature.png')
img = codage(img1, img2)
plt.imshow(img)
plt.show()

def decodage(img) :
    result =  [[[0,0,0] for _ in range(len(img[0]))] for _ in range(len(img))]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(3) :
                n = img[i][j][k]
                n = n*1000 - int(n*1000)
                result[i][j][k] = n
                
    return result

fig = plt.figure()
fig.suptitle("Décodage")
img2 = mpimg.imread('Lenna.png')
img1 = mpimg.imread('signature.png')
img = codage(img1, img2)
plt.imshow(decodage(img))
plt.show()


## Agrandissement entier


def agrandissement_entier(img, facteur) :
    result =  [[[0,0,0] for _ in range(len(img[0])*facteur)] for _ in range(len(img)*facteur)]
    for i in range(len(img)) :
        for j in range(len(img[i])) :
            for k in range(facteur) :
                for l in range(facteur) :
                    result[i*facteur+k][j*facteur+l] = img[i][j] 
                
    return result

fig = plt.figure()
fig.suptitle("Agrandissement entier")
img=mpimg.imread('Lenna.png')
plt.imshow(agrandissement_entier(img, 3))
plt.show()

## Agrandissement et réduction (voisin plus proche)

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

fig = plt.figure()
fig.suptitle("Agrandissement * 3")
img=mpimg.imread('Lenna.png')
plt.imshow(agrandissement(img, 3))

fig = plt.figure()
fig.suptitle("Facteur 1/16")
img=mpimg.imread('Lenna.png')
plt.imshow(agrandissement(img, 1/16))
plt.show()

## Réduction par moyenne

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
    
fig = plt.figure()
fig.suptitle("Réduction")
img=mpimg.imread('Lenna.png')
plt.imshow(reduction(img, 16))
plt.show()


