
template <class T>
class vec4 {
public:
	T x;
	T y;
	T z;
	T w;
	vec4() {}
	vec4(const T& a, const T& b, const T& c, const T& d) {
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

template <class T>
class vec3{
public:
    T x;
    T y;
    T z;

    vec3(){}
	vec3(const T& a, const T& b, const T& c) {
		x = a;
		y = b;
		z = c;
	}
};

template <class T>
class vec2{
public:
    T x;
    T y;
	vec2() {}
	vec2(const T& a, const T& b) {
		x = a;
		y = b;
	}
};


