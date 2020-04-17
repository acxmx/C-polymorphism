#include<stdio.h>
#include<stdlib.h>

typedef void (*fptrSet) (void *, int);
typedef int (*fptrGet) (void *);
typedef void (*fptrDisplay) ();

typedef struct _functions
{
	fptrSet setX;
	fptrGet getX;
	fptrSet setY;
	fptrGet getY;
	fptrDisplay display;
}vFunctions;

typedef struct _shape
{
	vFunctions functions;
	int x;
	int y;
}Shape;

void shapeDisplay(Shape *shape)
{
	printf("Shape\n");
}

void shapeSetX(Shape *shape, int x)
{
	shape->x = x;
}

void shapeSetY(Shape *shape, int y)
{
	shape->y  =y;
}

int shapeGetX(Shape *shape)
{
	return shape->x;
}

int shapeGetY(Shape *shape)
{
	return shape->y;
}

Shape *getShapeInstance()
{
	Shape *shape = (Shape *)malloc(sizeof(Shape));
	shape->functions.setX = shapeSetX;
	shape->functions.getX = shapeGetX;
	shape->functions.setY = shapeSetY;
	shape->functions.getY = shapeGetY;
	shape->functions.display = shapeDisplay;
	shape->x = 0;
	shape->y = 0;
	return shape;
}

typedef struct _rectangle
{
	Shape base;
	int width;
	int height;
}Rectangle;

void rectangleSetX(Rectangle *rectangle, int x)
{
	rectangle->base.x = x;
}

int rectangleGetX(Rectangle *rectangle)
{
	return rectangle->base.x;
}

void rectangleSetY(Rectangle *rectangle, int y)
{
	rectangle->base.y = y;
}

int rectangleGetY(Rectangle *rectangle)
{
	return rectangle->base.y;
}

void rectangleDisplay(Rectangle *rectangle)
{
	printf("Rectangle\n");
}

Rectangle *getRectangleInstance()
{
	Rectangle *rectangle = (Rectangle *)malloc(sizeof(Rectangle));
	rectangle->base.functions.display = rectangleDisplay;
	rectangle->base.functions.setX = rectangleSetX;
	rectangle->base.functions.getX = rectangleGetX;
	rectangle->base.functions.setY = rectangleSetY;
	rectangle->base.functions.getY = rectangleGetY;
	rectangle->base.x = 0;
	rectangle->base.y = 0;
	rectangle->width = 0;
	rectangle->height = 0;
	return rectangle;
}

int main(void)
{
	Shape *sptr = getShapeInstance();
	Rectangle *rptr = getRectangleInstance();
	rptr->base.functions.setX(rptr, 30);
	sptr->functions.setX(sptr, 20);
	sptr->functions.display();
	rptr->base.functions.display();
	printf("shape->x:%d\n", sptr->functions.getX(sptr));
	printf("rectangle->x:%d\n", rptr->base.functions.getX(rptr));
	printf("---------------------------------\n");
	printf("C语言实现的多态：\n");
	printf("定义父类对象Shape并调用其display()函数:\n");
	Shape *sp = getShapeInstance();
	sp->functions.display();
	printf("定义子类Rectangle对象，并让父类指针指向它,"
	"然后调用display函数：\n");
	Rectangle *rp = getRectangleInstance();
	sp = rp;
	sp->functions.display();
	return 0;
}
