#include "tlv/tlv.h"

const double a=1e2;
int qx,qy,N;
double R=0.0;

std::vector<double> xi(int i)
{
    std::vector<double> retval={R+a*(i%qx),R+a*((i/qx)%qy)};
    return retval;
}

std::vector<int> nn(int i)
{
    std::vector<int> retval(4);
    retval[0]=(i%qx+1)%qx+(i/qx)*qx;
    retval[1]=(i%qx+(i/qx+1)*qx)%N;
    retval[2]=(i%qx-1+qx)%qx+(i/qx)*qx;
    retval[3]=(i%qx+(i/qx-1)*qx+N)%N;
    return retval;
}

void carbon(std::string fname)
{
    std::vector<double> L=xi(N);
    R=floor(0.3333*a);
    tlv::svg *img=new tlv::svg(a*(qx-1)+2.0*R,a*(qy-1)+2.0*R);
    tlv_drw(img,rect x1="%g" y1="%g" width="%g" height="%g" fill="%s",0.0,0.0,img->width,img->height,"white");
    for(int i=0;i<N;i++)
    {
        std::vector<double> position=xi(i);
        std::vector<int> neighbors=nn(i);
        for(int j:neighbors)
        {
            std::vector<double> neighbor_position=xi(j);
            tlv_drw(img,line x1="%g" y1="%g" x2="%g" y2="%g" stroke="blue" stroke-width="%g",position[0],position[1],neighbor_position[0],neighbor_position[1],0.2*R);
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
    (argc==3)?(qx=atoi(argv[1]),qy=atoi(argv[2])):(qx=5,qy=6);
    N=qx*qy;
    printf("##%d=%dx%d\n",N,qx,qy);
    printf("##i(x,y) --> (j0,j1,j2,j3)\n");
    for(int i=0;i<N;i++)
    {
        std::vector<double> position=xi(i);
        std::vector<int> neighbors=nn(i);
        printf("%d(%g,%g) --> (%d,%d,%d,%d)\n",i,position[0]/a,position[1]/a,neighbors[0],neighbors[1],neighbors[2],neighbors[3]);
    }
    carbon(std::string(argv[0])+std::string(".svg"));
    return EXIT_SUCCESS;
}
