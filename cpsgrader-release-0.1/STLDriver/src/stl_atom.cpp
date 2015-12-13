#include "stdafx.h"
#include <transducer.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "tools.h"
#include <exception>
#include "signal_expr.h"

namespace CPSGrader {

constant_transducer::constant_transducer(const string &p) {

	value = 0.;
	if (!s_to_d(p, value))  param = p;

}

double stl_atom::compute_robustness() {

//	cout << "stl_atom::compute_robustness - start_time:" << start_time << " end_time:" << end_time << endl;
	// Assumes childL and childR have signals with same number of samples
	// should be eventually improved with proper operations on signals
	childL->compute_robustness();
	childR->compute_robustness();
	auto itL = childL->z.begin();
	auto itR = childR->z.begin();

	for (; itL != childL->z.end();itL++, itR++) {
		double t = (*itL).time;
		double vL = (*itL).value;
		double vR = (*itR).value;
		if (comp == comparator::LESSTHAN )
			z.appendSample(t, vR - vL); // comparator::LESSTHAN
		else
			z.appendSample(t, vL - vR); // comparator::GREATERTHAN
	}

//	cout << "z:" << z << endl;
	return z.front().value;

}

double signal_transducer::compute_robustness() {

	//	cout << "Getting Signal values" << endl;
	short i = signal_map[variable];
	double t0 =  (*trace_data_ptr->begin())[0] ;


	if (i) {
		for (auto step = trace_data_ptr->begin(); step != trace_data_ptr->end();
				step++) {

			double t = (*step)[0]-t0;
			double v = (*step)[i];
			z.appendSample(t, v);
			if (t>end_time)
				break;
		}
	} else {
		return 0.;
	}

	return z.front().value;
}

double constant_transducer::compute_robustness() {

	// TODO exception if parameter not found for some reason ? For now, we get 0. as a default silent value.
	if (!param.empty()) {
		get_param(param, value);
	}

	double t0 =  (*trace_data_ptr->begin())[0] ;
	for (auto step = trace_data_ptr->begin(); step != trace_data_ptr->end();
			step++) {
		double t = (*step)[0]-t0;

		z.appendSample(t, value);
		if (t>end_time)
			break;

	}

	return z.front().value;

}

}

