#include <vector>
#include <sstream>
#include <golite/identifier.h>
#include <golite/expression.h>
#include <golite/function_param.h>

namespace golite {
    class Pretty {
    public:
        /**
         * Join identifiers with a comma
         * @param identifiers
         * @return string
         */
        inline static std::string implodeIdentifiers(const std::vector<golite::Identifier*> &identifiers){
            std::stringstream ss;
            for(size_t i = 0; i < identifiers.size(); i++) {
                if(i != 0) {
                    ss << ", ";
                }
                ss << identifiers[i]->toGoLite(0);
            }
            return ss.str();
        }

        /**
         * Join expressions with a comma
         * @param expressions
         * @return string
         */
        inline static std::string implodeExpressions(const std::vector<golite::Expression*> &expressions){
            std::stringstream ss;
            for(size_t i = 0; i < expressions.size(); i++) {
                if(i != 0) {
                    ss << ", ";
                }
                ss << expressions[i]->toGoLite(0);
            }
            return ss.str();
        }

        /**
         * Join function params with a comma
         * @param expressions
         * @return string
         */
        inline static std::string implodeParams(const std::vector<golite::FunctionParam*> &params){
            std::stringstream ss;
            for(size_t i = 0; i < params.size(); i++) {
                if(i != 0) {
                    ss << ", ";
                }
                ss << params[i]->toGoLite(0);
            }
            return ss.str();
        }
    };
}