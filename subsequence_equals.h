#pragma once

#include <iterator>
#include <utility>

namespace reality {

	template <typename TCont1, typename TCont2>
	bool subsequence_equals( TCont1&& cont1, TCont2&& cont2 ) {
		return subsequence_equals( std::begin( cont1 ), std::end( cont1 ), std::begin( cont2 ), std::end( cont2 ) );
	}

	template <typename TCont1, typename TCont2, typename TPred>
	bool subsequence_equals( TCont1&& cont1, TCont2&& cont2, TPred&& pred ) {
		return subsequence_equals( std::begin( cont1 ), std::end( cont1 ), std::begin( cont2 ), std::end( cont2 ), std::forward<TPred>( pred ) );
	}

	template <typename TIter1, typename TIter2>
	bool subsequence_equals( TIter1 biter1, TIter1 eiter1, TIter2 biter2, TIter2 eiter2 ) {
		typedef typename std::add_const<decltype( *biter1 )>::type ref1_t;
		typedef typename std::add_const<decltype( *biter2 )>::type ref2_t;
		return subsequence_equals( biter1, eiter1, biter2, eiter2, [ ] ( ref1_t a, ref2_t b ) { return a == b; } );
	}

	template <typename TIter1, typename TIter2, typename TPred>
	bool subsequence_equals( TIter1 biter1, TIter1 eiter1, TIter2 biter2, TIter2 eiter2, TPred&& predicate ) {
		while ( biter1 != eiter1 && biter2 != eiter2 ) {
			if ( !predicate( *biter1, *biter2 ) ) {
				return false;
			}
			++biter1;
			++biter2;
		}
		return true;
	}
}