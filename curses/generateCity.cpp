#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>


void city:: setTileMap()
{
    std::vector<tile*> blank1;
    blank1.resize(tileMapSize);
    tileMap.resize(tileMapSize);
  for(int a=0; a<tileMapSize; a++)
    {
        tileMap[a]=blank1;
        for(int b=0; b<tileMapSize; b++)
        {
            tileMap[a][b]=new tile('0',10,10);
            tileMap[a][b]->position = coordinate(b,a);
            tileMap[a][b]->isDoor = false;
        }
    }

}


void city:: deleteTileMap()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap.size(); b++)
        {
            delete tileMap[a][b];
        }
    }
}

void box::makeRoad(road* myRoad, std::vector<std::vector<tile*> > & tileMap, int level)
{

 if(myRoad->vertical==true)
 {
  for(int a=0; a<=(myRoad->Point2->y-myRoad->Point1->y); a++)
  {
      for(int b=0; b<level; b++)
      {
          tileMap[(myRoad->Point1->y)+a][myRoad->Point1->x-level/2+b]=new tile('1',10,10);
      }

  }
 }

  else
  {
  for(int a=0; a<=myRoad->Point2->x-myRoad->Point1->x; a++)
   {
       for(int b=0; b<level; b++)
       {
           tileMap[myRoad->Point1->y-level/2+b][myRoad->Point1->x+a]=new tile('1',10,10);
       }

   }
  }


}


void box::divideBox(int level, std::vector<std::vector<tile*> > & tileMap)
{
    if(level==3){srand(time(NULL));}


  if(level!=0)
  {

    if(rand()%2==0 and right-left>3) //if line vertical and there is space to draw single line
    {
        int splitPoint=left+2+rand()%(right-left-3);
        coordinate lowPoint(splitPoint, bottom);
        coordinate highPoint(splitPoint, top);

        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;
        makeRoad(&tempRoad, tileMap, level); //draws road on tile map

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint;
        subBox1->top=top;
        subBox1->bottom=bottom;

        subBox2->left=splitPoint;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

        subBox1->divideBox(level-1, tileMap);
        subBox2->divideBox(level-1, tileMap);
        delete subBox1;
        delete subBox2;

    }

    else if (top-bottom>3)
    {//line horizontal
        int splitPoint=bottom+2+rand()%(top-bottom-3);
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;

        makeRoad(&tempRoad, tileMap, level); //draws road on tileMap

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=right;
        subBox1->top=top;
        subBox1->bottom=splitPoint;

        subBox2->left=left;
        subBox2->right=right;
        subBox2->top=splitPoint;
        subBox2->bottom=bottom;  //forms 2 new boxes
        subBox1->divideBox(level-1, tileMap);
        subBox2->divideBox(level-1, tileMap);
        delete subBox1;
        delete subBox2;

    }



  }

}

  void city::generateCity()
{
setTileMap();
divideBox(4,tileMap); //recursive box dividing and road drawing
}


