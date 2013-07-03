#if !defined (XML_DOCUMENT_HPP)
#define XML_DOCUMENT_HPP

#include <boost/format.hpp>
#include "cdata.hpp"
#include "comment.hpp"
#include "element.hpp"
#include "notation.hpp"
#include "processing_instruction.hpp"
#include "text.hpp"

namespace xml
{

template <typename T>
class basic_document
{
public:

    typedef basic_node<T> node_type;
    typedef typename node_type::pointer_type node_ptr;
    typedef typename node_type::char_type char_type;
    typedef typename node_type::string_type string_type;

    typedef basic_cdata<char_type> cdata_type;
    typedef basic_comment<char_type> comment_type;
    typedef basic_element<char_type> element_type;
    typedef basic_notation<char_type> notation_type;
    typedef basic_processing_instruction<char_type> processing_instruction_type;
    typedef basic_text<char_type> text_type;

    typedef typename cdata_type::pointer_type cdata_ptr;
    typedef typename comment_type::pointer_type comment_ptr;
    typedef typename element_type::pointer_type element_ptr;
    typedef typename notation_type::pointer_type notation_ptr;
    typedef typename processing_instruction_type::pointer_type processing_instruction_ptr;
    typedef typename text_type::pointer_type text_ptr;

    typedef boost::basic_format<char_type> format_type;

    struct format
    {
        static format_type const version;
    };

    basic_document(string_type const& v, string_type const& e)
    : m_version(v)
    , m_encoding(e)
    , m_root(std::make_shared<node_type>(string_type(), string_type()))
    {
    }

    string_type const& version() const
    {
        return m_version;
    }

    string_type const& encoding() const
    {
        return m_encoding;
    }

    cdata_ptr cdata(string_type const& value) const
    {
        return std::make_shared<cdata_type>(value);
    }

    comment_ptr comment(string_type const& value) const
    {
        return std::make_shared<comment_type>(value);
    }

    element_ptr element(string_type const& name, string_type const& value = string_type()) const
    {
        return std::make_shared<element_type>(name, value);
    }

    notation_ptr notation(string_type const& n, string_type const& p, string_type const& s) const
    {
        return std::make_shared<notation_type>(n, p, s);
    }

    processing_instruction_ptr processing_instruction(string_type const& n, string_type const& v) const
    {
        return std::make_shared<processing_instruction_type>(n, v);
    }

    text_ptr text(string_type const& t) const
    {
        return std::make_shared<text_type>(t);
    }

    node_ptr root() const
    {
        return m_root;
    }

    typename node_type::set query(string_type const& expression)
    {
        return typename node_type::set(); // TODO: implement XPath-request ^_^
    }

private:

    string_type m_version;
    string_type m_encoding;
    node_ptr m_root;
};

basic_document<char>   ::format_type const basic_document<char>   ::format::version = boost::format ( "<?xml version=\"%1%\" encoding=\"%2%\"?>");
basic_document<wchar_t>::format_type const basic_document<wchar_t>::format::version = boost::wformat(L"<?xml version=\"%1%\" encoding=\"%2%\"?>");

template <typename T>
std::basic_ostream<T>& operator << (std::basic_ostream<T>& stream, basic_document<T> const& doc)
{
    return stream << basic_document<T>::format_type(basic_document<T>::format::version) % doc.version() % doc.encoding() << *doc.root();
}

typedef basic_document<char> document;
typedef basic_document<wchar_t> wdocument;

} // namespace xml

#endif // XML_DOCUMENT_HPP