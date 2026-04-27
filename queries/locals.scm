(for_statement
  variable: (identifier) @local.definition)

(for_statement
  variable: (identifier_list
    (identifier) @local.definition))

(set_statement
  variable: (identifier) @local.definition)

(set_statement
  variable: (identifier_list
    (identifier) @local.definition))

(macro_statement
  name: (identifier) @local.definition)

(block_statement
  name: (identifier) @local.definition)

(import_statement
  alias: (identifier) @local.definition)

(identifier) @local.reference
