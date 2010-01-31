#include "processes.hh"
#include <dirent.h>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;
using namespace optimization;

GPid
Processes::Parent(GPid child)
{
	stringstream path;

	path << "/proc/" << child << "/stat";
	fstream st(path.str().c_str(), ios::in);
	string line;

	if (!st || !getline(st, line))
	{
		st.close();
		return -1;
	}

	st.close();
	size_t pos = line.find_first_of(')');

	if (pos == string::npos)
	{
		return -1;
	}

	stringstream s(line.substr(pos + 1));
	string dummy;
	GPid parentPid;

	if (!(s >> dummy >> parentPid))
	{
		return -1;
	}

	return parentPid;
}

vector<GPid>
Processes::Collect(map<GPid, vector<GPid> > const &mapping, GPid parent, bool recurse)
{
	map<GPid, vector<GPid> >::const_iterator found;
	vector<GPid> ret;

	found = mapping.find(parent);

	if (found == mapping.end())
	{
		return ret;
	}

	for (vector<GPid>::const_iterator iter = found->second.begin(); iter != found->second.end(); ++iter)
	{
		ret.push_back(*iter);

		if (recurse)
		{
			vector<GPid> r = Collect(mapping, *iter, true);
			copy(r.begin(), r.end(), back_inserter(ret));
		}
	}

	return ret;
}

vector<GPid>
Processes::Children(GPid parent, bool recurse)
{
	map<GPid, vector<GPid> > childMap;
	DIR *d = opendir("/proc");

	if (d == 0)
	{
		return vector<GPid>();
	}

	dirent *entry;

	while ((entry = readdir (d)) != 0)
	{
		stringstream s;
		s << entry->d_name;

		GPid child;

		if (!(s >> child))
		{
			continue;
		}

		GPid parentPid = Parent(child);

		if (parentPid == -1)
		{
			continue;
		}

		map<GPid, vector<GPid> >::iterator found = childMap.find(parentPid);

		if (found == childMap.end())
		{
			vector<GPid> children;
			children.push_back(child);

			childMap[parentPid] = children;
		}
		else
		{
			found->second.push_back(child);
		}
	}

	closedir(d);
	return Processes::Collect(childMap, parent, recurse);
}
