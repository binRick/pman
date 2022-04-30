jq <clib.json | jq -M '.dependencies' | cut -d'"' -f2 | grep '^[a-z]' | xargs -I % echo clib i % -c | bash
