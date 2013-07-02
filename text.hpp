#if !defined (XML_TEXT_HPP)
#define XML_TEXT_HPP

#include "node.hpp"

namespace xml
{

template <typename T>
class basic_text : public basic_node<T>
{
public:

    basic_text(string_type const& t)
    : basic_node("", t)
    {
    }

    virtual ostream_type& output(ostream_type& stream) const
    {
        return stream << value();
    }
};

} // namespace xml

#endif // XML_TEXT_HPP