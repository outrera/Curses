#include <iostream>
#include "tiles.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>
#include "generateCity.h"

using namespace noise;
tiles::tiles()
{
    zoomOut=1;
    height=40;
    width=40;
    mesh=30;
    makeElevationMap();
    fillMap();
    placeCities();


}

int tiles::mod(signed int a, int b)
{
    if(a<0)
    {
        while(a<0)
        {
            a+=b;
        }
    }
    else if (a>=0)
    {
        while(a>=b)
        {
        a-=b;
        }
    }
    return a;
}

void tiles::fillMap()
{
    tileMap.resize(2);

        tileMap[0].resize(height*mesh);
        tileMap[1].resize(height*mesh);
        for(double b=0; b<tileMap[0].size(); b++)
    {
        tileMap[0][b].resize(width*mesh);
        tileMap[1][b].resize(width*mesh);
        for(double c=0; c<tileMap[0][b].size(); c++)
        {
            if((b>=mesh*(height-1) or b<2*mesh) and (c>mesh*(width-1) or b<2*mesh))
               {

            double elevation=finalTerrain.GetValue(c*zoomOut/(width*mesh), b*zoomOut/(height*mesh), 0.5);
            tileMap[0][b][c]=new tile(grass,0,findTileType(elevation));
            tileMap[0][b][c]->elevation=elevation;
            tileMap[0][b][c]->position.y=b;
            tileMap[0][b][c]->position.x=c;
            tileMap[1][b][c]=new tile();
               }
               else
                {
                tileMap[0][b][c]=new tile;
                tileMap[1][b][c]=new tile;
               }
        }
    }


    //fills tileMap with blanks
}



void tiles::makeElevationMap()
{
srand(time(NULL));

    preLandTerrain1.SetFrequency(1);
    preLandTerrain1.SetSeed(rand());


    landTerrain1.SetSourceModule(0,preLandTerrain1);
    landTerrain1.SetBias(-0.1);


    preLandTerrain2.SetFrequency(2);
    preLandTerrain2.SetSeed(rand());


    landTerrain2.SetSourceModule(0,preLandTerrain2);
    landTerrain2.SetScale(1.2);
    landTerrain2.SetBias(-0.2);


    preOceanTerrain.SetFrequency(32);


    oceanTerrain.SetSourceModule(0,preOceanTerrain);
    oceanTerrain.SetScale(1.2);
    oceanTerrain.SetBias(-0.2);
    //preTerrainType.SetFrequency();


    finalTerrain_.SetSourceModule(0,oceanTerrain);
    finalTerrain_.SetSourceModule(1,landTerrain1);
    finalTerrain_.SetControlModule(landTerrain2);
    finalTerrain_.SetBounds(-100.0,-.7);


    finalTerrain.SetSourceModule(0,finalTerrain_);
    finalTerrain.SetSourceModule(1,landTerrain2);
    finalTerrain.SetControlModule(landTerrain2);
    finalTerrain.SetBounds(-0.7,100);
    finalTerrain.SetEdgeFalloff(0.5);
    //generate ma
/*
utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
  heightMapBuilder.SetSourceModule(finalTerrain);
  heightMapBuilder.SetDestNoiseMap(heightMap);
  heightMapBuilder.SetDestSize (100, 100);
  heightMapBuilder.SetBounds (0,1 , 0, 1);



   heightMapBuilder.Build ();
    utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
  renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
  renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
  renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
  renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
  renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
  renderer.AddGradientPoint ( 1.200, utils::Color (255,255,255,255));
  renderer.EnableLight();
  renderer.SetLightContrast(3.0);
  renderer.SetLightBrightness(2.0);
  renderer.Render ();
   utils::WriterBMP writer;
  writer.SetSourceImage (image);
  writer.SetDestFilename ("tutorial.bmp");
  writer.WriteDestFile ();
  std::cout << "Here\n";
  std::cout<<finalTerrain.GetValue(0,0,0.5);
    //sets elevations*/
}

tiles::~tiles()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap[a].size(); b++)
        {
            for(int c=0; c<tileMap[a][b].size(); c++)
            {
                delete tileMap[a][b][c];
            }

        }
    }
}

std::string tiles::findTileType(double elevation)
{
     if(elevation<waterBelow)
    {
      return "water";

    }
    else if(elevation<sandBelow)
    {
        return "sand";
    }
    else if(elevation<grassBelow)
    {
        return "grass";
    }
    else if(elevation<dirtBelow)
    {
        return "dirt";
    }
    else if(elevation<rockBelow)
    {
        return "stone";
    }
    else
    {
        return "white";//snow
    }
}
void tiles::updateTileMap(signed int gridx,signed int gridy,signed int newGridx,signed int newGridy)
{

signed int deltax=newGridx-gridx;
signed int deltay=newGridy-gridy;
signed int gridxDelete=mod(gridx-deltax,width);
signed int gridyDelete=mod(gridy-deltay,height);
   //delete x stuff

  for(signed int c=-1; c<=1; c++)
  {
int gridxc=mod(gridx+c,width);
int gridyc=mod(gridy+c,height);

      for(int a=0; a<mesh; a++)
      {
          for(int b=0; b<mesh; b++)
      {
         if(deltax!=0)//horizontal movement
         {
             if(tileMap[0][gridyDelete*mesh+a][gridxDelete*mesh+b]->isCity==false)
             {
                 tileMap[0][gridyDelete*mesh+a][gridxDelete*mesh+b]=new tile;
             }


            double x=mod(newGridx+deltax,width)*mesh+b;
            double y=gridyc*mesh+a;

            if(tileMap[0][y][x]->isCity==false and tileMap[1][y][x]->isCity==false)
            {
            double elevation=finalTerrain.GetValue(x*zoomOut/(width*mesh), y*zoomOut/(height*mesh), 0.5);
            tileMap[0][y][x]=new tile(grass,0,findTileType(elevation));
            tileMap[0][y][x]->elevation=elevation;
            tileMap[0][y][x]->position.x=x;
            tileMap[0][y][x]->position.y=y;
            }

         }

         if(deltay!=0) //vertical movement
         {
             if(tileMap[0][gridyDelete*mesh+a][gridxc*mesh+b]->isCity==false)
             {
             tileMap[0][gridyDelete*mesh+a][gridxc*mesh+b]=new tile;
             }


             double x=gridxc*mesh+b;
             double y=mod(newGridy+deltay,height)*mesh+a;
             if(tileMap[0][y][x]->isCity==false and tileMap[1][y][x]->isCity==false)
             {
                 double elevation=finalTerrain.GetValue(x*zoomOut/(width*mesh),y*zoomOut/(height*mesh), 0.5);
             tileMap[0][y][x]=new tile(grass,0,findTileType(elevation));
             tileMap[0][y][x]->elevation=elevation;
             tileMap[0][y][x]->position.x=x;
             tileMap[0][y][x]->position.y=y;
             }

         }
      }
      }
  }

}

void tiles::placeCities()
{
    unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
     std::mt19937 generator(seed);
     std::uniform_int_distribution<int> chooseTestx(0,mesh*width);
     std::uniform_int_distribution<int> chooseTesty(0, mesh*height);
 int cityWidth=100;
 int cityHeight=100;
 int x;
 int y;
 bool goodSpot;
 city* A;
 double elevationHere;
    for(int a=0; a<20; a++)
    {
    x=chooseTestx(generator);
    y=chooseTesty(generator);
    goodSpot=true;
    for(double b=0; b<100; b++)
    {
        for(double c=0; c<100; c++)
        {
            elevationHere=finalTerrain.GetValue(zoomOut*(x+c)/(mesh*width),zoomOut*(y+b)/(mesh*height), 0.5);
           if(sandBelow>=elevationHere or dirtBelow<=elevationHere)
           {
               goodSpot=false;
               break;
           }
        }
        if(goodSpot==false)
        {
            break;
        }
    }

              if(goodSpot==true)
              {
                  std::cout<<"City Made \n";
                   A=new city(x,y,100,100,tileMap);
              }

    }
}

   /* module::Turbulence turbulence;
    turbulence.SetSourceModule(0,turbulence);
    turbulence.SetFrequency(4.0);
    turbulence.SetPower(0.125);
*/




   // myModule.SetSeed(rand()%time(NULL));

   // module::Perlin terrainType;
   //e.SetSourceModule(0, myModule);
   // inverter.SetSourceModule(myModule);

// double perlin_map_width=2;
// double perlin_map_height=2;

