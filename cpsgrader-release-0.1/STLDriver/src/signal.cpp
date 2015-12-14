#include "stdafx.h"
#include "signal.h"
#include "iomanip"

/* 
 * class Signal member functions
 */
Signal::Signal(double T, double V, int n) {

	beginTime=T;
	endTime=T;
	push_back(Sample(T, V, 0.));

}

Signal::Signal(double * T, double * V, int n) {
#ifdef DEBUG__
	cout << "Entering Signal::Signal" << endl;
#endif

	beginTime=T[0];
	endTime=T[n-1];

	if (n==1)
		push_back(Sample(T[0], V[0], 0.));
	else {
		for(int i=0; i < n-1; i++) {
			push_back(Sample(T[i], V[i], (V[i+1]-V[i]) / (T[i+1] - T[i])));
		}
		push_back(Sample(T[n-1], V[n-1], 0.));
	}
}

void Signal::appendSample(double t, double v) {

	//cout << "Appending t=" << t << " v=" << v << endl;

	if ((t<=endTime)&&size()>0)
		return;

	if (size()==0) {
		push_back(Sample(t,v,0.));
		beginTime=t;
	}
	else {
		back().derivative = (v-back().value) / (t - back().time);
		push_back(Sample(t,v,0));
		endTime= t;
	}
}

//remove linear interpolations
void Signal::simplify() {
#ifdef DEBUG__
	cout << "Entering Signal::simplify" << endl;
#endif
	push_back(front());
	pop_front();
	while (front().time != beginTime) {
		if( back().valueAt(front().time) != front().value || back().derivative != front().derivative ) {
			push_back(front());
		}
		pop_front();
	}

	// check last sample
	if (back().time < endTime)
		push_back(Sample(endTime, back().valueAt(endTime), 0.));

}

void Signal::resize(double s, double t, double v) {

#ifdef DEBUG__
	cout << "Entering Signal::resize" << endl;
#endif

	if ( t<s ) {
		clear();
		beginTime=0.;
		endTime=0;
		return;
	}
	Sample first;

	//trim or extend front of signal

	if(beginTime > s) {
		push_front(Sample(s, v, 0));
	}
	else {
		while((!empty())&&(front().time < s)) {
			first=front();
			pop_front();
		}
		if(!empty()&&front().time > s) {
			push_front(Sample(s, first.valueAt(s), 0));
		}
	}

	//trim or extend back of signal

	if(endTime < t) {
		push_back(Sample(endTime, v, 0));
	}
	else {
		while(!empty()&&back().time >t) {
			pop_back();
		}
	}
	if (empty())
		push_back(Sample(s, v, 0));

	beginTime=s;
	endTime=t;
}

void Signal::shift(double a) {
	Signal::iterator i;

	beginTime=beginTime + a;
	endTime=endTime + a;

	for(i = begin(); i != end(); i++) {
		i->time=i->time + a;
	}
}

void Signal::removeInf() {

	while((!empty())&&
        			(back().value==TOP ||
					back().derivative == TOP ||
					back().value==BOTTOM ||
					back().derivative == BOTTOM)) {
		pop_back();
	}
}

/*
 * friend functions
 */
 std::ostream & operator<<(std::ostream & out, const Point & point) {
	 out << point.time << ";" << point.value ;
	 return out;
 }

 std::ostream & operator<<(std::ostream & out, const Sample & sample) {

	 out << std::setprecision(8) << std::setw(12) << sample.time << "  " << std::setprecision(8) << std::setw(12)  << sample.value << "  " << sample.derivative;
	 return out;
 }

 std::ostream & operator<<(std::ostream & out, const Sequence & M) {
	 Sequence::const_iterator i;

	 if(M.empty()) return out << "EMPTY" << std::endl;

	 for(i = M.begin(); i != M.end(); i++) {
		 out << *i << std::endl;
	 }
	 return out;
 }

 std::ostream & operator<<(std::ostream & out, const Signal & y) {
	 Signal::const_iterator i;

	 if(y.begin() == y.end()) return out << "EMPTY" << std::endl;

	 out << "def = [" << y.beginTime << ", " << y.endTime << ")" << std::endl;
	 for(i = y.begin(); i != y.end(); i++) {
		 out << *i << std::endl;
	 }
	 return out;
 }

