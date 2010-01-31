#include "processes.hh"
#include <dirent.h>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;
using namespace optimization;

pid_t
Processes::Parent(pid_t child)
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
	pid_t parentPid;

	if (!(s >> dummy >> parentPid))
	{
		return -1;
	}

	return parentPid;
}

vector<pid_t>
Processes::Collect(map<pid_t, vector<pid_t> > const &mapping, pid_t parent, bool recurse)
{
	map<pid_t, vector<pid_t> >::const_iterator found;
	vector<pid_t> ret;

	found = mapping.find(parent);

	if (found == mapping.end())
	{
		return ret;
	}

	for (vector<pid_t>::const_iterator iter = found->second.begin(); iter != found->second.end(); ++iter)
	{
		ret.push_back(*iter);

		if (recurse)
		{
			vector<pid_t> r = Collect(mapping, *iter, true);
			copy(r.begin(), r.end(), back_inserter(ret));
		}
	}

	return ret;
}

vector<pid_t>
Processes::Children(pid_t parent, bool recurse)
{
	map<pid_t, vector<pid_t> > childMap;
	DIR *d = opendir("/proc");

	if (d == 0)
	{
		return vector<pid_t>();
	}

	dirent *entry;

	while ((entry = readdir (d)) != 0)
	{
		stringstream s;
		s << entry->d_name;

		pid_t child;

		if (!(s >> child))
		{
			continue;
		}

		pid_t parentPid = Parent(child);

		if (parentPid == -1)
		{
			continue;
		}

		map<pid_t, vector<pid_t> >::iterator found = childMap.find(parentPid);

		if (found == childMap.end())
		{
			vector<pid_t> children;
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
