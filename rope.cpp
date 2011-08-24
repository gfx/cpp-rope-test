#include <cstdlib>
#include <string>
#include <deque>
#include <iostream>
#include <sstream>

#define BOOST_SP_DISABLE_THREADS 1
#include <boost/shared_ptr.hpp>

#include "./cpp-scoped_timer/scoped_timer.hpp"

namespace gfx {
    class rope {
        typedef boost::shared_ptr<const std::string> string_ptr;
        typedef std::deque< string_ptr > list_t;
        typedef list_t::const_iterator citer;

        list_t list_;

        public:
        rope() : list_() {
        }
        rope(const char* const cstr) : list_() {
            string_ptr s(new std::string(cstr));
            this->list_.push_back(s);
        }
        
        rope(const rope& r) : list_(r.list_) { }

        void append(const rope& r) {
            const citer end = r.list_.end();
            for(citer i = r.list_.begin(); i != end; ++i) {
                this->list_.push_back( *i );
            }
        }

        template <typename Stream>
        void put_to(Stream& o) const {
            const list_t& l = this->list_;
            const citer end = l.end();
            for(citer i = l.begin(); i != end; ++i) {
                o << **i;
            }
        }
    };

    std::ostream& operator<< (std::ostream& o, const rope& r) {
        r.put_to(o);
        return o;
    }
}

template <typename StringT>
void doit(const int n, StringT part) {
    StringT s;
    for(int i = 0; i < n; i++) {
        s.append(part);
    }


    if(true) {
        std::ostringstream buff;
        buff << s;
    }
}

int main() {
    gfx::rope s0("Hello, ");
    gfx::rope s1("world!");

    s0.append(s1);

    std::cout << s0 << std::endl;

    const char* const longstr
        = "01234567890123456789012345678901234567890123456789"; // 50b
    const char* const shortstr = "."; // 1b

    const int N = 2 * 1000 * 1000;
    gfx::scoped_timer_cputime::elapsed_type e;
    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "std::string (long)");
        doit<std::string>(N, longstr);
    }
    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "std::string (short)");
        doit<std::string>(N, shortstr);
    }

    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "gfx::rope (long)");
        doit<gfx::rope>(N, longstr);
    }
    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "gfx::rope (short)");
        doit<gfx::rope>(N, shortstr);
    }
    return 0;
}
