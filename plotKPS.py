import matplotlib.pyplot as plt
import os
num=1
type="KPS"
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
	

	# pathPoints=os.getcwd()+'/output'+type+'/output'+str(num)+type+'.txt'
	# pointsFile=open(pathPoints,'r')
	# pointsX=[]
	# pointsY=[]
	# for line in pointsFile.readlines():
	# 	pointsX.append((float)(line[:-1].split(" ")[0]))
	# 	pointsY.append((float)(line[:-1].split(" ")[1]))
	# print(pointsX)
	# print(pointsY)
	
	# pathPointsLow=os.getcwd()+'/output'+type+'/output'+str(num)+type+'Low.txt'
	# pointsFileLow=open(pathPointsLow,'r')
	# pointsXLow=[]
	# pointsYLow=[]
	# for line in pointsFileLow.readlines():
	# 	pointsXLow.append((float)(line[:-1].split(" ")[0]))
	# 	pointsYLow.append((float)(line[:-1].split(" ")[1]))
	# print(pointsXLow)
	# print(pointsYLow)
	

	plt.axis([-0.6,0.6,-0.6,0.6])
	plt.scatter(pointsXFull,pointsYFull,c='k')
	plt.plot(pointsX,pointsY,'g')
	# plt.plot(pointsXLow,pointsYLow,'g')
	# plt.savefig(os.getcwd()+'/plotsKPS/'+str(num)+'/plotLOJM.png')
	plt.savefig(os.getcwd()+'/plotsKPS/'+str(num)+'/plotFullJM.png')

	# pointsX=[]
	# pointsY=[]
	# for index in indices:
	# 	pointsX.append((float)(points[index][0]))
	# 	pointsY.append((float)(points[index][1]))
	# pointsX.append((float)(points[indices[0]][0]))
	# pointsY.append((float)(points[indices[0]][1]))
	# # print(pointsX)
	# # print(pointsY)
	# pointsXFull=[]
	# pointsYFull=[]
	# for point in points:
	# 	pointsXFull.append(float(point[0]))
	# 	pointsYFull.append(float(point[1]))		
	# for i in range(1,len(pointsX)+1):
	# 	plt.axis([-0.6,0.6,-0.6,0.6])
	# 	plt.scatter(pointsXFull,pointsYFull,c='k')
	# 	plt.plot(pointsX[:i],pointsY[:i],'g')
	# 	plt.savefig(os.getcwd()+'/plotsJM/'+str(num)+'/plot'+str(i)+'JM.png')
