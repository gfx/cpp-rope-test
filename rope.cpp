#include <cstdlib>
#include <string>
#include <deque>
#include <iostream>
#include <sstream>

#include "./cpp-scoped_timer/scoped_timer.hpp"

namespace gfx {
    class rope {
        typedef std::deque< std::string > list_t;
        typedef list_t::const_iterator citer;

        list_t list_;

        public:
        rope() : list_() {
        }
        rope(const char* const cstr) : list_() {
            this->list_.push_back(std::string(cstr));
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
                o << *i;
            }
        }
        std::string join() const {
	  std::string r;
	  std::string::size_type len = 0;
	  for (list_t::const_iterator i = list_.begin(); i != list_.end(); ++i)
	    len += i->size();
	  r.reserve(len);
	  for (list_t::const_iterator i = list_.begin(); i != list_.end(); ++i)
	    r.append(*i);
	  return r;
        }
    };

}

template <typename T> std::string join_s(const T& s)
{
  return s;
}

template<> std::string join_s<gfx::rope>(const gfx::rope& s)
{
  return s.join();
}

const int N = 100 * 1000;
const int M = 1000;

template <typename StringT>
void doit(StringT part) {
    for(int i = 0; i < N; ++i) {
        StringT s;
        for(int i = 0; i < M; i++) {
            s.append(part);
        }

        if(true) {
            join_s(s);
        }
    }
}

int main() {
    gfx::rope s0("Hello, ");
    gfx::rope s1("world!");

    s0.append(s1);

    std::cout << join_s(s0) << std::endl;

    const char* const longstr // 100 bytes
        = "01234567890123456789012345678901234567890123456789"
          "01234567890123456789012345678901234567890123456789";
    const char* const shortstr = "."; // 1 bytes

    gfx::scoped_timer_cputime::elapsed_type e;
    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "std::string (long)");
        doit<std::string>(longstr);
    }
    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "std::string (short)");
        doit<std::string>(shortstr);
    }

    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "gfx::rope (long)");
        doit<gfx::rope>(longstr);
    }
    for(int i = 0; i < 2; i++){
        gfx::scoped_timer_cputime t(e, "gfx::rope (short)");
        doit<gfx::rope>(shortstr);
    }
    return 0;
}
