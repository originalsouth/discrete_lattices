#include "tlv/tlv.h"

const double a=1e2;
int qx,qy,N;
double R=0.0;

std::vector<double> xi(int i)
{
    std::vector<double> retval(2,R);
    retval[0]+=a*0.5*sqrt(3.0)*(i%qx);
    retval[1]+=a*(1.5*((i/qx)%qy)+0.5*abs(i%qx%2-(i/qx)%qy%2));
    return retval;
}

std::vector<int> nn(int i)
{
    std::vector<int> retval(3);
    retval[0]=(i%qx+1)%qx+(i/qx)*qx;
    retval[1]=(i%qx+qx-1)%qx+(i/qx)*qx;
    retval[2]=(i+(2*abs(i%qx%2-(i/qx)%qy%2)-1)*qx+qx*qy)%(qx*qy);
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
    tlv::svg *img=new tlv::svg(L[0]+2.0*R,L[1]+2.0*R);
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
    (argc==3)?(qx=2*atoi(argv[1]),qy=atoi(argv[2])):(qx=6,qy=5);
    N=qx*qy;
    printf("##%d=%dx%d\n",N,qx,qy);
    printf("##i(x,y) --> (j0,j1,j2)\n");
    for(int i=0;i<N;i++)
    {
        std::vector<double> position=xi(i);
        std::vector<int> neighbors=nn(i);
        printf("%d(%g,%g) --> (%d,%d,%d)\n",i,position[0]/a,position[1]/a,neighbors[0],neighbors[1],neighbors[2]);
    }
    carbon(std::string(argv[0])+std::string(".svg"));
    return EXIT_SUCCESS;
}
