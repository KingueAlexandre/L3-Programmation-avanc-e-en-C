import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import math

from ctypes import *
import timeit
from PIL import Image

from Function import*

image_libc = cdll.LoadLibrary("./basic_image_process.so")

## Default

img = Image.open("panda.png")
plt.imshow(img)
plt.show()

## Inversion couleur

fig = plt.figure()
fig.suptitle("Inversion")
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.invert_color(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.show()

## Niveaux de gris

fig = plt.figure()
fig.suptitle("Niveaux de gris")

fig.add_subplot(131)
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.niveaux_de_gris_moy(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.axis("off")


fig.add_subplot(132)
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.niveaux_de_gris_clarte(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.axis("off")


fig.add_subplot(133)
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.niveaux_de_gris_luminance(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.axis("off")
plt.show()

## Seuillage Noir et Blanc

fig = plt.figure()
fig.suptitle("Seuillage")
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.seuillage_noir_blanc(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.show()

## Plus Rouge / Tres Vert


fig = plt.figure()
fig.suptitle("plus rouge")
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.plus_rouge(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.show()


fig = plt.figure()
fig.suptitle("encore plus vert")
img = Image.open("panda.png")
''
img_c = convert_bitmap_to_c(img)
image_libc.tres_vert(img_c)
rebuild_image(img_c, img)
''
plt.imshow(img)
plt.show()


## Degrade 
'''
''
img_test = image_libc.degrade()
rebuild_image(img_test, img)
''
fig = plt.figure()
fig.suptitle("dégradé")
plt.imshow(img)
plt.show()'''