#include "FLOAT.h"

FLOAT Fabs(FLOAT a) {
	if(a >> 31 == 0){
		return a;
	}else{
		return (~a) + 1;
	}
}
FLOAT F_mul_F(FLOAT a, FLOAT b) {
//	nemu_assert(0);
	int result;
	int i = 0;
	// a * 2^i < 0x7fffffff
	while(Fabs(a) / 2 > 16384){
		i++;
		a = a / 2;
		if(i == 16)
			break;
	}
	while(Fabs(b) / 2 > 16384){
		i++;
		b = b / 2;
		if(i == 16)
			break;
	}
	result = a * b;
	while(i != 16){
		i++;
		result /= 2;
	}
	return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	int result;
	int i = 0;
	// a * 2^i < 0x7fffffff
	while(F_mul_int(Fabs(a),2) >> 31 == 0){
		i++;
		a = a * 2;
		if(i == 16)
			break;
	}
	result = a / b;
	while(i != 16){
		i++;
		result *= 2;
	}
	return result;
}

FLOAT f2F(float a) {
	FLOAT af = *(FLOAT *) &a;
	FLOAT result;
	FLOAT s,e,f;
	f = af & 0x7fffff;
	e = (af >> 23) & 0xff;
	s = (af >> 31) & 0x1;
	f = f | 0x800000;
	e = e - 127;
	e = e + 16;	//* 2^16
	if(e > 23){
		result = f << (e - 23);
	}else{
		result = f >> (23 - e);
	}
	if(s == 1){
		result = (~result) + 1;
	}else{
		result = result & 0x7fffffff;
	}
	return result;
}


FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

