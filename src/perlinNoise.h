#ifndef PERLINNOISE_H_INCLUDED
#define PERLINNOISE_H_INCLUDED

class perlinNoise
{
public:
    vector<vector<double> > shade;
    vector<vector<vector<double> > > blank3;
    vector<vector<double> > blank2;
    vector<double> blank1;
    vector<double> coordinate;
    coordinate.push_back(0);
    coordinate.push_back(0);
    vector<vector<vector<vector<double> > > > gradients;
    vector<vector<double> > perlin_noise_sum;
    double dot_product(vector<double>,vector<double>);
    double ease(double);
    double perlin_noise(vector<double>, vector<double>, vector<double>, vector<double>, vector<double>);
    void callPerlin();
};

double  perlinNoise::dot_product(vector<double> x, vector<double> y)
{
    double sum=0;
    for(int a=0; a<x.size(); a++)
    {
        sum+=(x[a]*y[a]);
    }

    return sum;
}

double  perlinNoise::ease(double x)
{
    double y=3*pow(x,2)-2*pow(x,3);
    return y;
}

double  perlinNoise::perlin_noise(vector<double> coordinate,vector<double> gradient1,vector<double> gradient2,vector<double> gradient3,vector<double> gradient4)
{
    vector<double> l1;
    vector<double> l2;
    vector<double> l3;
    vector<double> l4;
    l1.push_back(coordinate[0]); l1.push_back(coordinate[1]);
    l2.push_back(1-coordinate[0]); l2.push_back(coordinate[1]);
    l3.push_back(1-coordinate[0]); l3.push_back(1-coordinate[1]);
    l4.push_back(coordinate[0]); l4.push_back(1-coordinate[1]);

    double a=dot_product(l1,gradient1);
    double b=dot_product(l2,gradient2);
    double c=dot_product(l3,gradient3);
    double d=dot_product(l4,gradient4);
    double S1=ease(coordinate[0]);
    double S2=ease(coordinate[1]);
    return a*(1-S1)*(1-S2)+b*S1*(1-S2)+c*S1*S2+d*(1-S1)*S2;
}

perlinNoise::callPerlin()
{
    srand(time(NULL));
    int grid_length;

    for(int x=0; x<1000; x++)
    {
        perlin_noise_sum.push_back(blank1);
        for(int y=0; y<1000; y++)
        {
           perlin_noise_sum[x].push_back(0);
        }
    }

    for(int f=0; f<4; f++)
    {
        grid_length=1000/pow(2,f);
        gradients.push_back(blank3);
        for(int a=0; a<pow(2,f); a++)
        {
            gradients[a].push_back(blank2);
            for(int b=0; b<pow(2,f); b++)
            {
                gradients[f][a].push_back(blank1);
                double theta=rand()*6.283/RAND_MAX;
                gradients[f][a][b].push_back(cos(theta));
                gradients[f][a][b].push_back(sin(theta));
            }
        } //initializes gradients

        for(double x=0; x<1000; x++)
        {
            for(double y=0; y<1000; y++)
            {
                coordinate[0]=fmod(x,grid_length)/grid_length;
                coordinate[1]=fmod(y,grid_length)/grid_length;
                perlin_noise_sum[x][y]+=400/pow(2,f)*perlin_noise(coordinate,gradients[x/grid_length][y/grid_length],gradients[x/grid_length+1][y/grid_length],gradients[x/grid_length+1][y/grid_length+1],gradients[x/grid_length][y/grid_length+1]);
            }
        }//calls perlin_noise at each point
    }
}

#endif // PERLINNOISE_H_INCLUDED