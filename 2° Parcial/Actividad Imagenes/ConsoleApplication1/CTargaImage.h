#ifndef __TARGA_LIB
#define __TARGA_LIB

enum TGATypes
{
	TGA_NODATA = 0,
	TGA_INDEXED = 1,
	TGA_RGB = 2,
	TGA_GRAYSCALE = 3,
	TGA_INDEXED_RLE = 9,
	TGA_RGB_RLE = 10,
	TGA_GRAYSCALE_RLE = 11
};

// Formatos de la imagen
#define	IMAGE_RGB       0
#define IMAGE_RGBA      1
#define IMAGE_LUMINANCE 2

// Tipos de datos de la imagen
#define	IMAGE_DATA_UNSIGNED_BYTE 0

/*
   Transferencia de los datos del pixel desde el archivo hacia la pantalla:
   Estas máscaras son AND's con el valor imageDesc del encabezado TGA
   el bit 4 es un ordenamiento de izquierda a derecha
   el bit 5 es de arriba hacia abajo
*/
#define BOTTOM_LEFT  0x00	// El primer pixel es la esquina inferior izquierda
#define BOTTOM_RIGHT 0x10	// El primer pixel es la esquina inferior derecha
#define TOP_LEFT     0x20	// El primer pixel es la esquina superior izquierda
#define TOP_RIGHT    0x30	// El primer pixel es la esquina superior derecha

// Encabezado TGA
struct tgaheader_t
{
	unsigned char  idLength;
	unsigned char  colorMapType;
	unsigned char  imageTypeCode;
	unsigned char  colorMapSpec[5];
	unsigned short xOrigin;
	unsigned short yOrigin;
	unsigned short width;
	unsigned short height;
	unsigned char  bpp;
	unsigned char  imageDesc;
};

struct rgba_t
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct rgb_t
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class CTargaImage
{
	private:
		unsigned char  m_colorDepth;
		unsigned char  m_imageDataType;
		unsigned char  m_imageDataFormat;
		unsigned char *m_pImageData;
		unsigned short m_width;
		unsigned short m_height;
		unsigned long  m_imageSize;

		// Intercambiar los componentes rojo y azul en los datos de la imagen
		void SwapRedBlue();

	public:
		CTargaImage();
		virtual ~CTargaImage();

		// Cargar y descargar
		bool Load(const char *filename);
		void Release();

		// Ajustar la imagen verticalmente
		bool FlipVertical();

		unsigned short GetWidth() { return m_width; }
		unsigned short GetHeight() { return m_height; }
		unsigned char  GetImageFormat() { return m_imageDataFormat; }

		// Convertir el formato RGB a RGBA y viceversa
		bool ConvertRGBAToRGB();
		bool ConvertRGBToRGBA(unsigned char alphaValue);

		// Devolver los datos de la imagen
		unsigned char *GetImage() { return m_pImageData; }
};

#endif
