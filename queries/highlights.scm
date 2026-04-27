(comment) @comment

(string) @string
(integer) @number
(float) @number
(boolean) @boolean
(none) @constant.builtin

(identifier) @variable

(member_expression
  property: (identifier) @property)

(call_expression
  function: (identifier) @function)

(filter_expression
  name: (identifier) @function.builtin)

(test_expression
  name: (identifier) @function.builtin)

(keyword_argument
  key: (identifier) @property)

(pair
  key: (identifier) @property)

["{{" "{{-" "{{~" "}}" "-}}" "~}}"
 "{%" "{%-" "{%~" "%}" "-%}" "~%}"
 "{#" "{#-" "{#~" "#}" "-#}" "~#}"] @punctuation.special

["(" ")" "[" "]" "{" "}"] @punctuation.bracket

["," "." "|" "~"] @punctuation.delimiter

["+" "-" "*" "/" "//" "%" "**"
 "==" "!=" "<" ">" "<=" ">=" "===" "!=="
 "??" "?." "?" ":"
 "b-and" "b-or" "b-xor"] @operator

["if" "elif" "elseif" "else" "endif"
 "for" "in" "endfor" "recursive"
 "block" "endblock" "extends"
 "macro" "endmacro" "call" "endcall"
 "filter" "endfilter" "raw" "endraw"
 "set" "endset" "with" "endwith"
 "include" "import" "from" "as"
 "autoescape" "endautoescape"
 "do" "is" "not" "and" "or"
 "ignore" "missing" "scoped"
 "verbatim" "endverbatim"
 "context" "without"] @keyword
