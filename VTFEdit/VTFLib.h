/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

// ============================================================
// NOTE: This file is commented for compatibility with Doxygen.
// ============================================================
/*!
	\file VTFLib.h
	\brief VTFLib main header.
*/

/*!
	\mainpage VTFLib - Copyright &copy; 2005-2007 Neil Jedrzejewski & Ryan Gregg

	\section intro Introduction

	\subsection intro_sec What is VTFLib?
	VTFLib is an open source programming library which allows developers to
	add support for VMT and VTF files used by the material system of Valve
	Software's Source game engine. It functions independent of Steam allowing
	third party apps to use these file types without the need for Steam to be running.

	VTFLib offers a simply API which allows you to read or write VMT and VTF files
	through a few simple functions. It also takes care of a lot of formatting and
	validation of the files.

	\subsection whatcando_sec What can VTFLib do?
	VTFLib comprises of two modules, VMTFile and VTFFile.

	VMTFile allows you to read and write VMT files using a hierarchical node
	based system similar to how one might navigate an XML file. The system uses
	a series of VMTNode objects which have a name and data type. These can be set,
	read or parented as needed by your application.

	You can load an existing VMT file, navigate and modify it or create a new file
	from scratch. VMTFile will handle indentation and formatting of the file output.

	The VTFFile module allows you to read and write binary image data in VTF files.
	Internally, the module uses RGBA8888 (32-bit) data for images and requires either
	your own functions or a 3rd party library to read and write more common image formats.
	We use and have tested it with DevIL.

	It supports single frame, multiple frame and cube map files and can read and write
	compressed and uncompressed formats and allows access to individual frames, faces
	and MIP levels. It contains functions to automatically create MIP levels for you using
	a number of different filter types, can automatically generate sphere maps and even create
	Normal and DuDv maps from RGB and greyscale source images.

	\section started Getting Started with VTFLib

	\subsection settingup_sec Setting up your project for VTFLib
	If you have used third party libraries in your projects before, you probably know
	how to do the following, but if not here is a brief explanation of how to use VTFLib
	with your project. The following example is for Visual Studio C++ .NET 2003 but setting
	up for Visual C++ 6.0 is pretty much the same. We are assuming you have downloaded the
	binary distribution or have downloaded and compiled the source distribution of VTFLib
	to your liking.

	Within your projects setting, make sure under Linker Options, that you include the
	VTFLib.lib file and include the path to it in the library search paths. Alternatively
	you can use a pragma directive. Next, add VTFLib.h in your source files where you will
	be wanting to access VTFLib functions.

	All being well you should be up and ready to use VTFLib. Don't forget to make sure you
	place VTFLib.dll in a location where your application can find it.

	\section workingwith Working with textures using VTFFile

	\subsection vtfformat The VTF file format
	The VTF file format is not particularly complicated. Specific details can be found within
	the VTFLib source code however for convenience here is a short overview.

	VTF files are essentially bitmap files containing the data which makes up an image. The format
	is not dissimilar to Microsoft's DDS format, just organised a little different and with a
	different header.

	The files header is 64 bytes and contains a magic-number to identify the file as being VTF
	format, information on the width and height of the image and flags to indicate certain properties.
	It also contains information on the format of the bitmap data for the main image, low-res
	version, MIP levels, reflectivity and bump scale.

	Following the header is the data which makes up the low-res version of the image. This low-res
	image is used to get colour values when you hit a surface covered in the image with a weapon.

	After the low-res data comes the main data compressed in the chosen format. The data is stored
	smallest MIP level first interpolated with data for any additional faces (in the case of cube
	maps) or frames for animated textures.
*/


#ifndef VTFLIB_H
#define VTFLIB_H
/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

// ============================================================
// NOTE: This file is commented for compatibility with Doxygen.
// ============================================================
/*!
	\file StdAfx.h
	\brief Application framework header plus VTFLib custom data types.
*/

#ifdef VTFLIB_EXPORTS
#	define VTFLIB_API __declspec(dllexport)
#else
#	define VTFLIB_API __declspec(dllimport)
#endif

// Custom data types
typedef unsigned char	vlBool;				//!< Boolean value 0/1.
typedef char			vlChar;				//!< Single signed character.
typedef unsigned char	vlByte;				//!< Single unsigned byte.
typedef signed short	vlShort;			//!< Signed short floating point value.
typedef unsigned short	vlUShort;			//!< Unsigned short floating point value.
typedef signed int		vlInt;				//!< Signed integer value.
typedef unsigned int	vlUInt;				//!< Unsigned integer value.
typedef signed long		vlLong;				//!< Signed long number.
typedef unsigned long	vlULong;			//!< Unsigned long number.
typedef float			vlSingle;			//!< Floating point number
typedef double			vlDouble;			//!< Double number
typedef void			vlVoid;				//!< Void value.

typedef unsigned __int8		vlUInt8;
typedef unsigned __int16	vlUInt16;
typedef unsigned __int32	vlUInt32;
typedef unsigned __int64	vlUInt64;

typedef vlSingle		vlFloat;			//!< Floating point number (same as vlSingled).

#define vlFalse			0
#define vlTrue			1

#if _MSC_VER >= 1400
#	define _CRT_SECURE_NO_WARNINGS
#	define _CRT_NONSTDC_NO_DEPRECATE
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>

#if _MSC_VER >= 1600 // Visual Studio 2010
#	define STATIC_ASSERT(condition, message) static_assert(condition, message)
#else
#	define STATIC_ASSERT(condition, message) typedef char __C_ASSERT__[(condition) ? 1 : -1]
#endif

/*!
	\file Error.h
	\brief Error handling class header.
*/

namespace VTFLib
{
	namespace Diagnostics
	{
		//! VTFLib Error handling class
		/*!
			The Error handling class allows you to aceess a text description
			for the last error encountered.
		*/

		class CError
		{
		private:
			vlChar *cErrorMessage;

		public:
			CError();
			~CError();

			//! Clear the error message buffer.
			vlVoid Clear();

			//! Get the error message text.
			const vlChar *Get() const;

			//! Set the error message buffer.
			vlVoid SetFormatted(const vlChar *cFormat, ...);
			vlVoid Set(const vlChar *cErrorMessage, vlBool bSystemError = 0);
		};
	}
}

/*!
	\file VTFFile.h
	\brief Header file for the VTFFile class.
*/

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class IReader
			{
			public:
				virtual vlBool Opened() const = 0;

				virtual vlBool Open() = 0;
				virtual vlVoid Close() = 0;

				virtual vlUInt GetStreamSize() const = 0;
				virtual vlUInt GetStreamPointer() const = 0;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode) = 0;

				virtual vlBool Read(vlChar &cChar) = 0;
				virtual vlUInt Read(vlVoid *vData, vlUInt uiBytes) = 0;
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class CFileReader : public IReader
			{
			private:
				HANDLE hFile;
				vlChar *cFileName;

			public:
				CFileReader(const vlChar *cFileName);
				~CFileReader();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Read(vlChar &cChar);
				virtual vlUInt Read(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class CMemoryReader : public IReader
			{
			private:
				vlBool bOpened;

				const vlVoid *vData;
				vlUInt uiBufferSize;

				vlUInt uiPointer;

			public:
				CMemoryReader(const vlVoid *vData, vlUInt uiBufferSize);
				~CMemoryReader();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Read(vlChar &cChar);
				virtual vlUInt Read(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class CProcReader : public IReader
			{
			private:
				vlBool bOpened;
				vlVoid *pUserData;

			public:
				CProcReader(vlVoid *pUserData);
				~CProcReader();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Read(vlChar &cChar);
				virtual vlUInt Read(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Writers
		{
			class IWriter
			{
			public:
				virtual vlBool Opened() const = 0;

				virtual vlBool Open() = 0;
				virtual vlVoid Close() = 0;

				virtual vlUInt GetStreamSize() const = 0;
				virtual vlUInt GetStreamPointer() const = 0;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode) = 0;

				virtual vlBool Write(vlChar cChar) = 0;
				virtual vlUInt Write(vlVoid *vData, vlUInt uiBytes) = 0;
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Writers
		{
			class CFileWriter : public IWriter
			{
			private:
				HANDLE hFile;
				vlChar *cFileName;

			public:
				CFileWriter(const vlChar *cFileName);
				~CFileWriter();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Write(vlChar cChar);
				virtual vlUInt Write(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Writers
		{
			class CMemoryWriter : public IWriter
			{
			private:
				vlBool bOpened;

				vlVoid *vData;
				vlUInt uiBufferSize;

				vlUInt uiPointer;
				vlUInt uiLength;

			public:
				CMemoryWriter(vlVoid *vData, vlUInt uiBufferSize);
				~CMemoryWriter();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Write(vlChar cChar);
				virtual vlUInt Write(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

namespace VTFLib
{
	namespace IO
	{
		namespace Writers
		{
			class CProcWriter : public IWriter
			{
			private:
				vlBool bOpened;
				vlVoid *pUserData;

			public:
				CProcWriter(vlVoid *pUserData);
				~CProcWriter();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Write(vlChar cChar);
				virtual vlUInt Write(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

/*!
	\file VTFFormat.h
    \brief Structures and enumerations relating to the VTF file format.

	Contains's structures and enumerations relating to the VTF file format.

	Disk file format for VTF files is as follows:
	- VTF Header (80 bytes)
	- Low Res Image (size varies)
	- Image Data (size varies)

	Image Data is stored as follows:
	- For each MIP images (starting with the smallest and getting larger)
		- For each frame
			- For each face (for cubemaps)
				- For each Z slice
					- Image data (in relevant format)
*/

#ifdef __cplusplus
extern "C" {
#endif

// VTF version numbers (current version is 7.5)
//---------------------------------------------
#define VTF_MAJOR_VERSION					7		//!< VTF major version number
#define VTF_MINOR_VERSION					5		//!< VTF minor version number
#define VTF_MINOR_VERSION_DEFAULT			3

#define VTF_MINOR_VERSION_MIN_SPHERE_MAP	1
#define VTF_MINOR_VERSION_MIN_VOLUME		2
#define VTF_MINOR_VERSION_MIN_RESOURCE		3
#define VTF_MINOR_VERSION_MIN_NO_SPHERE_MAP	5

//! Image data formats VTFLib supports.
/*!
	Image data formats supported by VTFLib. Details show colour channel order, plus number
	of bits per-pixel.
	\note "Bluescreen" alpha uses any pixel with an pixel of R0, G0, B255 as transparent.
*/
typedef enum tagVTFImageFormat
{
	IMAGE_FORMAT_RGBA8888 = 0,				//!<  = Red, Green, Blue, Alpha - 32 bpp
	IMAGE_FORMAT_ABGR8888,					//!<  = Alpha, Blue, Green, Red - 32 bpp
	IMAGE_FORMAT_RGB888,					//!<  = Red, Green, Blue - 24 bpp
	IMAGE_FORMAT_BGR888,					//!<  = Blue, Green, Red - 24 bpp
	IMAGE_FORMAT_RGB565,					//!<  = Red, Green, Blue - 16 bpp
	IMAGE_FORMAT_I8,						//!<  = Luminance - 8 bpp
	IMAGE_FORMAT_IA88,						//!<  = Luminance, Alpha - 16 bpp
	IMAGE_FORMAT_P8,						//!<  = Paletted - 8 bpp
	IMAGE_FORMAT_A8,						//!<  = Alpha- 8 bpp
	IMAGE_FORMAT_RGB888_BLUESCREEN,			//!<  = Red, Green, Blue, "BlueScreen" Alpha - 24 bpp
	IMAGE_FORMAT_BGR888_BLUESCREEN,			//!<  = Red, Green, Blue, "BlueScreen" Alpha - 24 bpp
	IMAGE_FORMAT_ARGB8888,					//!<  = Alpha, Red, Green, Blue - 32 bpp
	IMAGE_FORMAT_BGRA8888,					//!<  = Blue, Green, Red, Alpha - 32 bpp
	IMAGE_FORMAT_DXT1,						//!<  = DXT1 compressed format - 4 bpp
	IMAGE_FORMAT_DXT3,						//!<  = DXT3 compressed format - 8 bpp
	IMAGE_FORMAT_DXT5,						//!<  = DXT5 compressed format - 8 bpp
	IMAGE_FORMAT_BGRX8888,					//!<  = Blue, Green, Red, Unused - 32 bpp
	IMAGE_FORMAT_BGR565,					//!<  = Blue, Green, Red - 16 bpp
	IMAGE_FORMAT_BGRX5551,					//!<  = Blue, Green, Red, Unused - 16 bpp
	IMAGE_FORMAT_BGRA4444,					//!<  = Red, Green, Blue, Alpha - 16 bpp
	IMAGE_FORMAT_DXT1_ONEBITALPHA,			//!<  = DXT1 compressed format with 1-bit alpha - 4 bpp
	IMAGE_FORMAT_BGRA5551,					//!<  = Blue, Green, Red, Alpha - 16 bpp
	IMAGE_FORMAT_UV88,						//!<  = 2 channel format for DuDv/Normal maps - 16 bpp
	IMAGE_FORMAT_UVWQ8888,					//!<  = 4 channel format for DuDv/Normal maps - 32 bpp
	IMAGE_FORMAT_RGBA16161616F,				//!<  = Red, Green, Blue, Alpha - 64 bpp
	IMAGE_FORMAT_RGBA16161616,				//!<  = Red, Green, Blue, Alpha signed with mantissa - 64 bpp
	IMAGE_FORMAT_UVLX8888,					//!<  = 4 channel format for DuDv/Normal maps - 32 bpp
	IMAGE_FORMAT_R32F,						//!<  = Luminance - 32 bpp
	IMAGE_FORMAT_RGB323232F,				//!<  = Red, Green, Blue - 96 bpp
	IMAGE_FORMAT_RGBA32323232F,				//!<  = Red, Green, Blue, Alpha - 128 bpp
	IMAGE_FORMAT_NV_DST16,
	IMAGE_FORMAT_NV_DST24,
	IMAGE_FORMAT_NV_INTZ,
	IMAGE_FORMAT_NV_RAWZ,
	IMAGE_FORMAT_ATI_DST16,
	IMAGE_FORMAT_ATI_DST24,
	IMAGE_FORMAT_NV_NULL,
	IMAGE_FORMAT_ATI2N,
	IMAGE_FORMAT_ATI1N,
	/*
	XBox:
	IMAGE_FORMAT_X360_DST16,
	IMAGE_FORMAT_X360_DST24,
	IMAGE_FORMAT_X360_DST24F,
	IMAGE_FORMAT_LINEAR_BGRX8888,			//!<  = Blue, Green, Red, Unused - 32 bpp
	IMAGE_FORMAT_LINEAR_RGBA8888,			//!<  = Red, Green, Blue, Alpha - 32 bpp
	IMAGE_FORMAT_LINEAR_ABGR8888,			//!<  = Alpha, Blue, Green, Red - 32 bpp
	IMAGE_FORMAT_LINEAR_ARGB8888,			//!<  = Alpha, Red, Green, Blue - 32 bpp
	IMAGE_FORMAT_LINEAR_BGRA8888,			//!<  = Blue, Green, Red, Alpha - 32 bpp
	IMAGE_FORMAT_LINEAR_RGB888,				//!<  = Red, Green, Blue - 24 bpp
	IMAGE_FORMAT_LINEAR_BGR888,				//!<  = Blue, Green, Red - 24 bpp
	IMAGE_FORMAT_LINEAR_BGRX5551,			//!<  = Blue, Green, Red, Unused - 16 bpp
	IMAGE_FORMAT_LINEAR_I8,					//!<  = Luminance - 8 bpp
	IMAGE_FORMAT_LINEAR_RGBA16161616,		//!<  = Red, Green, Blue, Alpha signed with mantissa - 64 bpp
	IMAGE_FORMAT_LE_BGRX8888,				//!<  = Blue, Green, Red, Unused - 32 bpp
	IMAGE_FORMAT_LE_BGRA8888,				//!<  = Blue, Green, Red, Alpha - 32 bpp
	*/

	IMAGE_FORMAT_COUNT,
	IMAGE_FORMAT_NONE = -1
} VTFImageFormat;


//! VTF image header flags.
typedef enum tagVTFImageFlag
{
	TEXTUREFLAGS_POINTSAMPLE								= 0x00000001,
	TEXTUREFLAGS_TRILINEAR									= 0x00000002,
	TEXTUREFLAGS_CLAMPS										= 0x00000004,
	TEXTUREFLAGS_CLAMPT										= 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC								= 0x00000010,
	TEXTUREFLAGS_HINT_DXT5									= 0x00000020,
	TEXTUREFLAGS_SRGB										= 0x00000040, // Originally internal to VTex as TEXTUREFLAGS_NOCOMPRESS.
	TEXTUREFLAGS_DEPRECATED_NOCOMPRESS						= 0x00000040,
	TEXTUREFLAGS_NORMAL										= 0x00000080,
	TEXTUREFLAGS_NOMIP										= 0x00000100,
	TEXTUREFLAGS_NOLOD										= 0x00000200,
	TEXTUREFLAGS_MINMIP										= 0x00000400,
	TEXTUREFLAGS_PROCEDURAL									= 0x00000800,
	TEXTUREFLAGS_ONEBITALPHA								= 0x00001000, //!< Automatically generated by VTex.
	TEXTUREFLAGS_EIGHTBITALPHA								= 0x00002000, //!< Automatically generated by VTex.
	TEXTUREFLAGS_ENVMAP										= 0x00004000,
	TEXTUREFLAGS_RENDERTARGET								= 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET							= 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE							= 0x00020000,
	TEXTUREFLAGS_SINGLECOPY									= 0x00040000,
	TEXTUREFLAGS_UNUSED0									= 0x00080000, //!< Originally internal to VTex as TEXTUREFLAGS_ONEOVERMIPLEVELINALPHA.
	TEXTUREFLAGS_DEPRECATED_ONEOVERMIPLEVELINALPHA			= 0x00080000,
	TEXTUREFLAGS_UNUSED1									= 0x00100000, //!< Originally internal to VTex as TEXTUREFLAGS_PREMULTCOLORBYONEOVERMIPLEVEL.
	TEXTUREFLAGS_DEPRECATED_PREMULTCOLORBYONEOVERMIPLEVEL	= 0x00100000,
	TEXTUREFLAGS_UNUSED2									= 0x00200000, //!< Originally internal to VTex as TEXTUREFLAGS_NORMALTODUDV.
	TEXTUREFLAGS_DEPRECATED_NORMALTODUDV					= 0x00200000,
	TEXTUREFLAGS_UNUSED3									= 0x00400000, //!< Originally internal to VTex as TEXTUREFLAGS_ALPHATESTMIPGENERATION.
	TEXTUREFLAGS_DEPRECATED_ALPHATESTMIPGENERATION			= 0x00400000,
	TEXTUREFLAGS_NODEPTHBUFFER								= 0x00800000,
	TEXTUREFLAGS_UNUSED4									= 0x01000000, //!< Originally internal to VTex as TEXTUREFLAGS_NICEFILTERED.
	TEXTUREFLAGS_DEPRECATED_NICEFILTERED					= 0x01000000,
	TEXTUREFLAGS_CLAMPU										= 0x02000000,
	TEXTUREFLAGS_VERTEXTEXTURE								= 0x04000000,
	TEXTUREFLAGS_SSBUMP										= 0x08000000,
	TEXTUREFLAGS_UNUSED5									= 0x10000000, //!< Originally TEXTUREFLAGS_UNFILTERABLE_OK.
	TEXTUREFLAGS_DEPRECATED_UNFILTERABLE_OK					= 0x10000000,
	TEXTUREFLAGS_BORDER										= 0x20000000,
	TEXTUREFLAGS_DEPRECATED_SPECVAR_RED						= 0x40000000,
	TEXTUREFLAGS_DEPRECATED_SPECVAR_ALPHA					= 0x80000000,
	TEXTUREFLAGS_LAST										= 0x20000000,
	TEXTUREFLAGS_COUNT										= 30
} VTFImageFlag;

//! VTF image cubemap face indices.
typedef enum tagVTFCubeMapFace
{
	CUBEMAP_FACE_RIGHT = 0,		// +x
	CUBEMAP_FACE_LEFT,			// -x
	CUBEMAP_FACE_BACK,			// +y
	CUBEMAP_FACE_FRONT,			// -y
	CUBEMAP_FACE_UP,			// +z
	CUBEMAP_FACE_DOWN,			// -z
	CUBEMAP_FACE_SphereMap,		// fall back
	CUBEMAP_FACE_COUNT
} VTFCubeMapFace;

//! MIP map reduction filter indices.
typedef enum tagVTFMipmapFilter
{
    MIPMAP_FILTER_BOX = 0,
    MIPMAP_FILTER_TRIANGLE,
    MIPMAP_FILTER_KAISER,
    MIPMAP_FILTER_COUNT
} VTFMipmapFilter;

typedef enum tagVTFResizeFilter
{
	RESIZE_FILTER_BOX = 0,
	RESIZE_FILTER_TRIANGLE,
	RESIZE_FILTER_KAISER,
	RESIZE_FILTER_MITCHELL,
	RESIZE_FILTER_COUNT
} VTFResizeFilter;

typedef enum tagDXTQuality
{
	DXT_QUALITY_LOW,
	DXT_QUALITY_MEDIUM,
	DXT_QUALITY_HIGH,
	DXT_QUALITY_HIGHEST,
	DXT_QUALITY_COUNT
} VTFDXTQuality;

//! Normal map height conversion method indices.
typedef enum tagVTFHeightConversionMethod
{
    HEIGHT_CONVERSION_METHOD_ALPHA = 0,
    HEIGHT_CONVERSION_METHOD_AVERAGE_RGB,
    HEIGHT_CONVERSION_METHOD_RED,
    HEIGHT_CONVERSION_METHOD_GREEN,
    HEIGHT_CONVERSION_METHOD_BLUE,
	HEIGHT_CONVERSION_METHOD_COUNT
} VTFHeightConversionMethod;

//! Normal map alpha channel handling indices.
typedef enum tagVTFNormalAlphaResult
{
	NORMAL_ALPHA_RESULT_NOCHANGE = 0,
    NORMAL_ALPHA_RESULT_HEIGHT,
    NORMAL_ALPHA_RESULT_BLACK,
    NORMAL_ALPHA_RESULT_WHITE,
	NORMAL_ALPHA_RESULT_COUNT
} VTFNormalAlphaResult;

//! Image re-size handling method indices.
typedef enum tagVTFResizeMethod
{
    RESIZE_NEAREST_POWER2 = 0,
    RESIZE_BIGGEST_POWER2,
    RESIZE_SMALLEST_POWER2,
    RESIZE_SET,
	RESIZE_COUNT
} VTFResizeMethod;

//! Spheremap creation look direction indices.
//--------------------------------------------
typedef enum tagVTFLookDir
{
	LOOK_DOWN_X = 0,
	LOOK_DOWN_NEGX,
	LOOK_DOWN_Y,
	LOOK_DOWN_NEGY,
	LOOK_DOWN_Z,
	LOOK_DOWN_NEGZ
} VTFLookDir;

#define MAKE_VTF_RSRC_ID(a, b, c) ((vlUInt)(((vlByte)a) | ((vlByte)b << 8) | ((vlByte)c << 16)))
#define MAKE_VTF_RSRC_IDF(a, b, c, d) ((vlUInt)(((vlByte)a) | ((vlByte)b << 8) | ((vlByte)c << 16) | ((vlByte)d << 24)))

//! Resource entry type flags.
//--------------------------------------------
typedef enum tagVTFResourceEntryTypeFlag
{
	RSRCF_HAS_NO_DATA_CHUNK = 0x02
} VTFResourceEntryTypeFlag;

//! Resource entry type idendifiers.
//--------------------------------------------
typedef enum tagVTFResourceEntryType
{
	VTF_LEGACY_RSRC_LOW_RES_IMAGE = ((vlUInt)(((vlByte)0x01) | ((vlByte)0 << 8) | ((vlByte)0 << 16))),
	VTF_LEGACY_RSRC_IMAGE = ((vlUInt)(((vlByte)0x30) | ((vlByte)0 << 8) | ((vlByte)0 << 16))),
	VTF_RSRC_SHEET = ((vlUInt)(((vlByte)0x10) | ((vlByte)0 << 8) | ((vlByte)0 << 16))),
	VTF_RSRC_CRC = ((vlUInt)(((vlByte)'C') | ((vlByte)'R' << 8) | ((vlByte)'C' << 16) | ((vlByte)RSRCF_HAS_NO_DATA_CHUNK << 24))),
	VTF_RSRC_TEXTURE_LOD_SETTINGS = ((vlUInt)(((vlByte)'L') | ((vlByte)'O' << 8) | ((vlByte)'D' << 16) | ((vlByte)RSRCF_HAS_NO_DATA_CHUNK << 24))),
	VTF_RSRC_TEXTURE_SETTINGS_EX = ((vlUInt)(((vlByte)'T') | ((vlByte)'S' << 8) | ((vlByte)'O' << 16) | ((vlByte)RSRCF_HAS_NO_DATA_CHUNK << 24))),
	VTF_RSRC_KEY_VALUE_DATA = ((vlUInt)(((vlByte)'K') | ((vlByte)'V' << 8) | ((vlByte)'D' << 16))),
	VTF_RSRC_MAX_DICTIONARY_ENTRIES = 32
} VTFResourceEntryType;

#pragma pack(1)

//! VTFFileHeader struct.
/*!

	The VTF file header sits at the start of a VTF file and is used to
	determine which version of the file is being loaded.
*/
struct SVTFFileHeader
{
	vlChar			TypeString[4];					//!< "Magic number" identifier- "VTF\0".
	vlUInt			Version[2];						//!< Version[0].version[1] (currently 7.2)
	vlUInt			HeaderSize;						//!< Size of the header struct (currently 80 bytes)
};

//! VTFHeader_70 struct.
/*!

	The complete header for v7.0 of the VTF file format.
*/
struct SVTFHeader_70 : public SVTFFileHeader
{
	vlUShort		Width;							//!< Width of the largest image
	vlUShort		Height;							//!< Height of the largest image
	vlUInt			Flags;							//!< Flags for the image
	vlUShort		Frames;							//!< Number of frames if animated (1 for no animation)
	vlUShort		StartFrame;						//!< Start frame (always 0)
	vlByte			Padding0[4];					//!< Reflectivity padding (16 byte alignment)
	vlSingle		Reflectivity[3];				//!< Reflectivity vector
	vlByte			Padding1[4];					//!< Reflectivity padding (8 byte packing)
	vlSingle		BumpScale;						//!< Bump map scale
	VTFImageFormat	ImageFormat;					//!< Image format index
	vlByte			MipCount;						//!< Number of MIP levels (including the largest image)
	VTFImageFormat	LowResImageFormat;				//!< Image format of the thumbnail image
	vlByte			LowResImageWidth;				//!< Thumbnail image width
	vlByte			LowResImageHeight;				//!< Thumbnail image height
};

//! VTFHeader_70_A struct.
/*!

	The complete header for v7.0 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_70_A : public SVTFHeader_70 {};

//! VTFHeader_71 struct.
/*!

	The complete header for v7.1 of the VTF file format.
*/
struct SVTFHeader_71 : public SVTFHeader_70
{

};

//! VTFHeader_71_A struct.
/*!

	The complete header for v7.1 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_71_A : public SVTFHeader_71 {};

//! VTFHeader_72 struct.
/*!

	The complete header for v7.2 of the VTF file format.
*/
struct SVTFHeader_72 : public SVTFHeader_71
{
	vlUShort		Depth;							//!< Depth of the largest image
};

//! VTFHeader_72_A struct.
/*!

	The complete header for v7.2 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_72_A : public SVTFHeader_72 {};

//! VTFHeader_73 struct.
/*!

	The complete header for v7.3 of the VTF file format.
*/
struct SVTFHeader_73 : public SVTFHeader_72
{
	vlByte		Padding2[3];
	vlUInt		ResourceCount;							//!< Number of image resources
};

//! VTFHeader_72_A struct.
/*!

	The complete header for v7.3 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_73_A : public SVTFHeader_73 {};

//! VTFHeader_74 struct.
/*!

	The complete header for v7.4 of the VTF file format.
*/
struct SVTFHeader_74 : public SVTFHeader_73
{

};

//! VTFHeader_74_A struct.
/*!

	The complete header for v7.4 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_74_A : public SVTFHeader_74 {};

//! VTFHeader_75 struct.
/*!

	The complete header for v7.5 of the VTF file format.
*/
struct SVTFHeader_75 : public SVTFHeader_74
{

};

//! VTFHeader_75_A struct.
/*!

	The complete header for v7.5 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_75_A : public SVTFHeader_75 {};

struct SVTFResource
{
	union
	{
		vlUInt Type;
		struct
		{
			vlByte ID[3];	//!< Unique resource ID
			vlByte Flags;	//!< Resource flags
		};
	};
	vlUInt Data;	//!< Resource data (e.g. for a  CRC) or offset from start of the file
};

struct SVTFResourceData
{
	vlUInt Size;	//!< Resource data buffer size
	vlByte *Data;	//!< Resource data bufffer
};

typedef struct tagSVTFTextureLODControlResource
{
	vlByte ResolutionClampU;
	vlByte ResolutionClampV;
	vlByte Padding[2];
} SVTFTextureLODControlResource;

typedef struct tagSVTFTextureSettingsExResource
{
	vlByte Flags0;
	vlByte Flags1;
	vlByte Flags2;
	vlByte Flags3;
} SVTFTextureSettingsExResource;

struct SVTFHeader : public SVTFHeader_74_A
{
	vlByte				Padding3[8];
	SVTFResource		Resources[VTF_RSRC_MAX_DICTIONARY_ENTRIES];
	SVTFResourceData	Data[VTF_RSRC_MAX_DICTIONARY_ENTRIES];
};

#pragma pack()

//! VTFImageFormat info struct.
/*!
	The SVTFImageFormatInfo struct provides information on VTF image formats.

	\see VTFImageFormat
*/
#pragma pack(1)
typedef struct tagSVTFImageFormatInfo
{
	const vlChar *lpName;			//!< Enumeration text equivalent.
	vlUInt	uiBitsPerPixel;			//!< Format bits per pixel.
	vlUInt	uiBytesPerPixel;		//!< Format bytes per pixel.
	vlUInt	uiRedBitsPerPixel;		//!< Format red bits per pixel.  0 for N/A.
	vlUInt	uiGreenBitsPerPixel;	//!< Format green bits per pixel.  0 for N/A.
	vlUInt	uiBlueBitsPerPixel;		//!< Format blue bits per pixel.  0 for N/A.
	vlUInt	uiAlphaBitsPerPixel;	//!< Format alpha bits per pixel.  0 for N/A.
	vlBool	bIsCompressed;			//!< Format is compressed (DXT).
	vlBool	bIsSupported;			//!< Format is supported by VTFLib.
} SVTFImageFormatInfo;
#pragma pack()

//! VTF Creation options struct.
/*!
	The SVTFCreateOptions struct defines options and settings to be used when
	creating VTF images	with methods such as CVTFFile::Create().

	\see CVTFFile::Create()
*/
#pragma pack(1)
typedef struct tagSVTFCreateOptions
{
	vlUInt uiVersion[2];								//!< Output image version.
	VTFImageFormat ImageFormat;							//!< Output image output storage format.

	vlUInt uiFlags;										//!< Output image header flags.
	vlUInt uiStartFrame;								//!< Output image start frame.
	vlSingle sBumpScale;								//!< Output image bump scale.
	vlSingle sReflectivity[3];							//!< Output image reflectivity. (Only used if bReflectivity is false.)

	vlBool bMipmaps;									//!< Generate MIPmaps. (Space is always allocated.)
	VTFMipmapFilter MipmapFilter;						//!< MIP map re-size filter.

	vlBool bThumbnail;									//!< Generate thumbnail image.
	vlBool bReflectivity;								//!< Compute image reflectivity.

	vlBool bResize;										//!< Resize the input image.
	VTFResizeMethod ResizeMethod;						//!< New size compution method.
	VTFResizeFilter ResizeFilter;						//!< Re-size filter.
	vlUInt uiResizeWidth;								//!< New width after re-size if method is RESIZE_SET.
	vlUInt uiResizeHeight;								//!< New height after re-size if method is RESIZE_SET.

	vlBool bResizeClamp;								//!< Clamp re-size size.
	vlUInt uiResizeClampWidth;							//!< Maximum width to re-size to.
	vlUInt uiResizeClampHeight;							//!< Maximum height to re-size to.

	vlBool bGammaCorrection;							//!< Gamma correct input image.
	vlSingle sGammaCorrection;							//!< Gamma correction to apply.

	vlBool bNormalMap;									//!< Convert input image to a normal map.
	VTFHeightConversionMethod HeightConversionMethod;	//!< Method or determining height from input image during normal map creation.
	VTFNormalAlphaResult NormalAlphaResult;				//!< How to handle output image alpha channel, post normal map creation.
	vlBool bNormalWrap;									//!< Wrap the normal map.

	vlBool bSphereMap;									//!< Generate a sphere map for six faced environment maps.
} SVTFCreateOptions;
#pragma pack()

#ifdef __cplusplus
}
#endif

namespace VTFLib
{
	//! VTF File access/creation class.
	/*!
		The CVTFFile class is the component designed for working with VTF
		format image files. Its public functions allow you to load, save
		and create new VTF files plus perform various processes on the
		image data such as the generation of MIP maps or Normal maps.

		VTFFile generally use RGBA8888 format for passing data to and from
		functions. This is 4 bytes per pixel, 8-bits per channel colour or
		in short, uncompressed 32-bit image data. There are functions for
		converting the data to other formats internally, however for image
		creation you are probably sticking best with RGBA8888 for simplicity.

		The majority of functions return a vlBool value. This is simply a
		test as to whether a function has succeeded or failed to execute properly.
		In the case of functions for checking flags, the vlBool indicates
		if the flag is set or unset. Other data types reflect the purpose
		of the function used.
	*/

	class VTFLIB_API CVTFFile
	{
	private:

		SVTFHeader *Header;						// VTF header

		vlUInt uiImageBufferSize;				// Size of VTF image data buffer
		vlByte *lpImageData;					// VTF image buffer

		vlUInt uiThumbnailBufferSize;			// Size of VTF thumbnail image data buffer
		vlByte *lpThumbnailImageData;			// VTF thumbnail image buffer

	public:

		CVTFFile();		//!< Default constructor

		//! Create a new VTFFile class as a copy of another.
		/*!
			Creates a new VTFFile class as a copy of an existing one. The copy is not linked
			so any changes to it will not effect the class instance it was derived from.

			\param VTFFile is the CVTFFile class you want to copy.
		*/

		CVTFFile(const CVTFFile &VTFFile);

		//! Create a new VTFFile class as a duplicate of another.
		/*!
			Create a new VTFFile class as a duplicate of an existing one, but convert
			the image data to the specified format.

			\param VTFFile is the CVTFFile class you want to copy.
			\param ImageFormat the format you want to convert the copied image data to.
		*/

		CVTFFile(const CVTFFile &VTFFile, VTFImageFormat ImageFormat);

		~CVTFFile();	//!< Deconstructor

	public:

		//! Creates a new empty VTF image..
		/*!
			Creates a new empty VTF format image within a the current CVTFFile class.

			\param uiWidth is the width in pixels of the main VTF image.
			\param uiHeight is the height in pixels of the main VTF image.
			\param uiFrames is the number of frames in the VTF image (default 1).
			\param uiFaces is the number of faces in the VTF image (default 1).
			\param uiSlices is the number of z slices in the VTF image (default 1).
			\param ImageFormat is the storage format of the main VTF image (default RGBA8888).
			\param bThumbnail sets if the VTF image will contain an additional thumbnail (default true).
			\param bNullImageData sets if the image data should be zero'd out on creation (default false).
			\return true on successful creation, otherwise false.
			\note Animated and static textures have 1 face. Cubemaps have 6, one for each side of the cube.
			\see tagSVTFCreateOptions
		*/

		vlBool Create(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames = 1, vlUInt uiFaces = 1, vlUInt uiSlices = 1, VTFImageFormat ImageFormat = IMAGE_FORMAT_RGBA8888, vlBool bThumbnail = 1, vlBool bMipmaps = 1, vlBool bNullImageData = 0);

		//! Create a new VTF image from existing data.
		/*!
			Creates a new VTF image using image data already stored in memory. The existing
			image data should be stored in RGBA8888 format.

			\param uiWidth is the width in pixels of the main VTF image.
			\param uiHeight is the height in pixels of the main VTF image.
			\param lpImageDataRGBA8888 is a pointer to the source RGBA8888 data.
			\param VTFCreateOptions contains the options for image creation.
			\return true on successful creation, otherwise false.
			\see tagSVTFCreateOptions
		*/

		vlBool Create(vlUInt uiWidth, vlUInt uiHeight, vlByte *lpImageDataRGBA8888, const SVTFCreateOptions &VTFCreateOptions);

		//! Create a new VTF multi-frame or cubemap image from existing data.
		/*!
			Creates a new multi-frame or cubemap VTF image using image data already stored
			in memory. The existing image data should be stored in RGBA8888 format.

			\param uiWidth is the width in pixels of the main VTF image.
			\param uiHeight is the height in pixels of the main VTF image.
			\param uiFrames is the number of frames in the VTF image.
			\param uiFaces is the number of faces in the VTF image.
			\param vlSlices is the number of z slices in the VTF image.
			\param lpImageDataRGBA8888 is an array of pointers to the image data for each frame/face.
			\param VTFCreateOptions contains the options for image creation.
			\return true on successful creation, otherwise false.
			\note Animated and static textures have 1 face. Cubemaps have 6, one for each side of the cube.
			\see tagSVTFCreateOptions
		*/

		vlBool Create(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt vlSlices, vlByte **lpImageDataRGBA8888, const SVTFCreateOptions &VTFCreateOptions);

		//! Destroys the current VTF image by setting the header, thumbnail and image data to zero.
		vlVoid Destroy();

		//! Check if a VTFFile image is loaded or valid.
		/*!
			Checks if a file was loaded or a new image was created correctly by
			checking for the existance of a valid header struct in the VTFFile class.

			\return true if header is valid, otherwise false.
			\see Create()
		*/

		vlBool IsLoaded() const;

		//! Loads a VTF image from disk.
		/*!
			Loads a VTF image file from disk into the current VTFFile class. You may choose to
			load just the header only if you want to get info about the file and save memory.

			\param cFileName is the path and filename of the file to load.
			\param bHeaderOnly sets whether to load just the VTF header or not (default false).
			\return true on sucessful load, otherwise false.
		*/

		vlBool Load(const vlChar *cFileName, vlBool bHeaderOnly = 0);

		//! Loads a VTF image from memory.
		/*!
			Loads a VTF image file stored in memory into the current VTFFile class.
			You may choose to load just the header only if you want to get info about the file
			and save memory.

			\param lpData is a pointer to the VTF file in memory.
			\param uiBufferSize is the size of the VTF file in bytes.
			\param bHeaderOnly sets whether to load just the VTF header or not (default false).
			\return true on sucessful load, otherwise false.
		*/

		vlBool Load(const vlVoid *lpData, vlUInt uiBufferSize, vlBool bHeaderOnly = 0);

		//! Loads a VTF image using callback functions.
		/*!
			Loads a VTF image file into the current VTFFile class.
			You may choose to load just the header only if you want to get info about the file
			and save memory.

			\param pUserData is a pointer to custom user data.
			\param bHeaderOnly sets whether to load just the VTF header or not (default false).
			\return true on sucessful load, otherwise false.
		*/

		vlBool Load(vlVoid *pUserData, vlBool bHeaderOnly = 0);

		//! Save a VTF image from disk.
		/*!
			Saves a VTF format image file to disk from the current VTFFile class.

			\param cFileName is the path and filename of the file to load.
			\return true on sucessful save, otherwise false.
		*/

		vlBool Save(const vlChar *cFileName) const;

		//! Save a VTF image to memory.
		/*!
			Saves a VTF format image file to memory from the current VTFFile class.

			\param lpData is a pointer to save the image to.
			\param uiBufferSize is the size of the VTF file in bytes.
			\return true on sucessful save, otherwise false.
		*/

		vlBool Save(vlVoid *lpData, vlUInt uiBufferSize, vlUInt &uiSize) const;

		//! Save a VTF image using callback functions.
		/*!
			Saves a VTF format image file from the current VTFFile class.

			\param pUserData is a pointer to custom user data.
			\return true on sucessful save, otherwise false.
		*/

		vlBool Save(vlVoid *pUserData) const;

	private:
		vlBool IsPowerOfTwo(vlUInt uiSize);
		vlUInt NextPowerOfTwo(vlUInt uiSize);

		vlVoid ComputeResources();	 //!< Computes header VTF directory resources.

		// Interface with out reader/writer classes
		vlBool Load(IO::Readers::IReader *Reader, vlBool bHeaderOnly);
		vlBool Save(IO::Writers::IWriter *Writer) const;

	public:

		//! Check if image data has been loaded.
		/*!
			Check to see if the image buffer has data in it. If a VTF file was loaded
			into the class with the bHeaderOnly option, this will return false.

			\return true if image data is present, otherwise false.
		*/

		vlBool GetHasImage() const;

		vlUInt GetMajorVersion() const;	 //!< Returns the VTF file major version number.
		vlUInt GetMinorVersion() const;	 //!< Returns the VTF file minor version number.
		vlUInt GetSize() const;			 //!< Returns the VTF file size in bytes.

		vlUInt GetWidth() const;	//!< Returns the width of the image in pixels from the VTF header.
		vlUInt GetHeight() const;	//!< Returns the height of the image in pixels from the VTF header.
		vlUInt GetDepth() const;	//!< Returns the depth of the image in pixels from the VTF header.

		vlUInt GetFrameCount() const;	//!< Returns the frame count from the VTF header.
		vlUInt GetFaceCount() const;	//!< Returns the face count from the VTF header.
		vlUInt GetMipmapCount() const;	//!< Returns the number of MIP levels in the image from the VTF header.

		vlUInt GetStartFrame() const;				//!< Returns the start frame from the VTF header.
		vlVoid SetStartFrame(vlUInt uiStartFrame);  //!< Sets the start frame in the VTF header.

		vlUInt GetFlags() const;	//!< Returns the image flags from the VTF header.
		vlVoid SetFlags(vlUInt uiFlags); 	//!< Sets the image flags in the VTF header.

		//! Check if a specific flag is set in the VTF header.
		/*!
			Checks to see if the given flag is set in the VTF header struct.

			\param ImageFlag is the flag you wish to check for.
			\return true if the flag is set, otherwise false.
		*/

		vlBool GetFlag(VTFImageFlag ImageFlag) const;

		//! Set the state of a specific flag in the VTF header.
		/*!
			Set the boolean state of the given flag in the VTF header struct.

			\param ImageFlag is the flag you wish to set.
			\param bState is the state you wish to set for the flag.
		*/

		vlVoid SetFlag(VTFImageFlag ImageFlag, vlBool bState);

		vlSingle GetBumpmapScale() const;	//!< Get the bump scale value.

		//! Set the bump scale value.
		/*!
			Sets the bump scale in the VTF header to the given floating point value.
			\param sBumpmapScale is the scale value to set.
		*/

		vlVoid SetBumpmapScale(vlSingle sBumpmapScale);

		//! Get the reflectivity values.
		/*!
			Get the reflectivity value for each vector axis from the VTF header.

			\param sX, sY, sZ are the variables to hold the values reflectivity vector.
		*/

		vlVoid GetReflectivity(vlSingle &sX, vlSingle &sY, vlSingle &sZ) const;

		//! Set the reflectivity values.
		/*!
			Set the reflectivity value for each vector axis in the VTF header.

			\param sX, sY, sZ are the values for each reflectivity vector axis.
		*/

		vlVoid SetReflectivity(vlSingle sX, vlSingle sY, vlSingle sZ);

		VTFImageFormat GetFormat() const;	//!< Returns the storage format of the main image data set in the VTF header.

		//! Get a pointer to the image data for a specific image.
		/*!
			Returns a pointer to the image data for a given frame, face and MIP level.

			\param uiFrame is the desired frame.
			\param uiFace is the desired face.
			\param uiSlice is the desired z slice.
			\param uiMipmapLevel is the desired MIP level.
			\note Frames start at index 0 for the first frame. Faces start at index 0
			for the first face. Cubemaps have 6 faces, others only 1. MIP levels start
			at index 0 for the largest image moving down in size.
			\see GetFormat()
		*/

		vlByte *GetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel) const;

		//! Set the image data for a specific image.
		/*!
			Sets the image data for a given frame, face and MIP level. The source image
			data pointed to by lpData must be in the format specified in the VTF header.

			\param uiFrame is the desired frame.
			\param uiFace is the desired face.
			\param uiSlice is the desired z slice.
			\param uiMipmapLevel is the desired MIP level.
			\param lpData is a pointer to the image data.
			\return vlByte pointer to the image data.
			\note Frames start at index 0 for the first frame. Faces start at index 0
			for the first face. Cubemaps have 6 faces, others only 1. MIP levels start
			at index 0 for the largest image moving down in size.
			\see GetFormat()
		*/

		vlVoid SetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, vlByte *lpData);

	public:

		vlBool GetHasThumbnail() const;		//!< Returns if a the current VTF image image contains a thumbnail version.

		vlUInt GetThumbnailWidth() const;	//!< Returns the width in pixels of the current images thumbnail.
		vlUInt GetThumbnailHeight() const;	//!< Returns the heught in pixels of the current images thumbnail.

		VTFImageFormat GetThumbnailFormat() const;	//!< Returns the image format of the current images thumbnail.

		//! Get a pointer to the thumbnail image data for the current image.
		/*!
			Returns a pointer to the thumbnail image data for the current image.
			\return vlByte pointer to the image data.
			\see GetThumbnailFormat()
		*/

		vlByte *GetThumbnailData() const;

		//! Set the thumbnail image data for the current image.
		/*!
			Sets the thumbnail image data for the current image. The source image
			data pointed to by lpData must be in the format specified for the thumbnail
			in the VTF header.

			\param lpData is a pointer to the image data.
			\see GetThumbnailFormat()
		*/

		vlVoid SetThumbnailData(vlByte *lpData);

	public:
		vlBool GetSupportsResources() const;			//!< Returns true if the current VTF file version supports resources.

		vlUInt GetResourceCount() const;				//!< Returns the number of resources contained within the VTF file.
		vlUInt GetResourceType(vlUInt uiIndex) const;	//!< Returns the resource type;
		vlBool GetHasResource(vlUInt uiType) const;		//!< Returns true if the resource exists.

		//! Get a VTF resource type's data.
		/*!
			Checks to see if the resource type exists and returns it's data.

			\param uiType is the resource type to retrieve.
			\param uiSize is the size of the resource data.
			\return a pointer to the resource data buffer if the resource exists.
		*/

		vlVoid *GetResourceData(vlUInt uiType, vlUInt &uiSize) const;

		//! Set a VTF resource type's data.
		/*!
			Set a resource type's data.  If the type deson't exist, the resource is
			created.  If uiSize is 0, the resource is deleted.

			\param uiType is the resource type to set.
			\param uiSize is the size of the resource data; if 0 the resource is deleted, otherwise if the resource does not have a data chunk this must be 4.
			\param lpData is the resource data; if null the resource data is zeroed.
			\return a pointer to the resource data buffer if the resource exists or was created.
		*/

		vlVoid *SetResourceData(vlUInt uiType, vlUInt uiSize, vlVoid *lpData);

	public:

		//! Generate MIP maps from the main image data.
		/*!
			Generates MIP maps for the image down to 1 x 1 pixel using the data in
			MIP level 0 as the source. Unless otherwise specified, a standard box
			filter with no sharpening is used during compression.

			\param MipmapFilter is the reduction filter to use (default Box).
			\param SharpenFilter is the sharpening filter to use (default none).
			\return true on sucessful creation, otherwise false.
		*/

		vlBool GenerateMipmaps(VTFMipmapFilter MipmapFilter = MIPMAP_FILTER_BOX);

		//! Generate MIP maps from a specific face and frame.
		/*!
			Generates MIP maps for the image down to 1 x 1 pixel using the data in
			the given face and frame as the source. Unless otherwise specified, a
			standard box filter with no sharpening is used during compression.

			\param uiFace is the face index to use.
			\param uiFrame is the frame index to use.
			\param MipmapFilter is the reduction filter to use (default Box).
			\param SharpenFilter is the sharpening filter to use (default none).
			\note Frames start at index 0 for the first frame. Faces start at index 0
			for the first face. Cubemaps have 6 faces, others only 1.
			\return true on sucessful creation, otherwise false.
		*/

		vlBool GenerateMipmaps(vlUInt uiFace, vlUInt uiFrame, VTFMipmapFilter MipmapFilter = MIPMAP_FILTER_BOX);

		//! Generate a thumbnail image.
		/*!
			Generates the thumbnail image for the VTF image by copying an existing MIP map
			of the right size and converting it to the required format.

			\return true on sucessful creation, otherwise false.
			\see SetThumbnailData()
		*/

		vlBool GenerateThumbnail();

		//! Convert image to a normal map.
		/*!
			Converts the image to a normal map using the image data in
			MIP level 0 as the source.

			\param KernelFilter is the kernel filter to use (default 3x3).
			\param HeightConversionMethod is the method of determining the height data from the source (default average RGB).
			\param NormalAlphaResult is how the alpha channel should be handled post processing (defaul make 100% opaque).
			\return true on sucessful creation, otherwise false.
			\note  The options for conversion are the same used in the nVidea NormalMap Photoshop plug-in.
		*/

		vlBool GenerateNormalMap(VTFHeightConversionMethod HeightConversionMethod = HEIGHT_CONVERSION_METHOD_AVERAGE_RGB, VTFNormalAlphaResult NormalAlphaResult = NORMAL_ALPHA_RESULT_WHITE);

		//! Convert image to a normal map from a specific frame.
		/*!
			Converts the image to a normal map using the image data in
			the given frame as the source.

			\param uiFrame is the frame index to use.
			\param KernelFilter is the kernel filter to use (default 3x3).
			\param HeightConversionMethod is the method of determining the height data from the source (default average RGB).
			\param NormalAlphaResult is how the alpha channel should be handled post processing (defaul make 100% opaque).
			\return true on sucessful creation, otherwise false.
			\note  The options for conversion are the same used in the nVidea NormalMap Photoshop plug-in.
		*/

		vlBool GenerateNormalMap(vlUInt uiFrame, VTFHeightConversionMethod HeightConversionMethod = HEIGHT_CONVERSION_METHOD_AVERAGE_RGB, VTFNormalAlphaResult NormalAlphaResult = NORMAL_ALPHA_RESULT_WHITE);

		vlBool GenerateSphereMap();		//!< Creates a spheremap from using the 6 faces of the image making up its cubemap.

	public:

		vlBool ComputeReflectivity();	//!< Calculates and sets the reflectivity vector values for the VTF image based on the colour averages of each pixel.

	public:

		//! Get VTFImageFormat info.
		/*!
			Returns a SImageFormatInfo info struct for the specified VTFImageFormat.

			\param ImageFormat is the format to get info on.
			\return SImageFormatInfo info struct.
		*/

		static SVTFImageFormatInfo const &GetImageFormatInfo(VTFImageFormat ImageFormat);

		//! Calculate data buffer size for an image
		/*!
			Returns the total memory needed in bytes for an image uiWidth and uiHeight in size,
			in the specified format. The result includes the memory used by all MIP map levels
			from the largest dimension down to 1 x 1 pixel.

			\param uiWidth is the width in pixels of the largest MIP level.
			\param uiHeight is the height in pixels of the largest MIP level.
			\param uiDepth is the depth in pixels of the largest MIP level.
			\param ImageFormat is the storage format of the image data.
			\return size of the image data in bytes.
		*/

		static vlUInt ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, VTFImageFormat ImageFormat);

		//! Calculate data buffer size for an image with MIP maps
		/*!
			Returns the total memory needed in bytes for an image uiWidth and uiHeight in size,
			in the specified format. The result includes the memory used by the number of MIP
			maps given as uiMipmaps starting with the original width and height.

			\param uiWidth is the width in pixels of the largest MIP level.
			\param uiHeight is the height in pixels of the largest MIP level.
			\param uiDepth is the depth in pixels of the largest MIP level.
			\param uiMipmaps is the number of MIP maps to include in the calculation starting with the largest.
			\param ImageFormat is the storage format of the image data.
			\return size of the image data in bytes.
		*/

		static vlUInt ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmaps, VTFImageFormat ImageFormat);

		//! Compute the number of MIP maps needed by an image
		/*!
			Returns how many MIP map levels an image of the specified size will need down to
			1 x 1 pixels. The count includes the original source image.

			\param uiWidth is the width in pixels of the original image.
			\param uiHeight is the height in pixels of the original image.
			\param uiDepth is the depth in pixels of the original image.
			\return number of MIP maps needed.
		*/

		static vlUInt ComputeMipmapCount(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth);	//!< Returns how many MIP map levels are required for an image uiWidth and uiHeight in size, down to 1x1 pixel.

		//! Compute the dimensions of a specific MIP level.
		/*!
			Returns the dimensions of a given MIP level where the largest MIP level
			(level 0) is the specified width and height.

			\param uiWidth is the width in pixels of the largest MIP level.
			\param uiHeight is the height in pixels of the largest MIP level.
			\param uiDepth is the depth in pixels of the largest MIP level.
			\param uiMipmapLevel is the MIP level you want the dimensions of.
			\param uiMipmapWidth is the variable to hold the calculated width.
			\param uiMipmapHeight is the variable to hold the calculated height.
			\param uiMipmapDepth is the variable to hold the calculated depth.
		*/

		static vlVoid ComputeMipmapDimensions(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, vlUInt &uiMipmapWidth, vlUInt &uiMipmapHeight, vlUInt &uiMipmapDepth);

		//! Compute how much memory a specific MIP map level needs.
		/*!
			Computers the total memory needed in bytes for the a specific MIP map level
			of an image of a given width and height stored in the specified image format.

			\param uiWidth is the width in pixels of the source image.
			\param uiHeight is the height in pixels of the source image.
			\param uiDepth is the depth in pixels of the source image.
			\param uiMipmapLevel is the MIP level you want the size of.
			\param ImageFormat is the image format the MIP map image data is stored in.
			\return size of the MIP map image data in bytes.
		*/

		static vlUInt ComputeMipmapSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat);

	private:

		// Calculates where in the VTF image the data begins
		vlUInt ComputeDataOffset(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat) const;

	public:

		//! Convert an image to RGBA8888 format.
		/*!
			Converts image data stored in the given format to RGBA8888 format.

			\param lpSource is a pointer to the source image data.
			\param lpDest is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param SourceFormat is the image format of the source data.
			\return true on sucessful conversion, otherwise false.
		*/

		static vlBool ConvertToRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat);

		//! Convert an image from RGBA8888 format.
		/*!
			Converts image data stored in RGBA8888 format to the the specified storage format.

			\param lpSource is a pointer to the source image data in RGBA8888 format.
			\param lpDest is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param DestFormat is the image format you wish to convert to.
			\return true on sucessful conversion, otherwise false.
		*/

		static vlBool ConvertFromRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat);

		//! Convert an image from any format to any format.
		/*!
			Converts image data stored in any format to the the specified storage format.

			\param lpSource is a pointer to the source image data.
			\param lpDest is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param SourceFormat is the image format you are converting from.
			\param DestFormat is the image format you wish to convert to.
			\return true on sucessful conversion, otherwise false.
		*/

		static vlBool Convert(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat, VTFImageFormat DestFormat);

		//! Convert an image to a normal map.
		/*!
			Converts image data stored in RGBA8888 format to a normal map.

			\param lpSourceRGBA8888 is a pointer to the source image data in RGBA8888 format.
			\param lpDestRGBA8888 is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param KernelFilter is the kernel filter to use (default 3x3).
			\param HeightConversionMethod is the method of determining the height data from the source (default average RGB).
			\param NormalAlphaResult is how the alpha channel should be handled post processing (defaul make 100% opaque).
			\param bMinimumZ is the minimum normal Z value (default 0).
			\param sScale is the normal map height scale (default 2).
			\param bWrap sets whether the normal map should be tileable (default false).
			\param bInvertX sets if the normal map should be flipped along its X axis (default false).
			\param bInvertY sets if the normal map should be flipped along its Y axis (default false).
			\return true on sucessful conversion, otherwise false.
		*/

		static vlBool ConvertToNormalMap(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiWidth, vlUInt uiHeight, VTFHeightConversionMethod HeightConversionMethod = HEIGHT_CONVERSION_METHOD_AVERAGE_RGB, VTFNormalAlphaResult NormalAlphaResult = NORMAL_ALPHA_RESULT_WHITE, vlBool bWrap = 0);

		//! Re-sizes an image.
		/*!
			Re-sizes an image in RGBA8888 format to the given dimensions using the specified filters.

			\param lpSourceRGBA8888 is a pointer to the source image data in RGBA8888 format.
			\param lpDestRGBA8888 is a pointer to the buffer for the converted data.
			\param uiSourceWidth is the width of the source image in pixels.
			\param uiSourceHeight is the height of the source image in pixels.
			\param uiDestWidth is the width of the destination image in pixels.
			\param uiDestHeight is the height of the destination image in pixels.
			\param ResizeFilter is the image reduction filter to use (default triangle).
			\param SharpenFilter is the image sharpening filter to use (default none).
			\return true on sucessful re-size, otherwise false.
		*/

		static vlBool Resize(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiSourceWidth, vlUInt uiSourceHeight, vlUInt uiDestWidth, vlUInt uiDestHeight, VTFResizeFilter ResizeFilter = RESIZE_FILTER_TRIANGLE);

	private:

		// DXTn format decompression functions
		static vlBool DecompressDXT1(vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight);
		static vlBool DecompressDXT3(vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight);
		static vlBool DecompressDXT5(vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight);

		// DXTn format compression function
		static vlBool CompressDXTn(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat);

	public:

		//! Correct and images gamma.
		/*!
			Applies gamma correction to an image.

			\param lpImageDataRGBA8888 is a pointer to the image data in RGBA8888 format.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param sGammaCorrection is the amount of gamma correction to apply.
		*/

		static vlVoid CorrectImageGamma(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle sGammaCorrection);

		//! Computes the reflectivity for an image.
		/*!
			Calculates and sets the reflectivity vector values for the VTF image based on the
			colour averages of each pixel.

			\param lpImageDataRGBA8888 is a pointer to the image data in RGBA8888 format.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param sX, sY, sZ are the variables to hold the values reflectivity vector.
			\see ComputeReflectivity()
			\see GetReflectivity()
			\see SetReflectivity()
		*/

		static vlVoid ComputeImageReflectivity(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle &sX, vlSingle &sY, vlSingle &sZ);

		static vlVoid FlipImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);		//!< Flips an image vertically along its X-axis.
		static vlVoid MirrorImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);	//!< Flips an image horizontally along its Y-axis.
	};
}

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagVMTNodeType
{
	NODE_TYPE_GROUP = 0,
	NODE_TYPE_GROUP_END,
	NODE_TYPE_STRING,
	NODE_TYPE_INTEGER,
	NODE_TYPE_SINGLE,
	NODE_TYPE_COUNT
} VMTNodeType;

//! VMT parsing mode.
typedef enum tagVMTParseMode
{
	PARSE_MODE_STRICT = 0,
	PARSE_MODE_LOOSE,
	PARSE_MODE_COUNT
} VMTParseMode;

#ifdef __cplusplus
}
#endif

namespace VTFLib
{
	namespace Nodes
	{
		class CVMTGroupNode;
		class CVMTStringNode;
		class CVMTIntegerNode;
		class CVMTSingleNode;

		class VTFLIB_API CVMTNode
		{
		private:
			friend class CVMTGroupNode;	// For direct parent setting.

		private:
			vlChar *cName;
			CVMTGroupNode *Parent;

		public:
			CVMTNode(const vlChar *cName);
			virtual ~CVMTNode();

			const vlChar *GetName() const;
			vlVoid SetName(const vlChar *cName);

			CVMTGroupNode *GetParent();

			virtual VMTNodeType GetType() const = 0;
			virtual CVMTNode *Clone() const = 0;
		};

		class VTFLIB_API CVMTValueNode : public CVMTNode
		{
		public:
			CVMTValueNode(const vlChar *cName);
			virtual ~CVMTValueNode();

			virtual vlVoid SetValue(const vlChar *cValue) = 0;
		};

		class VTFLIB_API CVMTStringNode : public CVMTValueNode
		{
		private:
			vlChar *cValue;

		public:
			CVMTStringNode(const vlChar *cName);
			CVMTStringNode(const vlChar *cName, const vlChar *cValue);
			CVMTStringNode(const CVMTStringNode &StringNode);
			virtual ~CVMTStringNode();

			virtual vlVoid SetValue(const vlChar *cValue);

			const vlChar *GetValue() const;

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;
		};

		class VTFLIB_API CVMTIntegerNode : public CVMTValueNode
		{
		private:
			vlInt iValue;

		public:
			CVMTIntegerNode(const vlChar *cName);
			CVMTIntegerNode(const vlChar *cName, const vlChar *cValue);
			CVMTIntegerNode(const vlChar *cName, vlInt iValue);
			CVMTIntegerNode(const CVMTIntegerNode &IntegerNode);
			virtual ~CVMTIntegerNode();

			virtual vlVoid SetValue(const vlChar *cValue);

			vlVoid SetValue(vlInt iValue);
			const vlInt GetValue() const;

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;
		};

		class VTFLIB_API CVMTSingleNode : public CVMTValueNode
		{
		private:
			vlFloat fValue;

		public:
			CVMTSingleNode(const vlChar *cName);
			CVMTSingleNode(const vlChar *cName, const vlChar *cValue);
			CVMTSingleNode(const vlChar *cName, vlFloat fValue);
			CVMTSingleNode(const CVMTSingleNode &SingleNode);
			virtual ~CVMTSingleNode();

			virtual vlVoid SetValue(const vlChar *cValue);

			vlVoid SetValue(vlFloat fValue);
			const vlFloat GetValue() const;

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;
		};

		class VTFLIB_API CVMTGroupNode : public CVMTNode
		{
		private:
			void *VMTNodeList;

		public:
			CVMTGroupNode(const vlChar *cName);
			CVMTGroupNode(const CVMTGroupNode &GroupNode);
			virtual ~CVMTGroupNode();

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;

		public:
			vlUInt GetNodeCount() const;

			CVMTNode *AddNode(CVMTNode *VMTNode);
			CVMTGroupNode *AddGroupNode(const vlChar *cName);
			CVMTStringNode *AddStringNode(const vlChar *cName, const vlChar *cValue);
			CVMTIntegerNode *AddIntegerNode(const vlChar *cName, vlInt iValue);
			CVMTSingleNode *AddSingleNode(const vlChar *cName, vlFloat fValue);

			vlVoid RemoveNode(CVMTNode *VMTNode);
			vlVoid RemoveAllNodes();

			CVMTNode *GetNode(vlUInt uiIndex) const;
			CVMTNode *GetNode(const vlChar *cName) const;
		};
	}

	class VTFLIB_API CVMTFile
	{
	private:
		Nodes::CVMTGroupNode *Root;

	public:
		CVMTFile();
		CVMTFile(const CVMTFile &VMTFile);
		~CVMTFile();

	public:
		vlBool Create(const vlChar *cRoot);
		vlVoid Destroy();

		vlBool IsLoaded() const;

		vlBool Load(const vlChar *cFileName);
		vlBool Load(const vlVoid *lpData, vlUInt uiBufferSize);
		vlBool Load(vlVoid *pUserData);

		vlBool Save(const vlChar *cFileName) const;
		vlBool Save(vlVoid *lpData, vlUInt uiBufferSize, vlUInt &uiSize) const;
		vlBool Save(vlVoid *pUserData) const;

	private:
		vlBool Load(IO::Readers::IReader *Reader);
		vlBool Save(IO::Writers::IWriter *Writer) const;

		//Nodes::CVMTNode *Load(IO::Readers::IReader *Reader, vlBool bInGroup);

		vlVoid Indent(IO::Writers::IWriter *Writer, vlUInt uiLevel) const;
		vlVoid Save(IO::Writers::IWriter *Writer, Nodes::CVMTNode *Node, vlUInt uiLevel = 0) const;

	public:
		Nodes::CVMTGroupNode *GetRoot() const;
	};
}

#define VL_VERSION			140			//!< VTFLib version as integer
#define VL_VERSION_STRING	"1.4.0"		//!< VTFLib version as string

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagVTFLibOption
{
	VTFLIB_DXT_QUALITY,

	VTFLIB_LUMINANCE_WEIGHT_R,
	VTFLIB_LUMINANCE_WEIGHT_G,
	VTFLIB_LUMINANCE_WEIGHT_B,

	VTFLIB_BLUESCREEN_MASK_R,
	VTFLIB_BLUESCREEN_MASK_G,
	VTFLIB_BLUESCREEN_MASK_B,

	VTFLIB_BLUESCREEN_CLEAR_R,
	VTFLIB_BLUESCREEN_CLEAR_G,
	VTFLIB_BLUESCREEN_CLEAR_B,

	VTFLIB_FP16_HDR_KEY,
	VTFLIB_FP16_HDR_SHIFT,
	VTFLIB_FP16_HDR_GAMMA,

	VTFLIB_UNSHARPEN_RADIUS,
	VTFLIB_UNSHARPEN_AMOUNT,
	VTFLIB_UNSHARPEN_THRESHOLD,

	VTFLIB_XSHARPEN_STRENGTH,
	VTFLIB_XSHARPEN_THRESHOLD,

	VTFLIB_VMT_PARSE_MODE
} VTFLibOption;

//! Return the VTFLib version as an integer.
VTFLIB_API vlUInt vlGetVersion();

//! Return the VTFLib version as a string.
VTFLIB_API const vlChar *vlGetVersionString();

//! Return the last error message as a string.
VTFLIB_API const vlChar *vlGetLastError();

//! Initialisation function
VTFLIB_API vlBool vlInitialize();

//! Shutdown function
VTFLIB_API vlVoid vlShutdown();

//! Return the specified option.
VTFLIB_API vlBool vlGetBoolean(VTFLibOption Option);
//! Set the specified option.
VTFLIB_API vlVoid vlSetBoolean(VTFLibOption Option, vlBool bValue);

//! Return the specified option.
VTFLIB_API vlInt vlGetInteger(VTFLibOption Option);
//! Set the specified option.
VTFLIB_API vlVoid vlSetInteger(VTFLibOption Option, vlInt iValue);

//! Return the specified option.
VTFLIB_API vlSingle vlGetFloat(VTFLibOption Option);
//! Set the specified option.
VTFLIB_API vlVoid vlSetFloat(VTFLibOption Option, vlSingle sValue);
//
// Memory managment routines.
//

VTFLIB_API vlBool vlImageIsBound();
VTFLIB_API vlBool vlBindImage(vlUInt uiImage);

VTFLIB_API vlBool vlCreateImage(vlUInt *uiImage);
VTFLIB_API vlVoid vlDeleteImage(vlUInt uiImage);

//
// Library routines.  (Basically class wrappers.)
//

VTFLIB_API vlVoid vlImageCreateDefaultCreateStructure(SVTFCreateOptions *VTFCreateOptions);

VTFLIB_API vlBool vlImageCreate(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, VTFImageFormat ImageFormat, vlBool bThumbnail, vlBool bMipmaps, vlBool bNullImageData);
VTFLIB_API vlBool vlImageCreateSingle(vlUInt uiWidth, vlUInt uiHeight, vlByte *lpImageDataRGBA8888, SVTFCreateOptions *VTFCreateOptions);
VTFLIB_API vlBool vlImageCreateMultiple(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, vlByte **lpImageDataRGBA8888, SVTFCreateOptions *VTFCreateOptions);
VTFLIB_API vlVoid vlImageDestroy();

VTFLIB_API vlBool vlImageIsLoaded();

VTFLIB_API vlBool vlImageLoad(const vlChar *cFileName, vlBool bHeaderOnly);
VTFLIB_API vlBool vlImageLoadLump(const vlVoid *lpData, vlUInt uiBufferSize, vlBool bHeaderOnly);
VTFLIB_API vlBool vlImageLoadProc(vlVoid *pUserData, vlBool bHeaderOnly);

VTFLIB_API vlBool vlImageSave(const vlChar *cFileName);
VTFLIB_API vlBool vlImageSaveLump(vlVoid *lpData, vlUInt uiBufferSize, vlUInt *uiSize);
VTFLIB_API vlBool vlImageSaveProc(vlVoid *pUserData);

//
// Image routines.
//

VTFLIB_API vlUInt vlImageGetHasImage();

VTFLIB_API vlUInt vlImageGetMajorVersion();
VTFLIB_API vlUInt vlImageGetMinorVersion();
VTFLIB_API vlUInt vlImageGetSize();

VTFLIB_API vlUInt vlImageGetWidth();
VTFLIB_API vlUInt vlImageGetHeight();
VTFLIB_API vlUInt vlImageGetDepth();

VTFLIB_API vlUInt vlImageGetFrameCount();
VTFLIB_API vlUInt vlImageGetFaceCount();
VTFLIB_API vlUInt vlImageGetMipmapCount();

VTFLIB_API vlUInt vlImageGetStartFrame();
VTFLIB_API vlVoid vlImageSetStartFrame(vlUInt uiStartFrame);

VTFLIB_API vlUInt vlImageGetFlags();
VTFLIB_API vlVoid vlImageSetFlags(vlUInt uiFlags);

VTFLIB_API vlBool vlImageGetFlag(VTFImageFlag ImageFlag);
VTFLIB_API vlVoid vlImageSetFlag(VTFImageFlag ImageFlag, vlBool bState);

VTFLIB_API vlSingle vlImageGetBumpmapScale();
VTFLIB_API vlVoid vlImageSetBumpmapScale(vlSingle sBumpmapScale);

VTFLIB_API vlVoid vlImageGetReflectivity(vlSingle *sX, vlSingle *sY, vlSingle *sZ);
VTFLIB_API vlVoid vlImageSetReflectivity(vlSingle sX, vlSingle sY, vlSingle sZ);

VTFLIB_API VTFImageFormat vlImageGetFormat();

VTFLIB_API vlByte *vlImageGetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel);
VTFLIB_API vlVoid vlImageSetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, vlByte *lpData);

//
// Thumbnail routines.
//

VTFLIB_API vlBool vlImageGetHasThumbnail();

VTFLIB_API vlUInt vlImageGetThumbnailWidth();
VTFLIB_API vlUInt vlImageGetThumbnailHeight();

VTFLIB_API VTFImageFormat vlImageGetThumbnailFormat();

VTFLIB_API vlByte *vlImageGetThumbnailData();
VTFLIB_API vlVoid vlImageSetThumbnailData(vlByte *lpData);

//
// Resource routines.
//

VTFLIB_API vlBool vlImageGetSupportsResources();

VTFLIB_API vlUInt vlImageGetResourceCount();
VTFLIB_API vlUInt vlImageGetResourceType(vlUInt uiIndex);
VTFLIB_API vlBool vlImageGetHasResource(vlUInt uiType);

VTFLIB_API vlVoid *vlImageGetResourceData(vlUInt uiType, vlUInt *uiSize);
VTFLIB_API vlVoid *vlImageSetResourceData(vlUInt uiType, vlUInt uiSize, vlVoid *lpData);

//
// Helper routines.
//

VTFLIB_API vlBool vlImageGenerateMipmaps(vlUInt uiFace, vlUInt uiFrame, VTFMipmapFilter MipmapFilter);
VTFLIB_API vlBool vlImageGenerateAllMipmaps(VTFMipmapFilter MipmapFilter);

VTFLIB_API vlBool vlImageGenerateThumbnail();

VTFLIB_API vlBool vlImageGenerateNormalMap(vlUInt uiFrame, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult);
VTFLIB_API vlBool vlImageGenerateAllNormalMaps(VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult);

VTFLIB_API vlBool vlImageGenerateSphereMap();

VTFLIB_API vlBool vlImageComputeReflectivity();

//
// Conversion routines.
//

VTFLIB_API SVTFImageFormatInfo const *vlImageGetImageFormatInfo(VTFImageFormat ImageFormat);
VTFLIB_API vlBool vlImageGetImageFormatInfoEx(VTFImageFormat ImageFormat, SVTFImageFormatInfo *VTFImageFormatInfo);

VTFLIB_API vlUInt vlImageComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmaps, VTFImageFormat ImageFormat);

VTFLIB_API vlUInt vlImageComputeMipmapCount(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth);
VTFLIB_API vlVoid vlImageComputeMipmapDimensions(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, vlUInt *uiMipmapWidth, vlUInt *uiMipmapHeight, vlUInt *uiMipmapDepth);
VTFLIB_API vlUInt vlImageComputeMipmapSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat);

VTFLIB_API vlBool vlImageConvertToRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat);
VTFLIB_API vlBool vlImageConvertFromRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat);

VTFLIB_API vlBool vlImageConvert(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat, VTFImageFormat DestFormat);

VTFLIB_API vlBool vlImageConvertToNormalMap(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiWidth, vlUInt uiHeight, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult, vlBool bWrap);

VTFLIB_API vlBool vlImageResize(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiSourceWidth, vlUInt uiSourceHeight, vlUInt uiDestWidth, vlUInt uiDestHeight, VTFMipmapFilter ResizeFilter);

VTFLIB_API vlVoid vlImageCorrectImageGamma(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle sGammaCorrection);
VTFLIB_API vlVoid vlImageComputeImageReflectivity(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle *sX, vlSingle *sY, vlSingle *sZ);

VTFLIB_API vlVoid vlImageFlipImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);
VTFLIB_API vlVoid vlImageMirrorImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);

#ifdef __cplusplus
}
#endif

#endif