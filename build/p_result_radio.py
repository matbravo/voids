import os
import numpy
import pylab
import math
from random import choice
import matplotlib
import mpl_toolkits.mplot3d as a3




#### function findMatches: busca puntos de list_1 en list_2 con radio rad
#### list_1 y list_2 estan ordenados por el primer elemento. de desea match de los 3 primeros.
### o n2 irrelevante, son solo 700x300 casos.
def findMatches(list_1, list_2):
	result=[]
	volumen=0
	volumen_total=0
	v=0 #numero de matches
	for point_b in list_1:
		#print(str(point_b))
		element=point_b
		vol=0
		for point_f in list_2:
			dist= numpy.linalg.norm(point_b[0] - point_f[0])
			if dist<=point_b[2]:
				element.append(dist)
				#vol+= point_f[1]
				v+=1
		#volumen+=vol
		#result.append([element,vol,point_b[1]-vol])
		result.append(element)
	result.append([v,'de',len(list_2) ])			
	return result
			

############################################################################
# compara resultados obtenidos (found) con los puntos de referencia (base) #
############################################################################



## 1 copiar contenido de archivos en arreglos 
#found_file=open('outfileBetaR5','r') 
#found_file.readline()
#found_file.readline()
base_file=open('SDSSVOIDS_FINAL.dat','r')
found_file=open('SDSS_preprocess_output.dat','r')

points_base=[]
i=0
for line in base_file:
	#_id= float(line.split()[0].replace('\n',''))
	#print line
	x=float(line.split()[0].replace('\n',''))
	y=float(line.split()[1].replace('\n',''))
	z=float(line.split()[2].replace('\n',''))
	rad=float(line.split()[8].replace('\n',''))
	vol=float(line.split()[7].replace('\n',''))
	points_base.append([numpy.array([x,y,z]),vol, rad] )
base_file.close()

points_found=[]
i=0
for line in found_file:
	#_id= float(line.split()[0].replace('\n',''))
	x=float(line.split()[1].replace('\n',''))
	y=float(line.split()[2].replace('\n',''))
	z=float(line.split()[3].replace('\n',''))
	rad=float(line.split()[4].replace('\n',''))
	vol=float(line.split()[5].replace('\n',''))
	points_found.append([numpy.array([x,y,z]),vol, rad] )
found_file.close()



## 2 buscar puntos coincidentes dentro del radio del 2

result=findMatches(points_base,points_found)
#result=findMatches(points_found,points_base)

## 3 copiar en archivo de salida

compare_out=open('compare_out_radio','w')
for match in result:
	compare_out.write(str(match)+'\n')
compare_out.close()

