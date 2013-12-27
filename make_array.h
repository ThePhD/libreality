#pragma once

#include <array>
#include <utility>

namespace reality {
	
	template <class T, class... Tn>
	std::array<T, 1 + sizeof...( Tn )> make_array( T&& head, Tn&&... values ) {
		return{ std::forward<T>( head ), std::forward<Tn>( values )... };
	}

}
