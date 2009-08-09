#include "fitness.ih"

static bool
sort_on_name(pair<string, double> const &first, pair<string, double> const &second)
{
	return first.first < second.first;
}

vector<double> Fitness::values() const
{
	vector<double> ret;
	vector<pair<string, double> > per;
	
	for (map<string, double>::iterator iter = d_data->components.begin(); iter != d_data->components.end(); ++iter)
	{
		per.push_back(pair<string, double>(iter->first, iter->second));
	}
	
	sort(per.begin(), per.end(), &sort_on_name);
	
	for (vector<pair<string, double> >::iterator iter = per.begin(); iter != per.end(); ++iter)
	{
		ret.push_back(iter->second);
	}
	
	return ret;
}
