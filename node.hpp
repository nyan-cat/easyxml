#if !defined (XML_NODE_HPP)
#define XML_NODE_HPP

#include <memory>
#include <string>
#include <vector>
#include "entity.hpp"

namespace xml
{

template <typename T>
class basic_node
{
public:

    typedef T char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_ostream<char_type> ostream_type;
    typedef std::shared_ptr<basic_node> pointer_type;
    typedef std::vector<pointer_type> container_type;
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
    typedef basic_entity<char_type> entity_type;

    template <typename I>
    class basic_range
    {
    public:

        typedef I iterator_type;

        basic_range(iterator_type first, iterator_type second)
        : first(first)
        , second(second)
        {
        }

        iterator_type begin() const
        {
            return first;
        }

        iterator_type end() const
        {
            return second;
        }

    private:

        iterator_type first;
        iterator_type second;
    };

    typedef basic_range<iterator> range;
    typedef basic_range<const_iterator> const_range;

    basic_node(string_type const& n, string_type const& v)
    : m_name(n)
    , m_value(v)
    {

    }

    virtual ~basic_node()
    {
    }

    virtual ostream_type& output(ostream_type& stream) const = 0;

    template <typename N>
    bool is() const
    {
        return dynamic_cast<N>(this);
    }

    string_type const& name() const
    {
        return m_name;
    }

    void name(string_type const& str)
    {
        m_name = str;
    }

    string_type const& value() const
    {
        return m_value;
    }

    void value(string_type const& str)
    {
        m_value = str;
    }

    const_range children() const
    {
        return const_range(m_children.cbegin(), m_children.cend());
    }

    range children()
    {
        return range(m_children.begin(), m_children.end());
    }

    void append(pointer_type n)
    {
        m_children.push_back(n);
    }

private:

    string_type m_name;
    string_type m_value;
    container_type m_children;
};

template <typename T>
std::basic_ostream<T>& operator << (std::basic_ostream<T>& stream, basic_node<T> const& n)
{
    return n.output(stream);
}

} // namespace xml

#endif // XML_NODE_HPP