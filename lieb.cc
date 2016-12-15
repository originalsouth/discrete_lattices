#include "tlv/tlv.h"

const double a=1e2;
int qx,qy,N;
double R=0.0;

std::vector<double> xi(int i)
{
    std::vector<double> retval(2,R);
    const int n=3*qx/2+qx%2;
    const int f=i%n;
    if(f<qx)
    {
        retval[0]=a*f;
        retval[1]=2.0*a*((i/n)%qx);
    }
    else
    {
        retval[0]=2.0*a*(f-qx);
        retval[1]=2.0*a*((i/n)%qx+0.5);
    }
    retval[0]+=R;
    retval[1]+=R;
    return retval;
}

std::vector<int> nn(int i)
{
    std::vector<int> retval(2);
    const int n=3*qx/2+qx%2;
    const int f=i%n;
    if(f<qx)
    {
        if(f%2)
        {
            retval[0]=(f+1)%qx+(i/n)*n;
            retval[1]=(f-1+qx)%qx+(i/n)*n;
        }
        else
        {
            retval.resize(4);
            retval[0]=(f+1)%qx+(i/n)*n;
            retval[1]=(f/2+qx+(i/n)*n)%N;
            retval[2]=(f-1+qx)%qx+(i/n)*n;
            retval[3]=(f/2+qx+(i/n-1)*n+N)%N;
        }
    }
    else
    {
        retval[0]=(2*(f-qx)+(i/n+1)*n)%N;
        retval[1]=(2*(f-qx)+(i/n)*n)%N;
    }
    return retval;
}

double dist(std::vector<double> x1,std::vector<double> x2)
{
    return hypot(x2[0]-x1[0],x2[1]-x1[1]);
}

void carbon(std::string fname)
{
    std::vector<double> L=xi(N-1);
    R=floor(a/3.0);
    tlv::svg *img=new tlv::svg(L[0]+a+2.0*R,L[1]+2.0*R);
    tlv_drw(img,rect x1="%g" y1="%g" width="%g" height="%g" fill="%s",0.0,0.0,img->width,img->height,"white");
    for(int i=0;i<N;i++)
    {
        std::vector<double> position=xi(i);
        std::vector<int> neighbors=nn(i);
        for(int j:neighbors)
        {
            std::vector<double> neighbor_position=xi(j);
            if(dist(position,neighbor_position)<1.5*a) tlv_drw(img,line x1="%g" y1="%g" x2="%g" y2="%g" stroke="blue" stroke-width="%g",position[0],position[1],neighbor_position[0],neighbor_position[1],0.2*R);
        }
    }
    for(int i=0;i<N;i++)
    {
        std::vector<double> position=xi(i);
        tlv_drw(img,circle cx="%g" cy="%g" r="%g" fill="black",position[0],position[1],R);
    }
    img->write(fname);
}

int main(int argc,char *argv[])
{
    (argc==3)?(qx=atoi(argv[1]),qy=atoi(argv[2])):(qx=6,qy=6);
    N=qx*qy-(qx/2)*(qy/2);
    printf("##%d=%dx%d\n",N,qx,qy);
    printf("##i(x,y) --> (j0,j1,j2,j3)\n");
    printf("##i(x,y) --> (j0,j1)\n");
    for(int i=0;i<N;i++)
    {
        std::vector<double> position=xi(i);
        std::vector<int> neighbors=nn(i);
        if(neighbors.size()==2) printf("%d(%g,%g) --> (%d,%d)\n",i,position[0]/a,position[1]/a,neighbors[0],neighbors[1]);
        else printf("%d(%g,%g) --> (%d,%d,%d,%d)\n",i,position[0]/a,position[1]/a,neighbors[0],neighbors[1],neighbors[2],neighbors[3]);
    }
    carbon(std::string(argv[0])+std::string(".svg"));
    return EXIT_SUCCESS;
}
