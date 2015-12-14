#include "stdafx.h"
#include <transducer.h>
#include <algorithm>

namespace CPSGrader {

/* Interval robustness */

// default (static): interval robustness is the same as normal robustness
double transducer::compute_lower_rob(){
	compute_robustness();
	z_low = z;
 	return z_low.front().value;
};

double transducer::compute_upper_rob(){
	compute_robustness();
	z_up = z;
	return z_up.front().value;
};

// NOT transducer: swap upper and lower
double not_transducer::compute_upper_rob(){
	child->compute_lower_rob();
	if (child->z_low.empty())
		return TOP;

	z_up.compute_not(child->z_low);
	return z_up.front().value;
}

double not_transducer::compute_lower_rob(){
	child->compute_upper_rob();
	if (child->z_up.empty())
		return BOTTOM;

	z_low.compute_not(child->z_up);
	return z_low.front().value;
}

// EVENTUALLY
double ev_transducer::compute_lower_rob() {

//	cout << "Getting into ev_transducer::compute_lower_rob" << endl;
	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	if (child->compute_lower_rob()==BOTTOM) return BOTTOM;
//	cout << "child->z_low:" << child->z_low << endl;

	z_low.compute_timed_eventually(child->z_low, a, b);

	z_low.resize(0.,z_low.endTime,0.);
	return z_low.front().value;

}

double ev_transducer::compute_upper_rob() {

//	cout << "Getting into ev_transducer::compute_upper_rob" << endl;
	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	if (child->compute_upper_rob()==TOP) return TOP;
//	cout << "child->z_up:" << child->z_up << endl;

	z_up.compute_timed_eventually(child->z_up, a, b);
	z_up.resize(0, z_up.endTime-b,0.);

	if (z_up.empty())
		return TOP;
	else
		return z_up.front().value;
}

// ALWAYS
double alw_transducer::compute_lower_rob() {

//	cout << "Getting into alw_transducer::compute_lower_rob" << endl;
	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	if (child->compute_lower_rob()==BOTTOM) return BOTTOM;

//	cout << "child->z_low:" << child->z_low << endl;

	z_low.compute_timed_globally(child->z_low, a, b);
	z_low.resize(0, z_low.endTime-b,0.);

	if (z_low.empty())
			return BOTTOM;
		else
			return z_low.front().value;
}

double alw_transducer::compute_upper_rob() {

//	cout << "Getting into alw_transducer::compute_upper_rob" << endl;
	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

	if (child->compute_upper_rob() == TOP) return TOP;
//	cout << "child->z_up:" << child->z_up << endl;

	z_up.compute_timed_globally(child->z_up, a, b);
	return z_up.front().value;

}

// TODO the following is a super conservative implementation - (how) can we do better ?
double until_transducer::compute_lower_rob() {

//	cout << "Getting into until_transducer::compute_lower_rob" << endl;
	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

    if (childL->compute_lower_rob()==BOTTOM) return BOTTOM;
    if (childR->compute_lower_rob()==BOTTOM) return BOTTOM;

//	cout << "childL->z_low:" << childL->z_low << endl;
//	cout << "childR->z_low:" << childR->z_low << endl;

//  Too bad, doesn't work
//	childL->z_low.appendSample(childL->end_time, BOTTOM);
//	childR->z_low.appendSample(childR->end_time, BOTTOM);

//  z_low.compute_timed_until(childL->z_low,childR->z_low, a, b);
//	z_low.removeInf();

//  This does not work ...
//	if (z_low.empty())
//		return BOTTOM;
//	else
//		return z_low.front().value;

	z_low.compute_timed_until(childL->z_low,childR->z_low, a, b);
	z_low.resize(0, z_low.endTime-b,0.);

	if (z_low.empty())
		return BOTTOM;
	else
    	return z_low.front().value;

}


double until_transducer::compute_upper_rob() {

	double a,b;
	if (!get_param(I->begin_str,a)) a = I->begin;
	if (!get_param(I->end_str,b)) b = I->end;

    if (childL->compute_upper_rob()==TOP) return TOP;
    if (childR->compute_upper_rob()==TOP) return TOP;

//  Too bad this doesn't work
//	childL->z_up.appendSample(childL->end_time, TOP);
//	childR->z_up.appendSample(childR->end_time, TOP);
//
//	z_up.compute_timed_until(childL->z_up,childR->z_up, a, b);
//	z_up.removeInf();
//
//	if (z_up.empty())
//		return BOTTOM;
//	else
//		return z_up.front().value;

	z_up.compute_timed_until(childL->z_up,childR->z_up, a, b);
	z_up.resize(0, z_up.endTime-b,0.);

	if (z_up.empty())
		return TOP;
	else
		return z_up.front().value;
}



}
