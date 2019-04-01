import matplotlib.pyplot as plt
import os
num=7
type="GS"
if __name__=='__main__':
	pathPointsFull=os.getcwd()+'/input/input'+str(num)+'.txt'
	points=[] 
	pointsFullFile=open(pathPointsFull,'r')
	for point in pointsFullFile.readlines()[1:]:
		points.append([point[:-1].split(" ")[0],point[:-1].split(" ")[1]])
	pointsXFull=[]
	pointsYFull=[]
	for point in points:
		pointsXFull.append(float(point[0]))
		pointsYFull.append(float(point[1]))		
	
	pathPoints=os.getcwd()+'/output'+type+'/output'+str(num)+type+'.txt'
	pointsFile=open(pathPoints,'r')
	pointsX=[]
	pointsY=[]
	for line in pointsFile.readlines():
		pointsX.append((float)(line[:-1].split(" ")[0]))
		pointsY.append((float)(line[:-1].split(" ")[1]))

	for i in range(1,len(pointsX)+1):
		plt.axis([-0.6,0.6,-0.6,0.6])
		plt.scatter(pointsXFull,pointsYFull,c='k')
		plt.plot(pointsX[:i],pointsY[:i],'r')
		plt.savefig(os.getcwd()+'/plotsGS/'+str(num)+'/plot'+str(i)+'GS.png')

	plt.plot(pointsX[:i],pointsY[:i],'r')
	plt.plot([pointsX[i-1],pointsX[0]],[pointsY[i-1],pointsY[0]],'r')
	plt.savefig(os.getcwd()+'/plotsGS/'+str(num)+'/plot'+str(i+1)+'GS.png')