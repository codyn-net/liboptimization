/**
 * @mainpage
 *
 * liboptimization is a library with utitilities that are used throughout the
 * layers of the optimization framework. It provides classes which are used by
 * the master, worker and dispatcher processes.
 *
 * All communication in the optimization framework is done using google protobuf
 * messages. There are two namespaces related to messages send between the
 * different processes. The first is the optimization::messages::discovery
 * namespace, containing the messages optimization::messages::discovery::Wakeup
 * and optimization::messages::discovery::Greeting. A container message 
 * encapsulates these messages (optimization::messages::discovery::Discovery).
 * This is used by the worker and master to discover each other (see
 * optimization::Discovery).
 *
 * The second namespace is optimization::messages::task which contains all the
 * relevant messages for communication tasks between the processes. It defines
 * messages defining tasks (optimization::messages::task::Task, 
 * optimization::messages::task::Batch) and for sending responses 
 * (optimization::messages::task::Response).
 * All task communication goes through a container message 
 * (optimization::messages::task::Communication).
 *
 * A very small protocol is put on top of protobuf to define message boundaries
 * (as this is not handled by protobuf). Therefore, each messages has a
 * header containing a text representation of the length of the message,
 * followed by a single space, followed by the serialized protobuf message.
 *
 * optimization::Messages contains two convenient functions to serialize and
 * deserialize optimization messages (optimization::Messages::Create and
 * optimization::Messages::Extract).
 *
 * Besides these rather low level utilities, the library defines a Dispatcher
 * class which can be used as a convenient basis for implementing a dispatcher.
 * It abstracts receiving the task request (which is send on STDIN) and sending
 * a response back (on STDOUT).
 *
 * The library contains one more specialized class (optimization::Webots) which
 * is a singleton class that can be used in a webots controller in conjunction
 * with the webots dispatcher.
 *
 * NOTE: The generated documentation for the protobuf classes is a bit strange
 * with doxygen. Until a way is found to fix that, the nested protobuf classes
 * are indicated with <Base>_<Nested> (not the underscore). In your code the
 * prefered way of referring to this nested classes is <Base>::<Nested>.
 *
 */
