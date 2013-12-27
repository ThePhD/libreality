#include <reality.h>
#include <fixed_vector.h>
#include <make_array.h>
#include <subsequence_equals.h>
#include <really.h>
#include <cstdint>
namespace reality {
	
	typedef uint8_t byte;

	struct byte_magic {
		really identity;
		fixed_vector<byte, 16> data;
		std::size_t offset;
		fixed_vector<byte, 16> data2;
		std::size_t offset2;
	};

	really identify( const byte* bytes, std::size_t bytecount ) {
		typedef byte_magic magic;

		const static auto magics = make_array(
			magic{ really::Utf7, { (byte)0x38, (byte)0x2B, (byte)0x2F, (byte)0x76 }, 0, { }, 0 },
			magic{ really::Utf7a, { (byte)0x38, (byte)0x2B, (byte)0x2F, (byte)0x76 }, 0, { }, 0 },
			magic{ really::Utf7b, { (byte)0x39, (byte)0x2B, (byte)0x2F, (byte)0x76 }, 0, { }, 0 },
			magic{ really::Utf7c, { (byte)0x2B, (byte)0x2B, (byte)0x2F, (byte)0x76 }, 0, { }, 0 },
			magic{ really::Utf7d, { (byte)0x2F, (byte)0x2B, (byte)0x2F, (byte)0x76 }, 0, { }, 0 },
			magic{ really::Utf8, { (byte)0xBF, (byte)0xEF, (byte)0xBB }, 0, { }, 0 },
			magic{ really::Utf16, { (byte)0xFF, (byte)0xFE }, 0, { }, 0 },
			magic{ really::Utf16LittleEndian, { (byte)0xFF, (byte)0xFE }, 0, { }, 0 },
			magic{ really::Utf16BigEndian, { (byte)0xFE, (byte)0xFF }, 0, { }, 0 },
			magic{ really::Utf32, { (byte)0, (byte)0xFF, (byte)0xFE, (byte)0 }, 0, { }, 0 },
			magic{ really::Utf32LittleEndian, { (byte)0, (byte)0xFF, (byte)0xFE, (byte)0 }, 0, { }, 0 },
			magic{ really::Utf32BigEndian, { (byte)0xFF, (byte)0, (byte)0, (byte)0xFE }, 0, { }, 0 },
			magic{ really::DDS, { ( byte )'D', ( byte )'D', ( byte )'S', ( byte )' ' }, 0, { }, 0 },
			magic{ really::PNG, { (byte)0x89, ( byte )'P', ( byte )'N', ( byte )'G' }, 0, { }, 0 },
			magic{ really::JPEG, { (byte)0xD8, (byte)0xFF }, 0, { }, 0 },
			magic{ really::JPG, { (byte)0xD8, (byte)0xFF }, 0, { }, 0 },
			magic{ really::ICO, { (byte)0x0, (byte)0, (byte)0, (byte)0x1 }, 0, { }, 0 },
			magic{ really::CUR, { (byte)0x0, (byte)0, (byte)0, (byte)0x2 }, 0, { }, 0 },
			magic{ really::ANI, { ( byte )'R', ( byte )'I', ( byte )'F', ( byte )'F' }, 0, { 'A', 'C', 'O', 'N' }, 8 },
			magic{ really::PPMA, { ( byte )'P', ( byte )'3' }, 0, { }, 0 },
			magic{ really::PPMA, { ( byte )'P', ( byte )'2' }, 0, { }, 0 },
			magic{ really::PPMA, { ( byte )'P', ( byte )'1' }, 0, { }, 0 },
			magic{ really::PPM, { ( byte )'P', ( byte )'7' }, 0, { }, 0 },
			magic{ really::PPM, { ( byte )'P', ( byte )'6' }, 0, { }, 0 },
			magic{ really::PPM, { ( byte )'P', ( byte )'5' }, 0, { }, 0 },
			magic{ really::PPM, { ( byte )'P', ( byte )'4' }, 0, { }, 0 },
			magic{ really::PPM, { ( byte )'P', ( byte )'4' }, 0, { }, 0 },
			magic{ really::BMP, { ( byte )'B', ( byte )'M' }, 0, { }, 0 },
			magic{ really::BMP, { ( byte )'B', ( byte )'A' }, 0, { }, 0 },
			magic{ really::BMP, { ( byte )'C', ( byte )'I' }, 0, { }, 0 },
			magic{ really::BMP, { ( byte )'C', ( byte )'P' }, 0, { }, 0 },
			magic{ really::BMP, { ( byte )'I', ( byte )'C' }, 0, { }, 0 },
			magic{ really::BMP, { ( byte )'P', ( byte )'I' }, 0, { }, 0 },
			magic{ really::SGI, { ( byte )'\001', ( byte )'\332' }, 0, { }, 0 },
			magic{ really::WBMP, { 0, 0 }, 0, { }, 0 },
			magic{ really::Webp, { 'W', 'E', 'B', 'P' }, 8, { }, 0 },
			magic{ really::Radiance, { '#', '?', 'R', 'A', 'D', 'I', 'A', 'N', 'C', 'E' }, 0, { }, 0 },
			magic{ really::Radiance, { 'V', 'I', 'E', 'W', '=', ' ' }, 0, { }, 0 },
			magic{ really::GIF, { ( byte )'G', ( byte )'I', ( byte )'F', ( byte )'8', ( byte )'7', ( byte )'a' }, 0, { }, 0 },
			magic{ really::GIF, { ( byte )'G', ( byte )'I', ( byte )'F', ( byte )'8', ( byte )'9', ( byte )'a' }, 0, { }, 0 },
			magic{ really::Autodesk3DS, { ( byte )'4', ( byte )'D', ( byte )'4', ( byte )'D' }, 0, { }, 0 },
			magic{ really::MD2, { ( byte )'I', ( byte )'D', ( byte )'P', ( byte )'2' }, 0, { }, 0 },
			magic{ really::MD3, { ( byte )'I', ( byte )'D', ( byte )'P', ( byte )'3' }, 0, { }, 0 },
			magic{ really::MDX, { (byte)0x2E, (byte)0x58, (byte)0x44, (byte)0x4D }, 0, { }, 0 },
			magic{ really::X, { ( byte )'x', ( byte )'o', ( byte )'f', ( byte )' ' }, 0, { }, 0 },
			magic{ really::FBX, { ( byte )'K', ( byte )'a', ( byte )'y', ( byte )'d', ( byte )'a', ( byte )'r', ( byte )'a' }, 0, { }, 0 },
			magic{ really::Wave, { ( byte )'R', ( byte )'I', ( byte )'F', ( byte )'F' }, 0, { 'W', 'A', 'V', 'E' }, 8 },
			magic{ really::Flac, { (byte)0x43, (byte)0x66, (byte)0x4C, (byte)0x61 }, 0, { }, 0 },
			magic{ really::Ogg, { ( byte )'O', ( byte )'g', ( byte )'g', ( byte )'S' }, 0, { }, 0 },
			magic{ really::Vorbis, { (byte)0x73, (byte)0x01, (byte)0x76, (byte)0x6f, (byte)0x72, (byte)0x62, (byte)0x69 }, 0, { }, 0 },
			magic{ really::XNB, { ( byte )'X', ( byte )'N', ( byte )'B', ( byte )'w' }, 0, { }, 0 },
			magic{ really::XNB, { ( byte )'X', ( byte )'N', ( byte )'B', ( byte )'m' }, 0, { }, 0 },
			magic{ really::XNB, { ( byte )'X', ( byte )'N', ( byte )'B', ( byte )'x' }, 0, { }, 0 },
			magic{ really::PCX, { (byte)10, 0x02 }, 0, { }, 0 },
			magic{ really::PCX, { (byte)10, 0x05 }, 0, { }, 0 },
			magic{ really::Unknown, { }, 0, { }, 0 }
		);
		const static magic* magicbegin = magics.data( );
		const static magic* magicend = magics.data( ) + ( magics.size( ) - 1 );

		const byte* bytesbegin = bytes;
		const byte* bytesend = bytes + bytecount;

		auto target = std::find_if( magicbegin, magicend,
			[ &bytesbegin, &bytesend ] ( const magic& m ) {
			return subsequence_equals( bytesbegin + m.offset, bytesend - m.offset, m.data.begin( ), m.data.end( ) )
				&& ( m.data2.size( ) < 1 ? true : subsequence_equals( bytesbegin + m.offset2, bytesend - m.offset2, m.data2.begin( ), m.data2.end( ) ) );
		}
		);

		const magic& m = *target;
		return m.identity;
	}
}