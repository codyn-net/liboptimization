#ifndef __OPTIMIZATION_CONTAINER_H__
#define __OPTIMIZATION_CONTAINER_H__

#include <vector>
#include <map>
#include <string>

#include <base/Object/object.hh>

namespace optimization
{
	template <typename T>
	class Container : public base::Object
	{
		public:
			typedef T value_type;
			typedef typename std::vector<T *>::iterator iterator;
			typedef typename std::vector<T *>::const_iterator const_iterator;

			/* Public functions */
			Container();
			Container(const_iterator begin, const_iterator end);
			
			T &add(T const &item);
			int remove(std::string const &name);

			T const &operator[](std::string const &name) const;
			T &operator[](std::string const &name);
			
			T const &operator[](size_t idx) const;
			T &operator[](size_t idx);
			
			operator std::map<std::string, T *> const &() const;
			operator std::vector<T *> const &() const;
			
			virtual Container<T> *clone() const;
			virtual Container<T> *copy() const;
			
			std::vector<std::string> const &names() const;
			
			/* Iterators */
			iterator begin();
			const_iterator begin() const;
			
			iterator end();
			const_iterator end() const;
			
			bool includes(std::string const &name) const;
			
			size_t size() const;
		private:
			struct Data : public base::Object::PrivateData
			{
				/* Instance data */
				T dummy;

				std::map<std::string, T *> items;
				std::vector<T *> ordered;
				std::vector<std::string> names;
				
				~Data();
			};
	
			Data *d_data;

			/* Private functions */			
			void initialize();
			void remove(int i);
	};
	
	template <typename T>
	Container<T>::Container()
	{
		initialize();
	}
	
	template <typename T>
	Container<T>::Container(const_iterator begin, const_iterator end)
	{
		initialize();
		
		for (const_iterator iter = begin; iter != end; ++iter)
		{
			add(**iter);
		}
	}
	
	template <typename T>
	Container<T> *Container<T>::clone() const
	{
		return new Container<T>(*this);
	}
	
	template <typename T>
	Container<T> *Container<T>::copy() const
	{
		return new Container<T>(begin(), end());
	}
	
	template <typename T>
	void Container<T>::initialize()
	{
		d_data = new Data();
		addPrivateData(d_data);
	}
	
	template <typename T>
	T &Container<T>::add(T const &item)
	{
		if (d_data->items.find(item.name) == d_data->items.end())
		{
			T *nt = new T(item);
			
			d_data->items[nt->name] = nt;
			d_data->ordered.push_back(nt);
			d_data->names.push_back(nt->name);
			
			return *nt;
		}
		else
		{
			return d_data->dummy;
		}
	}
	
	template <typename T>
	int Container<T>::remove(std::string const &name)
	{
		if (!includes(name))
		{
			return -1;
		}
		
		for (int i = 0; i < d_data->ordered.size(); ++i)
		{
			if (d_data->ordered[i]->name == name)
			{
				remove(i);
				return i;
			}
		}
		
		return -1;
	}
	
	template <typename T>
	void Container<T>::remove(int i)
	{
		d_data->items.erase(d_data->ordered[i]->name);
		delete d_data->ordered[i];
		
		d_data->ordered.erase(d_data->ordered.begin() + i);
		d_data->names.erase(d_data->names.begin() + 1);
	}
	
	template <typename T>
	T const &Container<T>::operator[](std::string const &name) const
	{
		typename std::map<std::string, T *>::const_iterator iter = d_data->items.find(name);
		
		return (iter != d_data->items.end()) ? *(iter->second) : d_data->dummy;
	}
	
	template <typename T>
	T &Container<T>::operator[](std::string const &name)
	{
		typename std::map<std::string, T *>::iterator iter = d_data->items.find(name);
		
		return (iter != d_data->items.end()) ? *(iter->second) : d_data->dummy;
	}
	
	template <typename T>
	T const &Container<T>::operator[](size_t idx) const
	{
		return (idx >= size()) ? d_data->dummy : *d_data->ordered[idx];
	}
	
	template <typename T>
	T &Container<T>::operator[](size_t idx)
	{
		return (idx >= size()) ? d_data->dummy : *d_data->ordered[idx];
	}
	
	template <typename T>
	size_t Container<T>::size() const
	{
		return d_data->ordered.size();
	}
	
	template <typename T>
	Container<T>::operator std::map<std::string, T *> const &() const
	{
		return d_data->items;
	}
	
	template <typename T>
	Container<T>::operator std::vector<T *> const &() const
	{
		return d_data->ordered;
	}
	
	template <typename T>
	typename Container<T>::iterator Container<T>::begin()
	{
		return d_data->ordered.begin();
	}
	
	template <typename T>
	typename Container<T>::iterator Container<T>::end()
	{
		return d_data->ordered.end();
	}
	
	template <typename T>
	typename Container<T>::const_iterator Container<T>::begin() const
	{
		return d_data->ordered.begin();
	}
	
	template <typename T>
	typename Container<T>::const_iterator Container<T>::end() const
	{
		return d_data->ordered.end();
	}
	
	template <typename T>
	Container<T>::Data::~Data() 
	{
		for (typename std::vector<T *>::iterator iter = ordered.begin(); iter != ordered.end(); ++iter)
		{
			delete *iter;
		}
	}
	
	template <typename T>
	bool Container<T>::includes(std::string const &name) const
	{
		return d_data->items.find(name) != d_data->items.end();
	}
	
	template <typename T>
	std::vector<std::string> const &Container<T>::names() const
	{
		return d_data->names;
	}
}

#endif /* __OPTIMIZATION_CONTAINER_H__ */
