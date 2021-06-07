#pragma once
#define M_PI       3.14159265358979323846   // pi
#include <vector>
#include <cmath>//<cmath.h>>
 
#include <cassert>

/*
Args:\n\
	h (int): Time Horizon parameter ,  which controls the size of horizon window in seconds,
	and controls which microclusters become expired (landmark window);
	q (int): Maximum number of micro clusters to use, which controls how many microclusters are kept
	(a total q MicroClusters to maintain at any moments --from the paper)  
	t (int): Multiplier for the Cluster radius,(the maximal boundary factor,calculated by the 
	  RMS deviation of the data points in Mp from the centroid. in the paper), 
	which controls how large the radius of a microcluster is to  allow new instances to be appended

Attributes:\n\
	 
	timestamp (int): current timestamp 
	points_fitted (int): number of datapoints that entered the 'fit' case 
	points_forgot (int): number of datapoints that entered the 'forgot microcluster' case 
	points_merged (int): number of datapoints that entered the 'merged microcluster' case"

*/

const double RADIUS_FACTOR = 1.8;
const double EPSILON = 0.00005;
const double MIN_VARIANCE = 1e-50;

typedef std::vector<double> Point;

class Kernel{
public:
	double t;
	unsigned int q;

	unsigned int n;
	Point ls;
	Point ss;
	double lst;
	double sst;

	Point center;

	Kernel(Point& datapoint,long timestamp, double t, unsigned int q);
	void insert(Point& datapoint,long timestamp);
	void add(Kernel& other);
	double get_relevance_stamp();
	double get_mu_time();
	double get_sigma_time();
	double get_quantile(double z);
	double get_radius();
	double get_deviation();
	Point get_center();
	double get_inclusion_probability(Point& datapoint);
	Point get_variance_vector();
	double calc_normalized_distance(Point& datapoint);
	double inverse_error(double x);
};

