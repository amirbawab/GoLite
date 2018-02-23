#ifndef GOLITE_PRIMARY_COMPOSITE_H
#define GOLITE_PRIMARY_COMPOSITE_H

#include <vector>
#include <golite/primary.h>

namespace golite {
    class PrimaryComposite : public Primary {
    private:
        std::vector<Primary*> children_;
    public:

        /**
         * Add a child
         * @param child
         */
        void addChild(Primary* child);
    };
}

#endif