import sys
import re
mydict={}
dict_inter={}
vertex={}
vertex_list=[]
intersection_list=[]
edge_list=[]

class Point(object):
    def __init__ (self, x, y):
        self.x = float(x)
        self.y = float(y)
        self.point =  '(' + str(self.x) + ',' + str(self.y) + ')'
    def __repr__(self):
        return '({0:.2f},{1:.2f})'.format(self.x, self.y)


class Line(object):
    def __init__ (self, src, dst):
        self.src = src
        self.dst = dst

    def __str__(self):
        return str(self.src) + '-->' + str(self.dst)

def intersect (l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
    

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    
    if xden != 0 and yden != 0:
        xcoor =  xnum / xden
        ycoor = ynum / yden
        if min(x1, x2) <= xcoor <= max(x1, x2) and min(y1,y2) <= ycoor <= max(y1, y2):              #to check that intersection point lies on l1
            if min(x3, x4) <= xcoor <= max(x3, x4) and min( y3, y4) <= ycoor <= max(y3, y4):        #to check that intersection point lies on l2
                return Point (xcoor, ycoor)
    else:
        return None
def add():
    v=[]
    l=[]
    for j in temp1:
        v.append(Point(j[0], j[1]))
    for k in range(0,len(v)-1):
        l.append(Line(v[k],v[k+1]))
        mydict[cmd2]=l
        
def rm():
    del mydict[cmd2]
def mod():
    del mydict[cmd2]
def vertexfunc():
    id=0
    street = list(mydict.keys())
    length=len(street)
    for i in range(length- 1):
        street1 = mydict[street[i]]
        for j in range(i + 1, length):
            street2 = mydict[street[j]]

            for l1 in street1:
                for l2 in street2:
                    point_of_intersection = intersect(l1, l2)
                    if point_of_intersection is not None:
                        list_inter=[]
                        list_inter.append(l1)
                        list_inter.append(l2)
                        dict_inter[point_of_intersection]=list_inter

                        if not str(point_of_intersection) in intersection_list:
                            intersection_list.append(point_of_intersection)

                        if not str(point_of_intersection) in vertex_list:
                            id = id + 1
                            vertex[id] = point_of_intersection
                            vertex_list.append(str(point_of_intersection))
                        
                        segment_coord = [l1.src, l1.dst, l2.src, l2.dst]

                        for c in segment_coord:

                            if not str(c) in vertex_list:
                                id = id + 1
                                vertex[id] = c
                                vertex_list.append(str(c))
                        


def edges():
    street = list(mydict.keys())
    for k in range(len(street)):
        s = mydict[street[k]]
        for l in s:
            endpoint1 = l.src
            endpoint2 = l.dst
            elist = []

            for point in intersection_list:
                
                inter_line = dict_inter[point]

                for segment in inter_line:

                    if segment == l:

                        if str(endpoint1) not in elist:
                            elist.append(str(endpoint1))

                        if str(point) not in elist:
                            elist.append(str(point))

            if str(endpoint2) not in elist:
                elist.append(str(endpoint2))

            leng=len(elist)
            for m in range(leng - 1):
                l = Line(elist[m], elist[m + 1])
                if str(l) not in edge_list:
                    edge_list.append(l)


def clear():
    dict_inter.clear()
    vertex.clear()
    vertex_list.clear()
    intersection_list.clear()
    edge_list.clear()

def gg():
    vertexfunc()
    print('V = {')
    for i in vertex:
        print(str(i) + str(': ') + str(vertex[i]))
    print('}')
    edges()
    print('E = {')
    count = 0
    verticestokey = {str(v): k for k, v in vertex.items()}
    for edge in edge_list:
        v1 = verticestokey[edge.src]
        v2 = verticestokey[edge.dst]
        count = count + 1
        if count < len(edge_list):
            print(str('<') + str(v1) + str(',') + str(v2) + str('>') + str(','))
        else:
            print(str('<') + str(v1) + str(',') + str(v2) + str('>'))
    print('}')
    clear()


def main():
    mylist=[]
    global cmd2
    global temp1
    while True:
        line = sys.stdin.readline()
        if line == "":
            break
        #print("read a line:", line)
        #ptrn = r'(add|mod|rm|gg)\s\"([a-zA-z]+\s?)*([a-zA-z]+)\"\s(\(\-?\d\,\-?\d\)\s)*\(\-?\d\,\-?\d\)$'
        a=r'^(add)\s\"([a-zA-Z]+\s?)*([a-zA-Z]+)\"\s(\(\-?\d+\,\-?\d+\)\s)+\(\-?\d+\,\-?\d+\)$'
        add_check = re.compile(a)
        m=r'^(mod)\s\"([a-zA-Z]+\s?)*([a-zA-Z]+)\"\s(\(\-?\d+\,\-?\d+\)\s)+\(\-?\d+\,\-?\d+\)$'
        mod_check = re.compile(m)
        r= r'^(rm)\s\"([a-zA-Z]+\s?)*([a-zA-Z]+)\"$'
        rm_check=re.compile(r)
        g=r'^(gg)$'
        gg_check=re.compile(g)
        if add_check.match(line) or mod_check.match(line) or rm_check.match(line) or gg_check.match(line):
            command=line[0]
            if command=='a':
                flag=0
                cmd=line.split("\"",2)
                cmd2=cmd[1]
                cmd2=cmd2.lower()
                cmd3=cmd[2]
                temp1 = re.findall(r'\((\-?\d+),(\-?\d+)\)', cmd3)
                for i in temp1:
                    for j in i:
                        if re.match(r'\-0+$', j):
                            flag=1
                            
                if cmd2 in mydict:
                    print("Error: street name already exists")
                elif flag==1:
                    print("Error: invalid input -0")
                else:
                    add()
                    
            if command=='m':
                flag=0
                cmd=line.split("\"",2)
                cmd2=cmd[1]
                cmd2=cmd2.lower()
                cmd3=cmd[2]
                temp1 = re.findall(r'\((\-?\d+),(\-?\d+)\)', cmd3)
                for i in temp1:
                    for j in i:
                        if re.match(r'\-0+$', j):
                            flag=1
                if flag==1:
                    print("Error: invalid input -0")
                elif not cmd2 in mydict:
                    print("Error: cannot modify street, name does not exists")
                else:
                    mod()
                    v=[]
                    l=[]
                    for j in temp1:
                        v.append(Point(j[0], j[1]))
                    for k in range(0,len(v)-1):
                        l.append(Line(v[k],v[k+1]))
                        mydict[cmd2]=l
                        
            if command=='r':
                cmd=line.split("\"",2)
                cmd2=cmd[1]
                cmd2=cmd2.lower()
                if not cmd2 in mydict:
                    print("Error: cannot remove street, name does not exists")
                else:
                    rm()
            if command=='g':
                gg()
                
        else:
            
            print("Error: Enter a valid command")
    sys.exit(0)


#add "Weber Street" (2,-1)(2,2)(5,5)(5,6)(3,8)
#add "King Street S" (4,2)(4,8)
#add "Davenport Road" (1,4)(5,8)

if __name__ == "__main__":
    main()
