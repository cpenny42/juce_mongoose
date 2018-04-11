
/**
 * A session contains the user specific values
 */ 
namespace Mongoose
{
    class Session
    {
        public:
            Session();

            /**
             * Sets the value of a session variable
             *
             * @param std::string the name of the variable
             * @param std::string the value of the variable
             */
            void setValue(std::string key, std::string value);

            /**
             * Unset a session varaible
             *
             * @param std::string the variable name
             */
            void unsetValue(std::string key);

            /**
             * Check if the given variable exists
             *
             * @param std::string the name of the variable
             */
            bool hasValue(std::string key);

            /**
             * Try to get the value for the given variable
             *
             * @pram std::string the name of the variable
             * @param std::string the fallback value
             *
             * @return std::string the value of the variable if it exists, fallback else
             */
            std::string get(std::string key, std::string fallback = "");

            /**
             * Pings the session, this will update the creation date to now
             * and "keeping it alive"
             */
            void ping();

            /**
             * Returns the session age, in seconds
             *
             * @return int the number of sessions since the last activity of the session
             */
            int getAge();

        protected:
            std::map<std::string, std::string> values;
            int date;
            Mutex mutex;
    };
}

