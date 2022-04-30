name={{ name }}
name len={{ name|length }}

{% if name|length < 9 %}short name{% else %}
long name
{% endif %}

