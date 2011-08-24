#include <cstdlib>
#include <string>
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>

namespace gfx {
    class rope {

        typedef boost::shared_ptr<std::string> string_ptr;
        typedef std::list< string_ptr > list_t;
        typedef list_t::const_iterator citer;

        list_t list_;

        public:
        rope(const char* const cstr) : list_() {
            string_ptr s(new std::string(cstr));
            this->list_.push_back(s);
        }
        
        rope(const rope& r) : list_(r.list_) { }

        template <typename Stream>
        void put_to(Stream& o) const {
            const citer end = this->list_.end();
            for(citer i = this->list_.begin(); i != end; i++) {
                o << **i;
            }
        }

        void append(const rope& r) {
            const citer end = r.list_.end();
            for(citer i = r.list_.begin(); i != end; i++) {
                this->list_.push_back( *i );
            }
        }
    };

    std::ostream& operator<< (std::ostream& o, const rope& r) {
        r.put_to(o);
        return o;
    }
}

int main() {
    gfx::rope s0("Hello, ");
    gfx::rope s1("world!");

    s0.append(s1);

    std::cout << s0 << std::endl;
    return 0;
}
