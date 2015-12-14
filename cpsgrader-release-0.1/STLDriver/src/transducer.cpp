#include "stdafx.h"
#include <transducer.h>
#include <algorithm>

namespace CPSGrader {

/* init horizon */
void transducer::init_horizon() {
}

void unary_transducer::init_horizon() {
	child->set_horizon(start_time, end_time);
	child->init_horizon();
}

void binary_transducer::init_horizon() {
	childL->set_horizon(start_time, end_time);
	childR->set_horizon(start_time, end_time);
	childL->init_horizon();
	childR->init_horizon();

}

void timed_unary_transducer::init_horizon() {

//	cout << "timed_unary_transducer::init_horizon - start_time:" << start_time <<  endl;
	// checks whether a and b are given by parameters, and assign corresponding values
	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	// update start_time and end_time of child
	child->set_horizon(start_time+a,end_time+b);
	child->init_horizon();

}

void timed_binary_transducer::init_horizon() {

	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	// update start_time and end_time of children
	childL->set_horizon(start_time, end_time+b);
	childR->set_horizon(start_time+a, end_time+b);
	childL->init_horizon();
	childR->init_horizon();

}

/* Compute robustness */
double not_transducer::compute_robustness() {
//	cout << "Computing robustness of NOT" << endl;
	child->compute_robustness();
	z.compute_not(child->z);
	return z.front().value;
}

double ev_transducer::compute_robustness() {

	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	child->compute_robustness();

	z.compute_timed_eventually(child->z, a, b);
	z.resize(0., z.endTime, 0.);

	return z.front().value;
}

double alw_transducer::compute_robustness() {
//	cout << "Computing robustness of ALW" << endl;

	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	child->compute_robustness();
	z.compute_timed_globally(child->z, a, b);
    z.resize(0.,z.endTime,0.);

    return z.front().value;
}

double and_transducer::compute_robustness() {

//	cout << "Computing robustness of AND" << endl;
	childL->compute_robustness();
	childR->compute_robustness();

	z.compute_and(childL->z, childR->z);

	z.resize(0.,z.endTime,0.);
	return z.front().value;
}

double or_transducer::compute_robustness() {

//	cout << "Computing robustness of AND" << endl;

	childL->compute_robustness();
	childR->compute_robustness();

	z.compute_or(childL->z,childR->z);
//	cout << "Or:" << z << endl;

    z.resize(0.,z.endTime,0.);
	return z.front().value;
}

double implies_transducer::compute_robustness() {

	childL->compute_robustness();
	childR->compute_robustness();

	Signal *rob = computeImplies(&childL->z, &childR->z);
	z = *rob;
	delete rob;

    z.resize(0.,z.endTime,0.);
	return z.front().value;
}

double until_transducer::compute_robustness() {

	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	// update robustness of children
    childL->compute_robustness();
    childR->compute_robustness();

	z.compute_timed_until(childL->z,childR->z, a, b);
    z.resize(0.,z.endTime,0.);
	return z.front().value;

}

/* Utility functions */

Signal transducer::get_signal() const {
	return z;
}

bool transducer::get_param(const string & param, double & val) {

	 map<string, double>::iterator it;
	 if ( (it= param_map.find(param)) != param_map.end()) {
		 val = it->second;
		 return true;
	 }
	 else{
		 val = 0.;
		 return false;
	 }
}

std::ostream& operator<<(std::ostream& os, const transducer& T) {
	T.print(os);
	return os;
}

}
