#pragma once

namespace reality {

	enum class really {
		Unknown,
		Wave,
		Flac,
		Vorbis,
		Ogg,

		Autodesk3DS,
		X,
		MDX,
		MD2,
		MD3,
		OBJ,
		MTL,
		FBX,

		XNB,

		Utf7,
		Utf7a,
		Utf7b,
		Utf7c,
		Utf7d,
		Utf8,
		Utf16LittleEndian,
		Utf16BigEndian,
		Utf16 = Utf16LittleEndian,
		Utf32LittleEndian,
		Utf32BigEndian,
		Utf32 = Utf32LittleEndian,

		JPG,
		JPEG,
		BMP,
		SGI,
		WBMP,
		Webp,
		GIF,
		PNG,
		DDS,
		TGA,
		PPM,
		PPMA,
		ICO,
		CUR,
		PCX,
		Radiance,
		ANI,

		HLSLSource,
		GLSLSource,
		HLSLBytecode,
	};

}