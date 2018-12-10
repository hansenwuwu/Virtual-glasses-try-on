#include <math.h>

#ifndef __SCENE__
#define __SCENE__


#ifdef __cplusplus
extern "C" {
#endif

/*	struct define
_______________________________________________________________*/

	typedef struct _point_xy_int			point2i;
	typedef struct _point_xy_float			point2f;
	typedef struct _point_xyz_int			point3i, vector3i;
	typedef struct _point_xyz_float			point3f, vector3f;
	typedef struct _color_rgb_float			color3f, rgb;
	typedef struct _color_rgb_uchar			color3uc, rgbuc;
	typedef struct _color_rgba_float		color4f, rgba;
	typedef struct _color_rgba_uchar		color4uc, rgbauc;
	typedef struct _rectangle_int			rectanglei;
	typedef struct _rectangle_float			rectanglef;
	typedef struct _rectangle_detail_int	rectangleDi;
	typedef struct _rectangle_detail_float	rectangleDf;
	typedef struct _ellipse_xy_int			ellipsei;
	typedef struct _ellipse_xy_float		ellipsef;
	typedef struct _triangle_xyz_float		trianglef;
	typedef struct _size_wh_int				size2i;
	typedef struct _size_wh_float			size2f;
	typedef struct _plane_vd_float			planevf;

#define	S_TRANSFORM_INV
	typedef struct _transform_float			transformf;

/*	point :	int x, y
_______________________________________________________________*/

	struct _point_xy_int {
		int x, y;

		_point_xy_int( void ) { x = y = 0; }
		_point_xy_int( int _n ) { x = y = _n; }
		_point_xy_int( int _x, int _y ) { x = _x; y = _y; }

		// operator += and +
		_point_xy_int const &_point_xy_int::operator+=( _point_xy_int const &_s ) { x += _s.x; y += _s.y; return *this; }
		_point_xy_int const &_point_xy_int::operator+=( int _s ) { x += _s; y += _s; return *this; }
		_point_xy_int const &_point_xy_int::operator+=( float _s ) { x += (int)_s; y += (int)_s; return *this; }
		_point_xy_int const &_point_xy_int::operator+=( double _s ) { x += (int)_s; y += (int)_s; return *this; }
		_point_xy_int operator+( _point_xy_int const &_s ) { return _point_xy_int( *this ) += _s; }
		_point_xy_int operator+( int _s ) { return _point_xy_int( *this ) += _s; }
		_point_xy_int operator+( float _s ) { return _point_xy_int( *this ) += _s; }
		_point_xy_int operator+( double _s ) { return _point_xy_int( *this ) += _s; }

		// operator -= and -
		_point_xy_int const &_point_xy_int::operator-=( _point_xy_int const &_s ) { x -= _s.x; y -= _s.y; return *this; }
		_point_xy_int const &_point_xy_int::operator-=( int _s ) { x -= _s; y -= _s; return *this; }
		_point_xy_int const &_point_xy_int::operator-=( float _s ) { x -= (int)_s; y -= (int)_s; return *this; }
		_point_xy_int const &_point_xy_int::operator-=( double _s ) { x -= (int)_s; y -= (int)_s; return *this; }
		_point_xy_int operator-( _point_xy_int const &_s ) { return _point_xy_int( *this ) -= _s; }
		_point_xy_int operator-( int _s ) { return _point_xy_int( *this ) -= _s; }
		_point_xy_int operator-( float _s ) { return _point_xy_int( *this ) -= _s; }
		_point_xy_int operator-( double _s ) { return _point_xy_int( *this ) -= _s; }

		// operator *= and *
		_point_xy_int const &_point_xy_int::operator*=( _point_xy_int const &_s ) { x *= _s.x; y *= _s.y; return *this; }
		_point_xy_int const &_point_xy_int::operator*=( int _s ) { x *= _s; y *= _s; return *this; }
		_point_xy_int const &_point_xy_int::operator*=( float _s ) { x = (int)( x*_s ); y = (int)( y*_s ); return *this; }
		_point_xy_int const &_point_xy_int::operator*=( double _s ) { x = (int)( x*_s ); y = (int)( y*_s ); return *this; }
		_point_xy_int operator*( _point_xy_int const &_s ) { return _point_xy_int( *this ) *= _s; }
		_point_xy_int operator*( int _s ) { return _point_xy_int( *this ) *= _s; }
		_point_xy_int operator*( float _s ) { return _point_xy_int( *this ) *= _s; }
		_point_xy_int operator*( double _s ) { return _point_xy_int( *this ) *= _s; }

		// operator /= and /
		_point_xy_int const &_point_xy_int::operator/=( _point_xy_int const &_s ) { x /= _s.x; y /= _s.y; return *this; }
		_point_xy_int const &_point_xy_int::operator/=( int _s ) { x /= _s; y /= _s; return *this; }
		_point_xy_int const &_point_xy_int::operator/=( float _s ) { x = (int)( x/_s ); y = (int)( y/_s ); return *this; }
		_point_xy_int const &_point_xy_int::operator/=( double _s ) { x = (int)( x/_s ); y = (int)( y/_s ); return *this; }
		_point_xy_int operator/( _point_xy_int const &_s ) { return _point_xy_int( *this ) /= _s; }
		_point_xy_int operator/( int _s ) { return _point_xy_int( *this ) /= _s; }
		_point_xy_int operator/( float _s ) { return _point_xy_int( *this ) /= _s; }
		_point_xy_int operator/( double _s ) { return _point_xy_int( *this ) /= _s; }

		// operator =, == and !=
		_point_xy_int const operator=( _point_xy_int const &_s ) { x = _s.x; y = _s.y; return *this; }
		bool const operator==( _point_xy_int const &_s ) { return ( x != _s.x || y != _s.y ) ? false : true; }
		bool const operator!=( _point_xy_int const &_s ) { return ( x != _s.x || y != _s.y ) ? true : false; }
	};



/*	point :	float x, y
_______________________________________________________________*/

	struct _point_xy_float {
		float x, y;

		_point_xy_float( void ) { x = y = 0.f; }
		_point_xy_float( float _n ) { x = y = _n; }
		_point_xy_float( float _x, float _y ) { x = _x; y = _y; }

		// operator += and +
		_point_xy_float const &_point_xy_float::operator+=( _point_xy_int const &_s ) { x += _s.x; y += _s.y; return *this; }
		_point_xy_float const &_point_xy_float::operator+=( _point_xy_float const &_s ) { x += _s.x; y += _s.y; return *this; }
		_point_xy_float const &_point_xy_float::operator+=( int _s ) { x += _s; y += _s; return *this; }
		_point_xy_float const &_point_xy_float::operator+=( float _s ) { x += _s; y += _s; return *this; }
		_point_xy_float const &_point_xy_float::operator+=( double _s ) { x += (float)_s; y += (float)_s; return *this; }
		_point_xy_float operator+( _point_xy_float const &_s ) { return _point_xy_float( *this ) += _s; }
		_point_xy_float operator+( int _s ) { return _point_xy_float( *this ) += _s; }
		_point_xy_float operator+( float _s ) { return _point_xy_float( *this ) += _s; }
		_point_xy_float operator+( double _s ) { return _point_xy_float( *this ) += _s; }

		// operator -= and -
		_point_xy_float const &_point_xy_float::operator-=( _point_xy_float const &_s ) { x -= _s.x; y -= _s.y; return *this; }
		_point_xy_float const &_point_xy_float::operator-=( int _s ) { x -= _s; y -= _s; return *this; }
		_point_xy_float const &_point_xy_float::operator-=( float _s ) { x -= _s; y -= _s; return *this; }
		_point_xy_float const &_point_xy_float::operator-=( double _s ) { x -= (float)_s; y -= (float)_s; return *this; }
		_point_xy_float operator-( _point_xy_float const &_s ) { return _point_xy_float( *this ) -= _s; }
		_point_xy_float operator-( int _s ) { return _point_xy_float( *this ) -= _s; }
		_point_xy_float operator-( float _s ) { return _point_xy_float( *this ) -= _s; }
		_point_xy_float operator-( double _s ) { return _point_xy_float( *this ) -= _s; }

		// operator *= and *
		_point_xy_float const &_point_xy_float::operator*=( _point_xy_float const &_s ) { x *= _s.x; y *= _s.y; return *this; }
		_point_xy_float const &_point_xy_float::operator*=( int _s ) { x *= _s; y *= _s; return *this; }
		_point_xy_float const &_point_xy_float::operator*=( float _s ) { x *= _s; y *= _s; return *this; }
		_point_xy_float const &_point_xy_float::operator*=( double _s ) { x *= (float)_s; y *= (float)_s; return *this; }
		_point_xy_float operator*( _point_xy_float const &_s ) { return _point_xy_float( *this ) *= _s; }
		_point_xy_float operator*( int _s ) { return _point_xy_float( *this ) *= _s; }
		_point_xy_float operator*( float _s ) { return _point_xy_float( *this ) *= _s; }
		_point_xy_float operator*( double _s ) { return _point_xy_float( *this ) *= _s; }

		// operator /= and /
		_point_xy_float const &_point_xy_float::operator/=( _point_xy_float const &_s ) { x /= _s.x; y /= _s.y; return *this; }
		_point_xy_float const &_point_xy_float::operator/=( int _s ) { x /= _s; y /= _s; return *this; }
		_point_xy_float const &_point_xy_float::operator/=( float _s ) { x /= _s; y /= _s; return *this; }
		_point_xy_float const &_point_xy_float::operator/=( double _s ) { x /= (float)_s; y /= (float)_s; return *this; }
		_point_xy_float operator/( _point_xy_float const &_s ) { return _point_xy_float( *this ) /= _s; }
		_point_xy_float operator/( int _s ) { return _point_xy_float( *this ) /= _s; }
		_point_xy_float operator/( float _s ) { return _point_xy_float( *this ) /= _s; }
		_point_xy_float operator/( double _s ) { return _point_xy_float( *this ) /= _s; }

		// operator =, == and !=
		_point_xy_float const operator=( _point_xy_float const &_s ) { x = _s.x; y = _s.y; return *this; }
		bool const operator==( _point_xy_float const &_s ) { return ( x != _s.x || y != _s.y ) ? false : true; }
		bool const operator!=( _point_xy_float const &_s ) { return ( x != _s.x || y != _s.y ) ? true : false; }
	};



/*	point :	int x, y, z
_______________________________________________________________*/

	struct _point_xyz_int {
		int x, y, z;

		_point_xyz_int( void ) { x = y = z = 0; }
		_point_xyz_int( int _n ) { x = y = z = _n; }
		_point_xyz_int( int _x, int _y, int _z ) { x = _x; y = _y; z = _z; }

		// operator += and +
		_point_xyz_int const &_point_xyz_int::operator+=( _point_xyz_int const &_s ) { x += _s.x; y += _s.y; z += _s.z; return *this; }
		_point_xyz_int const &_point_xyz_int::operator+=( int _s ) { x += _s; y += _s; z += _s; return *this; }
		_point_xyz_int const &_point_xyz_int::operator+=( float _s ) { x += (int)_s; y += (int)_s; z += (int)_s; return *this; }
		_point_xyz_int const &_point_xyz_int::operator+=( double _s ) { x += (int)_s; y += (int)_s; z += (int)_s; return *this; }
		_point_xyz_int operator+( _point_xyz_int const &_s ) { return _point_xyz_int( *this ) += _s; }
		_point_xyz_int operator+( int _s ) { return _point_xyz_int( *this ) += _s; }
		_point_xyz_int operator+( float _s ) { return _point_xyz_int( *this ) += _s; }
		_point_xyz_int operator+( double _s ) { return _point_xyz_int( *this ) += _s; }

		// operator -= and -
		_point_xyz_int const &_point_xyz_int::operator-=( _point_xyz_int const &_s ) { x -= _s.x; y -= _s.y; z -= _s.z; return *this; }
		_point_xyz_int const &_point_xyz_int::operator-=( int _s ) { x -= _s; y -= _s; z -= _s; return *this; }
		_point_xyz_int const &_point_xyz_int::operator-=( float _s ) { x -= (int)_s; y -= (int)_s; z -= (int)_s; return *this; }
		_point_xyz_int const &_point_xyz_int::operator-=( double _s ) { x -= (int)_s; y -= (int)_s; z -= (int)_s; return *this; }
		_point_xyz_int operator-( _point_xyz_int const &_s ) { return _point_xyz_int( *this ) -= _s; }
		_point_xyz_int operator-( int _s ) { return _point_xyz_int( *this ) -= _s; }
		_point_xyz_int operator-( float _s ) { return _point_xyz_int( *this ) -= _s; }
		_point_xyz_int operator-( double _s ) { return _point_xyz_int( *this ) -= _s; }

		// operator *= and *
		_point_xyz_int const &_point_xyz_int::operator*=( _point_xyz_int const &_s ) { x *= _s.x; y *= _s.y; z *= _s.z; return *this; }
		_point_xyz_int const &_point_xyz_int::operator*=( int _s ) { x *= _s; y *= _s; z *= _s; return *this; }
		_point_xyz_int const &_point_xyz_int::operator*=( float _s ) { x = (int)( x*_s ); y = (int)( y*_s ); z = (int)( z*_s ); return *this; }
		_point_xyz_int const &_point_xyz_int::operator*=( double _s ) { x = (int)( x*_s ); y = (int)( y*_s ); z = (int)( z*_s ); return *this; }
		_point_xyz_int operator*( _point_xyz_int const &_s ) { return _point_xyz_int( *this ) *= _s; }
		_point_xyz_int operator*( int _s ) { return _point_xyz_int( *this ) *= _s; }
		_point_xyz_int operator*( float _s ) { return _point_xyz_int( *this ) *= _s; }
		_point_xyz_int operator*( double _s ) { return _point_xyz_int( *this ) *= _s; }

		// operator /= and /
		_point_xyz_int const &_point_xyz_int::operator/=( _point_xyz_int const &_s ) { x /= _s.x; y /= _s.y; z /= _s.z; return *this; }
		_point_xyz_int const &_point_xyz_int::operator/=( int _s ) { x /= _s; y /= _s; z /= _s; return *this; }
		_point_xyz_int const &_point_xyz_int::operator/=( float _s ) { x = (int)( x/_s ); y = (int)( y/_s ); z = (int)( z/_s ); return *this; }
		_point_xyz_int const &_point_xyz_int::operator/=( double _s ) { x = (int)( x/_s ); y = (int)( y/_s ); z = (int)( z/_s ); return *this; }
		_point_xyz_int operator/( _point_xyz_int const &_s ) { return _point_xyz_int( *this ) /= _s; }
		_point_xyz_int operator/( int _s ) { return _point_xyz_int( *this ) /= _s; }
		_point_xyz_int operator/( float _s ) { return _point_xyz_int( *this ) /= _s; }
		_point_xyz_int operator/( double _s ) { return _point_xyz_int( *this ) /= _s; }

		// operator =, == and !=
		_point_xyz_int const operator=( _point_xyz_int const &_s ) { x = _s.x; y = _s.y; z = _s.z; return *this; }
		bool const operator==( _point_xyz_int const &_s ) { return ( x != _s.x || y != _s.y || z != _s.z ) ? false : true; }
		bool const operator!=( _point_xyz_int const &_s ) { return ( x != _s.x || y != _s.y || z != _s.z ) ? true : false; }
	};



/*	point :	float x, y, z
_______________________________________________________________*/

	struct _point_xyz_float {
		float x, y, z;

		_point_xyz_float( void ) { x = y = z = 0.f; }
		_point_xyz_float( float _n ) { x = y = z = _n; }
		_point_xyz_float( float _x, float _y, float _z ) { x = _x; y = _y; z = _z; }
		_point_xyz_float( float* _v) { x = _v[0]; y = _v[1]; z = _v[2]; }

		// operator += and +
		_point_xyz_float const &_point_xyz_float::operator+=( _point_xyz_float const &_s ) { x += _s.x; y += _s.y; z += _s.z; return *this; }
		_point_xyz_float const &_point_xyz_float::operator+=( int _s ) { x += _s; y += _s; z += _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator+=( float _s ) { x += _s; y += _s; z += _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator+=( double _s ) { x += (float)_s; y += (float)_s; z += (float)_s; return *this; }
		_point_xyz_float operator+( _point_xyz_float const &_s ) { return _point_xyz_float( *this ) += _s; }
		_point_xyz_float operator+( int _s ) { return _point_xyz_float( *this ) += _s; }
		_point_xyz_float operator+( float _s ) { return _point_xyz_float( *this ) += _s; }
		_point_xyz_float operator+( double _s ) { return _point_xyz_float( *this ) += _s; }

		// operator -= and -
		_point_xyz_float const &_point_xyz_float::operator-=( _point_xyz_float const &_s ) { x -= _s.x; y -= _s.y; z -= _s.z; return *this; }
		_point_xyz_float const &_point_xyz_float::operator-=( int _s ) { x -= _s; y -= _s; z -= _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator-=( float _s ) { x -= _s; y -= _s; z -= _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator-=( double _s ) { x -= (float)_s; y -= (float)_s; z -= (float)_s; return *this; }
		_point_xyz_float operator-( _point_xyz_float const &_s ) { return _point_xyz_float( *this ) -= _s; }
		_point_xyz_float operator-( int _s ) { return _point_xyz_float( *this ) -= _s; }
		_point_xyz_float operator-( float _s ) { return _point_xyz_float( *this ) -= _s; }
		_point_xyz_float operator-( double _s ) { return _point_xyz_float( *this ) -= _s; }

		// operator *= and *
		_point_xyz_float const &_point_xyz_float::operator*=( _point_xyz_float const &_s ) { x *= _s.x; y *= _s.y; z *= _s.z; return *this; }
		_point_xyz_float const &_point_xyz_float::operator*=( int _s ) { x *= _s; y *= _s; z *= _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator*=( float _s ) { x *= _s; y *= _s; z *= _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator*=( double _s ) { x *= (float)_s; y *= (float)_s; z *= (float)_s; return *this; }
		_point_xyz_float operator*( _point_xyz_float const &_s ) { return _point_xyz_float( *this ) *= _s; }
		_point_xyz_float operator*( int _s ) { return _point_xyz_float( *this ) *= _s; }
		_point_xyz_float operator*( float _s ) { return _point_xyz_float( *this ) *= _s; }
		_point_xyz_float operator*( double _s ) { return _point_xyz_float( *this ) *= _s; }

		// operator /= and /
		_point_xyz_float const &_point_xyz_float::operator/=( _point_xyz_float const &_s ) { x /= _s.x; y /= _s.y; z /= _s.z; return *this; }
		_point_xyz_float const &_point_xyz_float::operator/=( int _s ) { x /= _s; y /= _s; z /= _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator/=( float _s ) { x /= _s; y /= _s; z /= _s; return *this; }
		_point_xyz_float const &_point_xyz_float::operator/=( double _s ) { x /= (float)_s; y /= (float)_s; z /= (float)_s; return *this; }
		_point_xyz_float operator/( _point_xyz_float const &_s ) { return _point_xyz_float( *this ) /= _s; }
		_point_xyz_float operator/( int _s ) { return _point_xyz_float( *this ) /= _s; }
		_point_xyz_float operator/( float _s ) { return _point_xyz_float( *this ) /= _s; }
		_point_xyz_float operator/( double _s ) { return _point_xyz_float( *this ) /= _s; }

		// operator =, == and !=
		_point_xyz_float const operator=( _point_xyz_float const &_s ) { x = _s.x; y = _s.y; z = _s.z; return *this; }
		bool const operator==( _point_xyz_float const &_s ) { return ( x != _s.x || y != _s.y || z != _s.z ) ? false : true; }
		bool const operator!=( _point_xyz_float const &_s ) { return ( x != _s.x || y != _s.y || z != _s.z ) ? true : false; }
		float& operator[](int i)
		{
		  return x;
		}
		void normalize()
		{
			float lenght = powf((x*x + y*y + z*z) , 0.5);
			x /= lenght;
			y /= lenght;
			z /= lenght;
		}
	};



/*	color :	float r, g, b
_______________________________________________________________*/

	struct _color_rgb_float {
		float r, g, b;

		_color_rgb_float( void ) { r = g = b = 0.f; }
		_color_rgb_float( float _n ) { r = g = b = _n; }
		_color_rgb_float( float _r, float _g, float _b ) { r = _r; g = _g; b = _b; }

		// operator += and +
		_color_rgb_float const &_color_rgb_float::operator+=( _color_rgb_float const &_s ) { r += _s.r; g += _s.g; b += _s.b; return *this; }
		_color_rgb_float const &_color_rgb_float::operator+=( int _s ) { r += _s; g += _s; b += _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator+=( float _s ) { r += _s; g += _s; b += _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator+=( double _s ) { r += (float)_s; g += (float)_s; b += (float)_s; return *this; }
		_color_rgb_float operator+( _color_rgb_float const &_s ) { return _color_rgb_float( *this ) += _s; }
		_color_rgb_float operator+( int _s ) { return _color_rgb_float( *this ) += _s; }
		_color_rgb_float operator+( float _s ) { return _color_rgb_float( *this ) += _s; }
		_color_rgb_float operator+( double _s ) { return _color_rgb_float( *this ) += _s; }

		// operator -= and -
		_color_rgb_float const &_color_rgb_float::operator-=( _color_rgb_float const &_s ) { r -= _s.r; g -= _s.g; b -= _s.b; return *this; }
		_color_rgb_float const &_color_rgb_float::operator-=( int _s ) { r -= _s; g -= _s; b -= _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator-=( float _s ) { r -= _s; g -= _s; b -= _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator-=( double _s ) { r -= (float)_s; g -= (float)_s; b -= (float)_s; return *this; }
		_color_rgb_float operator-( _color_rgb_float const &_s ) { return _color_rgb_float( *this ) -= _s; }
		_color_rgb_float operator-( int _s ) { return _color_rgb_float( *this ) -= _s; }
		_color_rgb_float operator-( float _s ) { return _color_rgb_float( *this ) -= _s; }
		_color_rgb_float operator-( double _s ) { return _color_rgb_float( *this ) -= _s; }

		// operator *= and *
		_color_rgb_float const &_color_rgb_float::operator*=( int _s ) { r *= _s; g *= _s; b *= _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator*=( float _s ) { r *= _s; g *= _s; b *= _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator*=( double _s ) { r *= (float)_s; g *= (float)_s; b *= (float)_s; return *this; }
		_color_rgb_float operator*( int _s ) { return _color_rgb_float( *this ) *= _s; }
		_color_rgb_float operator*( float _s ) { return _color_rgb_float( *this ) *= _s; }
		_color_rgb_float operator*( double _s ) { return _color_rgb_float( *this ) *= _s; }

		// operator /= and /
		_color_rgb_float const &_color_rgb_float::operator/=( int _s ) { r /= _s; g /= _s; b /= _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator/=( float _s ) { r /= _s; g /= _s; b /= _s; return *this; }
		_color_rgb_float const &_color_rgb_float::operator/=( double _s ) { r /= (float)_s; g /= (float)_s; b /= (float)_s; return *this; }
		_color_rgb_float operator/( int _s ) { return _color_rgb_float( *this ) /= _s; }
		_color_rgb_float operator/( float _s ) { return _color_rgb_float( *this ) /= _s; }
		_color_rgb_float operator/( double _s ) { return _color_rgb_float( *this ) /= _s; }

		// operator =, == and !=
		_color_rgb_float const operator=( _color_rgb_float const &_s ) { r = _s.r; g = _s.g; b = _s.b; return *this; }
		bool const operator==( _color_rgb_float const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? false : true; }
		bool const operator!=( _color_rgb_float const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? true : false; }

		// operator <, <=, > and >=
		bool const operator<( _color_rgb_float const &_s ) { return ( r >= _s.r || g >= _s.g || b >= _s.b ) ? false : true; }
		bool const operator<=( _color_rgb_float const &_s ) { return ( r > _s.r || g > _s.g || b > _s.b ) ? false : true; }
		bool const operator>( _color_rgb_float const &_s ) { return ( r <= _s.r || g <= _s.g || b <= _s.b ) ? false : true; }
		bool const operator>=( _color_rgb_float const &_s ) { return ( r < _s.r || g < _s.g || b < _s.b ) ? false : true; }
	};



/*	color :	unsigned char r, g, b
_______________________________________________________________*/

	struct _color_rgb_uchar {
		unsigned char r, g, b;

		_color_rgb_uchar( const _color_rgb_float &_s ) { r = (int)( _s.r*255 ); g = (int)( _s.g*255 ); b = (int)( _s.b*255 ); }
		_color_rgb_uchar( void ) { r = g = b = 0; }
		_color_rgb_uchar( unsigned char _n ) { r = g = b = _n; }
		_color_rgb_uchar( unsigned char _r, unsigned char _g, unsigned char _b ) { r = _r; g = _g; b = _b; }

		// operator += and +
		_color_rgb_uchar const &_color_rgb_uchar::operator+=( _color_rgb_uchar const &_s ) { r += _s.r; g += _s.g; b += _s.b; return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator+=( int _s ) { r += _s; g += _s; b += _s; return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator+=( float _s ) { return *this += (int)_s; }
		_color_rgb_uchar const &_color_rgb_uchar::operator+=( double _s ) { return *this += (int)_s; }
		_color_rgb_uchar operator+( _color_rgb_uchar const &_s ) { return _color_rgb_uchar( *this ) += _s; }
		_color_rgb_uchar operator+( int _s ) { return _color_rgb_uchar( *this ) += _s; }
		_color_rgb_uchar operator+( float _s ) { return _color_rgb_uchar( *this ) += (int)_s; }
		_color_rgb_uchar operator+( double _s ) { return _color_rgb_uchar( *this ) += (int)_s; }

		// operator -= and -
		_color_rgb_uchar const &_color_rgb_uchar::operator-=( _color_rgb_uchar const &_s ) { r -= _s.r; g -= _s.g; b -= _s.b; return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator-=( int _s ) { r -= _s; g -= _s; b -= _s; return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator-=( float _s ) { return *this -= (int)_s; }
		_color_rgb_uchar const &_color_rgb_uchar::operator-=( double _s ) { return *this -= (int)_s; }
		_color_rgb_uchar operator-( _color_rgb_uchar const &_s ) { return _color_rgb_uchar( *this ) -= _s; }
		_color_rgb_uchar operator-( int _s ) { return _color_rgb_uchar( *this ) -= _s; }
		_color_rgb_uchar operator-( float _s ) { return _color_rgb_uchar( *this ) -= (int)_s; }
		_color_rgb_uchar operator-( double _s ) { return _color_rgb_uchar( *this ) -= (int)_s; }

		// operator *= and *
		_color_rgb_uchar const &_color_rgb_uchar::operator*=( int _s ) { r *= _s; g *= _s; b *= _s; return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator*=( float _s ) { r = (int)( r*_s ); g = (int)( g*_s ); b = (int)( b*_s ); return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator*=( double _s ) { r = (int)( r*_s ); g = (int)( g*_s ); b = (int)( b*_s ); return *this; }
		_color_rgb_uchar operator*( int _s ) { return _color_rgb_uchar( *this ) *= _s; }
		_color_rgb_uchar operator*( float _s ) { return _color_rgb_uchar( *this ) *= _s; }
		_color_rgb_uchar operator*( double _s ) { return _color_rgb_uchar( *this ) *= _s; }

		// operator /= and /
		_color_rgb_uchar const &_color_rgb_uchar::operator/=( int _s ) { r /= _s; g /= _s; b /= _s; return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator/=( float _s ) { r = (int)( r/_s ); g = (int)( g/_s ); b = (int)( b/_s ); return *this; }
		_color_rgb_uchar const &_color_rgb_uchar::operator/=( double _s ) { r = (int)( r/_s ); g = (int)( g/_s ); b = (int)( b/_s ); return *this; }
		_color_rgb_uchar operator/( int _s ) { return _color_rgb_uchar( *this ) /= _s; }
		_color_rgb_uchar operator/( float _s ) { return _color_rgb_uchar( *this ) /= _s; }
		_color_rgb_uchar operator/( double _s ) { return _color_rgb_uchar( *this ) /= _s; }

		// operator =, == and !=
		_color_rgb_uchar const operator=( _color_rgb_uchar const &_s ) { r = _s.r; g = _s.g; b = _s.b; return *this; }
		bool const operator==( _color_rgb_uchar const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? false : true; }
		bool const operator!=( _color_rgb_uchar const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? true : false; }

		// operator <, <=, > and >=
		bool const operator<( _color_rgb_uchar const &_s ) { return ( r >= _s.r || g >= _s.g || b >= _s.b ) ? false : true; }
		bool const operator<=( _color_rgb_uchar const &_s ) { return ( r > _s.r || g > _s.g || b > _s.b ) ? false : true; }
		bool const operator>( _color_rgb_uchar const &_s ) { return ( r <= _s.r || g <= _s.g || b <= _s.b ) ? false : true; }
		bool const operator>=( _color_rgb_uchar const &_s ) { return ( r < _s.r || g < _s.g || b < _s.b ) ? false : true; }
	};



/*	color :	float r, g, b, a
_______________________________________________________________*/

	struct _color_rgba_float {
		float r, g, b, a;

		_color_rgba_float( void ) { r = g = b = 0.f; a = 1.f; }
		_color_rgba_float( float _n ) { r = g = b = _n; a = 1.f; }
		_color_rgba_float( const color3f _c, float _a ) { r = _c.r; g = _c.g; b = _c.b; a = _a; }
		_color_rgba_float( float _r, float _g, float _b, float _a ) { r = _r; g = _g; b = _b; a = _a; }

		// operator += and +
		_color_rgba_float const &_color_rgba_float::operator+=( _color_rgba_float const &_s ) { r += _s.r; g += _s.g; b += _s.b; return *this; }
		_color_rgba_float const &_color_rgba_float::operator+=( int _s ) { r += _s; g += _s; b += _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator+=( float _s ) { r += _s; g += _s; b += _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator+=( double _s ) { r += (float)_s; g += (float)_s; b += (float)_s; return *this; }
		_color_rgba_float operator+( _color_rgba_float const &_s ) { return _color_rgba_float( *this ) += _s; }
		_color_rgba_float operator+( int _s ) { return _color_rgba_float( *this ) += _s; }
		_color_rgba_float operator+( float _s ) { return _color_rgba_float( *this ) += _s; }
		_color_rgba_float operator+( double _s ) { return _color_rgba_float( *this ) += _s; }

		// operator -= and -
		_color_rgba_float const &_color_rgba_float::operator-=( _color_rgba_float const &_s ) { r -= _s.r; g -= _s.g; b -= _s.b; return *this; }
		_color_rgba_float const &_color_rgba_float::operator-=( int _s ) { r -= _s; g -= _s; b -= _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator-=( float _s ) { r -= _s; g -= _s; b -= _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator-=( double _s ) { r -= (float)_s; g -= (float)_s; b -= (float)_s; return *this; }
		_color_rgba_float operator-( _color_rgba_float const &_s ) { return _color_rgba_float( *this ) -= _s; }
		_color_rgba_float operator-( int _s ) { return _color_rgba_float( *this ) -= _s; }
		_color_rgba_float operator-( float _s ) { return _color_rgba_float( *this ) -= _s; }
		_color_rgba_float operator-( double _s ) { return _color_rgba_float( *this ) -= _s; }

		// operator *= and *
		_color_rgba_float const &_color_rgba_float::operator*=( int _s ) { r *= _s; g *= _s; b *= _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator*=( float _s ) { r *= _s; g *= _s; b *= _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator*=( double _s ) { r *= (float)_s; g *= (float)_s; b *= (float)_s; return *this; }
		_color_rgba_float operator*( int _s ) { return _color_rgba_float( *this ) *= _s; }
		_color_rgba_float operator*( float _s ) { return _color_rgba_float( *this ) *= _s; }
		_color_rgba_float operator*( double _s ) { return _color_rgba_float( *this ) *= _s; }

		// operator /= and /
		_color_rgba_float const &_color_rgba_float::operator/=( int _s ) { r /= _s; g /= _s; b /= _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator/=( float _s ) { r /= _s; g /= _s; b /= _s; return *this; }
		_color_rgba_float const &_color_rgba_float::operator/=( double _s ) { r /= (float)_s; g /= (float)_s; b /= (float)_s; return *this; }
		_color_rgba_float operator/( int _s ) { return _color_rgba_float( *this ) /= _s; }
		_color_rgba_float operator/( float _s ) { return _color_rgba_float( *this ) /= _s; }
		_color_rgba_float operator/( double _s ) { return _color_rgba_float( *this ) /= _s; }

		// operator =, == and !=
		_color_rgba_float const operator=( _color_rgb_float const &_s ) { r = _s.r; g = _s.g; b = _s.b; a = 1.f; return *this; }
		_color_rgba_float const operator=( _color_rgba_float const &_s ) { r = _s.r; g = _s.g; b = _s.b; a = _s.a; return *this; }
		bool const operator==( _color_rgba_float const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? false : true; }
		bool const operator!=( _color_rgba_float const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? true : false; }

		// operator <, <=, > and >=
		bool const operator<( _color_rgba_float const &_s ) { return ( r >= _s.r || g >= _s.g || b >= _s.b ) ? false : true; }
		bool const operator<=( _color_rgba_float const &_s ) { return ( r > _s.r || g > _s.g || b > _s.b ) ? false : true; }
		bool const operator>( _color_rgba_float const &_s ) { return ( r <= _s.r || g <= _s.g || b <= _s.b ) ? false : true; }
		bool const operator>=( _color_rgba_float const &_s ) { return ( r < _s.r || g < _s.g || b < _s.b ) ? false : true; }
	};



/*	color :	unsigned char r, g, b, a
_______________________________________________________________*/

	struct _color_rgba_uchar {
		unsigned char r, g, b, a;

		_color_rgba_uchar( void ) { r = g = b = 0; a = 255; }
		_color_rgba_uchar( unsigned char _n ) { r = g = b = _n; a = 255; }
		_color_rgba_uchar( const color3uc _c, unsigned char _a ) { r = _c.r; g = _c.g; b = _c.b; a = _a; }
		_color_rgba_uchar( const color4f _c ) { r = (unsigned char)( 255*_c.r ); g = (unsigned char)( 255*_c.g ); b = (unsigned char)( 255*_c.b ); a = (unsigned char)( 255*_c.a ); }
		_color_rgba_uchar( unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a ) { r = _r; g = _g; b = _b; a = _a; }

		// operator += and +
		_color_rgba_uchar const &_color_rgba_uchar::operator+=( _color_rgba_uchar const &_s ) { r += _s.r; g += _s.g; b += _s.b; return *this; }
		_color_rgba_uchar const &_color_rgba_uchar::operator+=( int _s ) { r += _s; g += _s; b += _s; return *this; }
		_color_rgba_uchar const &_color_rgba_uchar::operator+=( float _s ) { return *this += (unsigned char)_s; }
		_color_rgba_uchar const &_color_rgba_uchar::operator+=( double _s ) { return *this += (unsigned char)_s; }
		_color_rgba_uchar operator+( _color_rgba_uchar const &_s ) { return _color_rgba_uchar( *this ) += _s; }
		_color_rgba_uchar operator+( int _s ) { return _color_rgba_uchar( *this ) += _s; }
		_color_rgba_uchar operator+( float _s ) { return _color_rgba_uchar( *this ) += _s; }
		_color_rgba_uchar operator+( double _s ) { return _color_rgba_uchar( *this ) += _s; }

		// operator -= and -
		_color_rgba_uchar const &_color_rgba_uchar::operator-=( _color_rgba_uchar const &_s ) { r -= _s.r; g -= _s.g; b -= _s.b; return *this; }
		_color_rgba_uchar const &_color_rgba_uchar::operator-=( int _s ) { r -= _s; g -= _s; b -= _s; return *this; }
		_color_rgba_uchar const &_color_rgba_uchar::operator-=( float _s ) { return *this -= (unsigned char)_s; }
		_color_rgba_uchar const &_color_rgba_uchar::operator-=( double _s ) { return *this -= (unsigned char)_s; }
		_color_rgba_uchar operator-( _color_rgba_uchar const &_s ) { return _color_rgba_uchar( *this ) -= _s; }
		_color_rgba_uchar operator-( int _s ) { return _color_rgba_uchar( *this ) -= _s; }
		_color_rgba_uchar operator-( float _s ) { return _color_rgba_uchar( *this ) -= _s; }
		_color_rgba_uchar operator-( double _s ) { return _color_rgba_uchar( *this ) -= _s; }

		// operator *= and *
		_color_rgba_uchar const &_color_rgba_uchar::operator*=( int _s ) { r *= _s; g *= _s; b *= _s; return *this; }
		_color_rgba_uchar const &_color_rgba_uchar::operator*=( float _s ) { return *this *= (unsigned char)_s; }
		_color_rgba_uchar const &_color_rgba_uchar::operator*=( double _s ) { return *this *= (unsigned char)_s; }
		_color_rgba_uchar operator*( int _s ) { return _color_rgba_uchar( *this ) *= _s; }
		_color_rgba_uchar operator*( float _s ) { return _color_rgba_uchar( *this ) *= _s; }
		_color_rgba_uchar operator*( double _s ) { return _color_rgba_uchar( *this ) *= _s; }

		// operator /= and /
		_color_rgba_uchar const &_color_rgba_uchar::operator/=( int _s ) { r /= _s; g /= _s; b /= _s; return *this; }
		_color_rgba_uchar const &_color_rgba_uchar::operator/=( float _s ) { return *this /= (unsigned char)_s; }
		_color_rgba_uchar const &_color_rgba_uchar::operator/=( double _s ) { return *this /= (unsigned char)_s; }
		_color_rgba_uchar operator/( int _s ) { return _color_rgba_uchar( *this ) /= _s; }
		_color_rgba_uchar operator/( float _s ) { return _color_rgba_uchar( *this ) /= _s; }
		_color_rgba_uchar operator/( double _s ) { return _color_rgba_uchar( *this ) /= _s; }

		// operator =, == and !=
		_color_rgba_uchar const operator=( _color_rgb_uchar const &_s ) { r = _s.r; g = _s.g; b = _s.b; a = 255; return *this; }
		_color_rgba_uchar const operator=( _color_rgba_uchar const &_s ) { r = _s.r; g = _s.g; b = _s.b; a = _s.a; return *this; }
		bool const operator==( _color_rgba_uchar const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? false : true; }
		bool const operator!=( _color_rgba_uchar const &_s ) { return ( r != _s.r || g != _s.g || b != _s.b ) ? true : false; }

		// operator <, <=, > and >=
		bool const operator<( _color_rgba_uchar const &_s ) { return ( r >= _s.r || g >= _s.g || b >= _s.b ) ? false : true; }
		bool const operator<=( _color_rgba_uchar const &_s ) { return ( r > _s.r || g > _s.g || b > _s.b ) ? false : true; }
		bool const operator>( _color_rgba_uchar const &_s ) { return ( r <= _s.r || g <= _s.g || b <= _s.b ) ? false : true; }
		bool const operator>=( _color_rgba_uchar const &_s ) { return ( r < _s.r || g < _s.g || b < _s.b ) ? false : true; }
	};



/*	rectangle :	int location( x, y )
				int width, height
_______________________________________________________________*/

	struct _rectangle_int {
		point2i location;
		int width, height, area;

		_rectangle_int( void ) { width = height = area = 0; }
		_rectangle_int( int _x, int _y, int _w, int _h ) { location = point2i( _x, _y ); width = _w; height = _h; area = _w*_h; }
		_rectangle_int( point2i &_a, point2i &_b )
		{
			if( _a.x < _b.x ) { location.x = _a.x; width = _b.x - _a.x; } else { location.x = _b.x; width = _a.x - _b.x; }
			if( _a.y < _b.y ) { location.y = _a.y; height = _b.y - _a.y; } else { location.y = _b.y; height = _a.y - _b.y; }
			area = width*height;
		}
		
		// operator =, == and !=
		_rectangle_int const operator=( _rectangle_int const &_s ) { location = _s.location; width = _s.width; height = _s.height; return *this; }
		bool const operator==( _rectangle_int const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? false : true; }
		bool const operator!=( _rectangle_int const &_s ) { return ( ( location != _s.location ) || width != _s.width || height != _s.height ) ? true : false; }
	};



/*	rectangle :	float location( x, y )
				float width, height
_______________________________________________________________*/

	struct _rectangle_float {
		point2f location;
		float width, height, area;

		_rectangle_float( void ) { width = height = area = 0.f; }
		_rectangle_float( float _x, float _y, float _w,float _h ) { location = point2f( _x, _y ); width = _w; height = _h; area = _w*_h; }
		_rectangle_float( point2f &_a, point2f &_b )
		{
			if( _a.x < _b.x ) { location.x = _a.x; width = _b.x - _a.x; } else { location.x = _b.x; width = _a.x - _b.x; }
			if( _a.y < _b.y ) { location.y = _a.y; height = _b.y - _a.y; } else { location.y = _b.y; height = _a.y - _b.y; }
			area = width*height;
		}
		
		// operator =, == and !=
		_rectangle_float const operator=( _rectangle_float const &_s ) { location = _s.location; width = _s.width; height = _s.height; return *this; }
		bool const operator==( _rectangle_float const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? false : true; }
		bool const operator!=( _rectangle_float const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? true : false; }
	};



/*	rectangle :	int location( x, y )
				int top_left( x, y ), top_right( x, y ), bottom_left( x, y ), bottom_right( x, y )
				int width, height
_______________________________________________________________*/

	struct _rectangle_detail_int {
		point2i location;
		int width, height, area;
		point2i top_left, top_right, bottom_left, bottom_right;

		_rectangle_detail_int( void ) { width = height = 0; }
		_rectangle_detail_int( int _x, int _y, int _w, int _h )
		{
			location = point2i( _x, _y );
			width = _w;
			height = _h;
			SideCalculate();
		}
		_rectangle_detail_int( point2i &_a, point2i &_b )
		{
			if( _a.x < _b.x ) { location.x = _a.x; width = _b.x - _a.x; } else { location.x = _b.x; width = _a.x - _b.x; }
			if( _a.y < _b.y ) { location.y = _a.y; height = _b.y - _a.y; } else { location.y = _b.y; height = _a.y - _b.y; }
			SideCalculate();
		}
		_rectangle_detail_int( point2f &_a, point2f &_b )
		{
			if( _a.x < _b.x ) { location.x = (int)_a.x; width = (int)( _b.x - _a.x ); } else { location.x = (int)_b.x; width = (int)( _a.x - _b.x ); }
			if( _a.y < _b.y ) { location.y = (int)_a.y; height = (int)( _b.y - _a.y ); } else { location.y = (int)_b.y; height = (int)( _a.y - _b.y ); }
			SideCalculate();
		}
		_rectangle_detail_int( _rectangle_int &_s )
		{
			location = _s.location;
			width = _s.width;
			height = _s.height;
			SideCalculate();
		}

		// operator =, == and !=
		_rectangle_detail_int const operator=( _rectangle_detail_int const &_s )
		{
			width = _s.width; height = _s.height; area = _s.area;
			location = top_left = _s.top_left;
			top_right = _s.top_right; bottom_left = _s.bottom_left; bottom_right = _s.bottom_right;
			return *this;
		}
		bool const operator==( _rectangle_detail_int const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? false : true; }
		bool const operator!=( _rectangle_detail_int const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? true : false; }

		void const SideCalculate( void )
		{
			area = width*height;
			top_left = location;
			top_right = point2i( location.x + width, location.y );
			bottom_left = point2i( location.x, location.y - height );
			bottom_right = point2i( location.x + width, location.y - height );
		}
	};



/*	rectangle :	float location( x, y )
				float top_left( x, y ), top_right( x, y ), bottom_left( x, y ), bottom_right( x, y )
				float width, height
_______________________________________________________________*/

	struct _rectangle_detail_float {
		point2f location;
		float width, height, area;
		point2f top_left, top_right, bottom_left, bottom_right;
		
		void const SideCalculate( void )
		{
			area = width*height;
			top_left = location;
			top_right = point2f( location.x + width, location.y );
			bottom_left = point2f( location.x, location.y - height );
			bottom_right = point2f( location.x + width, location.y - height );
		}

		_rectangle_detail_float( void ) { width = height = area = 0; }
		_rectangle_detail_float( float _x, float _y, float _w, float _h )
		{
			location = point2f( _x, _y );
			width = _w;
			height = _h;
			SideCalculate();
		}		
		_rectangle_detail_float( point2i &_a, point2i &_b )
		{
			if( _a.x < _b.x ) { location.x = (float)_a.x; width = (float)( _b.x - _a.x ); } else { location.x = (float)_b.x; width = (float)( _a.x - _b.x ); }
			if( _a.y < _b.y ) { location.y = (float)_a.y; height = (float)( _b.y - _a.y ); } else { location.y = (float)_b.y; height = (float)( _a.y - _b.y ); }
			SideCalculate();
		}
		_rectangle_detail_float( point2f &_a, point2f &_b )
		{
			if( _a.x < _b.x ) { location.x = _a.x; width = _b.x - _a.x; } else { location.x = _b.x; width = _a.x - _b.x; }
			if( _a.y > _b.y ) { location.y = _a.y; height = _b.y - _a.y; } else { location.y = _b.y; height = _a.y - _b.y; }
			SideCalculate();
		}
		_rectangle_detail_float( _rectangle_float &_s )
		{
			location = _s.location;
			width = _s.width;
			height = _s.height;
			SideCalculate();
		}

		// operator =, == and !=
		_rectangle_detail_float const operator=( _rectangle_detail_float const &_s )
		{
			width = _s.width; height = _s.height; area = _s.area;
			location = top_left = _s.location;
			top_right = _s.top_right; bottom_left = _s.bottom_left; bottom_right = _s.bottom_right;
			return *this;
		}
		bool const operator==( _rectangle_detail_float const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? false : true; }
		bool const operator!=( _rectangle_detail_float const &_s ) { return ( location != _s.location || width != _s.width || height != _s.height ) ? true : false; }
	};



/*	ellipse :	int center( x, y )
				int alfa : length of long-axis
				int beta : length of short-axis
				int theta : angle between long-axis and x-axis
_______________________________________________________________*/

	struct _ellipse_xy_int {
		point2i center;
		int alfa, beta, theta;

		_ellipse_xy_int( void ) { alfa = beta = theta = 0; }
		_ellipse_xy_int( point2i &_s, int _a, int _b, int _t ) { center = _s; alfa = _a; beta = _b; theta = _t; }
		
		// operator =, == and !=
		_ellipse_xy_int const operator=( _ellipse_xy_int const &_s )
		{
			center = _s.center;
			alfa = _s.alfa;
			beta = _s.beta;
			theta = _s.theta;
			return *this;
		}
		bool const operator==( _ellipse_xy_int const &_s ) { return ( center != _s.center || alfa != _s.alfa || beta != _s.beta || theta != _s.theta ) ? false : true; }
		bool const operator!=( _ellipse_xy_int const &_s ) { return ( center != _s.center || alfa != _s.alfa || beta != _s.beta || theta != _s.theta ) ? true : false; }
	};



/*	ellipse :	float center( x, y )
				float alfa : length of long-axis
				float beta : length of short-axis
				float theta : angle between long-axis and x-axis
_______________________________________________________________*/

	struct _ellipse_xy_float {
		point2f center;
		float alfa, beta, theta;

		_ellipse_xy_float( void ) { alfa = beta = theta = 0; }
		_ellipse_xy_float( point2f &_s, float _a, float _b, float _t ) { center = _s; alfa = _a; beta = _b; theta = _t; }
		
		// operator =, == and !=
		_ellipse_xy_float const operator=( _ellipse_xy_float const &_s )
		{
			center = _s.center;
			alfa = _s.alfa;
			beta = _s.beta;
			theta = _s.theta;
			return *this;
		}
		bool const operator==( _ellipse_xy_float const &_s ) { return ( center != _s.center || alfa != _s.alfa || beta != _s.beta || theta != _s.theta ) ? false : true; }
		bool const operator!=( _ellipse_xy_float const &_s ) { return ( center != _s.center || alfa != _s.alfa || beta != _s.beta || theta != _s.theta ) ? true : false; }
	};



/*	triangle :	float p1( x, y, z ), p2( x, y, z ), p3( x, y, z )
_______________________________________________________________*/

	struct _triangle_xyz_float {
		point3f p1, p2, p3;

		_triangle_xyz_float( void ) { p1 = p2 = p3 = 0.f; }
		_triangle_xyz_float( point3f &_s1, point3f &_s2, point3f &_s3 ) { p1 = _s1; p2 = _s2; p3 = _s3; }

		// operator =, == and !=
		_triangle_xyz_float const operator=( _triangle_xyz_float const &_s )
		{
			p1 = _s.p1;
			p2 = _s.p2;
			p3 = _s.p3;
			return *this;
		}
		bool const operator==( _triangle_xyz_float const &_s )
		{
			int t1, t2, t3;
			t1 = t2 = t3 = 0x0;
			if( p1 == _s.p1 ) t1 ^= 0x1; if( p1 == _s.p2 ) t1 ^= 0x2; if( p1 == _s.p3 ) t1 ^= 0x4;
			if( p2 == _s.p1 ) t2 ^= 0x1; if( p2 == _s.p2 ) t2 ^= 0x2; if( p2 == _s.p3 ) t2 ^= 0x4;
			if( p3 == _s.p1 ) t3 ^= 0x1; if( p3 == _s.p2 ) t3 ^= 0x2; if( p3 == _s.p3 ) t3 ^= 0x4;
			if( !t1 || !t2 || !t3 ) return false;
			if( t1 & 0x1 ) if( t2 & 0x2 && t3 & 0x4 ) return true; else if( t2 & 0x4 && t3 & 0x2 ) return true;
			if( t2 & 0x1 ) if( t1 & 0x2 && t3 & 0x4 ) return true; else if( t1 & 0x4 && t3 & 0x2 ) return true;
			if( t3 & 0x1 ) if( t1 & 0x2 && t2 & 0x4 ) return true; else if( t1 & 0x4 && t2 & 0x2 ) return true;
			return false;
		}
		bool const operator!=( _triangle_xyz_float const &_s )
		{
			return ( ( p1 != _s.p1 && p1 != _s.p2 && p1 != _s.p3 ) || ( p2 != _s.p1 && p2 != _s.p2 && p2 != _s.p3 ) || ( p3 != _s.p1 && p3 != _s.p2 && p3 != _s.p3 ) ) ? true : false;
		}
	};


	
/*	size :	int width, height
_______________________________________________________________*/
	
	struct _size_wh_int {
		int width, height;

		_size_wh_int( void ) { width = height = 0; }
		_size_wh_int( int _w, int _h ) { width = _w; height = _h; }
		
		// operator =, == and !=
		_size_wh_int const operator=( _size_wh_int const &_s )
		{
			width = _s.width;
			height = _s.height;
			return *this;
		}
		bool const operator==( _size_wh_int const &_s )
		{
			return ( width != _s.width || height != _s.height ) ? false : true;
		}
		bool const operator!=( _size_wh_int const &_s )
		{
			return ( width != _s.width || height != _s.height ) ? true : false;
		}
	};


	
/*	size :	float width, height
_______________________________________________________________*/
	
	struct _size_wh_float {
		float width, height;

		_size_wh_float( void ) { width = height = 0; }
		_size_wh_float( float _w, float _h ) { width = _w; height = _h; }
		
		// operator =, == and !=
		_size_wh_float const operator=( _size_wh_float const &_s )
		{
			width = _s.width;
			height = _s.height;
			return *this;
		}
		bool const operator==( _size_wh_float const &_s )
		{
			return ( width != _s.width || height != _s.height ) ? false : true;
		}
		bool const operator!=( _size_wh_float const &_s )
		{
			return ( width != _s.width || height != _s.height ) ? true : false;
		}
	};




/*	plane :	vector3f n
			float d
_______________________________________________________________*/

	struct _plane_vd_float {
		vector3f n;
		float d;

		_plane_vd_float( void ) { n = 0.f; d = 0.f; }
		_plane_vd_float( float _n ) { n = _n; d = 0.f; }
		_plane_vd_float( float _a, float _b, float _c, float _d ) { n = vector3f( _a, _b, _c ); d = _d; }
		_plane_vd_float( vector3f _n, float _d ) { n = _n; d = _d; }

		// operator =, == and !=
		_plane_vd_float const operator=( _plane_vd_float const &_s ) { n = _s.n; d = _s.d; return *this; }
		bool const operator==( _plane_vd_float const &_s ) { return ( n != _s.n || d != _s.d ) ? false : true; }
		bool const operator!=( _plane_vd_float const &_s ) { return ( n != _s.n || d != _s.d ) ? true : false; }
	};




/*	transform :	vector3f mx, my, mz, mt

				if S_TRANSFORM_INV :		else
				[ mx.x mx.y mx.z mt.x ]		[ mx.x my.x mz.x mt.x ]
				[ my.x my.y my.z mt.y ]		[ mx.y my.y mz.y mt.y ]
				[ mz.x mz.y mz.z mt.z ]		[ mx.z my.z mz.z mt.z ]
				[    0    0    0    1 ]		[    0    0    0    1 ]
_______________________________________________________________*/

	struct _transform_float {
		vector3f mx, my, mz, mt;

		_transform_float( void )
		{
			mx = vector3f( 1.f, 0.f, 0.f );
			my = vector3f( 0.f, 1.f, 0.f );
			mz = vector3f( 0.f, 0.f, 1.f );
			mt = 0.f;
		}
		_transform_float( vector3f &_t )
		{
			mx = vector3f( 1.f, 0.f, 0.f );
			my = vector3f( 0.f, 1.f, 0.f );
			mz = vector3f( 0.f, 0.f, 1.f );
			mt = _t;
		}
		_transform_float( vector3f &_x, vector3f &_y, vector3f &_z ) { mx = _x; my = _y; mz = _z; mt = 0.f; }
		_transform_float( vector3f &_x, vector3f &_y, vector3f &_z, vector3f &_t ) { mx = _x; my = _y; mz = _z; mt = _t; }

		// operator =, == and !=
		_transform_float const operator=( _transform_float const &_s ) { mx = _s.mx; my = _s.my; mz = _s.mz; mt = _s.mt; return *this; }
		bool const operator==( _transform_float const &_s ) { return ( mx != _s.mx || my != _s.my || mz != _s.mz || mt != _s.mt ) ? false : true; }
		bool const operator!=( _transform_float const &_s ) { return ( mx != _s.mx || my != _s.my || mz != _s.mz || mt != _s.mt ) ? true : false; }
	};



#ifdef __cplusplus
}
#endif

#endif