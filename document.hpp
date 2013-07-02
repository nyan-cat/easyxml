#if !defined (XML_DOCUMENT_HPP)
#define XML_DOCUMENT_HPP

#include "element.hpp"
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
    typedef basic_element<char_type> element_type;
    typedef basic_text<char_type> text_type;
    typedef typename element_type::pointer_type element_ptr;
    typedef typename text_type::pointer_type text_ptr;

    basic_document(string_type const& v, string_type const& e)
    : m_version(v)
    , m_encoding(e)
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

    element_ptr element(string_type const& name, string_type const& value = string_type()) const
    {
        return std::make_shared<element_type>(name, value);
    }

    text_ptr text(string_type const& t) const
    {
        return std::make_shared<text_type>(t);
    }

    node_ptr root() const
    {
        return m_root;
    }

    void root(node_ptr r)
    {
        m_root = r;
    }

private:

    string_type m_version;
    string_type m_encoding;
    node_ptr m_root;
};

template <typename T>
std::basic_ostream<T>& operator << (std::basic_ostream<T>& stream, basic_document<T> const& doc)
{
    return stream << *doc.root();
}

} // namespace xml

#endif // XML_DOCUMENT_HPP