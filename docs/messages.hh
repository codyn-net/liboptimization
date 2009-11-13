namespace optimization::messages::task
{
/**
 * @class Communication
 * @brief Main communication message.
 *
 * The communication message is a container for all the messages send between
 * the optimizer, master and worker. It's a simple message which contains a 
 * type, indicating what message it contains, and for each possible type
 * an optional nested message.
 *
 */

/**
 * @fn bool Communication::has_type() const
 * @brief Whether the type field has been set.
 *
 * Get whether the type field has been set.
 *
 * @return: true if the type field is set, false otherwise
 *
 */

/**
 * @fn void Communication::clear_type()
 * @brief Clear the type field.
 *
 * Clears the type field.
 *
 */

/**
 * @fn void Communication::set_type(::optimization::messages::task::Communication_Type value)
 * @brief Set the communication type.
 * @param value the communication type
 *
 * Set the communication type. This type corresponds to the message which
 * should be set in the subsequent fields.
 *
 */

/**
 * @fn Communication_Type Communication::type() const
 * @brief Get the communication type.
 *
 * Get the communication type.
 *
 * @return: the communication type
 *
 */

/**
 * @fn bool Communication::has_batch() const
 * @brief Get whether the batch field has been set.
 *
 * Get whether the batch field has been set.
 *
 * @return whether the batch field has been set
 *
 */

/**
 * @fn void Communication::clear_batch()
 * @brief Clear the batch field.
 *
 * Clear the batch field.
 *
 */

/**
 * @fn Batch &Communication::batch() const
 * @brief Get the batch field.
 *
 * Get the batch field.
 *
 * @return the value of the batch field
 *
 */

/**
 * @fn Batch *Communication::mutable_batch()
 * @brief Get the mutable batch field value.
 *
 * Get the mutable batch field value.
 *
 * @return the mutable batch field value
 *
 */

/**
 * @fn bool Communication::has_task() const
 * @brief Get whether the task field has been set.
 *
 * Get whether the task field has been set.
 *
 * @return whether the task field has been set
 *
 */

/**
 * @fn void Communication::clear_task()
 * @brief Clear the task field.
 *
 * Clear the task field.
 *
 */

/**
 * @fn Task &Communication::task() const
 * @brief Get the task field.
 *
 * Get the task field.
 *
 * @return the value of the task field
 *
 */

/**
 * @fn Task *Communication::mutable_task()
 * @brief Get the mutable task field value.
 *
 * Get the mutable task field value.
 *
 * @return the mutable task field value
 *
 */

/**
 * @fn bool Communication::has_response() const
 * @brief Get whether the response field has been set.
 *
 * Get whether the response field has been set.
 *
 * @return whether the response field has been set
 *
 */

/**
 * @fn void Communication::clear_response()
 * @brief Clear the response field.
 *
 * Clear the response field.
 *
 */

/**
 * @fn Response &Communication::response() const
 * @brief Get the response field.
 *
 * Get the response field.
 *
 * @return the value of the response field
 *
 */

/**
 * @fn Response *Communication::mutable_response()
 * @brief Get the mutable response field value.
 *
 * Get the mutable response field value.
 *
 * @return the mutable response field value
 *
 */

/**
 * @fn bool Communication::has_token() const
 * @brief Get whether the token field has been set.
 *
 * Get whether the token field has been set.
 *
 * @return whether the token field has been set
 *
 */

/**
 * @fn void Communication::clear_token()
 * @brief Clear the token field.
 *
 * Clear the token field.
 *
 */

/**
 * @fn Token &Communication::token() const
 * @brief Get the token field.
 *
 * Get the token field.
 *
 * @return the value of the token field
 *
 */

/**
 * @fn Token *Communication::mutable_token()
 * @brief Get the mutable token field value.
 *
 * Get the mutable token field value.
 *
 * @return the mutable token field value
 *
 */

/**
 * @fn bool Communication::has_cancel() const
 * @brief Get whether the cancel field has been set.
 *
 * Get whether the cancel field has been set.
 *
 * @return whether the cancel field has been set
 *
 */

/**
 * @fn void Communication::clear_cancel()
 * @brief Clear the cancel field.
 *
 * Clear the cancel field.
 *
 */

/**
 * @fn Cancel &Communication::cancel() const
 * @brief Get the cancel field.
 *
 * Get the cancel field.
 *
 * @return the value of the cancel field
 *
 */

/**
 * @fn Cancel *Communication::mutable_cancel()
 * @brief Get the mutable cancel field value.
 *
 * Get the mutable cancel field value.
 *
 * @return the mutable cancel field value
 *
 */


/**
 * @class optimization::messages::task::Batch
 * @brief The task batch message.
 *
 * This message describes a batch of tasks, usually communicated from an
 * optimizer process to the master prococess. The master process will queue
 * the tasks and start executing them, relaying the responses back to the
 * optimizer using the Response message.
 *
 */

/**
 * @fn bool Batch::has_priority() const
 * @brief Get whether the priority field has been set.
 *
 * Get whether the priority field has been set.
 *
 * @return whether the priority field has been set
 *
 */

/**
 * @fn void Batch::clear_priority()
 * @brief Clears the priority field.
 *
 * Clears the priority field.
 *
 */

/**
 * @fn void Batch::set_priority(double value)
 * @brief Set the priority field.
 * @param priority the field value
 *
 * Set the value of the priority field.
 *
 */

/**
 * @fn double Batch::priority() const
 * @brief Get the priority field.
 *
 * Get the priority field.
 *
 * @return the value of the priority field
 *
 */

/**
 * @fn bool Batch::has_timeout() const
 * @brief Get whether the timeout field has been set.
 *
 * Get whether the timeout field has been set.
 *
 * @return whether the timeout field has been set
 *
 */

/**
 * @fn void Batch::clear_timeout()
 * @brief Clears the timeout field.
 *
 * Clears the timeout field.
 *
 */

/**
 * @fn void Batch::set_timeout(double value)
 * @brief Set the timeout field.
 * @param timeout the field value
 *
 * Set the value of the timeout field.
 *
 */

/**
 * @fn double Batch::timeout() const
 * @brief Get the timeout field.
 *
 * Get the timeout field.
 *
 * @return the value of the timeout field
 *
 */
 
/**
 * @fn int Batch::tasks_size() const
 * @brief Get the number of items in the tasks field list.
 *
 * Get the number of items in the tasks field list.
 *
 * @return the number of items in the tasks field list
 *
 */

/**
 * @fn void Batch::clear_tasks()
 * @brief Clears the tasks field.
 *
 * Clears the tasks field.
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Task> &Batch::tasks() const
 * @brief Get the tasks field list.
 *
 * Get the tasks field list.
 *
 * @return the tasks field list
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Task> *Batch::mutable_tasks()
 * @brief Get the mutable tasks field list.
 *
 * Get the mutable tasks field list.
 *
 * @return the mutable tasks field list
 *
 */

/**
 * @fn Task &Batch::tasks(int index) const
 * @brief Get an item from the tasks field list.
 * @param index the item index
 *
 * Get a specific item from the tasks field list.
 *
 * @return the tasks item
 *
 */

/**
 * @fn Task *Batch::mutable_tasks(int index)
 * @brief Get a mutable item from the tasks field list.
 * @param index the item index
 *
 * Get a specific mutable item from the tasks field list.
 *
 * @return the mutable tasks item
 *
 */

/**
 * @fn Task *Batch::add_tasks()
 * @brief Add a new tasks item to the list.
 *
 * Add a new tasks item to the list.
 *
 * @return the newly added tasks item
 *
 */

/**
 * @class Task
 * @brief Single task message.
 *
 * The task message is a full description of a single task, as to be carried
 * out by a worker/dispatcher. It describes the task id, which dispatcher to
 * use, and the general task description (see Task_Description).
 *
 */

/**
 * @fn bool Task::has_id() const
 * @brief Get whether the id field has been set.
 *
 * Get whether the id field has been set.
 *
 * @return whether the id field has been set
 *
 */

/**
 * @fn void Task::clear_id()
 * @brief Clears the id field.
 *
 * Clears the id field.
 *
 */

/**
 * @fn void Task::set_id(::google::protobuf::uint32 value)
 * @brief Set the id field.
 * @param value the field value
 *
 * Set the value of the id field.
 *
 */

/**
 * @fn ::google::protobuf::uint32 Task::id() const
 * @brief Get the id field.
 *
 * Get the id field.
 *
 * @return the value of the id field
 *
 */

/**
 * @fn bool Task::has_dispatcher() const
 * @brief Get whether the dispatcher field has been set.
 *
 * Get whether the dispatcher field has been set.
 *
 * @return whether the dispatcher field has been set
 *
 */

/**
 * @fn void Task::clear_dispatcher()
 * @brief Clears the dispatcher field.
 *
 * Clears the dispatcher field.
 *
 */

/**
 * @fn void Task::set_dispatcher(const ::std::string &value)
 * @brief Set the dispatcher field.
 * @param dispatcher the field value
 *
 * Set the value of the dispatcher field.
 *
 */

/**
 * @fn void Task::set_dispatcher(const char *value)
 * @brief Set the dispatcher field.
 * @param dispatcher the field value
 *
 * Set the value of the dispatcher field.
 *
 */


/**
 * @fn const ::std::string &Task::dispatcher() const
 * @brief Get the dispatcher field.
 *
 * Get the dispatcher field.
 *
 * @return the value of the dispatcher field
 *
 */

/**
 * @fn ::std::string *Task::mutable_dispatcher()
 * @brief Get the mutable dispatcher field.
 *
 * Get the mutable dispatcher field.
 *
 * @return the mutable value of the dispatcher field
 *
 */

/**
 * @fn bool Task::has_description() const
 * @brief Get whether the description field has been set.
 *
 * Get whether the description field has been set.
 *
 * @return whether the description field has been set
 *
 */

/**
 * @fn void Task::clear_description()
 * @brief Clear the description field.
 *
 * Clear the description field.
 *
 */

/**
 * @fn Task_Description &Task::description() const
 * @brief Get the description field.
 *
 * Get the description field.
 *
 * @return the value of the description field
 *
 */

/**
 * @fn Task_Description *Task::mutable_description()
 * @brief Get the mutable description field value.
 *
 * Get the mutable description field value.
 *
 * @return the mutable description field value
 *
 */

/**
 * @class Task_Description
 * @brief Main task description message.
 *
 * The task description message describes the actual task that is caried out.
 * This message is contained within a Task message which is send to the worker
 * process. The worker then sends the Task_Description message to the 
 * dispatcher.
 *
 */

/**
 * @fn bool Task_Description::has_job() const
 * @brief Get whether the job field has been set.
 *
 * Get whether the job field has been set.
 *
 * @return whether the job field has been set
 *
 */

/**
 * @fn void Task_Description::clear_job()
 * @brief Clears the job field.
 *
 * Clears the job field.
 *
 */

/**
 * @fn void Task_Description::set_job(const ::std::string &value)
 * @brief Set the job field.
 * @param job the field value
 *
 * Set the value of the job field.
 *
 */

/**
 * @fn void Task_Description::set_job(const char *value)
 * @brief Set the job field.
 * @param job the field value
 *
 * Set the value of the job field.
 *
 */

/**
 * @fn const ::std::string &Task_Description::job() const
 * @brief Get the job field.
 *
 * Get the job field.
 *
 * @return the value of the job field
 *
 */

/**
 * @fn ::std::string *Task_Description::job()
 * @brief Get the mutable job field.
 *
 * Get the mutable job field.
 *
 * @return the mutable value of the job field
 *
 */

/**
 * @fn bool Task_Description::has_optimizer() const
 * @brief Get whether the optimizer field has been set.
 *
 * Get whether the optimizer field has been set.
 *
 * @return whether the optimizer field has been set
 *
 */

/**
 * @fn void Task_Description::clear_optimizer()
 * @brief Clears the optimizer field.
 *
 * Clears the optimizer field.
 *
 */

/**
 * @fn void Task_Description::set_optimizer(const ::std::string &value)
 * @brief Set the optimizer field.
 * @param optimizer the field value
 *
 * Set the value of the optimizer field.
 *
 */

/**
 * @fn void Task_Description::set_optimizer(const char *value)
 * @brief Set the optimizer field.
 * @param optimizer the field value
 *
 * Set the value of the optimizer field.
 *
 */

/**
 * @fn const ::std::string &Task_Description::optimizer() const
 * @brief Get the optimizer field.
 *
 * Get the optimizer field.
 *
 * @return the value of the optimizer field
 *
 */

/**
 * @fn ::std::string *Task_Description::optimizer()
 * @brief Get the mutable optimizer field.
 *
 * Get the mutable optimizer field.
 *
 * @return the mutable value of the optimizer field
 *
 */

/**
 * @fn int Task_Description::parameters_size() const
 * @brief Get the number of items in the parameters field list.
 *
 * Get the number of items in the parameters field list.
 *
 * @return the number of items in the parameters field list
 *
 */

/**
 * @fn void Task_Description::clear_parameters()
 * @brief Clears the parameters field.
 *
 * Clears the parameters field.
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Task_Description_Parameter> &Task_Description::parameters() const
 * @brief Get the parameters field list.
 *
 * Get the parameters field list.
 *
 * @return the parameters field list
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Task_Description_Parameter> *Task_Description::mutable_parameters()
 * @brief Get the mutable parameters field list.
 *
 * Get the mutable parameters field list.
 *
 * @return the mutable parameters field list
 *
 */

/**
 * @fn Task_Description_Parameter &Task_Description::parameters(int index) const
 * @brief Get an item from the parameters field list.
 * @param index the item index
 *
 * Get a specific item from the parameters field list.
 *
 * @return the parameters item
 *
 */

/**
 * @fn Task_Description_Parameter *Task_Description::mutable_parameters(int index)
 * @brief Get a mutable item from the parameters field list.
 * @param index the item index
 *
 * Get a specific mutable item from the parameters field list.
 *
 * @return the mutable parameters item
 *
 */

/**
 * @fn Task_Description_Parameter *Task_Description::add_parameters()
 * @brief Add a new parameters item to the list.
 *
 * Add a new parameters item to the list.
 *
 * @return the newly added parameters item
 *
 */

/**
 * @fn int Task_Description::settings_size() const
 * @brief Get the number of items in the settings field list.
 *
 * Get the number of items in the settings field list.
 *
 * @return the number of items in the settings field list
 *
 */

/**
 * @fn void Task_Description::clear_settings()
 * @brief Clears the settings field.
 *
 * Clears the settings field.
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Task_Description_KeyValue> &Task_Description::settings() const
 * @brief Get the settings field list.
 *
 * Get the settings field list.
 *
 * @return the settings field list
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Task_Description_KeyValue> *Task_Description::mutable_settings()
 * @brief Get the mutable settings field list.
 *
 * Get the mutable settings field list.
 *
 * @return the mutable settings field list
 *
 */

/**
 * @fn Task_Description_KeyValue &Task_Description::settings(int index) const
 * @brief Get an item from the settings field list.
 * @param index the item index
 *
 * Get a specific item from the settings field list.
 *
 * @return the settings item
 *
 */

/**
 * @fn Task_Description_KeyValue *Task_Description::mutable_settings(int index)
 * @brief Get a mutable item from the settings field list.
 * @param index the item index
 *
 * Get a specific mutable item from the settings field list.
 *
 * @return the mutable settings item
 *
 */

/**
 * @fn Task_Description_KeyValue *Task_Description::add_settings()
 * @brief Add a new settings item to the list.
 *
 * Add a new settings item to the list.
 *
 * @return the newly added settings item
 *
 */

/**
 * @class Task_Description_Parameter
 * @brief A task parameter message.
 *
 * Describes a single parameter in the task.
 *
 */

/**
 * @fn bool Task_Description_Parameter::has_name() const
 * @brief Get whether the name field has been set.
 *
 * Get whether the name field has been set.
 *
 * @return whether the name field has been set
 *
 */

/**
 * @fn void Task_Description_Parameter::clear_name()
 * @brief Clears the name field.
 *
 * Clears the name field.
 *
 */

/**
 * @fn void Task_Description_Parameter::set_name(const ::std::string &value)
 * @brief Set the name field.
 * @param name the field value
 *
 * Set the value of the name field.
 *
 */

/**
 * @fn void Task_Description_Parameter::set_name(const char *value)
 * @brief Set the name field.
 * @param name the field value
 *
 * Set the value of the name field.
 *
 */

/**
 * @fn const ::std::string &Task_Description_Parameter::name() const
 * @brief Get the name field.
 *
 * Get the name field.
 *
 * @return the value of the name field
 *
 */

/**
 * @fn ::std::string *Task_Description_Parameter::name()
 * @brief Get the mutable name field.
 *
 * Get the mutable name field.
 *
 * @return the mutable value of the name field
 *
 */

/**
 * @fn bool Task_Description_Parameter::has_value() const
 * @brief Get whether the value field has been set.
 *
 * Get whether the value field has been set.
 *
 * @return whether the value field has been set
 *
 */

/**
 * @fn void Task_Description_Parameter::clear_value()
 * @brief Clears the value field.
 *
 * Clears the value field.
 *
 */

/**
 * @fn void Task_Description_Parameter::set_value(double value)
 * @brief Set the value field.
 * @param value the field value
 *
 * Set the value of the value field.
 *
 */

/**
 * @fn double Task_Description_Parameter::value() const
 * @brief Get the value field.
 *
 * Get the value field.
 *
 * @return the value of the value field
 *
 */

/**
 * @fn bool Task_Description_Parameter::has_min() const
 * @brief Get whether the min field has been set.
 *
 * Get whether the min field has been set.
 *
 * @return whether the min field has been set
 *
 */

/**
 * @fn void Task_Description_Parameter::clear_min()
 * @brief Clears the min field.
 *
 * Clears the min field.
 *
 */

/**
 * @fn void Task_Description_Parameter::set_min(double value)
 * @brief Set the min field.
 * @param min the field value
 *
 * Set the value of the min field.
 *
 */

/**
 * @fn double Task_Description_Parameter::min() const
 * @brief Get the min field.
 *
 * Get the min field.
 *
 * @return the value of the min field
 *
 */

/**
 * @fn bool Task_Description_Parameter::has_max() const
 * @brief Get whether the max field has been set.
 *
 * Get whether the max field has been set.
 *
 * @return whether the max field has been set
 *
 */

/**
 * @fn void Task_Description_Parameter::clear_max()
 * @brief Clears the max field.
 *
 * Clears the max field.
 *
 */

/**
 * @fn void Task_Description_Parameter::set_max(double value)
 * @brief Set the max field.
 * @param max the field value
 *
 * Set the value of the max field.
 *
 */

/**
 * @fn double Task_Description_Parameter::max() const
 * @brief Get the max field.
 *
 * Get the max field.
 *
 * @return the value of the max field
 *
 */

/**
 * @class Task_Description_KeyValue
 * @brief A simple Key/Value message.
 *
 * Describes a key/value pair used to make up a dictionary.
 *
 */

/**
 * @fn bool Task_Description_KeyValue::has_key() const
 * @brief Get whether the key field has been set.
 *
 * Get whether the key field has been set.
 *
 * @return whether the key field has been set
 *
 */

/**
 * @fn void Task_Description_KeyValue::clear_key()
 * @brief Clears the key field.
 *
 * Clears the key field.
 *
 */

/**
 * @fn void Task_Description_KeyValue::set_key(const ::std::string &value)
 * @brief Set the key field.
 * @param key the field value
 *
 * Set the value of the key field.
 *
 */

/**
 * @fn void Task_Description_KeyValue::set_key(const char *value)
 * @brief Set the key field.
 * @param key the field value
 *
 * Set the value of the key field.
 *
 */

/**
 * @fn const ::std::string &Task_Description_KeyValue::key() const
 * @brief Get the key field.
 *
 * Get the key field.
 *
 * @return the value of the key field
 *
 */

/**
 * @fn ::std::string *Task_Description_KeyValue::key()
 * @brief Get the mutable key field.
 *
 * Get the mutable key field.
 *
 * @return the mutable value of the key field
 *
 */

/**
 * @fn bool Task_Description_KeyValue::has_value() const
 * @brief Get whether the value field has been set.
 *
 * Get whether the value field has been set.
 *
 * @return whether the value field has been set
 *
 */

/**
 * @fn void Task_Description_KeyValue::clear_value()
 * @brief Clears the value field.
 *
 * Clears the value field.
 *
 */

/**
 * @fn void Task_Description_KeyValue::set_value(const ::std::string &value)
 * @brief Set the value field.
 * @param value the field value
 *
 * Set the value of the value field.
 *
 */

/**
 * @fn void Task_Description_KeyValue::set_value(const char *value)
 * @brief Set the value field.
 * @param value the field value
 *
 * Set the value of the value field.
 *
 */

/**
 * @fn const ::std::string &Task_Description_KeyValue::value() const
 * @brief Get the value field.
 *
 * Get the value field.
 *
 * @return the value of the value field
 *
 */

/**
 * @fn ::std::string *Task_Description_KeyValue::value()
 * @brief Get the mutable value field.
 *
 * Get the mutable value field.
 *
 * @return the mutable value of the value field
 *
 */


/**
 * @class Response
 * @brief A optimization response message.
 *
 * The response message is contains the response to a previous task message.
 * It contains the status of the evaluated task, and if this the task could
 * be evaluated successfully, it contains a pair of fitness values.
 *
 */

/**
 * @fn bool Response::has_id() const
 * @brief Get whether the id field has been set.
 *
 * Get whether the id field has been set.
 *
 * @return whether the id field has been set
 *
 */

/**
 * @fn void Response::clear_id()
 * @brief Clears the id field.
 *
 * Clears the id field.
 *
 */

/**
 * @fn void Response::set_id(::google::protobuf::uint32 value)
 * @brief Set the id field.
 * @param value the field value
 *
 * Set the value of the id field.
 *
 */

/**
 * @fn ::google::protobuf::uint32 Response::id() const
 * @brief Get the id field.
 *
 * Get the id field.
 *
 * @return the value of the id field
 *
 */

/**
 * @fn bool Response::has_status() const
 * @brief Get whether the status field has been set.
 *
 * Get whether the status field has been set.
 *
 * @return whether the status field has been set
 *
 */

/**
 * @fn void Response::clear_status()
 * @brief Clears the status field.
 *
 * Clears the status field.
 *
 */

/**
 * @fn void Response::set_status(Response_Status value)
 * @brief Set the status field.
 * @param status the field value
 *
 * Set the value of the status field.
 *
 */

/**
 * @fn Response_Status Response::status() const
 * @brief Get the status field.
 *
 * Get the status field.
 *
 * @return the value of the status field
 *
 */

/**
 * @fn int Response::fitness_size() const
 * @brief Get the number of items in the fitness field list.
 *
 * Get the number of items in the fitness field list.
 *
 * @return the number of items in the fitness field list
 *
 */

/**
 * @fn void Response::clear_fitness()
 * @brief Clears the fitness field.
 *
 * Clears the fitness field.
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Response_Fitness> &Response::fitness() const
 * @brief Get the fitness field list.
 *
 * Get the fitness field list.
 *
 * @return the fitness field list
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Response_Fitness> *Response::mutable_fitness()
 * @brief Get the mutable fitness field list.
 *
 * Get the mutable fitness field list.
 *
 * @return the mutable fitness field list
 *
 */

/**
 * @fn Response_Fitness &Response::fitness(int index) const
 * @brief Get an item from the fitness field list.
 * @param index the item index
 *
 * Get a specific item from the fitness field list.
 *
 * @return the fitness item
 *
 */

/**
 * @fn Response_Fitness *Response::mutable_fitness(int index)
 * @brief Get a mutable item from the fitness field list.
 * @param index the item index
 *
 * Get a specific mutable item from the fitness field list.
 *
 * @return the mutable fitness item
 *
 */

/**
 * @fn Response_Fitness *Response::add_fitness()
 * @brief Add a new fitness item to the list.
 *
 * Add a new fitness item to the list.
 *
 * @return the newly added fitness item
 *
 */

/**
 * @fn bool Response::has_challenge() const
 * @brief Get whether the challenge field has been set.
 *
 * Get whether the challenge field has been set.
 *
 * @return whether the challenge field has been set
 *
 */

/**
 * @fn void Response::clear_challenge()
 * @brief Clears the challenge field.
 *
 * Clears the challenge field.
 *
 */

/**
 * @fn void Response::set_challenge(const ::std::string &value)
 * @brief Set the challenge field.
 * @param challenge the field value
 *
 * Set the value of the challenge field.
 *
 */

/**
 * @fn void Response::set_challenge(const char *value)
 * @brief Set the challenge field.
 * @param challenge the field value
 *
 * Set the value of the challenge field.
 *
 */

/**
 * @fn const ::std::string &Response::challenge() const
 * @brief Get the challenge field.
 *
 * Get the challenge field.
 *
 * @return the value of the challenge field
 *
 */

/**
 * @fn ::std::string *Response::challenge()
 * @brief Get the mutable challenge field.
 *
 * Get the mutable challenge field.
 *
 * @return the mutable value of the challenge field
 *
 */

/**
 * @fn bool Response::has_failure() const
 * @brief Get whether the failure field has been set.
 *
 * Get whether the failure field has been set.
 *
 * @return whether the failure field has been set
 *
 */

/**
 * @fn void Response::clear_failure()
 * @brief Clears the failure field.
 *
 * Clears the failure field.
 *
 */

/**
 * @fn void Response::set_failure(Response_Failure value)
 * @brief Set the failure field.
 * @param failure the field value
 *
 * Set the value of the failure field.
 *
 */

/**
 * @fn Response_Failure Response::failure() const
 * @brief Get the failure field.
 *
 * Get the failure field.
 *
 * @return the value of the failure field
 *
 */

/**
 * @fn int Response::data_size() const
 * @brief Get the number of items in the data field list.
 *
 * Get the number of items in the data field list.
 *
 * @return the number of items in the data field list
 *
 */

/**
 * @fn void Response::clear_data()
 * @brief Clears the data field.
 *
 * Clears the data field.
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Response_KeyValue> &Response::data() const
 * @brief Get the data field list.
 *
 * Get the data field list.
 *
 * @return the data field list
 *
 */

/**
 * @fn google::protobuf::RepeatedPtrField<Response_KeyValue> *Response::mutable_data()
 * @brief Get the mutable data field list.
 *
 * Get the mutable data field list.
 *
 * @return the mutable data field list
 *
 */

/**
 * @fn Response_KeyValue &Response::data(int index) const
 * @brief Get an item from the data field list.
 * @param index the item index
 *
 * Get a specific item from the data field list.
 *
 * @return the data item
 *
 */

/**
 * @fn Response_KeyValue *Response::mutable_data(int index)
 * @brief Get a mutable item from the data field list.
 * @param index the item index
 *
 * Get a specific mutable item from the data field list.
 *
 * @return the mutable data item
 *
 */

/**
 * @fn Response_KeyValue *Response::add_data()
 * @brief Add a new data item to the list.
 *
 * Add a new data item to the list.
 *
 * @return the newly added data item
 *
 */

/**
 * @var Response::Success
 * @brief The task was successfully completed.
 */

/**
 * @var Response::Failed
 * @brief The task failed (see Response_Failure).
 */

/**
 * @var Response::Challenge
 * @brief The task is challenged for a token.
 */

/**
 * @class Response_Fitness
 * @brief A response fitness value.
 *
 * Represents a response fitness value which consists of a name and a value.
 *
 */

/**
 * @fn bool Response_Fitness::has_name() const
 * @brief Get whether the name field has been set.
 *
 * Get whether the name field has been set.
 *
 * @return whether the name field has been set
 *
 */

/**
 * @fn void Response_Fitness::clear_name()
 * @brief Clears the name field.
 *
 * Clears the name field.
 *
 */

/**
 * @fn void Response_Fitness::set_name(const ::std::string &value)
 * @brief Set the name field.
 * @param name the field value
 *
 * Set the value of the name field.
 *
 */

/**
 * @fn void Response_Fitness::set_name(const char *value)
 * @brief Set the name field.
 * @param name the field value
 *
 * Set the value of the name field.
 *
 */

/**
 * @fn const ::std::string &Response_Fitness::name() const
 * @brief Get the name field.
 *
 * Get the name field.
 *
 * @return the value of the name field
 *
 */

/**
 * @fn ::std::string *Response_Fitness::name()
 * @brief Get the mutable name field.
 *
 * Get the mutable name field.
 *
 * @return the mutable value of the name field
 *
 */

/**
 * @fn bool Response_Fitness::has_value() const
 * @brief Get whether the value field has been set.
 *
 * Get whether the value field has been set.
 *
 * @return whether the value field has been set
 *
 */

/**
 * @fn void Response_Fitness::clear_value()
 * @brief Clears the value field.
 *
 * Clears the value field.
 *
 */

/**
 * @fn void Response_Fitness::set_value(double value)
 * @brief Set the value field.
 * @param value the field value
 *
 * Set the value of the value field.
 *
 */

/**
 * @fn double Response_Fitness::value() const
 * @brief Get the value field.
 *
 * Get the value field.
 *
 * @return the value of the value field
 *
 */

/**
 * @class Response_KeyValue
 * @brief A simple key value pair.
 *
 * A simple string key value pair used in Response to make a data dictionary.
 *
 */

/**
 * @fn bool Response_KeyValue::has_name() const
 * @brief Get whether the name field has been set.
 *
 * Get whether the name field has been set.
 *
 * @return whether the name field has been set
 *
 */

/**
 * @fn void Response_KeyValue::clear_name()
 * @brief Clears the name field.
 *
 * Clears the name field.
 *
 */

/**
 * @fn void Response_KeyValue::set_name(const ::std::string &value)
 * @brief Set the name field.
 * @param name the field value
 *
 * Set the value of the name field.
 *
 */

/**
 * @fn void Response_KeyValue::set_name(const char *value)
 * @brief Set the nam field.
 * @param nam the field value
 *
 * Set the value of the nam field.
 *
 */

/**
 * @fn const ::std::string &Response_KeyValue::name() const
 * @brief Get the name field.
 *
 * Get the name field.
 *
 * @return the value of the name field
 *
 */

/**
 * @fn ::std::string *Response_KeyValue::name()
 * @brief Get the mutable nam field.
 *
 * Get the mutable nam field.
 *
 * @return the mutable value of the name field
 *
 */

/**
 * @fn bool Response_KeyValue::has_value() const
 * @brief Get whether the value field has been set.
 *
 * Get whether the value field has been set.
 *
 * @return whether the value field has been set
 *
 */

/**
 * @fn void Response_KeyValue::clear_value()
 * @brief Clears the value field.
 *
 * Clears the value field.
 *
 */

/**
 * @fn void Response_KeyValue::set_value(const ::std::string &value)
 * @brief Set the value field.
 * @param value the field value
 *
 * Set the value of the value field.
 *
 */

/**
 * @fn void Response_KeyValue::set_value(const char *value)
 * @brief Set the value field.
 * @param value the field value
 *
 * Set the value of the value field.
 *
 */

/**
 * @fn const ::std::string &Response_KeyValue::value() const
 * @brief Get the value field.
 *
 * Get the value field.
 *
 * @return the value of the value field
 *
 */

/**
 * @fn ::std::string *Response_KeyValue::value()
 * @brief Get the mutable value field.
 *
 * Get the mutable value field.
 *
 * @return the mutable value of the value field
 *
 */


/**
 * @class Token
 * @brief The token message.
 *
 * A token message is send from the optimizer all the way to the dispatcher
 * (which is the optirooter application in case tokens are used) in response
 * to a previous challenge Response.
 *
 */

/**
 * @fn bool Token::has_id() const
 * @brief Get whether the id field has been set.
 *
 * Get whether the id field has been set.
 *
 * @return whether the id field has been set
 *
 */

/**
 * @fn void Token::clear_id()
 * @brief Clears the id field.
 *
 * Clears the id field.
 *
 */

/**
 * @fn void Token::set_id(::google::protobuf::uint32 value)
 * @brief Set the id field.
 * @param value the field value
 *
 * Set the value of the id field.
 *
 */

/**
 * @fn ::google::protobuf::uint32 Token::id() const
 * @brief Get the id field.
 *
 * Get the id field.
 *
 * @return the value of the id field
 *
 */

/**
 * @fn bool Token::has_response() const
 * @brief Get whether the response field has been set.
 *
 * Get whether the response field has been set.
 *
 * @return whether the response field has been set
 *
 */

/**
 * @fn void Token::clear_response()
 * @brief Clears the response field.
 *
 * Clears the response field.
 *
 */

/**
 * @fn void Token::set_response(const ::std::string &value)
 * @brief Set the response field.
 * @param response the field value
 *
 * Set the value of the response field.
 *
 */

/**
 * @fn void Token::set_response(const char *value)
 * @brief Set the response field.
 * @param response the field value
 *
 * Set the value of the response field.
 *
 */

/**
 * @fn const ::std::string &Token::response() const
 * @brief Get the response field.
 *
 * Get the response field.
 *
 * @return the value of the response field
 *
 */

/**
 * @fn ::std::string *Token::response()
 * @brief Get the mutable response field.
 *
 * Get the mutable response field.
 *
 * @return the mutable value of the response field
 *
 */

/**
 * @class Cancel
 * @brief The cancel message.
 *
 * A cancel message is usually send from the master to the worker to indicate
 * that the currently running task on the worker should be cancelled. This can
 * happen for instance when an optimizer is suddenly disconnected.
 *
 */

/**
 * @fn bool Cancel::has_id() const
 * @brief Get whether the id field has been set.
 *
 * Get whether the id field has been set.
 *
 * @return whether the id field has been set
 *
 */

/**
 * @fn void Cancel::clear_id()
 * @brief Clears the id field.
 *
 * Clears the id field.
 *
 */

/**
 * @fn void Cancel::set_id(::google::protobuf::uint32 value)
 * @brief Set the id field.
 * @param value the field value
 *
 * Set the value of the id field.
 *
 */

/**
 * @fn ::google::protobuf::uint32 Cancel::id() const
 * @brief Get the id field.
 *
 * Get the id field.
 *
 * @return the value of the id field
 *
 */

/**
 * @class Response_Failure
 * @brief The response failure message.
 *
 * This message is set in Response when the response status is set to Failed.
 * It describes in more detail what kind of failure occurred while trying to
 * execute the task.
 *
 */

/**
 * @fn bool Response_Failure::has_type() const
 * @brief Get whether the type field has been set.
 *
 * Get whether the type field has been set.
 *
 * @return whether the type field has been set
 *
 */

/**
 * @fn void Response_Failure::clear_type()
 * @brief Clears the type field.
 *
 * Clears the type field.
 *
 */

/**
 * @fn void Response_Failure::set_type(::optimization::messages::task::Response_Failure_Type value)
 * @brief Set the type field.
 * @param value the field value
 *
 * Set the value of the type field.
 *
 */

/**
 * @fn ::optimization::messages::task::Response_Failure_Type Response_Failure::type() const
 * @brief Get the type field.
 *
 * Get the type field.
 *
 * @return the value of the type field
 *
 */

/**
 * @fn bool Response_Failure::has_message() const
 * @brief Get whether the message field has been set.
 *
 * Get whether the message field has been set.
 *
 * @return whether the message field has been set
 *
 */

/**
 * @fn void Response_Failure::clear_message()
 * @brief Clears the message field.
 *
 * Clears the message field.
 *
 */

/**
 * @fn void Response_Failure::set_message(const ::std::string &value)
 * @brief Set the message field.
 * @param message the field value
 *
 * Set the value of the message field.
 *
 */

/**
 * @fn void Response_Failure::set_message(const char *value)
 * @brief Set the message field.
 * @param message the field value
 *
 * Set the value of the message field.
 *
 */

/**
 * @fn const ::std::string &Response_Failure::message() const
 * @brief Get the message field.
 *
 * Get the message field.
 *
 * @return the value of the message field
 *
 */

/**
 * @fn ::std::string *Response_Failure::message()
 * @brief Get the mutable message field.
 *
 * Get the mutable message field.
 *
 * @return the mutable value of the message field
 *
 */

/**
 * @var Response_Failure::Timeout
 * @brief A timeout occurred.
 */

/**
 * @var Response_Failure::DispatcherNotFound
 * @brief The dispatcher could not be found.
 */

/**
 * @var Response_Failure::NoResponse
 * @brief No response was received from the dispatcher.
 */

/**
 * @var Response_Failure::Dispatcher
 * @brief An error occurred in the dispatcher.
 */

/**
 * @var Response_Failure::Unknown
 * @brief Unknown failure.
 */

/**
 * @var Response_Failure::WrongRequest
 * @brief The task request did not have the right format.
 */

/**
 * @var Response_Failure::Disconnected
 * @brief The worker was disconnected while running.
 */
}

namespace optimization::messages::discovery
{

/**
 * @class Wakeup
 * @brief Discovery wakeup message.
 *
 * The wakeup message is broadcasted from the master to request workers to send
 * Greeting messages. This is used to make workers announce themselves to 
 * master as quickly as possible when the master starts.
 *
 */

/**
 * @fn bool Wakeup::has_connection() const
 * @brief Get whether the connection field has been set.
 *
 * Get whether the connection field has been set.
 *
 * @return whether the connection field has been set
 *
 */

/**
 * @fn void Wakeup::clear_connection()
 * @brief Clears the connection field.
 *
 * Clears the connection field.
 *
 */

/**
 * @fn void Wakeup::set_connection(const ::std::string &value)
 * @brief Set the connection field.
 * @param connection the field value
 *
 * Set the value of the connection field.
 *
 */

/**
 * @fn void Wakeup::set_connection(const char *value)
 * @brief Set the connection field.
 * @param connection the field value
 *
 * Set the value of the connection field.
 *
 */

/**
 * @fn const ::std::string &Wakeup::connection() const
 * @brief Get the connection field.
 *
 * Get the connection field.
 *
 * @return the value of the connection field
 *
 */

/**
 * @fn ::std::string *Wakeup::connection()
 * @brief Get the mutable connection field.
 *
 * Get the mutable connection field.
 *
 * @return the mutable value of the connection field
 *
 */

/**
 * @class Greeting
 * @brief The discovery greeting message.
 *
 * The discovery greeting message is send from workers to the master to announce
 * themselves ready for work. This message is usually send periodically from
 * the worker, but also in response to receiving a Wakup message.
 *
 */

/**
 * @fn bool Greeting::has_connection() const
 * @brief Get whether the connection field has been set.
 *
 * Get whether the connection field has been set.
 *
 * @return whether the connection field has been set
 *
 */

/**
 * @fn void Greeting::clear_connection()
 * @brief Clears the connection field.
 *
 * Clears the connection field.
 *
 */

/**
 * @fn void Greeting::set_connection(const ::std::string &value)
 * @brief Set the connection field.
 * @param connection the field value
 *
 * Set the value of the connection field.
 *
 */

/**
 * @fn void Greeting::set_connection(const char *value)
 * @brief Set the connection field.
 * @param connection the field value
 *
 * Set the value of the connection field.
 *
 */

/**
 * @fn const ::std::string &Greeting::connection() const
 * @brief Get the connection field.
 *
 * Get the connection field.
 *
 * @return the value of the connection field
 *
 */

/**
 * @fn ::std::string *Greeting::connection()
 * @brief Get the mutable connection field.
 *
 * Get the mutable connection field.
 *
 * @return the mutable value of the connection field
 *
 */

/**
 * @class Discovery
 * @brief Discovery message container.
 *
 * Message container for discovery messages. It can either contain a Wakeup
 * or a Greeting message, depending on the type field.
 *
 */

/**
 * @fn bool Discovery::has_type() const
 * @brief Get whether the type field has been set.
 *
 * Get whether the type field has been set.
 *
 * @return whether the type field has been set
 *
 */

/**
 * @fn void Discovery::clear_type()
 * @brief Clears the type field.
 *
 * Clears the type field.
 *
 */

/**
 * @fn void Discovery::set_type(::optimization::messages::discovery::Discovery_Type value)
 * @brief Set the type field.
 * @param value the field value
 *
 * Set the value of the type field.
 *
 */

/**
 * @fn ::optimization::messages::discovery::Discovery_Type Discovery::type() const
 * @brief Get the type field.
 *
 * Get the type field.
 *
 * @return the value of the type field
 *
 */

/**
 * @fn bool Discovery::has_wakeup() const
 * @brief Get whether the wakeup field has been set.
 *
 * Get whether the wakeup field has been set.
 *
 * @return whether the wakeup field has been set
 *
 */

/**
 * @fn void Discovery::clear_wakeup()
 * @brief Clear the wakeup field.
 *
 * Clear the wakeup field.
 *
 */

/**
 * @fn Wakeup &Discovery::wakeup() const
 * @brief Get the wakeup field.
 *
 * Get the wakeup field.
 *
 * @return the value of the wakeup field
 *
 */

/**
 * @fn Wakeup *Discovery::mutable_wakeup()
 * @brief Get the mutable wakeup field value.
 *
 * Get the mutable wakeup field value.
 *
 * @return the mutable wakeup field value
 *
 */

/**
 * @fn bool Discovery::has_greeting() const
 * @brief Get whether the greeting field has been set.
 *
 * Get whether the greeting field has been set.
 *
 * @return whether the greeting field has been set
 *
 */

/**
 * @fn void Discovery::clear_greeting()
 * @brief Clear the greeting field.
 *
 * Clear the greeting field.
 *
 */

/**
 * @fn Greeting &Discovery::greeting() const
 * @brief Get the greeting field.
 *
 * Get the greeting field.
 *
 * @return the value of the greeting field
 *
 */

/**
 * @fn Greeting *Discovery::mutable_greeting()
 * @brief Get the mutable greeting field value.
 *
 * Get the mutable greeting field value.
 *
 * @return the mutable greeting field value
 *
 */

/**
 * @fn bool Discovery::has_namespace_() const
 * @brief Get whether the namespace field has been set.
 *
 * Get whether the namespace field has been set.
 *
 * @return whether the namespace field has been set
 *
 */

/**
 * @fn void Discovery::clear_namespace_()
 * @brief Clears the namespace field.
 *
 * Clears the namespace field.
 *
 */

/**
 * @fn void Discovery::set_namespace_(const ::std::string &value)
 * @brief Set the namespace field.
 * @param namespace the field value
 *
 * Set the value of the namespace field.
 *
 */

/**
 * @fn void Discovery::set_namespace_(const char *value)
 * @brief Set the namespace field.
 * @param namespace the field value
 *
 * Set the value of the namespace field.
 *
 */

/**
 * @fn const ::std::string &Discovery::namespace_() const
 * @brief Get the namespace field.
 *
 * Get the namespace field.
 *
 * @return the value of the namespace field
 *
 */

/**
 * @fn ::std::string *Discovery::namespace_()
 * @brief Get the mutable namespace field.
 *
 * Get the mutable namespace field.
 *
 * @return the mutable value of the namespace field
 *
 */

/**
 * @var Discovery::TypeGreeting
 * @brief Discovery message is of type Greeting
 */

/**
 * @var Discovery::TypeWakeup
 * @brief Discovery message is of type Wakeup
 */
}
