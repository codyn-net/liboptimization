#ifndef __OPTIMIZATION_OPTIMIZER_H__
#define __OPTIMIZATION_OPTIMIZER_H__

#include <base/Object/object.hh>
#include <base/Signals/Signal/signal.hh>
#include <math/math.hh>

#include <optimization/Boundaries/boundaries.hh>
#include <optimization/Parameters/parameters.hh>
#include <optimization/Settings/settings.hh>
#include <optimization/Solution/solution.hh>
#include <optimization/Fitness/fitness.hh>
#include <optimization/Messages/worker.pb.h>

#include <db/SQLite/sqlite.hh>

namespace optimization
{
	/** Basic optimizer abstract class
	 */
	class Optimizer : public base::Object
	{
		public:
			class Extension : public base::Object
			{
				struct Data : public base::Object::PrivateData
				{
					Optimizer *optimizer;
					Settings settings;
					std::string name;
		
					~Data();
				};
	
				Data *d_data;
	
				public:
					Extension();
		
					std::string const &name() const;
					void setName(std::string const &name);
		
					void setOptimizer(Optimizer const &optimizer);
					Optimizer &optimizer();
					Optimizer const &optimizer() const;

					Settings &settings();
					void set(Settings const &settings, std::string const &name);

					/* Interface functions */
					virtual Extension *clone() const;

					virtual void newSolution(Solution &solution);

					virtual void update(Solution &solution);
					virtual void update();
					
					virtual void save(Solution &solution);
					virtual void save();

					virtual bool done();

					virtual void customRequest(Solution &solution, messages::worker::Request &request);
					virtual void customResponse(Solution &solution, messages::worker::Response &response);
					virtual void initializeDatabase();
					
					virtual void clear();
				private:
					/* Private functions */
	
			};
			
			struct Module
			{
				struct Extension
				{
					typedef optimization::Optimizer::Extension type;
					typedef optimization::Optimizer::Extension *(*Constructor)();

					static std::string const loader;

					std::string name;

					Constructor constructor;
					typedef void (*Loader)(Extension *info);		
				};
				
				typedef Optimizer type;
				typedef Optimizer *(*Constructor)(void);

				static std::string const loader;

				std::string name;

				Constructor constructor;
				typedef void (*Loader)(Module *info);
			};

			Optimizer();
			Optimizer(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness);
			
			// Accessors
			Boundaries const &boundaries() const;
			Parameters const &parameters() const;
			Settings const &settings() const;
			Fitness const &fitness() const;

			Boundaries &boundaries();
			Parameters &parameters();
			Settings &settings();
			Fitness &fitness();
			math::Random &random();

			// Bes solution so far			
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
			
			// Extensions
			void addExtension(Extension &extension);
			Extension &getExtension(std::string const &name);
			Extension const &getExtension(std::string const &name) const;
			
			// Solutions
			std::vector<base::Cloneable<Solution> > &solutions();
			std::vector<base::Cloneable<Solution> > const &solutions() const;

			void setup(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness);

			// Reset
			void reset();
			void addSolution(Solution &solution);
			bool iteration();
			db::SQLite &db();
			
			// Virtual methods
			virtual Solution *createSolution(size_t id);
			virtual Optimizer *clone() const;
			
			// Custom request/response to add/process extensions
			virtual void customRequest(Solution &solution, messages::worker::Request &request);
			virtual void customResponse(Solution &solution, messages::worker::Response &response);
			
			virtual void clear();
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
				Settings settings;
			
				math::Random random;
			
				std::string name;

				base::Cloneable<Fitness> fitness;
				std::vector<base::Cloneable<Solution> > solutions;
				std::vector<base::Cloneable<Extension> > extensions;

				base::Cloneable<Solution> best;
			
				size_t iteration;

				/* Default settings */
				size_t maxIterations;
				size_t populationSize;
				size_t timeout;
				unsigned int seed;
			
				void setSeed(unsigned int const &seed);
				
				~Data();
			};
		
			Data *d_data;

			void initialize(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness);
	};
	
	inline std::string const &Optimizer::name() const
	{
		return d_data->name;
	}
	
	inline void Optimizer::setName(std::string const &name)
	{
		d_data->name = name;
	}

	inline Boundaries const &Optimizer::boundaries() const
	{
		return d_data->boundaries;
	}
	
	inline Parameters const &Optimizer::parameters() const
	{
		return d_data->parameters;
	}
	
	inline Settings const &Optimizer::settings() const
	{
		return d_data->settings;
	}
	
	inline Fitness const &Optimizer::fitness() const
	{
		return d_data->fitness;
	}
	
	inline Boundaries &Optimizer::boundaries()
	{
		return d_data->boundaries;
	}
	
	inline Parameters &Optimizer::parameters()
	{
		return d_data->parameters;
	}
	
	inline Settings &Optimizer::settings()
	{
		return d_data->settings;
	}
	
	inline Fitness &Optimizer::fitness()
	{
		return d_data->fitness;
	}
	
	inline math::Random &Optimizer::random()
	{
		return d_data->random;
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

