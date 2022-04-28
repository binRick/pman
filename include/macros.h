
#define LIST_QTY(LIST)    {                  \
    ((sizeof(LIST) / sizeof((LIST)[0])) - 1) \
}

#define TEMPLATES_QTY    ((sizeof(__embedded_table__) / sizeof((__embedded_table__)[0])) - 1)
