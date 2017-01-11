#include "PhysicMatrixOperations.h"

void BuildTransformMatrix(double x, double y, double z, double b, double d, double c, mat3_4d M)
{
    double cb=cos(b);
    double cd=cos(d);
    double cc=cos(c);
    double sb=sin(b);
    double sd=sin(d);
    double sc=sin(c);

    M[0][0]=cc*cd;  M[0][1]=sc*sb-cc*sd*cb;     M[0][2]=sc*cb+cc*sd*sb;     M[0][3]=x;
    M[1][0]=sc*cd;  M[1][1]=-cc*sb-sc*sd*cb;    M[1][2]=-cc*cb+sc*sd*sb;    M[1][3]=y;
    M[2][0]=sd;     M[2][1]=cd*cb;              M[2][2]=-cd*sb;             M[2][3]=z;
}
void BuildTransformMatrix2(double x, double y, double z, double b, double d, double c, mat3_4d M)
{
    mat3d SR={1.0,0.0,0.0,0.0,0.0,-1.0,0.0,1.0,0.0};
    mat3d R;

    double ang=sqrt(b*b+d*d+c*c);
    if (ang>1E-30)
    {
        double u[3];
        u[0]=b/ang;
        u[1]=d/ang;
        u[2]=c/ang;
        double ca=cos(ang);
        double sa=sin(ang);

        R[0][0]=ca+u[0]*u[0]*(1.0-ca);
        R[0][1]=u[0]*u[1]*(1.0-ca)-u[2]*sa;
        R[0][2]=u[0]*u[2]*(1.0-ca)+u[1]*sa;
        R[1][0]=u[1]*u[0]*(1.0-ca)+u[2]*sa;
        R[1][1]=ca+u[1]*u[1]*(1.0-ca);
        R[1][2]=u[1]*u[2]*(1.0-ca)-u[0]*sa;
        R[2][0]=u[2]*u[0]*(1.0-ca)-u[1]*sa;
        R[2][1]=u[2]*u[1]*(1.0-ca)+u[0]*sa;
        R[2][2]=ca+u[2]*u[2]*(1.0-ca);
    }
    else SetMatrix(R,1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0);

    mat3d RM;
    MultiMatrix(R,SR,RM);


    M[0][0]=RM[0][0];  M[0][1]=RM[0][1];    M[0][2]=RM[0][2];    M[0][3]=x;
    M[1][0]=RM[1][0];  M[1][1]=RM[1][1];    M[1][2]=RM[1][2];    M[1][3]=y;
    M[2][0]=RM[2][0];  M[2][1]=RM[2][1];    M[2][2]=RM[2][2];    M[2][3]=z;
}
void RotationMatrixFromAxis(vec3d r, mat3d R)
{
    double l=sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
    if (l<1E-60)
    {
        R[0][0]=1.0;    R[0][1]=0.0;    R[0][2]=0.0;
        R[1][0]=0.0;    R[1][1]=1.0;    R[1][2]=0.0;
        R[2][0]=0.0;    R[2][1]=0.0;    R[2][2]=1.0;
    }
    else
    {
        vec3d u;
        u[0]=r[0]/l;
        u[1]=r[1]/l;
        u[2]=r[2]/l;
        RotationMatrixFromAxisAngle(l,u,R);
    }
}

void RotationMatrixFromAxisAngle(double a, vec3d u, mat3d R)
{
    double ca=cos(a);
    double sa=sin(a);

    R[0][0]=ca+u[0]*u[0]*(1.0-ca);
    R[0][1]=u[0]*u[1]*(1.0-ca)-u[2]*sa;
    R[0][2]=u[0]*u[2]*(1.0-ca)+u[1]*sa;
    R[1][0]=u[1]*u[0]*(1.0-ca)+u[2]*sa;
    R[1][1]=ca+u[1]*u[1]*(1.0-ca);
    R[1][2]=u[1]*u[2]*(1.0-ca)-u[0]*sa;
    R[2][0]=u[2]*u[0]*(1.0-ca)-u[1]*sa;
    R[2][1]=u[2]*u[1]*(1.0-ca)+u[0]*sa;
    R[2][2]=ca+u[2]*u[2]*(1.0-ca);
}

void BuildTransformMatrix3(double x, double y, double z, double b, double d, double c, mat3_4d M)
{
    //Строим матрицу вращения
    mat3d XR;
    double cb=cos(b);
    double sb=sin(b);
    XR[0][0]=1.0;   XR[0][1]=0.0;   XR[0][2]=0.0;
    XR[1][0]=0.0;   XR[1][1]=cb;    XR[1][2]=-sb;
    XR[2][0]=0.0;   XR[2][1]=sb;    XR[2][2]=cb;

    vec3d y_axis={0.0,1.0,0.0};
    vec3d d_axis;
    MultiVector(XR,y_axis,d_axis);

    mat3d YR;
    RotationMatrixFromAxisAngle(d,d_axis,YR);

    mat3d XYR;
    MultiMatrix(YR,XR,XYR);

    vec3d z_axis={0.0,0.0,1.0};
    vec3d c_axis;
    MultiVector(XYR,z_axis,c_axis);

    mat3d ZR;
    RotationMatrixFromAxisAngle(c,c_axis,ZR);
    mat3d R;
    MultiMatrix(ZR,XYR,R);

    mat3d SR={1.0,0.0,0.0,0.0,0.0,-1.0,0.0,1.0,0.0};

    mat3d RM;
    MultiMatrix(R,SR,RM);

    M[0][0]=RM[0][0];  M[0][1]=RM[0][1];    M[0][2]=RM[0][2];    M[0][3]=x;
    M[1][0]=RM[1][0];  M[1][1]=RM[1][1];    M[1][2]=RM[1][2];    M[1][3]=y;
    M[2][0]=RM[2][0];  M[2][1]=RM[2][1];    M[2][2]=RM[2][2];    M[2][3]=z;
}

void MultiQuaternions(vec4d a, vec4d b, vec3d res)
{
    res[0]=b[0]*a[3]+a[0]*b[3]+a[1]*b[2]-a[2]*b[1];
    res[1]=b[1]*a[3]+a[1]*b[3]+a[2]*b[0]-a[0]*b[2];
    res[2]=b[2]*a[3]+a[2]*b[3]+a[0]*b[1]-a[1]*b[0];
    res[3]=a[3]*b[3]-a[0]*b[0]-a[1]*b[1]-a[2]*b[2];
}

void NormalizeQuaternion(vec4d q)
{
    double l=1.0/sqrt(q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3]);
    q[0]*=l;
    q[1]*=l;
    q[2]*=l;
    q[3]*=l;

}

void GetNormalizedQuaternion(vec4d q, vec4d rq)
{
    double l=1.0/sqrt(q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3]);
    rq[0]=q[0]*l;
    rq[1]=q[1]*l;
    rq[2]=q[2]*l;
    rq[3]=q[3]*l;
}

void AxisToQuaternion(vec3d ax, vec4d q)
{
    vec4d axis;
    double l=sqrtf(ax[0]*ax[0]+ax[1]*ax[1]+ax[2]*ax[2]);
    if (l>=1E-60)
    {
        axis[0]=ax[0]/l;
        axis[1]=ax[1]/l;
        axis[2]=ax[2]/l;
    }
    else
    {
        axis[0]=1.0;
        axis[1]=0.0;
        axis[2]=0.0;
    }

    double ang=l*0.5;
    double cos_a=cos(ang);
    double sin_a=sin(ang);

    q[0]=axis[0]*sin_a;
    q[1]=axis[1]*sin_a;
    q[2]=axis[2]*sin_a;
    q[3]=cos_a;
}

void AxisToQuaternion(vec3d u, double a, vec4d q)
{
    double ang=a*0.5;
    double cos_a=cos(ang);
    double sin_a=sin(ang);

    q[0]=u[0]*sin_a;
    q[1]=u[1]*sin_a;
    q[2]=u[2]*sin_a;
    q[3]=cos_a;
}

void AxisFromQuaternion(vec4d q, vec3d axis)
{
    double ang=2.0*acos(q[3]);
    double sq=1.0-q[3]*q[3];
    if (sq<1E-60)
    {
        axis[0]=1.0;
        axis[1]=0.0;
        axis[2]=0.0;
    }
    else
    {
        sq=1.0/sqrt(sq);
        axis[0]=q[0]*sq;
        axis[1]=q[1]*sq;
        axis[2]=q[2]*sq;
    }
    axis[0]*=ang;
    axis[1]*=ang;
    axis[2]*=ang;
}

void MatrixToQuaternion(mat3d M, vec4d q)
{
    double tr = M[0][0]+M[1][1]+M[2][2];
    double S;
    if (tr > 0)
    {
        S=sqrt(tr+1.0)*2.0;
        q[0]=(M[2][1]-M[1][2])/S;
        q[1]=(M[0][2]-M[2][0])/S;
        q[2]=(M[1][0]-M[0][1])/S;
        q[3]=0.25*S;
    }
    else if ((M[0][0]>M[1][1])&&(M[0][0]>M[2][2]))
    {
        S=sqrt(1.0+M[0][0]-M[1][1]-M[2][2])*2.0;
        q[0]=0.25*S;
        q[1]=(M[0][1]+M[1][0])/S;
        q[2]=(M[0][2]+M[2][0])/S;
        q[3]=(M[2][1]-M[1][2])/S;
    }
    else if (M[1][1]>M[2][2])
    {
        S=sqrt(1.0+M[1][1]-M[0][0]-M[2][2])*2.0;
        q[0]=(M[0][1]+M[1][0])/S;
        q[1]=0.25*S;
        q[2]=(M[1][2]+M[2][1])/S;
        q[3]=(M[0][2]-M[2][0])/S;
    }
    else
    {
        S=sqrt(1.0+M[2][2]-M[0][0]-M[1][1])*2.0;
        q[0]=(M[0][2]+M[2][0])/S;
        q[1]=(M[1][2]+M[2][1])/S;
        q[2]=0.25*S;
        q[3]=(M[1][0]-M[0][1])/S;
    }
}

void MatrixFromQuaternion(vec4d q, mat3d M)
{
    M[0][0]=1.0-2.0*q[1]*q[1]-2.0*q[2]*q[2];
    M[0][1]=2.0*q[0]*q[1]-2.0*q[2]*q[3];
    M[0][2]=2.0*q[0]*q[2]+2.0*q[1]*q[3];
    M[1][0]=2.0*q[0]*q[1]+2.0*q[2]*q[3];
    M[1][1]=1.0-2.0*q[0]*q[0]-2.0*q[2]*q[2];
    M[1][2]=2.0*q[1]*q[2]-2.0*q[0]*q[3];
    M[2][0]=2.0*q[0]*q[2]-2.0*q[1]*q[3];
    M[2][1]=2.0*q[1]*q[2]+2.0*q[0]*q[3];
    M[2][2]=1.0-2.0*q[0]*q[0]-2.0*q[1]*q[1];
}


void CrossSkewSymm(vec3d a, mat3d SM)
{
    SM[0][0]=0.0;   SM[0][1]=-a[2]; SM[0][2]=a[1];
    SM[1][0]=a[2];  SM[1][1]=0.0;   SM[1][2]=-a[0];
    SM[2][0]=-a[1]; SM[2][1]=a[0];  SM[2][2]=0.0;
}
void CrossSkewSymm_minus(vec3d a, mat3d SM)
{
    SM[0][0]=0.0;   SM[0][1]=a[2]; SM[0][2]=-a[1];
    SM[1][0]=-a[2]; SM[1][1]=0.0;  SM[1][2]=a[0];
    SM[2][0]=a[1];  SM[2][1]=-a[0];SM[2][2]=0.0;
}

void MultiMatrix(const mat4d M1, const mat4d M2, mat4d R)
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            R[i][j]=M1[i][0]*M2[0][j]+M1[i][1]*M2[1][j]+M1[i][2]*M2[2][j]+M1[i][3]*M2[3][j];
}

void MatTranspose(const mat4d M, mat4d MT)
{
    MT[0][0]=M[0][0]; MT[0][1]=M[1][0]; MT[0][2]=M[2][0]; MT[0][3]=M[3][0];
    MT[1][0]=M[0][1]; MT[1][1]=M[1][1]; MT[1][2]=M[2][1]; MT[1][3]=M[3][1];
    MT[2][0]=M[0][2]; MT[2][1]=M[1][2]; MT[2][2]=M[2][2]; MT[2][3]=M[3][2];
    MT[3][0]=M[0][3]; MT[3][1]=M[1][3]; MT[3][2]=M[2][3]; MT[3][3]=M[3][3];
}
