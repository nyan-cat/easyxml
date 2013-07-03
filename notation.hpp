#if !defined (XML_NOTATION_HPP)
#define XML_NOTATION_HPP

#include <boost/format.hpp>
#include "node.hpp"

namespace xml
{

template <typename T>
class basic_notation : public basic_node<T>
{
public:

    typedef typename basic_node::string_type string_type;
    typedef typename basic_node::ostream_type ostream_type;
    typedef std::shared_ptr<basic_notation> pointer_type;
    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const notation;
        static format_type const notation_public;
        static format_type const notation_system;
    };

    basic_notation(string_type const& n, string_type const& p = string_type(), string_type const& s = string_type())
    : basic_node(n, string_type())
    , m_public(p)
    , m_system(s)
    {
    }

    virtual typename basic_node::pointer_type copy() const
    {
        return std::make_shared<basic_notation>(*this);
    }

    virtual ostream_type& serialize(ostream_type& stream) const
    {
        if(!m_public.empty() && !m_system.empty())
        {
            return stream << format_type(format::notation) % name() % m_public % m_system;
        }
        else if(!m_public.empty())
        {
            return stream << format_type(format::notation_public) % name() % m_public;
        }
        else if(!m_system.empty())
        {
            return stream << format_type(format::notation_system) % name() % m_system;
        }
        else
        {
            return stream;
        }
    }

private:

    string_type m_public;
    string_type m_system;
};

basic_notation<char>   ::format_type const basic_notation<char>   ::format::notation = boost::format ( "<!NOTATION %1% PUBLIC \"%2%\" \"%3%\">");
basic_notation<wchar_t>::format_type const basic_notation<wchar_t>::format::notation = boost::wformat(L"<!NOTATION %1% PUBLIC \"%2%\" \"%3%\">");

basic_notation<char>   ::format_type const basic_notation<char>   ::format::notation_public = boost::format ( "<!NOTATION %1% PUBLIC \"%2%\">");
basic_notation<wchar_t>::format_type const basic_notation<wchar_t>::format::notation_public = boost::wformat(L"<!NOTATION %1% PUBLIC \"%2%\">");

basic_notation<char>   ::format_type const basic_notation<char>   ::format::notation_system = boost::format ( "<!NOTATION %1% SYSTEM \"%2%\">");
basic_notation<wchar_t>::format_type const basic_notation<wchar_t>::format::notation_system = boost::wformat(L"<!NOTATION %1% SYSTEM \"%2%\">");

} // namespace xml

#endif // XML_NOTATION_HPP