#include "generateCity.h"
void road::makeRoad()
{
 if(vertical==true)
 {
  for(int a=0; a<=Point2->y-Point1->y; a++)
  {
   tileMap[Point1->y+a][Point2->x]->defaultChar='/';
   tileMap[Point2->y+a][Point1->x]->movementCost=10;
   tileMap[Point2->y+a][Point1->x]->material=stone;
  }
  }

  if(vertical==false)
 {
  for(int a=0; a<Point2->x-Point1->; a++)
  {

   tileMap[Point2->y][Point1->x+a]->defaultChar='/';
   tileMap[Point2->y][Point1->x+a]->movementCost=10;
   tileMap[Point2->y][Point1->x+a]->material=stone;
  }
  }


}
void city::setTileMap();
{
  for(int a=0 a<50; a++)
    {
        for(b=0; b<50; b++)
        {
            tileMap[a][b]=new tile('/',10,grass);
        }
    }
}



void city::deleteTileMap50()
{
    for(int a=0; a<50; a++)
    {
        for(b=0; b<50; b++)
        {
            delete tileMap[a][b];
        }
    }
}



void city::makeCity()
 {
      for(int a=0; a<roads.size(); a++)
      {
          road[a]->makeRoad();
      }
}

void city::generateCity()
{
divideBox(3);
drawGameWorld();
}


void box::divideBox(int level)
{
  if(level!=0)
  {

    if(uniform_int_distribution(0,1)==0) //if line vertical
    {
        width=right-left;
        uniform_real_distribution<double>(left+width/10, right+width/10) splitPoint;
        coordinate lowPoint(bottom, splitPoint);
        coordinate highPoint(top, splitPoint);
       tempRoad=new road;
        tempRoad->vertical=true;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        drawRoad(tempRoad); //builds list of roads
        delete tempRoad;
        delete bottomPoint;
        delete topPoint;

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint;
        subBox1->top=top;
        subBox1->bottom;
        subBox2->left=splitPoint;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

    }

    else
    {
        height=top-bottom;
        uniform_real_distribution<double>(bottom+height/10, top-height/10) splitPoint;
        coordinate leftPoint(splitPoint, left);
        coordinate rightPoint(splitPoint, right);

        tempRoad=new road;
        tempRoad->vertical=false;
        tempRoad->Point1=&leftPoint;
        tempRoad->Point2=&rightPoint;
        drawRoad(tempRoad); //builds list of roads
        delete tempRoad;
        delete leftPoint
        delete rightPoint;


        box1=new box;
        box2=new box;

        box1->left=left;
        box1->right=right;
        box1->top=top;
        box1->splitPoint;
        box2->left=left;
        box2->right=right;
        box2->top=splitPoint;
        box2->bottom=bottom;  //forms
    }

    box1->myCity=myCity;
    box2->myCity=myCity
    level-=1;
    box1->divideBox(level);
    box2->divideBox(level);
    delete box1;
    delete box2;

  }
}



