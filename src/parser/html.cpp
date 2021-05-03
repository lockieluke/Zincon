#include <iostream>
#include <lexbor/html/parser.h>
#include <lexbor/dom/interfaces/element.h>

#include "html.h"

void parser_html()
{
    lxb_status_t status;
    const lxb_char_t *tag_name;
    lxb_html_document *document;

    static const lxb_char_t html[] = "<div>Work fine!</div>";
    size_t html_len = sizeof(html) - 1;

    document = lxb_html_document_create();
    if (document == NULL)
    {
        exit(EXIT_FAILURE);
    }

    status = lxb_html_document_parse(document, html, html_len);
    if (status != LXB_STATUS_OK)
    {
        exit(EXIT_FAILURE);
    }

    tag_name = lxb_dom_element_qualified_name(lxb_dom_interface_element(document->body),
                                              NULL);

    std::cout << "Tag name: " << tag_name << std::endl;

    lxb_html_document_destroy(document);
}