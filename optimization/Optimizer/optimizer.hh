#ifndef __OPTIMIZATION_OPTIMIZER_H__
#define __OPTIMIZATION_OPTIMIZER_H__

#include <base/Object/object.hh>
#include <base/Signals/Signal/signal.hh>
#include <math/math.hh>
#include <sstream>

#include <optimization/Boundaries/boundaries.hh>
#include <optimization/Parameters/parameters.hh>
#include <optimization/Settings/settings.hh>
#include <optimization/Solution/solution.hh>
#include <optimization/Fitness/fitness.hh>

#include <db/SQLite/sqlite.hh>
#include <string>

namespace optimization
{
	/** Basic optimizer abstract class
	 */
	class Optimizer : public base::Object
	{
		public:
			struct LogType
			{
				static std::string names[4];

				enum Values
				{
					None = 0,
					Info = 1,
					Warning = 2,
					Error = 3
				};
			};
			
			class Logger
			{
				base::Enum<LogType> d_logType;
				Optimizer *d_optimizer;

				std::stringstream d_stream;
			
				public:
					struct End
					{
					};

					Logger(Optimizer *job, base::Enum<LogType> const &logtype);
					Logger(Logger const &other);
					
					template <typename T>
					Logger &operator<<(T t);
			};

			Optimizer();
			Optimizer(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness);
			
			// Accessors
			Boundaries const &boundaries() const;
			Boundaries &boundaries();
			
			Parameters const &parameters() const;
			Parameters &parameters();
			
			Fitness const &fitness() const;
			Fitness &fitness();

			Settings const &settings() const;
			Settings &settings();

			State const &state() const;
			State &state();

			// Best solution so far			
			bool hasBest() const;
			Solution &best();
			Solution const &best() const;
			
			// Current iteration
			size_t currentIteration() const;
			
			// Name
			std::string const &name() const;
			void setName(std::string const &name);
			
			// Data file name
			void setDataFilename(std::string const &filename);
			
			// Solutions
			std::vector<base::Cloneable<Solution> > &solutions();
			std::vector<base::Cloneable<Solution> > const &solutions() const;

			void initialize(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness);

			// New iteration
			bool iteration();

			db::SQLite &db();
			
			// Logging
			void log(base::Enum<LogType> const &type, std::string const &message);
			Logger log(base::Enum<LogType> const &type);
			
			// Virtual methods
			virtual Solution *createSolution(size_t id);
			virtual void addSolution(Solution &solution);

			virtual void clear();
			virtual Optimizer *clone() const;
		protected:
			virtual void save();
			virtual void save(Solution &solution);

			virtual bool done();

			virtual void update();
			virtual void update(Solution &solution);

			virtual void initialPopulation();
			virtual void initializeDatabase();
		private:
			struct Data : public base::Object::PrivateData
			{
				std::string dataFilename;
				db::SQLite db;

				Boundaries boundaries;
				Parameters parameters;
				
				State state;
			
				std::string name;

				Fitness fitness;

				std::vector<base::Cloneable<Solution> > solutions;
				base::Cloneable<Solution> best;

				size_t iteration;

				/* Default settings */
				size_t maxIterations;
				size_t populationSize;
				unsigned int seed;
				
				// Setter function for seed property			
				void setSeed(unsigned int const &seed);
			};
		
			Data *d_data;

			void setup(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness);

			void initializeFitnessTable();
			std::string normalizeFitnessName(std::string const &name);
	};
	
	template <typename T>
	inline Optimizer::Logger &Optimizer::Logger::operator<<(T t)
	{
		d_stream << t;
		return *this;
	}
	
	template <>
	inline Optimizer::Logger &Optimizer::Logger::operator<<(Optimizer::Logger::End t)
	{
		d_optimizer->log(d_logType, d_stream.str());
		return *this;
	}
	
	inline Optimizer::Logger::Logger(Optimizer *optimizer, base::Enum<LogType> const &logType)
	:
		d_logType(logType),
		d_optimizer(optimizer)
	{
	}
	
	inline Optimizer::Logger::Logger(Optimizer::Logger const &other)
	:
		d_logType(other.d_logType),
		d_optimizer(other.d_optimizer)
	{
	}
	
	inline std::string const &Optimizer::name() const
	{
		return d_data->name;
	}
	
	inline void Optimizer::setName(std::string const &name)
	{
		d_data->name = name;
	}

	inline Boundaries &Optimizer::boundaries()
	{
		return d_data->boundaries;
	}

	inline Boundaries const &Optimizer::boundaries() const
	{
		return d_data->boundaries;
	}
	
	inline Parameters &Optimizer::parameters()
	{
		return d_data->parameters;
	}

	inline Parameters const &Optimizer::parameters() const
	{
		return d_data->parameters;
	}

	inline Settings &Optimizer::settings()
	{
		return d_data->state.settings;
	}
		
	inline Settings const &Optimizer::settings() const
	{
		return d_data->state.settings;
	}
	
	inline Fitness &Optimizer::fitness()
	{
		return d_data->fitness;
	}
	
	inline Fitness const &Optimizer::fitness() const
	{
		return d_data->fitness;
	}
	
	inline State &Optimizer::state()
	{
		return d_data->state;
	}
	
	inline State const &Optimizer::state() const
	{
		return d_data->state;
	}
	
	inline std::vector<base::Cloneable<Solution> > &Optimizer::solutions()
	{
		return d_data->solutions;
	}
	
	inline std::vector<base::Cloneable<Solution> > const &Optimizer::solutions() const
	{
		return d_data->solutions;
	}
	
	inline size_t Optimizer::currentIteration() const
	{
		return d_data->iteration;
	}
}

#endif /* __OPTIMIZATION_OPTIMIZER_H__ */

