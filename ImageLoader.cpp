#include "ImageLoader.h"

bool il_initialized=false;

void InitImageLoader()
{
	if (il_initialized) return;
	FreeImage_Initialise();	
	il_initialized=true;
}
vector3ub* LoadImage3ub(char* filename, int &w, int &h, int from, int to)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;	
	FIBITMAP *dib=NULL;	
	unsigned char* bits=NULL;	
	w=0;
	h=0;	
	vector3ub* res=NULL;
			
	fif=FreeImage_GetFileType(filename, 0);	
	if(fif==FIF_UNKNOWN) fif=FreeImage_GetFIFFromFilename(filename);	
	if(fif==FIF_UNKNOWN) return NULL;
	if(FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);	
	if (!dib) return NULL;	
		
	int id;
	int bpp=FreeImage_GetBPP(dib);
	if (bpp==8 || bpp==24 || bpp==32)  //Читаем только эти форматы
	{
		bpp/=8;
		w=FreeImage_GetWidth(dib);
		h=FreeImage_GetHeight(dib);
		if (to==-1) to=h-1;
		if (to>h-1) to=h-1;
		if (from<0) from=0;
		if (from>to) from=to;

		h=to-from+1;

		if((w==0)||(h==0)) return NULL;

		res=new vector3ub[w*h];

		int c0,c1,c2;
		if (bpp==1){c0=0; c1=0; c2=0;}
		else {c0=FI_RGBA_RED; c1=FI_RGBA_GREEN; c2=FI_RGBA_BLUE;}
		
		for (int i=0; i<h; i++)
		{
			bits=FreeImage_GetScanLine(dib,i+from);
			for (int j=0; j<w; j++)
			{
				id=i*w+j;
				res[id][0]=bits[c0];
				res[id][1]=bits[c1];
				res[id][2]=bits[c2];				
				bits+=bpp;
			}
		}		
	}
	FreeImage_Unload(dib);
	return res;
}

vector4ub* LoadImage4ub(char* filename, int &w, int &h, int from, int to)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;	
	FIBITMAP *dib=NULL;	
	unsigned char* bits=NULL;	
	w=0;
	h=0;	
	vector4ub* res=NULL;
			
	fif=FreeImage_GetFileType(filename, 0);	
	if(fif==FIF_UNKNOWN) fif=FreeImage_GetFIFFromFilename(filename);	
	if(fif==FIF_UNKNOWN) return NULL;
	if(FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);	
	if (!dib) return NULL;	
		
	int id;
	int bpp=FreeImage_GetBPP(dib);
	if (bpp==8 || bpp==24 || bpp==32)  //Читаем только эти форматы
	{
		bpp/=8;
		w=FreeImage_GetWidth(dib);
		h=FreeImage_GetHeight(dib);
		if (to==-1) to=h-1;
		if (to>h-1) to=h-1;
		if (from<0) from=0;
		if (from>to) from=to;

		h=to-from+1;

		if((w==0)||(h==0)) return NULL;

		res=new vector4ub[w*h];
		if (!res){FreeImage_Unload(dib); w=0; h=0; return NULL;}

		int c0,c1,c2,c3;
		if (bpp==1){c0=0; c1=0; c2=0; c3=0;}
		else {c0=FI_RGBA_RED; c1=FI_RGBA_GREEN; c2=FI_RGBA_BLUE; c3=FI_RGBA_ALPHA;}
		
		for (int i=0; i<h; i++)
		{
			bits=FreeImage_GetScanLine(dib,i+from);
			for (int j=0; j<w; j++)
			{
				id=i*w+j;
				res[id][0]=bits[c0];
				res[id][1]=bits[c1];
				res[id][2]=bits[c2];
                                if (bpp==4) res[id][3]=bits[c3];
				else res[id][3]=255;
				bits+=bpp;
			}
		}		
	}
	FreeImage_Unload(dib);
	return res;
}
vec3* LoadImage3f(char* filename, int &w, int &h, int from, int to)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;	
	FIBITMAP *dib=NULL;	
	unsigned char* bits=NULL;	
	w=0;
	h=0;	
	vec3* res=NULL;
			
	fif=FreeImage_GetFileType(filename, 0);	
	if(fif==FIF_UNKNOWN) fif=FreeImage_GetFIFFromFilename(filename);	
	if(fif==FIF_UNKNOWN) return NULL;
	if(FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);	
	if (!dib) return NULL;	
		
	int id;
	int bpp=FreeImage_GetBPP(dib);
	if (bpp==8 || bpp==24 || bpp==32)  //Читаем только эти форматы
	{
		bpp/=8;
		w=FreeImage_GetWidth(dib);
		h=FreeImage_GetHeight(dib);
		if (to==-1) to=h-1;
		if (to>h-1) to=h-1;
		if (from<0) from=0;
		if (from>to) from=to;

		h=to-from+1;

		if((w==0)||(h==0)) return NULL;

		res=new vec3[w*h];
		if (!res){FreeImage_Unload(dib); w=0; h=0; return NULL;}

		int c0,c1,c2;
		if (bpp==1){c0=0; c1=0; c2=0;}
		else {c0=FI_RGBA_RED; c1=FI_RGBA_GREEN; c2=FI_RGBA_BLUE;}
		
		for (int i=0; i<h; i++)
		{
			bits=FreeImage_GetScanLine(dib,i+from);
			for (int j=0; j<w; j++)
			{
				id=i*w+j;
				res[id][0]=(float)bits[c0]/255.0f;
				res[id][1]=(float)bits[c1]/255.0f;
				res[id][2]=(float)bits[c2]/255.0f;				
				bits+=bpp;
			}
		}		
	}
	FreeImage_Unload(dib);
	return res;
}
vec4* LoadImage4f(char* filename, int &w, int &h, int from, int to)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;	
	FIBITMAP *dib=NULL;	
	unsigned char* bits=NULL;	
	w=0;
	h=0;	
	vec4* res=NULL;
			
	fif=FreeImage_GetFileType(filename, 0);	
	if(fif==FIF_UNKNOWN) fif=FreeImage_GetFIFFromFilename(filename);	
	if(fif==FIF_UNKNOWN) return NULL;
	if(FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);	
	if (!dib) return NULL;	
		
	int id;
	int bpp=FreeImage_GetBPP(dib);
	if (bpp==8 || bpp==24 || bpp==32)  //Читаем только эти форматы
	{
		bpp/=8;
		w=FreeImage_GetWidth(dib);
		h=FreeImage_GetHeight(dib);
		if (to==-1) to=h-1;
		if (to>h-1) to=h-1;
		if (from<0) from=0;
		if (from>to) from=to;

		h=to-from+1;

		if((w==0)||(h==0)) return NULL;

		res=new vec4[w*h];
		if (!res){FreeImage_Unload(dib); w=0; h=0; return NULL;}

		int c0,c1,c2,c3;
		if (bpp==1){c0=0; c1=0; c2=0; c3=0;}
		else {c0=FI_RGBA_RED; c1=FI_RGBA_GREEN; c2=FI_RGBA_BLUE; c3=FI_RGBA_ALPHA;}
		
		for (int i=0; i<h; i++)
		{
			bits=FreeImage_GetScanLine(dib,i+from);
			for (int j=0; j<w; j++)
			{
				id=i*w+j;
				res[id][0]=(float)bits[c0]/255.0f;
				res[id][1]=(float)bits[c1]/255.0f;
				res[id][2]=(float)bits[c2]/255.0f;
                                if (bpp==4) res[id][3]=(float)bits[c3]/255.0f;
				else res[id][3]=1.0f;
				bits+=bpp;
			}
		}		
	}
	FreeImage_Unload(dib);
	return res;
}
float* LoadImage1f(char* filename, int &w, int &h, int from, int to)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;	
	FIBITMAP *dib=NULL;	
    unsigned char* bits=NULL;
    unsigned short* bits2=NULL;
	w=0;
	h=0;	
	float* res=NULL;
			
	fif=FreeImage_GetFileType(filename, 0);	
	if(fif==FIF_UNKNOWN) fif=FreeImage_GetFIFFromFilename(filename);	
	if(fif==FIF_UNKNOWN) return NULL;
	if(FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);	
	if (!dib) return NULL;	
		
	int id;
	int bpp=FreeImage_GetBPP(dib);
    if (bpp==8 || bpp==24 || bpp==32)  //Читаем только эти форматы
	{
		bpp/=8;
		w=FreeImage_GetWidth(dib);
		h=FreeImage_GetHeight(dib);
		if (to==-1) to=h-1;
		if (to>h-1) to=h-1;
		if (from<0) from=0;
		if (from>to) from=to;

		h=to-from+1;

		if((w==0)||(h==0)) return NULL;

		res=new float[w*h];

		int c0,c1,c2;
		if (bpp==1){c0=0; c1=0; c2=0;}
		else {c0=FI_RGBA_RED; c1=FI_RGBA_GREEN; c2=FI_RGBA_BLUE;}
		
		for (int i=0; i<h; i++)
		{
			bits=FreeImage_GetScanLine(dib,i+from);
			for (int j=0; j<w; j++)
			{
				id=i*w+j;
				res[id]=(float)bits[c0]*IMAGE_LOADER_RB/255.0f+(float)bits[c1]*IMAGE_LOADER_GB/255.0f+(float)bits[c2]*IMAGE_LOADER_BB/255.0f;								
				bits+=bpp;
			}
		}		
	}
    else if (bpp==16 || bpp==48 || bpp==64) //Два бита на цвет
    {
        bpp/=16;
        w=FreeImage_GetWidth(dib);
        h=FreeImage_GetHeight(dib);
        if (to==-1) to=h-1;
        if (to>h-1) to=h-1;
        if (from<0) from=0;
        if (from>to) from=to;

        h=to-from+1;

        if((w==0)||(h==0)) return NULL;

        res=new float[w*h];

        int c0,c1,c2;
        if (bpp==1){c0=0; c1=0; c2=0;}
        else {c0=FI_RGBA_RED; c1=FI_RGBA_GREEN; c2=FI_RGBA_BLUE;}

        for (int i=0; i<h; i++)
        {
            bits2=(unsigned short*)FreeImage_GetScanLine(dib,i+from);
            for (int j=0; j<w; j++)
            {
                id=i*w+j;
                res[id]=(float)bits2[c0]*IMAGE_LOADER_RB/65536.0f+(float)bits2[c1]*IMAGE_LOADER_GB/65536.0f+(float)bits2[c2]*IMAGE_LOADER_BB/65536.0f;
                bits2+=bpp;
            }
        }
    }
	FreeImage_Unload(dib);
	return res;
}
bool GetImageSize(char* filename, int &w, int &h)
{
    FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;
    FIBITMAP *dib=NULL;
    //unsigned char* bits=NULL;
    w=0;
    h=0;
    //float* res=NULL;

    fif=FreeImage_GetFileType(filename, 0);
    if(fif==FIF_UNKNOWN) fif=FreeImage_GetFIFFromFilename(filename);
    if(fif==FIF_UNKNOWN) return false;
    if(FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, filename);
    if (!dib) return false;
    int bpp=FreeImage_GetBPP(dib);
    if (!(bpp==8 || bpp==24 || bpp==32)) return false;

    w=FreeImage_GetWidth(dib);
    h=FreeImage_GetHeight(dib);
    FreeImage_Unload(dib);
    return true;
}
bool SaveImageAsJPEG(char* filename, vector3ub* img, int w, int h, int quality)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=img[id][0];
			bits[FI_RGBA_GREEN]=img[id][1];
			bits[FI_RGBA_BLUE]=img[id][2];			
			bits+=bpp;
		}
	}
	bool saved=false;
	if (quality==0)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYBAD);	
	else if (quality==1)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYAVERAGE);	
	else if (quality==2)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYNORMAL);	
	else if (quality==3)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYGOOD);	
	else if (quality==4)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYSUPERB);	
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsJPEG(char* filename, vec3* img, int w, int h, int quality)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id][0]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id][1]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id][2]*255.0f);
			bits+=bpp;
		}
	}
	bool saved=false;
	if (quality==0)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYBAD);	
	else if (quality==1)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYAVERAGE);	
	else if (quality==2)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYNORMAL);	
	else if (quality==3)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYGOOD);	
	else if (quality==4)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYSUPERB);	
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsJPEG(char* filename, float* img, int w, int h, int quality)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id]*255.0f);		
			bits+=bpp;
		}
	}
	bool saved=false;
	if (quality==0)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYBAD);	
	else if (quality==1)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYAVERAGE);	
	else if (quality==2)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYNORMAL);	
	else if (quality==3)	saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYGOOD);	
	else					saved=FreeImage_Save(FIF_JPEG,dib,filename,JPEG_QUALITYSUPERB);	
	FreeImage_Unload(dib);
	return saved;
}


bool SaveImageAsBMP(char* filename, vector3ub* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=img[id][0];
			bits[FI_RGBA_GREEN]=img[id][1];
			bits[FI_RGBA_BLUE]=img[id][2];			
			bits+=bpp;
		}
	}
	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_BMP,dib,filename,BMP_DEFAULT);	
	else				saved=FreeImage_Save(FIF_BMP,dib,filename,BMP_SAVE_RLE);		
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsBMP(char* filename, vec3* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id][0]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id][1]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id][2]*255.0f);
			bits+=bpp;
		}
	}
	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_BMP,dib,filename,BMP_DEFAULT);	
	else				saved=FreeImage_Save(FIF_BMP,dib,filename,BMP_SAVE_RLE);		
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsBMP(char* filename, float* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id]*255.0f);		
			bits+=bpp;
		}
	}

	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_BMP,dib,filename,BMP_DEFAULT);	
	else				saved=FreeImage_Save(FIF_BMP,dib,filename,BMP_SAVE_RLE);		
	FreeImage_Unload(dib);
	return saved;
}


bool SaveImageAsPNG(char* filename, vector3ub* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=img[id][0];
			bits[FI_RGBA_GREEN]=img[id][1];
			bits[FI_RGBA_BLUE]=img[id][2];			
			bits+=bpp;
		}
	}
	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_DEFAULT);	
	else if (compress==1)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_SPEED);	
	else if (compress==2)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_DEFAULT_COMPRESSION);	
	else if (compress==3)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_COMPRESSION);	
	else if (compress==4)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_NO_COMPRESSION);	
	else if (compress==5)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_INTERLACED);	
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsPNG(char* filename, vec3* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id][0]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id][1]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id][2]*255.0f);
			bits+=bpp;
		}
	}
	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_DEFAULT);	
	else if (compress==1)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_SPEED);	
	else if (compress==2)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_DEFAULT_COMPRESSION);	
	else if (compress==3)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_COMPRESSION);	
	else if (compress==4)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_NO_COMPRESSION);	
	else if (compress==5)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_INTERLACED);	
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsPNG(char* filename, vector4ub* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,32);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=img[id][0];
			bits[FI_RGBA_GREEN]=img[id][1];
			bits[FI_RGBA_BLUE]=img[id][2];
			bits[FI_RGBA_ALPHA]=img[id][3];
			bits+=bpp;
		}
	}
	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_DEFAULT);	
	else if (compress==1)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_SPEED);	
	else if (compress==2)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_DEFAULT_COMPRESSION);	
	else if (compress==3)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_COMPRESSION);	
	else if (compress==4)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_NO_COMPRESSION);	
	else if (compress==5)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_INTERLACED);	
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsPNG(char* filename, vec4* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,32);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id][0]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id][1]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id][2]*255.0f);
			bits[FI_RGBA_ALPHA]=(unsigned char)(img[id][3]*225.0f);
			bits+=bpp;
		}
	}
	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_DEFAULT);	
	else if (compress==1)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_SPEED);	
	else if (compress==2)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_DEFAULT_COMPRESSION);	
	else if (compress==3)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_COMPRESSION);	
	else if (compress==4)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_NO_COMPRESSION);	
	else if (compress==5)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_INTERLACED);	
	FreeImage_Unload(dib);
	return saved;
}
bool SaveImageAsPNG(char* filename, float* img, int w, int h, int compress)
{
	FIBITMAP* dib=FreeImage_Allocate(w,h,24);
	if (!dib) return false;
	int bpp=FreeImage_GetBPP(dib)/8;	
	unsigned char* bits=NULL;

	int id;
	for (int i=0; i<h; i++)
	{
		bits=FreeImage_GetScanLine(dib,i);
		for (int j=0; j<w; j++)
		{
			id=i*w+j;
			bits[FI_RGBA_RED]=(unsigned char)(img[id]*255.0f);
			bits[FI_RGBA_GREEN]=(unsigned char)(img[id]*255.0f);
			bits[FI_RGBA_BLUE]=(unsigned char)(img[id]*255.0f);		
			bits+=bpp;
		}
	}

	bool saved=false;
	if (compress==0)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_DEFAULT);	
	else if (compress==1)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_SPEED);	
	else if (compress==2)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_DEFAULT_COMPRESSION);	
	else if (compress==3)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_BEST_COMPRESSION);	
	else if (compress==4)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_Z_NO_COMPRESSION);	
	else if (compress==5)	saved=FreeImage_Save(FIF_PNG,dib,filename,PNG_INTERLACED);	
	FreeImage_Unload(dib);
	return saved;
}


bool SaveImage(char* filename, vector3ub* img, int w, int h, int param)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;						
	fif=FreeImage_GetFIFFromFilename(filename);	
	if (fif==FIF_BMP)
	{		
		if (param<0) return SaveImageAsBMP(filename, img, w, h);
		else return SaveImageAsBMP(filename, img, w, h, param);
	}
	else if (fif==FIF_PNG)
	{
		if (param<0) return SaveImageAsPNG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}
	else if (fif==FIF_JPEG)
	{
		if (param<0) return SaveImageAsJPEG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}
	return false;
}
bool SaveImage(char* filename, vector4ub* img, int w, int h, int param)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;						
	fif=FreeImage_GetFIFFromFilename(filename);		
	if (fif==FIF_PNG)
	{
		if (param<0) return SaveImageAsPNG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}	
	return false;
}
bool SaveImage(char* filename, vec3* img, int w, int h, int param)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;						
	fif=FreeImage_GetFIFFromFilename(filename);	
	if (fif==FIF_BMP)
	{		
		if (param<0) return SaveImageAsBMP(filename, img, w, h);
		else return SaveImageAsBMP(filename, img, w, h, param);
	}
	else if (fif==FIF_PNG)
	{
		if (param<0) return SaveImageAsPNG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}
	else if (fif==FIF_JPEG)
	{
		if (param<0) return SaveImageAsJPEG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}
	return false;
}
bool SaveImage(char* filename, vec4* img, int w, int h, int param)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;						
	fif=FreeImage_GetFIFFromFilename(filename);		
	if (fif==FIF_PNG)
	{
		if (param<0) return SaveImageAsPNG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}	
	return false;
}
bool SaveImage(char* filename, float* img, int w, int h, int param)
{
	FREE_IMAGE_FORMAT fif=FIF_UNKNOWN;						
	fif=FreeImage_GetFIFFromFilename(filename);	
	if (fif==FIF_BMP)
	{		
		if (param<0) return SaveImageAsBMP(filename, img, w, h);
		else return SaveImageAsBMP(filename, img, w, h, param);
	}
	else if (fif==FIF_PNG)
	{
		if (param<0) return SaveImageAsPNG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}
	else if (fif==FIF_JPEG)
	{
		if (param<0) return SaveImageAsJPEG(filename, img, w, h);
		else return SaveImageAsPNG(filename, img, w, h, param);
	}
	return false;
}

void FreeImageLoader()
{
	if (!il_initialized) return;
	il_initialized=false;
}
