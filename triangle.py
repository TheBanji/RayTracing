import numpy as np
import matplotlib.pyplot as plt

class Point:
    def __init__(self, x, y, z) -> None:
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, point) -> float:
        return Point(self.x + point.x, self.y + point.y, self.z + point.z)
    
    def __sub__(self, point) -> float:
        return Point(self.x - point.x, self.y - point.y, self.z - point.z)
    
    def __mul__(self, point) -> float:
        return self.x*point.x + self.y*point.y + self.z*point.z
    
    def __xor__(self, point):
        return Point(self.y*point.z - point.y*self.z, self.z*point.x - point.z*self.x, self.x*point.y - point.x*self.y)
    
    def __iadd__(self, point):
        self.x += point.x
        self.y += point.y
        self.z += point.z
        return self
    
    def __isub__(self, point):
        self.x -= point.x
        self.y -= point.y
        self.z -= point.z
        return self

    def mul(self, a) -> None:
        self.x *= a
        self.y *= a
        self.z *= a

    def print(self) -> None:
        print("(", self.x, ", ", self.y, ", ", self.z, ")")

class Line:
    def __init__(self, M: Point, v: Point) -> None:
        self.M = M
        self.v = v
    
    def __call__(self, t: float) -> Point:
        return self.M + Point(t * self.v.x, t * self.v.y, t * self.v.z)

class Triangle:
    def __init__(self, p1: Point, p2: Point, p3: Point) -> None:
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        self.u = self.p2 - self.p1
        self.v = self.p3 - self.p2
        self.w = self.p1 - self.p3
        self.n  = self.u ^ self.w
    
    def normal(self) -> Point:
        return self.n
    
    def intersects(self, L: Line) -> bool:
        if(abs(L.v * self.n) <= 1e-4):
            return (False, 0)
        t = -((L.M - self.p1) * self.n)/(L.v * self.n)
        if(t < 0):
            return (False, 0)
        IntersecPt = L(t)
        A_IntersecPt = IntersecPt - self.p1
        B_IntersecPt = IntersecPt - self.p2
        C_IntersecPt = IntersecPt - self.p3
        v1 = self.u ^ A_IntersecPt
        v2 = self.v ^ B_IntersecPt
        v3 = self.w ^ C_IntersecPt
        ps12 = v1 * v2
        ps23 = v2 * v3
        return (ps12 > 0 and ps23 > 0, IntersecPt)

def draw_triangles(Triangles: list) -> list:
    renderList = []
    for triangle in Triangles:
        renderList.append([[], []])
        for x in np.arange(0, 5, 0.01):
            for y in np.arange(0, 5, 0.05):
                l = Line(Point(x, y, 0), Point(0, 0, 1))
                resIntersec = triangle.intersects(l)
                if(resIntersec[0]):
                    renderList[-1][0].append(resIntersec[1].x)
                    renderList[-1][1].append(resIntersec[1].y)
    return renderList

p1 = Point(1, 1, 1)
p2 = Point(1, 3, 1)
p3 = Point(2, 3, 1)
t = Triangle(p1, p2, p3)

renderList = draw_triangles([t])

for triangleCoords in renderList:
    plt.scatter(triangleCoords[0], triangleCoords[1])
plt.show()