import matplotlib.pyplot as plt
import os
num=1
type="JM"
if __name__=='__main__':
	pathPoints=os.getcwd()+'/input/input'+str(num)+'.txt'
	pathIndices=os.getcwd()+'/outputJM/output'+str(num)+type+'.txt'
	# print(path)
	points=[] 
	pointsFile=open(pathPoints,'r')
	for point in pointsFile.readlines()[1:]:
		points.append([point[:-1].split(" ")[0],point[:-1].split(" ")[1]])
	indices=[]
	linesFile=open(pathIndices,'r')
	for line in linesFile.readlines():
		indices.append((int)(line[:-1].split(" ")[0]))
	pointsX=[]
	pointsY=[]
	for index in indices:
		pointsX.append((float)(points[index][0]))
		pointsY.append((float)(points[index][1]))
	pointsX.append((float)(points[indices[0]][0]))
	pointsY.append((float)(points[indices[0]][1]))
	# print(pointsX)
	# print(pointsY)
	pointsXFull=[]
	pointsYFull=[]
	for point in points:
		pointsXFull.append(float(point[0]))
		pointsYFull.append(float(point[1]))		
	for i in range(1,len(pointsX)+1):
		plt.axis([-0.6,0.6,-0.6,0.6])
		plt.scatter(pointsXFull,pointsYFull,c='k')
		plt.plot(pointsX[:i],pointsY[:i],'g')
		plt.savefig(os.getcwd()+'/plotsJM/'+str(num)+'/plot'+str(i)+'JM.png')