#pragma once

#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <algorithm>

namespace reality {

	template <typename T, std::size_t n, std::size_t a = std::alignment_of<T>::value>
	class fixed_vector {
	public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef pointer_type iterator;
		typedef const pointer_type const_iterator;

	private:
		typename std::aligned_storage<sizeof(T)* n, a>::type items;
		std::size_t len;

		T* ptrat( std::size_t idx ) {
			return static_cast<T*>( static_cast<void*>( &items ) ) + idx;
		}

		const T* ptrat( std::size_t idx ) const {
			return static_cast<const T*>( static_cast<const void*>( &items ) ) + idx;
		}

		T& refat( std::size_t idx ) {
			return *ptrat( idx );
		}

		const T& refat( std::size_t idx ) const {
			return *ptrat( idx );
		}

	public:
		static const std::size_t max_size( ) {
			return n;
		}

		fixed_vector( ) : len( 0 ) {

		}

		fixed_vector( fixed_vector&& mov ) : len( 0 ) {
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( std::move( mov[ i ] ) );
			mov.clear( );
		}

		fixed_vector( const fixed_vector& mov ) : len( 0 ) {
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( mov[ i ] );
		}

		fixed_vector& operator=( fixed_vector&& mov ) {
			clear( );
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( std::move( mov[ i ] ) );
			mov.clear( );
		}

		fixed_vector& operator=( const fixed_vector& mov ) {
			clear( );
			for ( std::size_t i = 0; i < mov.size( ); ++i )
				push_back( mov[ i ] );
			mov.clear( );
		}

		fixed_vector( std::size_t capacity ) : len( std::min( n, capacity ) ) {

		}

		template <std::size_t c>
		fixed_vector( const T( &arr )[ c ] ) : len( c ) {
			static_assert( c < n, "Array too large to initialize fixed_vector" );
			std::copy( std::addressof( arr[ 0 ] ), std::addressof( arr[ c ] ), data( ) );
		}

		fixed_vector( std::initializer_list<T> initializer ) : len( std::min( n, initializer.size( ) ) ) {
			std::copy( initializer.begin( ), initializer.begin( ) + len, data( ) );
		}

		bool empty( ) const {
			return len < 1;
		}

		bool not_empty( ) const {
			return len > 0;
		}

		bool full( ) const {
			return len >= n;
		}

		void push_back( const T& item ) {
			new( ptrat( len ) ) T( item );
			len++;
		}

		void push_back( T&& item ) {
			new( ptrat( len ) ) T( std::move( item ) );
			len++;
		}

		template <typename ...Tn>
		void emplace_back( Tn&&... argn ) {
			new( ptrat( len ) ) T( std::forward<Tn>( argn )... );
			len++;
		}

		void pop_back( ) {
			T& addr = refat( len - 1 );
			addr.~T( );
			--len;
		}

		void clear( ) {
			for ( ; len > 0; ) {
				pop_back( );
			}
		}

		std::size_t size( ) const {
			return len;
		}

		std::size_t capacity( ) const {
			return n;
		}

		void resize( std::size_t sz ) {
			len = std::min( sz, n );
		}

		T* data( ) {
			return ptrat( 0 );
		}

		const T* data( ) const {
			return ptrat( 0 );
		}

		T& operator[] ( std::size_t idx ) {
			return refat( idx );
		}

		const T& operator[] ( std::size_t idx ) const {
			return refat( idx );
		}

		T& front( ) {
			return refat( 0 );
		}

		T& back( ) {
			return refat( len - 1 );
		}

		const T& front( ) const {
			return refat( 0 );
		}

		const T& back( ) const {
			return refat( len - 1 );
		}

		T* begin( ) {
			return data( );
		}

		const T* cbegin( ) {
			return data( );
		}

		const T* begin( ) const {
			return data( );
		}

		const T* cbegin( ) const {
			return data( );
		}

		T* end( ) {
			return data( ) + len;
		}

		const T* cend( ) {
			return data( ) + len;
		}

		const T* end( ) const {
			return data( ) + len;
		}

		const T* cend( ) const {
			return data( ) + len;
		}
	};

}